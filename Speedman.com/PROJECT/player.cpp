//---------------------------
//Author:�O��q��
//���f��(player.cpp)
//---------------------------
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"
#include "model.h"
#include "camera.h"
#include "fade.h"
#include "shadow.h"
#include "camerapanel.h"
#include "gamepad.h"
#include "game.h"
#include "select_ui.h"
#include "veceffect3d.h"
#include "straight3d.h"
#include "effect_ui.h"

#include "score.h"
#include "sound.h"
#include "select_ui.h"
//=============================================================================
//�ÓI
//=============================================================================
int CPlayer::m_nControl = 0;
int CPlayer::m_nLife = 0;
//=============================================================================
//�}�N��
//=============================================================================
#define RAND_COLOR (int(rand()%255) + 30)	//�F�����_��
#define RAND_MOVE ((int(rand() % 3) + 1 )- (int (rand()%3) + 1))	//�ړ��l�����_��
#define RAND_MOVE_2 ((int(rand() % 3) + 1 ))	//�ړ��l�����_��

CPlayer::CPlayer(int nPriority) : CScene3D::CScene3D(nPriority)
{

}

CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	//�v���C���[�̃��f���ȂǓǂݍ���
	Load(aFileName);

	//�ݒ�
	SetPos(pos);
	SetRot(rot);
	m_rotDesh = rot;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = pos;
	m_RestartPos = pos;
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();
	m_pMouse = CManager::GetMouse();
	m_pCamera = CManager::GetRenderer()->GetCamera();
	m_pCamera->ResetRot();
	m_bSlack = false;
	m_bSlackMove = false;
	m_bJump = true;
	m_bLandObject = false;
	D3DXVECTOR3 size;
	size.x = GetRadius();
	size.y = 0.0f;
	size.z = GetRadius();
	m_pShadow = CShadow::Create(size, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));
	MotionChange(MOTIONTYPE_RETURN);
	m_nControl = 0;
	m_bLanding = true;
	m_nLife = MAX_LIFE;

	if (m_pGamePad != NULL)
	{
		//�Q�[���p�b�h��UI
		CSelectUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 35, 0, CSelectUI::SELECT_UI_CONTROL);
		CSelectUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 36, 1, CSelectUI::SELECT_UI_CONTROL);
	}
	else if (m_pKeyboard != NULL)
	{
		//�L�[�{�[�h��UI
		CSelectUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 37, 0, CSelectUI::SELECT_UI_CONTROL);
		CSelectUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 38, 1, CSelectUI::SELECT_UI_CONTROL);
	}
	return S_OK;
}

//�I������
void CPlayer::Uninit()
{
	if (m_pCamera != NULL)
	{
		m_pCamera = NULL;
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	int nCnt;
	for (nCnt = 0; nCnt < 32; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt] = NULL;
		}
	}
	if (m_pMouse != NULL)
	{
		m_pMouse = NULL;
	}
	if (m_pShadow != NULL)
	{
		m_pShadow->SetDeath(true);
		m_pShadow = NULL;
	}
	CScene3D::Uninit();
}

