//=============================================================================
//�`���[�g���A���Ǘ�[Tutorial.cpp]
// Author : satou syusuke
//=============================================================================
//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#if 1
#include "Tutorial.h"
#include "player.h"

#include "UI.h"
#include "select_ui.h"
#include "change_ui.h"
#include "gamepad.h"

#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "load.h"

#include "camera.h"
#include "player.h"
#include "field.h"
#include "light.h"
#include "billboard.h"
#include "Fade.h"
#include "goal.h"
#include "object.h"
#include "trampoline.h"
#include "slack.h"
#include "camerapanel.h"

#include "straight3d.h"
#include "sound.h"
#endif
//*****************************************************************************
//�ÓI
//*****************************************************************************
bool CTutorial::m_bFade = NULL;
int CTutorial::m_nSelectNum = 1;

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define MAX_TUTORIALSERECT (4)
#define TUTO_FILE "data/tutorial.txt"

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTutorial::CTutorial()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTutorial::~CTutorial()
{

}
#endif

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CTutorial::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	CLoad::Load(TUTO_FILE);		//�X�e�[�W�̃��[�h

	//�t�F�[�h
	CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	m_nSelectNum = 1;
	CManager::SetPause(false);
	CSound::Play(CSound::SOUND_LABEL_GAMEBGM);
	CSound::ControlVoice(CSound::SOUND_LABEL_GAMEBGM, 0.5);

	m_bFade = false;
	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CTutorial::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// �X�V