//�X�V����
void CPlayer::Update()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	pos = GetPos();
	posOld = pos;
	bool bRun = false;
	bool bJump;

	//���n���ĂȂ�
	if (m_bJump == false && m_bLandObject == false)
	{
		bJump = false;
	}
	//���n���Ă�ꍇ�A�W�����v�\
	else
	{
		bJump = true;
		m_bJump = true;
	}

	bool bGameClear = CManager::GetGameClear();
	bool bCountDown = CGame::GetCountFlag();

	//���̕��@�ł���Pause�����v���o���܂���ł����A���܂�
	bool Pause = CManager::GetPause();

	//�N���A���ĂȂ��A�J�E���g�_�E����
	if (bGameClear == false && bCountDown == true)
	{
		//�|�[�Y���ĂȂ�
		if (Pause == false)
		{
			//�Q�[���p�b�h�q�����Ă�
			if (m_pGamePad != NULL)
			{
				//���ʂɈړ���
				if (m_bSlackMove == false)
				{
					//���X�e�B�b�N�ňړ�
					if (m_pGamePad->LeftStickX() != 0.0f || m_pGamePad->LeftStickY() != 0.0f)
					{
						Move(atan2f(m_pGamePad->LeftStickX(), -m_pGamePad->LeftStickY()) / D3DX_PI);
						bRun = true;
					}
					else
					{
						//�~�܂�
						Stop();
					}

					//�ړ����A�W�����v�\�A���[�V����������ȊO�̏ꍇ�A���郂�[�V�����ɂ���
					if (bRun == true && m_bJump == true && m_motionType != MOTIONTYPE_RUN)
					{
						MotionChange(MOTIONTYPE_RUN);
					}

					//�ړ����ĂȂ��A���郂�[�V�����̏ꍇ�A���^�[�����[�V����
					if (bRun == false && m_motionType == MOTIONTYPE_RUN)
					{
						MotionChange(MOTIONTYPE_RETURN);
					}

					//A�����A���n���Ă�
					if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_bJump == true)
					{
						//���[�v�͂ރt���O�������Ă�
						if (m_bSlack == true)
						{
							//���[�v�͂߂�
							if (CatchSlackline(&pos) == true)
							{
								//���[�v�͂�ňړ����ɂ���
								m_bLanding = false;
								m_bSlackMove = true;
								CSound::Play(CSound::SOUND_LABEL_GRAB);
								CSound::ControlVoice(CSound::SOUND_LABEL_GRAB, 3);

							}
							//�͂߂Ȃ�
							else
							{
								//�W�����v����
								m_move.y = m_fJump;
								m_bJump = false;
								m_bLanding = false;
								MotionChange(MOTIONTYPE_JUMP);
								CSound::Play(CSound::SOUND_LABEL_JUMP);
								CSound::ControlVoice(CSound::SOUND_LABEL_JUMP, 2);

							}
						}
						//���[�v�͂ރt���O�������ĂȂ�
						else
						{
							//�W�����v����
							m_move.y = m_fJump;
							m_bJump = false;
							m_bLanding = false;
							CSound::Play(CSound::SOUND_LABEL_JUMP);
							CSound::ControlVoice(CSound::SOUND_LABEL_JUMP, 2);
							MotionChange(MOTIONTYPE_JUMP);
						}
					}

					//���n���ĂȂ�
					if (m_bJump == false)
					{
						m_move.y -= m_fGravity;
					}

					//�I�u�W�F�N�g�ɒ��n���Ă�
					if (m_bLandObject == true)
					{
						//�W�����v�\
						m_bJump = true;
					}

					//�W�����v�\�����O�̃t���[���ł͋󒆂ɂ���
					if (m_bJump == true && bJump == false)
					{
						//���n���[�V����
						MotionChange(MOTIONTYPE_LANDING);
					}
				}
				//���[�v�͂�ňړ���
				else
				{
					//��ɓ|��
					if (m_pGamePad->LeftStickY() < 0.0f)
					{
						//�i��
						SlackMove(m_fRot - D3DX_PI);
						m_rotDesh.y = m_fRot;
						bRun = true;
					}
					//���ɓ|��
					else if (m_pGamePad->LeftStickY() > 0.0f)
					{
						//�߂�
						SlackMove(m_fRot);
						m_rotDesh.y = m_fRot - D3DX_PI;
						bRun = true;
					}
					else
					{
						//�~�܂�
						Stop();
					}

					//A����
					if (m_pGamePad->GetButton(CGamePad::DIP_A) == true)
					{
						//���^�[�����[�V�����A���ʂɈړ��J�n
						MotionChange(MOTIONTYPE_RETURN);
						m_bSlackMove = false;
					}

					//�ړ����Ă邩���[�v�͂񂾈ړ��ȊO�̃��[�V����
					if (bRun == true && m_motionType != MOTIONTYPE_ZIPMOVE)
					{
						//���[�v�͂񂾈ړ����[�V����
						MotionChange(MOTIONTYPE_ZIPMOVE);
					}

					//�ړ����ĂȂ������[�v�͂񂾈ړ��̃��[�V����
					if (bRun == false && m_motionType == MOTIONTYPE_ZIPMOVE)
					{
						//���[�v�͂񂾃��^�[�����[�V����
						MotionChange(MOTIONTYPE_ZIPRETURN);
					}
				}

				//�E�X�e�B�b�N�X����ƃJ������]
				if (m_pGamePad->RightStickX() != 0.0f)
				{
					//����]
					m_pCamera->AddRotY(m_pGamePad->RightStickX() * 0.03f);
				}
				if (m_pGamePad->RightStickY() != 0.0f)
				{
					//�c��]
					m_pCamera->AddRotX(m_pGamePad->RightStickY() * 0.03f);
				}
			}
			//�Q�[���p�b�h�͌q�����ĂȂ����A�L�[�{�[�h���q�����Ă�
			else if (m_pKeyboard != NULL)
			{
				//�ʏ�ړ�
				if (m_bSlackMove == false)
				{
					//���WASD�ɂ��ړ�
					if (m_pKeyboard->GetPress(DIK_LEFT) == true || m_pKeyboard->GetPress(DIK_A) == true)
					{
						if (m_pKeyboard->GetPress(DIK_DOWN) == true || m_pKeyboard->GetPress(DIK_S) == true)
						{
							//����
							Move(-0.75f);
						}
						else if (m_pKeyboard->GetPress(DIK_UP) == true || m_pKeyboard->GetPress(DIK_W) == true)
						{
							//����
							Move(-0.25f);
						}
						else
						{
							//��
							Move(-0.5f);
						}
						bRun = true;
					}
					else if (m_pKeyboard->GetPress(DIK_RIGHT) == true || m_pKeyboard->GetPress(DIK_D) == true)
					{
						if (m_pKeyboard->GetPress(DIK_DOWN) == true || m_pKeyboard->GetPress(DIK_S) == true)
						{
							//�E��
							Move(0.75f);
						}
						else if (m_pKeyboard->GetPress(DIK_UP) == true || m_pKeyboard->GetPress(DIK_W) == true)
						{
							//�E��
							Move(0.25f);
						}
						else
						{
							//�E
							Move(0.5f);
						}
						bRun = true;
					}
					else if (m_pKeyboard->GetPress(DIK_UP) == true || m_pKeyboard->GetPress(DIK_W) == true)
					{
						//��
						Move(0.0f);
						bRun = true;
					}
					else if (m_pKeyboard->GetPress(DIK_DOWN) == true || m_pKeyboard->GetPress(DIK_S) == true)
					{
						//��
						Move(1.0f);
						bRun = true;
					}
					else
					{
						//�~�܂�
						Stop();
						bRun = false;
					}

					//�ړ����A���n���Ă�A���[�V����������ȊO
					if (bRun == true && m_bJump == true && m_motionType != MOTIONTYPE_RUN)
					{
						//���郂�[�V����
						MotionChange(MOTIONTYPE_RUN);
					}

					//�ړ����ĂȂ��A���郂�[�V����
					if (bRun == false && m_motionType == MOTIONTYPE_RUN)
					{
						//���^�[�����[�V����
						MotionChange(MOTIONTYPE_RETURN);
					}

					//�X�y�[�X�������A���n�ς�
					if (m_pKeyboard->GetKey(DIK_SPACE) == true && m_bJump == true)
					{
						//���[�v�ɒ͂߂�
						if (m_bSlack == true)
						{
							//���[�v�͂�
							if (CatchSlackline(&pos) == true)
							{
								m_bLanding = false;
								m_bSlackMove = true;
								CSound::Play(CSound::SOUND_LABEL_GRAB);
								CSound::ControlVoice(CSound::SOUND_LABEL_GRAB, 3);
							}
							//���[�v�͂߂Ȃ�
							else
							{
								//�W�����v
								m_move.y = m_fJump;
								m_bJump = false;
								m_bLanding = false;
								MotionChange(MOTIONTYPE_JUMP);
								CSound::Play(CSound::SOUND_LABEL_JUMP);
								CSound::ControlVoice(CSound::SOUND_LABEL_JUMP, 2);
							}
						}
						//���[�v�͂߂Ȃ�
						else
						{
							//�W�����v
							m_move.y = m_fJump;
							m_bJump = false;
							m_bLanding = false;

							CSound::Play(CSound::SOUND_LABEL_JUMP);
							CSound::ControlVoice(CSound::SOUND_LABEL_JUMP, 2);

							MotionChange(MOTIONTYPE_JUMP);
						}
					}

					//���n���ĂȂ�
					if (m_bJump == false)
					{
						m_move.y -= m_fGravity;
					}

					//�I�u�W�F�N�g�ɏ���Ă�
					if (m_bLandObject == true)
					{
						//���n���Ă�
						m_bJump = true;
					}
				}
				//���[�v�͂�ł�
				else
				{
					//��
					if (m_pKeyboard->GetPress(DIK_UP) == true || m_pKeyboard->GetPress(DIK_W) == true)
					{
						//�i��
						SlackMove(m_fRot - D3DX_PI);
						m_rotDesh.y = m_fRot;
						bRun = true;
					}
					//��
					else if (m_pKeyboard->GetPress(DIK_DOWN) == true || m_pKeyboard->GetPress(DIK_S) == true)
					{
						//�߂�
						SlackMove(m_fRot);
						m_rotDesh.y = m_fRot - D3DX_PI;
						bRun = true;
					}
					else
					{
						//�~�܂�
						Stop();
					}

					//�X�y�[�X
					if (m_pKeyboard->GetKey(DIK_SPACE) == true)
					{
						//���^�[�����[�V�����A���ʂɈړ��J�n
						MotionChange(MOTIONTYPE_RETURN);
						m_bSlackMove = false;
					}

					//�ړ����Ă邩���[�v�͂񂾈ړ��ȊO�̃��[�V����
					if (bRun == true && m_motionType != MOTIONTYPE_ZIPMOVE)
					{
						//���[�v�͂񂾈ړ����[�V����
						MotionChange(MOTIONTYPE_ZIPMOVE);
					}

					//�ړ����ĂȂ������[�v�͂񂾈ړ��̃��[�V����
					if (bRun == false && m_motionType == MOTIONTYPE_ZIPMOVE)
					{
						//���[�v�͂񂾃��^�[�����[�V����
						MotionChange(MOTIONTYPE_ZIPRETURN);
					}
				}

				//�}�E�X�q�����Ă�
				if (m_pMouse != NULL)
				{
					//�������ƃJ��������
					m_pCamera->AddRotY(m_pMouse->MouseX() * 0.003f);
					m_pCamera->AddRotX(m_pMouse->MouseY() * 0.003f);
				}
			}
			pos += m_move;

			//�l�X�ȕ��Ƃ̓����蔻��
			CollisionObject(&pos, posOld);
			m_bJump = Land(&pos, posOld);
			Trampoline(&pos, posOld);
			CameraWarp(pos);
			m_bSlack = Slackline(&pos);

			//�󒆂ɂ���ꍇ�A�^���ɂ�����̂�T��(�e�̏���)
			if (m_bJump == false)
			{
				UnderSearch(pos);
			}
		}
	}

	//�J�����⎩���A�e�̈ړ�
	m_pCamera->SetPosV(D3DXVECTOR3(pos.x, pos.y + 140.0f, pos.z - 300.0f));
	m_pCamera->SetPosR(D3DXVECTOR3(pos.x, pos.y + m_fHeight, pos.z));
	SetPos(pos);
	m_pShadow->Move(pos.y);

	//�S�[���Ƃ̓����蔻��
	Goal(pos);

	//�����p�̃��X�|�[��
	if (pos.y < -300.0f)
	{
		//���C�t���炷
		m_nLife--;
		if (m_nLife < 0)
		{
			m_nLife = 0;
		}
		//�܂����C�t����
		else if(m_nLife >= 1)
		{
			//���X�|�[��
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			SetPos(m_RestartPos);
			MotionChange(MOTIONTYPE_RETURN);
			CSound::Play(CSound::SOUND_LABEL_FALL);
		}
	}

	//�����̐؂�ւ�
	if (m_bSlackMove == true || m_bSlack == true)
	{
		m_nControl = 1;
	}
	else
	{
		m_nControl = 0;
	}

	////�`�[�g����
	//if (m_pKeyboard != NULL)
	//{
	//	//���X�|�[���n�_�ɖ߂�
	//	if (m_pKeyboard->GetKey(DIK_RETURN) == true)
	//	{
	//		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		SetPos(m_RestartPos);
	//	}
	//	//���X�|�[���n�_�̐ݒ�
	//	if (m_pKeyboard->GetKey(DIK_LSHIFT) == true)
	//	{
	//		m_RestartPos = pos;
	//	}
	//}

	//�����̕����֘A
	D3DXVECTOR3 rot = GetRot();

	//rot������Ȃ��悤�ɂ���
	if (m_rotDesh.y >= D3DX_PI)
	{
		m_rotDesh.y -= D3DX_PI * 2;
	}
	if (m_rotDesh.y < -D3DX_PI)
	{
		m_rotDesh.y += D3DX_PI * 2;
	}
	if (rot.y >= D3DX_PI)
	{
		rot.y -= D3DX_PI * 2;
	}
	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	//�����̕����ƖړI�̕�������������Ȃ�
	if (rot.y != m_rotDesh.y)
	{
		if (m_rotDesh.y - rot.y < -D3DX_PI)
		{
			rot.y += (m_rotDesh.y - rot.y + D3DX_PI * 2) * 0.14f;
		}
		else if (m_rotDesh.y - rot.y > D3DX_PI)
		{
			rot.y += (m_rotDesh.y - rot.y - D3DX_PI * 2) * 0.14f;
		}
		else
		{
			rot.y += (m_rotDesh.y - rot.y) * 0.14f;
		}
	}
	if (Pause == false)
	{
		//���[�V�����Arot�ݒ�
		Motion();
		SetRot(rot);
	}
}