//***************************************************************************** 
void CTutorial::Update()
{
	bool bPause = CManager::GetPause();
	CFade::FADE Fade = CFade::GetFade();
	//�t�F�[�h���ĂȂ�
	if (Fade == CFade::FADE_NONE)
	{
		//�Q�[���p�b�h�q�����Ă�
		if (m_pGamePad != NULL)
		{
			float CrossKey = m_pGamePad->TriggerCrossKey();

			//Pause��Ԃ̐؂�ւ�
			if (m_pGamePad->GetButton(CGamePad::DIP_START) == true && bPause == false)
			{
				CManager::SetPause(true);

				//�������|���S������
				CChangeUI::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),
					D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT),
					D3DXVECTOR2(0.0f, 0.0f),
					1,
					D3DXCOLOR(255, 255, 255, 100),
					D3DXCOLOR(0, 0, 0, 0),
					CChangeUI::CHANGE_PAUSE,
					10,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(0.0f, 0.0f));

				//�|�[�Y���݂̂�UI�̐ݒu
				CChangeUI::Create(
					D3DXVECTOR3(860.0f, 490.0f, 0),
					D3DXVECTOR2(890.0f, 1000.0f),
					D3DXVECTOR2(0.0f, 0.0f),
					34,
					D3DXCOLOR(255, 255, 255, 255),
					D3DXCOLOR(0, 0, 0, 0),
					CChangeUI::CHANGE_PAUSE,
					10,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(0.0f, 0.0f));

				CChangeUI::Create(
					D3DXVECTOR3(590.0f, 220.0f, 0),
					D3DXVECTOR2(230.0f, 60.0f),
					D3DXVECTOR2(0.0f, 0.0f),
					33,
					D3DXCOLOR(255, 255, 255, 255),
					D3DXCOLOR(0, 0, 0, 0),
					CChangeUI::CHANGE_PAUSE,
					10,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(0.0f, 0.0f));

				//�I����UI�̐ݒu
				CSelectUI::Create(D3DXVECTOR3(1000.0f, 430.0f, 0.0f), 220.0f, 50.0f, 31, 1, CSelectUI::SELECT_UI_NOMAL);
				CSelectUI::Create(D3DXVECTOR3(1000.0f, 530.0f, 0.0f), 220.0f, 50.0f, 30, 2, CSelectUI::SELECT_UI_NOMAL);
				CSelectUI::Create(D3DXVECTOR3(1000.0f, 620.0f, 0.0f), 220.0f, 50.0f, 32, 3, CSelectUI::SELECT_UI_NOMAL);

				CSound::Play(CSound::SOUND_LABEL_PAUSE);

				m_nSelectNum = 1;
			}
			//Pause����
			if (m_pGamePad->GetButton(CGamePad::DIP_START) == true && bPause == true)
			{
				CManager::SetPause(false);
				CSound::Play(CSound::SOUND_LABEL_PAUSE);
			}

			//Pause���̏���
			if (bPause == true)
			{
				//�t�F�[�h���ĂȂ�
				if (m_bFade == false)
				{
					//�\���L�[��
					if (CrossKey == 0.0f)
					{
						m_nSelectNum--;
						if (m_nSelectNum <= 0)
						{
							m_nSelectNum = MAX_TUTORIALSERECT - 1;
						}
						CSound::Play(CSound::SOUND_LABEL_SELECT);
					}
					//��
					else if (CrossKey == 18000.0f)
					{
						m_nSelectNum++;
						if (m_nSelectNum >= MAX_TUTORIALSERECT)
						{
							m_nSelectNum = 1;
						}
						CSound::Play(CSound::SOUND_LABEL_SELECT);
					}

					//����
					if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_nSelectNum == 1)
					{
						CManager::SetPause(false);
					}
					else if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_nSelectNum == 2)
					{
						CFade::SetFade(CManager::MODE_TUTORIAL);
						CSound::Play(CSound::SOUND_LABEL_CLICK);
						CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
						m_bFade = true;
					}
					else if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_nSelectNum == 3)
					{
						CFade::SetFade(CManager::MODE_TITLE);
						CSound::Play(CSound::SOUND_LABEL_CLICK);
						CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
						m_bFade = true;
					}

				}
			}
		}
		//�L�[�{�[�h�q�����Ă�
		else if (m_pKeyboard != NULL)
		{
			//Pause��Ԃ̐؂�ւ�
			if (m_pKeyboard->GetKey(DIK_ESCAPE) == true && bPause == false)
			{
				CManager::SetPause(true);

				//�������|���S������
				CChangeUI::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),
					D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT),
					D3DXVECTOR2(0.0f, 0.0f),
					1,
					D3DXCOLOR(255, 255, 255, 100),
					D3DXCOLOR(0, 0, 0, 0),
					CChangeUI::CHANGE_PAUSE,
					10,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(0.0f, 0.0f));

				//�|�[�Y���݂̂�UI�̐ݒu
				CChangeUI::Create(
					D3DXVECTOR3(860.0f, 490.0f, 0),
					D3DXVECTOR2(890.0f, 1000.0f),
					D3DXVECTOR2(0.0f, 0.0f),
					34,
					D3DXCOLOR(255, 255, 255, 255),
					D3DXCOLOR(0, 0, 0, 0),
					CChangeUI::CHANGE_PAUSE,
					10,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(0.0f, 0.0f));

				//Pause
				CChangeUI::Create(
					D3DXVECTOR3(590.0f, 220.0f, 0),
					D3DXVECTOR2(260.0f, 80.0f),
					D3DXVECTOR2(0.0f, 0.0f),
					33,
					D3DXCOLOR(255, 255, 255, 255),
					D3DXCOLOR(0, 0, 0, 0),
					CChangeUI::CHANGE_PAUSE,
					10,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(0.0f, 0.0f));

				//�I����UI�̐ݒu
				CSelectUI::Create(D3DXVECTOR3(1000.0f, 430.0f, 0.0f), 225.0f, 60.0f, 31, 1, CSelectUI::SELECT_UI_NOMAL);
				CSelectUI::Create(D3DXVECTOR3(1000.0f, 530.0f, 0.0f), 220.0f, 65.0f, 30, 2, CSelectUI::SELECT_UI_NOMAL);
				CSelectUI::Create(D3DXVECTOR3(1000.0f, 620.0f, 0.0f), 210.0f, 60.0f, 32, 3, CSelectUI::SELECT_UI_NOMAL);

				m_nSelectNum = 1;
			}
			//Pause����
			if (m_pKeyboard->GetKey(DIK_ESCAPE) == true && bPause == true)
			{
				CManager::SetPause(false);
				CSound::Play(CSound::SOUND_LABEL_PAUSE);
			}

			//Pause���̏���
			if (bPause == true)
			{
				if (m_bFade == false)
				{
					//�I��ԍ��̕ω�
					if (m_pKeyboard->GetKey(DIK_UP) == true || m_pKeyboard->GetKey(DIK_W) == true)
					{
						m_nSelectNum--;
						if (m_nSelectNum <= 0)
						{
							m_nSelectNum = MAX_TUTORIALSERECT - 1;
						}
						CSound::Play(CSound::SOUND_LABEL_SELECT);
					}
					else if (m_pKeyboard->GetKey(DIK_DOWN) == true || m_pKeyboard->GetKey(DIK_S) == true)
					{
						m_nSelectNum++;
						if (m_nSelectNum >= MAX_TUTORIALSERECT)
						{
							m_nSelectNum = 1;
						}
						CSound::Play(CSound::SOUND_LABEL_SELECT);
					}
				}

				//����
				if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_nSelectNum == 1)			//Pause����
				{
					CManager::SetPause(false);
				}
				else if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_nSelectNum == 2)	//���X�^�[�g
				{
					CFade::SetFade(CManager::MODE_TUTORIAL);
					CSound::Play(CSound::SOUND_LABEL_CLICK);
					CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
					m_bFade = true;
				}
				else if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_nSelectNum == 3)	//�߂�
				{
					CFade::SetFade(CManager::MODE_TITLE);
					CSound::Play(CSound::SOUND_LABEL_CLICK);
					CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
					m_bFade = true;
				}
			}
		}
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			float Distanse = CIRCLE;
			CStraight3D::Create(D3DXVECTOR3(-150.0f + sinf(Distanse) * 20, 260.0f, -300.0f + cosf(Distanse) * 20),
				D3DXVECTOR3(5.0f, 5.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 5.0f, 0.0f),
				D3DXCOLOR(255, 255, 255, 255),
				D3DXCOLOR(0, 0, 0, 0),
				3, 30);
		}
	}
}

#if 1
//*****************************************************************************
//�`��
//***************************************************************************** 
void CTutorial::Draw()
{

}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CTutorial *CTutorial::Create()
{
	CTutorial *pGame = NULL;
	pGame = new CTutorial;		//�������m��

	//NULL�`�F�b�N
	if (pGame != NULL)
	{
		pGame->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pGame;
}
#endif