//�`�揈��
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxPlayer, mtxRot, mtxTrans;
	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����
	//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxPlayer);
	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxRot);
	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);
	//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);
	SetMatrix(mtxPlayer);
	int nCntModel;
	for (nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_pModel[nCntModel]->Draw();
	}
}

//�L�����ǂݍ���
void CPlayer::Load(const char *aFileName)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	int nParent;
	CModel *paModel[32];

	int nCntParts = 0;
	//int nCntModelParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	char aFile[256];
	float fRadius;
	int nLoop = 0;

	bool bChara = false;
	bool bParts = false;
	bool bMotion = false;
	bool bKey = false;
	bool bKeySet = false;
	int nIndex;
	//int nLoop;

	FILE *pFile;
	pFile = fopen(aFileName, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f���t�@�C���ǂݍ���
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				paModel[nCntParts] = CModel::Create(&aFile[0]);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET��
			{
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fJump);
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0) //�d��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fGravity);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRadius);
					SetRadius(fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fHeight);
				}
				if (strcmp(&aFile[0], "PARTSSET") == 0)	//�p�[�c�Z�b�g
				{
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)	//�p�[�c�Z�b�g�I���
				{
					bParts = false;
					nCntParts++;
				}
				if (bParts == true) //PARTSSET��
				{
					//if (strcmp(&aFile[0], "MOVEPARTS") == 0) //���ꂪ������g_player��pos�������i����Ȃ������j
					//{
					//	g_player.nMoveParts = nCntParts;
					//}
					if (strcmp(&aFile[0], "INDEX") == 0) //���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						m_pModel[nCntParts] = paModel[nIndex];
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);
						if (nParent != -1)
						{
							m_pModel[nCntParts]->SetParent(m_pModel[nParent]);
						}
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntParts]->SetOriPos(pos);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntParts]->SetOriRot(rot);
					}
				}
			}
			if (bMotion == true) //MOTIONSET��
			{
				if (strcmp(&aFile[0], "LOOP") == 0) //���̃��[�V���������[�v���邩(0���Ƃ��Ȃ��B����ȊO���Ƃ���)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
					if (nLoop == 0)
					{
						m_aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNumKey);
				}
				//if (strcmp(&aFile[0], "NON_OPE") == 0) //����s�\����
				//{
				//	fscanf(pFile, "%s", &aFile[0]);
				//	fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNonOpe);
				//}
				if (strcmp(&aFile[0], "KEYSET") == 0)	//�L�[�ݒ�J�n
				{
					bKeySet = true;
					nCntParts = 0;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)	//�L�[�ݒ�I��
				{
					bKeySet = false;
					nCntKey++;
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					//if (strcmp(&aFile[0], "MOVE") == 0) //�ړ���
					//{
					//	fscanf(pFile, "%s", &aFile[0]);
					//	fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
					//}
					if (strcmp(&aFile[0], "KEY") == 0)	//�L�[���Ƃ�pos��rot
					{
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)	//�L�[���Ƃ�pos��rot
					{
						bKey = false;
						nCntParts++;
					}
					if (bKey == true) //KEY��
					{
						if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
						}
					}
				}
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)	//�L�����ݒ�J�n
			{
				bChara = true;
				nCntParts = 0;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)	//�L�����ݒ�I��
			{
				bChara = false;
			}
			if (strcmp(&aFile[0], "MOTIONSET") == 0)	//���[�V�����ݒ�J�n
			{
				bMotion = true;
				nCntKey = 0;
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)	//���[�V�����ݒ�I��
			{
				bMotion = false;
				nCntMotion++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I����1��
			{
				break;
			}
		}
		fclose(pFile);
	}

	//�uMOTIONTYPE_RETURN�v�́A�j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	m_aMotionInfo[MOTIONTYPE_RETURN].bLoop = false;
	m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].nFrame = 10;
	m_aMotionInfo[MOTIONTYPE_RETURN].nNumKey = 1;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosX = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosY = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotX = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotY = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
	}

	//�uMOTIONTYPE_ZIPRETURN�v�́A���[�v�͂�ł�Ԃ̃j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	m_aMotionInfo[MOTIONTYPE_ZIPRETURN].bLoop = false;
	m_aMotionInfo[MOTIONTYPE_ZIPRETURN].aKeyInfo[0].nFrame = 10;
	m_aMotionInfo[MOTIONTYPE_ZIPRETURN].nNumKey = 1;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		m_aMotionInfo[MOTIONTYPE_ZIPRETURN].aKeyInfo[0].aKey[nCntParts].fPosX = m_aMotionInfo[MOTIONTYPE_ZIPNUETRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		m_aMotionInfo[MOTIONTYPE_ZIPRETURN].aKeyInfo[0].aKey[nCntParts].fPosY = m_aMotionInfo[MOTIONTYPE_ZIPNUETRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		m_aMotionInfo[MOTIONTYPE_ZIPRETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = m_aMotionInfo[MOTIONTYPE_ZIPNUETRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		m_aMotionInfo[MOTIONTYPE_ZIPRETURN].aKeyInfo[0].aKey[nCntParts].fRotX = m_aMotionInfo[MOTIONTYPE_ZIPNUETRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		m_aMotionInfo[MOTIONTYPE_ZIPRETURN].aKeyInfo[0].aKey[nCntParts].fRotY = m_aMotionInfo[MOTIONTYPE_ZIPNUETRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		m_aMotionInfo[MOTIONTYPE_ZIPRETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = m_aMotionInfo[MOTIONTYPE_ZIPNUETRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
	}
}

//�ړ�
void CPlayer::Move(float fRotY)
{
	m_move.x += (sinf(m_pCamera->GetRotY() + D3DX_PI * fRotY) * m_fMove - m_move.x) * 0.1f;
	m_move.z += (cosf(m_pCamera->GetRotY() + D3DX_PI * fRotY) * m_fMove - m_move.z) * 0.1f;
	m_rotDesh.y = m_pCamera->GetRotY() + D3DX_PI * fRotY + D3DX_PI;
}

//���[�v��͂�ł�Ԃ̈ړ�
void CPlayer::SlackMove(float fRotY)
{
	m_move.x += (sinf(fRotY) * m_fMove * 0.2f - m_move.x) * 0.05f;
	m_move.z += (cosf(fRotY) * m_fMove * 0.2f - m_move.z) * 0.05f;
}

//�~�܂�
void CPlayer::Stop()
{
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;
}

//�S�[���ɐG�ꂽ��
void CPlayer::Goal(D3DXVECTOR3 PlayerPos)
{
	CScene *pScene;
	pScene = GetScene(4);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�S�[���̂�
		if (pScene->GetObjType() == CScene::OBJCTTYPE_GOAL)
		{
			//pos�Ȃǂ��擾�A�����v�Z
			D3DXVECTOR3 pos = pScene->GetPos();
			float fRadius = pScene->GetRadius();
			float fLengthX = powf(GetPos().x - pos.x, 2);
			float fLengthZ = powf(GetPos().z - pos.z, 2);
			float fDistance = sqrtf(fLengthX + fLengthZ);

			//���������݂��̔��a���Z��
			if (fDistance <= fRadius + GetRadius())
			{
				//���g�̓����S�[��������
				if (PlayerPos.y + m_fHeight >= pos.y)
				{
					//�`���[�g���A��
					if (CManager::GetMode() == CManager::MODE_TUTORIAL)
					{
						//�Q�[���Ɉڍs
						CFade::SetFade(CManager::MODE_GAME);
						CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
						CScore::SetTime(TIME_LIMIT);
					}
					//�Q�[��
					else if (CManager::GetMode() == CManager::MODE_GAME)
					{
						//�N���A���ĂȂ�(�G�ꂽ�u��)
						bool GameClear = CManager::GetGameClear();
						if (GameClear == false)
						{
							//���X�̐���
							CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 190.0f, 0.0f), 920.0f, 110.0f, 26);
							CManager::SetGameEnd(true);

							CUI::Create(D3DXVECTOR3(640.0f, 280.0f, 0), 300.0f, 50.0f, 28);		//UI

							//�v���C���[�X�R�A
							CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 125.0f, 360.0f, 0), 50, 70, 2, 5, CScore::NUMBER_SCORE);

							//�p�[�e�B�N���o��
							CEffectUI::Create(D3DXVECTOR3(0.0, SCREEN_HEIGHT - 2, 0.0f), 0, 0, 0, CEffectUI::EFFECT_PETAL);
							CManager::SetGameClear(true);
							MotionChange(MOTIONTYPE_NEUTRAL);
							CSound::Play(CSound::SOUND_LABEL_CHEERS);
							CSound::ControlVoice(CSound::SOUND_LABEL_CHEERS, 2);
							CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
							CSound::Play(CSound::SOUND_LABEL_RESULTBGM);
							CSound::ControlVoice(CSound::SOUND_LABEL_RESULTBGM, 1.3f);
						}
					}
				}
			}
			break;
		}
		pScene = pSceneNext;
	}
}

//�J�����p�l���𓥂�
void CPlayer::CameraWarp(D3DXVECTOR3 pos)
{
	CScene *pScene;
	pScene = GetScene(2);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�J�����p�l��
		if (pScene->GetObjType() == CScene::OBJCTTYPE_CAMERAPANEL)
		{
			D3DXVECTOR3 ScenePos = pScene->GetPos();
			D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
			D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
			float fPRadius = GetRadius();

			//�����蔻��
			if (ScenePos.x + VtxMin.x <= pos.x + fPRadius && pos.x - fPRadius <= ScenePos.x + VtxMax.x &&
				ScenePos.z + VtxMin.z <= pos.z + fPRadius && pos.z - fPRadius <= ScenePos.z + VtxMax.z)
			{
				if (pos.y <= ScenePos.y && ScenePos.y <= pos.y + m_fHeight)
				{
					//�J�������w��̌����ɐ؂�ւ��
					m_pCamera->SetPosR(pScene->GetCameraPosR());
					m_pCamera->SetPosV(pScene->GetCameraPosV());
					m_pCamera->SetRot();
				}
			}
		}
		pScene = pSceneNext;
	}
}

//�g�����|����
void CPlayer::Trampoline(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = GetScene(4);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�g�����|����
		if (pScene->GetObjType() == CScene::OBJCTTYPE_TRAMPOLINE)
		{
			D3DXVECTOR3 pos = pScene->GetPos();
			float fRadius = pScene->GetRadius();
			float fLengthX = powf(pPos->x - pos.x, 2);
			float fLengthZ = powf(pPos->z - pos.z, 2);
			float fDistance = sqrtf(fLengthX + fLengthZ);

			//�����蔻��
			if (fDistance <= fRadius + GetRadius())
			{
				if (posOld.y >= pos.y && pos.y >= pPos->y)
				{
					//��W�����v����A�G�t�F�N�g�쐬
					pPos->y = pos.y;
					m_move.y = m_fJump * 1.7f;
					MotionChange(MOTIONTYPE_JUMP);

					CStraight3D::Create(D3DXVECTOR3(pPos->x, pPos->y, pPos->z),
						D3DXVECTOR3(2.0f, 2.0f, 0.0f),
						D3DXVECTOR3(4.0f, 4.0f, 0.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXCOLOR(255, 255, 255, 255),
						D3DXCOLOR(0, 0, 0, 0),
						5, 20);

					for (int nCnt = 0; nCnt < 10; nCnt++)
					{
						CVecEffect3D::Create(D3DXVECTOR3(pPos->x, pPos->y + 20, pPos->z),
							D3DXVECTOR3(5.0f, 5.0f, 0.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(sinf(CIRCLE) * 3, 0.0f, cosf(CIRCLE) * 3),
							D3DXCOLOR(0, 255, 255, 255),
							D3DXCOLOR(0, 0, 0, 0),
							3,
							30);
					}

					//���炷
					CSound::Play(CSound::SOUND_LABEL_JUMPPAD);
					CSound::ControlVoice(CSound::SOUND_LABEL_JUMPPAD,2);
				}
			}
		}
		pScene = pSceneNext;
	}
}

//���[�v�͂߂邩
bool CPlayer::Slackline(D3DXVECTOR3 *pPos)
{
	bool bSlack = false;
	CScene *pScene;
	pScene = GetScene(3);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�X���b�N���C��
		if (pScene->GetObjType() == CScene::OBJCTTYPE_SLACKLINE)
		{
			float fRadius = pScene->GetRadius();
			float fPRadius = GetRadius();
			D3DXVECTOR3 pos = pScene->GetPos();
			D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
			D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
			float fLengthX = pPos->x - pos.x;
			float fLengthY = pPos->y - pos.y;
			//float fLengthYbot = pPos->y + m_fHeight - pos.y;
			float fLengthZ = pPos->z - pos.z;
			fLengthX = powf(fLengthX, 2);
			fLengthY = powf(fLengthY, 2);
			fLengthZ = powf(fLengthZ, 2);
			
			//�\���߂�
			if (fLengthX + fLengthZ <= powf(fPRadius * 1.5f + fRadius, 2))
			{
				if (pPos->y <= pos.y + VtxMax.y && pPos->y + m_fHeight >= pos.y)
				{
					//�t���O�I��
					bSlack = true;
				}
			}

			//�������Ă�
			if (sqrtf(fLengthX + fLengthZ) <= fPRadius + fRadius)
			{
				if (pPos->y <= pos.y + VtxMax.y && pPos->y + m_fHeight >= pos.y)
				{
					//�v���C���[�����̂�����
					float fRotY = atan2f(pPos->x - pos.x, pPos->z - pos.z);
					pPos->x = pos.x + sinf(fRotY) * (fPRadius + fRadius);
					pPos->z = pos.z + cosf(fRotY) * (fPRadius + fRadius);
					
					//���[�v�͂�ňړ�����������A��������
					if (m_bSlackMove == true)
					{
						MotionChange(MOTIONTYPE_RETURN);
						m_bSlackMove = false;
					}
				}
			}
		}
		pScene = pSceneNext;
	}
	return bSlack;
}

bool CPlayer::CatchSlackline(D3DXVECTOR3 *pPos)
{
	CScene *pScene;
	pScene = GetScene(3);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�X���b�N���C��
		if (pScene->GetObjType() == CScene::OBJCTTYPE_SLACKLINE)
		{
			D3DXVECTOR3 pos = pScene->GetPos();
			D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
			D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
			float fRadius = pScene->GetRadius();
			float fPRadius = GetRadius();
			float fRotY;
			int nSlack = pScene->GetSlack();

			//�߂�
			if (pos.x - fRadius <= pPos->x + fPRadius && pPos->x - fPRadius <= pos.x + fRadius &&
				pos.z - fRadius <= pPos->z + fPRadius && pPos->z - fPRadius <= pos.z + fRadius)
			{
				if (pPos->y <= pos.y + VtxMax.y && pPos->y + m_fHeight >= pos.y)
				{
					//���Ɍ���������������
					D3DXVECTOR3 NextPos;
					if (nSlack % 2 == 0)
					{
						NextPos = SearchSlackline(nSlack + 1);
					}
					else
					{
						NextPos = SearchSlackline(nSlack - 1);
					}

					//����̏ꏊ�Ƀ��[�v�A���̕����Ɍ���
					fRotY = atan2f(pos.x - NextPos.x, pos.z - NextPos.z);
					m_rotDesh.y = fRotY;
					SetRot(m_rotDesh);
					m_fRot = fRotY;
					pPos->x = pos.x - sinf(fRotY) * (fRadius + fPRadius + 4.0f);
					pPos->z = pos.z - cosf(fRotY) * (fRadius + fPRadius + 4.0f);
					pPos->y = pos.y + 35.0f;
					m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					MotionChange(MOTIONTYPE_ZIPRETURN);
					return true;
				}
			}
		}
		pScene = pSceneNext;
	}
	return false;
}

//�X���b�N���C������
D3DXVECTOR3 CPlayer::SearchSlackline(int nNumber)
{
	CScene *pScene;
	pScene = GetScene(3);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�X���b�N���C��
		if (pScene->GetObjType() == CScene::OBJCTTYPE_SLACKLINE)
		{
			//�ԍ���v
			if (pScene->GetSlack() == nNumber)
			{
				return pScene->GetPos();
			}
		}
		pScene = pSceneNext;
	}
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//�I�u�W�F�N�g�Ƃ̓����蔻��
void CPlayer::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = GetScene(2);
	bool bLand = false;
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�u���b�N
		if(pScene->GetObjType() == CScene::OBJECTTYPE_BLOCK)
		{
			//�����蔻�肪����
			if (pScene->GetCollision() == CScene::COLLISION_SPHERE)
			{
				D3DXVECTOR3 pos = pScene->GetPos();
				float fRadius = pScene->GetRadius();
				//float fPRadius = GetRadius();
				float fRotY;
				float fLengthX = pPos->x - pos.x;
				float fLengthY = (pPos->y + (m_fHeight / 2)) - pos.y;
				//float fLengthYbot = pPos->y + m_fHeight - pos.y;
				float fLengthZ = pPos->z - pos.z;
				fLengthX = powf(fLengthX, 2);
				fLengthY = powf(fLengthY, 2);
				fLengthZ = powf(fLengthZ, 2);

				//��������
				if (fLengthX + fLengthY + fLengthZ <= powf((m_fHeight / 2) + fRadius, 2)/* || fLengthX + fLengthYbot + fLengthZ <= powf(fPRadius + fRadius, 2)*/)
				{
					//�v���C���[���ړ�������
					fRotY = atan2f(pos.x - pPos->x, pos.z - pPos->z);
					pPos->x = pos.x - sinf(fRotY) * ((m_fHeight / 2) + fRadius);
					pPos->z = pos.z - cosf(fRotY) * ((m_fHeight / 2) + fRadius);
					m_bSlackMove = false;
				}
			}

			//�����蔻�肪���^
			if (pScene->GetCollision() == CScene::COLLISION_SQUARE)
			{
				D3DXVECTOR3 pos = pScene->GetPos();
				D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
				D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
				float fPRadius = GetRadius();

				//XZ�ɓ������Ă�
				if (pos.x + VtxMin.x <= pPos->x + fPRadius && pPos->x - fPRadius <= pos.x + VtxMax.x &&
					pos.z + VtxMin.z <= pPos->z + fPRadius && pPos->z - fPRadius <= pos.z + VtxMax.z)
				{
					//�ォ�瓖����(���n)
					if (posOld.y >= pos.y + VtxMax.y && pPos->y <= pos.y + VtxMax.y)
					{
						pPos->y = pos.y + VtxMax.y;
						m_move.y = 0.0f;
						bLand = true;
						m_pShadow->MoveY(*pPos, 0.0f);

						//���n���ĂȂ�
						if (m_bLanding == false)
						{
							CSound::Play(CSound::SOUND_LABEL_LANDING);
							//���n�p�[�e�B�N��
							for (int nCnt = 0; nCnt < 10; nCnt++)
							{
								CVecEffect3D::Create(D3DXVECTOR3(pPos->x, pPos->y + 10, pPos->z),
									D3DXVECTOR3(3.0f, 3.0f, 0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXVECTOR3(sinf(CIRCLE) * 1, 0.0f, cosf(CIRCLE) * 1),
									D3DXCOLOR(255, 255, 0, 255),
									D3DXCOLOR(0, 0, 0, -10),
									3,
									30);
							}
							MotionChange(MOTIONTYPE_LANDING);
							m_bLanding = true;
						}
					}
					//�����瓖����
					else if (posOld.y + m_fHeight <= pos.y + VtxMin.y && pPos->y + m_fHeight >= pos.y + VtxMin.y)
					{
						pPos->y = pos.y + VtxMin.y - m_fHeight;
						m_move.y = 0.0f;
					}
					//Y���������Ă�
					else if (pos.y + VtxMin.y <= pPos->y + m_fHeight && pPos->y <= pos.y + VtxMax.y)
					{
						bool bIn = false;
						//���ɓ�����
						if (pos.x + VtxMin.x <= pPos->x + fPRadius && posOld.x + fPRadius <= pos.x + VtxMin.x)
						{
							pPos->x = pos.x + VtxMin.x - fPRadius;
							m_bSlackMove = false;
							bIn = true;
						}
						//�E�ɓ�����
						else if (pos.x + VtxMax.x >= pPos->x - fPRadius && posOld.x - fPRadius >= pos.x + VtxMax.x)
						{
							pPos->x = pos.x + VtxMax.x + fPRadius + 0.1f;
							m_bSlackMove = false;
							bIn = true;
						}
						//��O�ɓ�����
						if (pos.z + VtxMin.z <= pPos->z + fPRadius && posOld.z + fPRadius <= pos.z + VtxMin.z)
						{
							pPos->z = pos.z + VtxMin.z - fPRadius;
							m_bSlackMove = false;
							bIn = true;
						}
						//���ɓ�����
						else if (pos.z + VtxMax.z >= pPos->z - fPRadius && posOld.z - fPRadius >= pos.z + VtxMax.z)
						{
							pPos->z = pos.z + VtxMax.z + fPRadius + 0.1f;
							m_bSlackMove = false;
							bIn = true;
						}
						//�������������Ă��Ă���ɓ�����
						if (bIn == false)
						{
							float fMinDistance = 100000.0f;
							float fDistance[4];
							fDistance[0] = pos.x + VtxMax.x - pPos->x;
							fDistance[1] = pos.x + VtxMin.x - pPos->x;
							fDistance[2] = pos.z + VtxMax.z - pPos->z;
							fDistance[3] = pos.z + VtxMin.z - pPos->z;
							int nCnt;
							int nDistance;
							//4�ʂ���̋������v�Z�A��ԒZ����������
							for (nCnt = 0; nCnt < 4; nCnt++)
							{
								if (fabsf(fMinDistance) > fabsf(fDistance[nCnt]))
								{
									fMinDistance = fDistance[nCnt];
									nDistance = nCnt;
								}
							}

							//�����ɂ��A�����o���ʒu��ς���
							switch (nDistance)
							{
							case 0:	//�E
								pPos->x = pos.x + VtxMax.x + fPRadius + 0.1f;
								break;
							case 1:	//��
								pPos->x = pos.x + VtxMin.x - fPRadius;
								break;
							case 2:	//��
								pPos->z = pos.z + VtxMax.z + fPRadius + 0.1f;
								break;
							case 3:	//��O
								pPos->z = pos.z + VtxMin.z - fPRadius;
								break;
							default:
								break;
							}
							m_bSlackMove = false;
						}
					}
				}
			}
		}

		//�`�F�b�N�|�C���g
		if (pScene->GetObjType() == CScene::OBJCTTYPE_CHECKPOINT)
		{
			D3DXVECTOR3 pos = pScene->GetPos();
			float fRadius = pScene->GetRadius();
			float fPRadius = GetRadius();
			float fRotY;
			float fLengthX = pPos->x - pos.x;
			float fLengthY = pPos->y - pos.y;
			//float fLengthYbot = pPos->y + m_fHeight - pos.y;
			float fLengthZ = pPos->z - pos.z;
			fLengthX = powf(fLengthX, 2);
			fLengthY = powf(fLengthY, 2);
			fLengthZ = powf(fLengthZ, 2);

			//���������̋������v�Z
			if (fLengthX + fLengthZ <= powf(fPRadius + fRadius, 2))
			{
				//Y�����ɓ������Ă邩
				if (pos.y <= pPos->y + m_fHeight && pPos->y <= pos.y + fRadius)
				{
					fRotY = atan2f(pos.x - pPos->x, pos.z - pPos->z);
					pPos->x = pos.x - sinf(fRotY) * (fPRadius + fRadius);
					pPos->z = pos.z - cosf(fRotY) * (fPRadius + fRadius);
					m_RestartPos = pos;

					//�`�F�b�N�|�C���g�p�[�e�B�N��
					for (int nCnt = 0; nCnt < 20; nCnt++)
					{
						int nColorR = RAND_COLOR;
						int nColorG = RAND_COLOR;
						int nColorB = RAND_COLOR;

						float r = CIRCLE;
						int Movex = RAND_MOVE_2;
						int Movez = RAND_MOVE_2;
						int Movey = RAND_MOVE_2;

						CVecEffect3D::Create(D3DXVECTOR3(pos.x, pos.y + 10, pos.z),
							D3DXVECTOR3(3.0f, 3.0f, 0.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(sinf(r) * Movex, Movey, cosf(r) * Movez),
							D3DXCOLOR(nColorR, nColorG, nColorB, 255.0f),
							D3DXCOLOR(0, 0, 0, -0),
							3,
							30);
					}

					CSound::Play(CSound::SOUND_LABEL_CHECKPOINT);
					CSound::ControlVoice(CSound::SOUND_LABEL_CHECKPOINT, 2);

					pScene->SetDeath(true);
				}
			}
		}
		pScene = pSceneNext;
	}
	m_bLandObject = bLand;
}

void CPlayer::Motion() //���[�V�����̓���
{
	int nCntParts;
	m_nCntMotion++;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		if (m_nCntMotion == 1) //���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
		{
			/*if (nCntParts != g_player.nMoveParts)
			{*/
			m_aKeyDiff[nCntParts].fPosX = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fPosX - m_pModel[nCntParts]->GetPos().x;
			m_aKeyDiff[nCntParts].fPosY = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fPosY - m_pModel[nCntParts]->GetPos().y;
			m_aKeyDiff[nCntParts].fPosZ = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fPosZ - m_pModel[nCntParts]->GetPos().z;
			//}
			//else
			//{
			//	g_player.KeyMove.fPosX = sinf(D3DX_PI + g_player.rot.y) * g_player.MotionInfo.aKeyInfo[g_player.nKey].fMove;
			//	g_player.KeyMove.fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fPosY;
			//	g_player.KeyMove.fPosZ = cosf(D3DX_PI + g_player.rot.y) * g_player.MotionInfo.aKeyInfo[g_player.nKey].fMove;
			//}

			//�p�x������Ȃ��悤�ɂ���
			m_aKeyDiff[nCntParts].fRotX = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fRotX - m_pModel[nCntParts]->GetRot().x;
			if (m_aKeyDiff[nCntParts].fRotX < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotX += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].fRotX > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotX -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].fRotY = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fRotY - m_pModel[nCntParts]->GetRot().y;
			if (m_aKeyDiff[nCntParts].fRotY < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotY += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].fRotY > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotY -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].fRotZ = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fRotZ - m_pModel[nCntParts]->GetRot().z;
			if (m_aKeyDiff[nCntParts].fRotZ < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotZ += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].fRotZ > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotZ -= D3DX_PI * 2;
			}
		}
		//if (nCntParts != g_player.nMoveParts)
		//{

		//pos�����X�ɑ����Ă���
		D3DXVECTOR3 posOld;
		posOld = m_pModel[nCntParts]->GetPos();
		posOld.x += m_aKeyDiff[nCntParts].fPosX / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.y += m_aKeyDiff[nCntParts].fPosY / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.z += m_aKeyDiff[nCntParts].fPosZ / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetPos(posOld);
		//}
		//else
		//{
		//	if (g_player.KeyMove.fPosX != 0.0f)
		//	{
		//		g_player.move.x = g_player.KeyMove.fPosX;
		//	}
		//	//g_player.pos.y += g_player.KeyMove.fPosY / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
		//	if (g_player.KeyMove.fPosZ != 0.0f)
		//	{
		//		g_player.move.z = g_player.KeyMove.fPosZ;
		//	}
		//}

		//rot�����X�ɑ����Ă���
		D3DXVECTOR3 rotOld;
		rotOld = m_pModel[nCntParts]->GetRot();
		rotOld.x += m_aKeyDiff[nCntParts].fRotX / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.y += m_aKeyDiff[nCntParts].fRotY / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.z += m_aKeyDiff[nCntParts].fRotZ / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetRot(rotOld);
	}

	//���݂̃L�[�̎��Ԃ����̃��[�V�����̃L�[�̎��Ԃƈ�v
	if (m_nCntMotion == m_MotionInfo.aKeyInfo[m_nKey].nFrame)
	{
		//���݂̃L�[�̎��ԃ��Z�b�g�A�L�[���v���X
		m_nCntMotion = 0;
		m_nKey++;

		//�L�[�����݂̃��[�V�����̍ő�L�[�ƈ�v
		if (m_nKey == m_MotionInfo.nNumKey)
		{
			//���[�v���Ȃ�
			if (m_MotionInfo.bLoop == false)
			{
				//���[�v�͂�ňړ�������Ȃ�
				if (m_bSlackMove == false)
				{
					//���^�[�����[�V�����ȊO
					if (m_motionType != MOTIONTYPE_RETURN)
					{
						//���^�[�����[�V����
						MotionChange(MOTIONTYPE_RETURN);
					}
					//���^�[�����[�V������
					else
					{
						//�j���[�g����
						MotionChange(MOTIONTYPE_NEUTRAL);
					}
				}
				//���[�v�͂�ňړ�������Ȃ�
				else
				{
					//���^�[�����[�V�����ȊO
					if (m_motionType != MOTIONTYPE_ZIPRETURN)
					{
						//���^�[�����[�V����
						MotionChange(MOTIONTYPE_ZIPRETURN);
					}
					//���^�[�����[�V������
					else
					{
						//�j���[�g����
						MotionChange(MOTIONTYPE_ZIPNUETRAL);
					}
				}
			}
			m_nKey = 0;
		}
	}
}

//���[�V�����ύX
void CPlayer::MotionChange(MOTIONTYPE motionType)
{
	m_motionType = motionType;
	m_MotionInfo = m_aMotionInfo[motionType];
	m_nCntMotion = 0;
	m_nKey = 0;
}

//�n�ʂƂ̓����蔻��
bool CPlayer::Land(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = GetScene(0);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//��
		if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD)
		{
			D3DXVECTOR3 pos = pScene->GetPos();
			D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
			D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
			
			//XZ�����ɓ������Ă�
			if (pPos->x - GetRadius() <= pos.x + VtxMax.x && pos.x + VtxMin.x <= pPos->x + GetRadius() &&
				pPos->z - GetRadius() <= pos.z + VtxMax.z && pos.z + VtxMin.z <= pPos->z + GetRadius())
			{
				//�v���C���[������ʒu�̒n�ʂ̍����v�Z
				float fRotX = atan2f(VtxMax.y - VtxMin.y, VtxMax.z - VtxMin.z);
				float fFieldY = (pPos->z - (pos.z + VtxMin.z * 0.75f)) * tanf(fRotX) + pos.y + VtxMin.y * 0.75f;
				
				//��L�̌v�Z���ʂƑ�̈�v���Ă���
				if (posOld.y + 3.0f >= fFieldY && fFieldY >= pPos->y - 3.0f)
				{
					//���n������A�e���ړ�������
					m_move.y = 0.0f;
					pPos->y = fFieldY;
					m_pShadow->MoveY(*pPos, -fRotX);

					//���n�����u��
					if (m_bLanding == false)
					{
						CSound::Play(CSound::SOUND_LABEL_LANDING);
						//�W�����v�p�[�e�B�N��
						for (int nCnt = 0; nCnt < 10; nCnt++)
						{
							CVecEffect3D::Create(D3DXVECTOR3(pPos->x, pPos->y + 10, pPos->z),
								D3DXVECTOR3(3.0f, 3.0f, 0.0f),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXVECTOR3(sinf(CIRCLE) * 1, 0.0f, cosf(CIRCLE) * 1),
								D3DXCOLOR(255, 255, 0, 255),
								D3DXCOLOR(0, 0, 0, -10),
								3,
								30);
						}
						MotionChange(MOTIONTYPE_LANDING);
						m_bLanding = true;
					}
					return true;
				}

			}
		}
		pScene = pSceneNext;
	}
	return false;
}

//�^���ɂ���I�u�W�F�N�g�⏰��T��
void CPlayer::UnderSearch(D3DXVECTOR3 pos)
{
	CScene *pScene;
	CScene *pUnderScene = NULL;
	int nCntScene;
	for (nCntScene = 0; nCntScene < 7; nCntScene++)
	{
		pScene = GetScene(nCntScene);
		float fPosY = -10000.0f;
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->GetNext();
			//�����I�u�W�F�N�g
			if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD || pScene->GetObjType() == CScene::OBJECTTYPE_BLOCK)
			{
				D3DXVECTOR3 Scenepos = pScene->GetPos();
				D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
				D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
				//XZ�����ɓ������Ă�
				if (pos.x - GetRadius() < Scenepos.x + VtxMax.x && Scenepos.x + VtxMin.x < pos.x + GetRadius() &&
					pos.z - GetRadius() < Scenepos.z + VtxMax.z && Scenepos.z + VtxMin.z < pos.z + GetRadius())
				{
					//�����̈ʒu�����̂̈�ԉ��̈ʒu��荂���A���݂̉e�̈ʒu���Ⴂ
					if (pos.y >= Scenepos.y + VtxMin.y && fPosY <= Scenepos.y + VtxMin.y)
					{
						//�e�̈ʒu����ւ��A���̂̃|�C���^�擾
						fPosY = Scenepos.y + VtxMin.y;
						pUnderScene = pScene;
					}
				}
			}
			pScene = pSceneNext;
		}
	}

	//�|�C���^��NULL����Ȃ�
	if (pUnderScene != NULL)
	{
		D3DXVECTOR3 Scenepos = pUnderScene->GetPos();
		D3DXVECTOR3 VtxMax = pUnderScene->GetVtxMax();
		D3DXVECTOR3 VtxMin = pUnderScene->GetVtxMin();
		float fRotX;
		float fFieldY;
		//�n�ʂ̏ꍇ
		if (pUnderScene->GetObjType() == CScene::OBJECTTYPE_FIELD)
		{
			//�p�x���v�Z�A���̒n�_�̒n�ʂ̍������v�Z
			fRotX = atan2f(VtxMax.y - VtxMin.y, VtxMax.z - VtxMin.z);
			fFieldY = (pos.z - (Scenepos.z + VtxMin.z * 0.75f)) * tanf(fRotX) + Scenepos.y + VtxMin.y * 0.75f;
			if (pos.y < fFieldY)
			{
				fFieldY = -100000.0f;
			}
		}
		//����ȊO(=�I�u�W�F�N�g�̏ꍇ)
		else
		{
			//���̂��̂̍ő�̍���
			fRotX = 0.0f;
			fFieldY = Scenepos.y + VtxMax.y;
		}
		//�e���X���Ȃ���v�Z���������ɂ���
		m_pShadow->MoveY(D3DXVECTOR3(pos.x, fFieldY, pos.z), -fRotX);
	}
	else
	{
		//�K���Ȉʒu�ɂ���
		m_pShadow->MoveY(D3DXVECTOR3(pos.x, -10000.0f, pos.z), D3DX_PI);
	}
}

//�쐬
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer(3);
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, rot, aFileName);
	}
	return pPlayer;
}