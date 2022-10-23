//---------------------------
//Author:�O��q��
//���f��(player.cpp)
//---------------------------
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "gamepad.h"
#include "bullet.h"
#include "meshfield.h"
#include "object.h"
#include "enemy.h"
#include "rockon.h"
#include "field.h"
#include "mouse.h"
#include "ui.h"
#include "wall.h"
#include "item.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "billboard.h"

//�}�N����`
#define CHARAFILENAME "data/motion_Player.txt"

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_WALK,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_RELOAD,
	MOTIONTYPE_BUFF,
	MOTIONTYPE_ITEM,
	MOTIONTYPE_DAMAGE,
	MOTIONTYPE_DIE,
	MOTIONTYPE_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
	MAX_MOTION
} MOTIONTYPE;

typedef struct
{
	LPD3DXMESH pMesh; //���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat; //�}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD nNumMat; //�}�e���A���̐�
	LPDIRECT3DTEXTURE9 TextureModel[4] = {};
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 posOri; //���X�̈ʒu
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 rotOri; //���X�̌���
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nIdxModelParent; //�e���f���̃C���f�b�N�X
} Model;

typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nIdxModelParent; //�e���f���̃C���f�b�N�X
	float fRadius; //�����蔻��̑傫���̔��a
	int nStarttime; //�����蔻�肪�������鎞��
	int nFinishtime; //�����蔻�肪�����鎞��
	int nDamage; //�_���[�W��
	int nDamageTime; //�q�b�g�Ԋu
	float fHClash; //���������̐�����΂���
	float fVClash; //���������̐�����΂���
} Collision;

typedef struct
{
	D3DXVECTOR3 pos; //�O�Ղ̐�[�̈ʒu
	D3DXMATRIX TipmtxWorld;
	D3DXVECTOR3 TipposOld; //�O�Ղ̐�[�̑O��ʒu
	D3DXVECTOR3 posOld; //�O�Ղ̍����̑O��ʒu
	int nTime; //������܂ł̎���
	int nStartTime; //�������鎞��
	int nFinishTime; //�I���̎���
	int nIdxParent;
} Orbit;

typedef struct
{
	D3DXVECTOR3 pos; //���ˍ�
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nLag; //���ˊԊu
	int nBullet;
	int nStartBul; //�����n�߂̎���
	int nFinishBul; //�I���̎���
	int nIdxParent; //�e�C���f�b�N�X
	int nDamage; //�_���[�W��
	int nDamageTime; //�q�b�g�Ԋu
	float fHClash; //���������̐�����΂���
	float fVClash; //���������̐�����΂���
} Bang;

//�L�[�̍\����
typedef struct
{
	float fPosX; //�ʒuX
	float fPosY; //�ʒuY
	float fPosZ; //�ʒuZ
	float fRotX; //����X
	float fRotY; //����Y
	float fRotZ; //����Z
} KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame; //�t���[��
	float fMove; //���̃L�[�̈ړ���
	KEY aKey[32]; //�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
} KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop; //���[�v���邩�ǂ���
	int nNumKey; //�L�[�̑���
	Collision Collision[8];
	int nNumCol; //�����蔻��̋��̐�
	Orbit orbit[4];
	int nNumOrbit;
	int nNumBullet;
	Bang bullet;
	int nNonOpe;
	KEY_INFO aKeyInfo[16]; //�L�[��� []���̓L�[�̍ő吔
} MOTION_INFO;

typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 posOld; //�O��ʒu
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 rotDesh; //�ړI�̌���
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	D3DXVECTOR3 move; //�ړ���
	Model aModel[32]; //���f���i�p�[�c�j
	int nNumModel; //���f���i�p�[�c�j��
	int nShadow; //�e�̔ԍ�
	bool bMove; //�����Ă��邩
	bool bJump; //�W�����v�ł��邩(=�n�ʂƐڂ��Ă邩)
	MOTION_INFO aMotionInfo[MAX_MOTION]; //���[�V�������
	int nNumMotion; //���[�V������
	MOTIONTYPE motionType; //���[�V�����^�C�v
	int nKey; //�L�[No.
	int nCounterMotion; //���[�V�����̃J�E���^�[
	KEY aKeyDiff[32]; //���� []���̓p�[�c��
	KEY KeyMove; //���[�V�����J�n����̂��ǂꂾ��������
	float fRadius; //���a
	float fHeight; //����
	float fMove; //�ő呬�x
	float fJump; //�W�����v��
	int nNeutralTime; //�ړ��L�[���痣��������
	int nMoveParts; //���f���̊�ɂȂ镔��
	int nTotalTime; //���[�V�����J�n���獇�v�̎���
	MOTION_INFO MotionInfo;
	int nEnemy; //���Ԗڂ̓G�Ƀ��b�N�I�����Ă邩
	int nScore;
	int nItem;
	int nHP;
	int nMaxHP;
	int nSP;
	int nDamageTime;
	int nBullet;
	int nMaxBullet;
	int nNonOpe;
	int nChain;
	int nChainTime;
	float fRate;
	bool bSP;
	bool bDie;
} Player;

//�v���g�^�C�v�錾
void PlayerLoad(void);
D3DXVECTOR3 BulletPos(void);
float BulletMoveY(D3DXVECTOR3 bpos);
void CollisionPos(void);
void MotionChange(MOTIONTYPE motiontype);
void PlayerMotion(void);
void PlayerMove(void);
void PlayerSlow(void);
void UseItem(void);
void Shoot(void);
void Reload(void);
float PlayerHPRate(void);
float PlayerSPRate(void);

//�O���[�o���ϐ�
Player g_player; //�v���C���[�̏��
Model g_model[32]; //���f���̏��
int g_nNumModel; //�L�����Ɏg�����f��������ނ��邩

//����������
HRESULT InitPlayer(void)
{
	PlayerLoad();
	return S_OK;
}

//�I������
void UninitPlayer(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
	{
		//�e�N�X�`���̔j��
		if (g_model[nCntModel].pMesh != NULL)
		{
			g_model[nCntModel].pMesh->Release();
			g_model[nCntModel].pMesh = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_model[nCntModel].pBuffMat != NULL)
		{
			g_model[nCntModel].pBuffMat->Release();
			g_model[nCntModel].pBuffMat = NULL;
		}
	}
}

//�X�V����
void UpdatePlayer(void)
{
	bool bLand;
	bLand = g_player.bJump;
	g_player.posOld = g_player.pos;
	if (g_player.nNonOpe > 0)
	{
		g_player.nNonOpe--;
	}
	if (g_player.nDamageTime > 0)
	{
		g_player.nDamageTime--;
	}
	if (g_player.nChainTime > 0)
	{
		g_player.nChainTime--;
		ChainTimeUI(g_player.nChainTime);
	}
	else if (g_player.nChainTime == 0)
	{
		ChainTimeUI(g_player.nChainTime);
		g_player.nChain = 0;
		g_player.nChainTime = -1;
		g_player.fRate = 1.0f;
		ChainUI(g_player.nChain);
	}
	if (g_player.bSP == true)
	{
		g_player.nSP -= 4;
		SPUI(PlayerSPRate());
		if (g_player.nSP <= 0)
		{
			g_player.nSP = 0;
			g_player.bSP = false;
		}
	}
	else
	{
		if (g_player.nSP < 3600)
		{
			g_player.nSP++;
			SPUI(PlayerSPRate());
		}
		else if (g_player.nSP > 3600)
		{
			g_player.nSP = 3600;
		}
	}
	if (g_player.nNonOpe <= 0)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_player.rotDesh.y = D3DX_PI * 0.75f + CameraRot();
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_player.rotDesh.y = D3DX_PI * 0.25f + CameraRot();
			}
			else
			{
				g_player.rotDesh.y = D3DX_PI * 0.5f + CameraRot();
			}
			PlayerMove();
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_player.rotDesh.y = D3DX_PI * -0.75f + CameraRot();
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_player.rotDesh.y = D3DX_PI * -0.25f + CameraRot();
			}
			else
			{
				g_player.rotDesh.y = D3DX_PI * -0.5f + CameraRot();
			}
			PlayerMove();
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.rotDesh.y = D3DX_PI + CameraRot();
			PlayerMove();
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.rotDesh.y = CameraRot();
			PlayerMove();
		}
		else if (LeftStickX() != 0.0f || LeftStickY() != 0.0f)
		{
			g_player.rotDesh.y = atan2f(-LeftStickX(), LeftStickY()) + CameraRot();
			PlayerMove();
		}
		else
		{
			PlayerSlow();
		}
	}
	else
	{
		PlayerSlow();
	}
	if (GetKeyboardKey(DIK_Q) == true || GetGamePadButton(DIP_Y) == true)
	{
		if (g_player.nNonOpe <= 0 && g_player.nSP >= 3600 && g_player.bSP == false)
		{
			MotionChange(MOTIONTYPE_BUFF);
		}
	}
	if (g_player.bMove == true && g_player.motionType != MOTIONTYPE_WALK && g_player.bJump == true && g_player.nNonOpe <= 0)
	{
		MotionChange(MOTIONTYPE_WALK);
	}
	if (g_player.bMove == false && g_player.nNeutralTime >= 10 && g_player.motionType == MOTIONTYPE_WALK)
	{
		MotionChange(MOTIONTYPE_RETURN);
	}
	if (g_player.rot.y >= D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2;
	}
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2;
	}
	if (g_player.rotDesh.y >= D3DX_PI)
	{
		g_player.rotDesh.y -= D3DX_PI * 2;
	}
	if (g_player.rotDesh.y < -D3DX_PI)
	{
		g_player.rotDesh.y += D3DX_PI * 2;
	}
	if (g_player.rot.y != g_player.rotDesh.y)
	{
		if (g_player.rotDesh.y - g_player.rot.y < -3.14f)
		{
			g_player.rot.y += (g_player.rotDesh.y - g_player.rot.y + 6.28f) * 0.14f;
		}
		else if (g_player.rotDesh.y - g_player.rot.y > 3.14f)
		{
			g_player.rot.y += (g_player.rotDesh.y - g_player.rot.y - 6.28f) * 0.14f;
		}
		else
		{
			g_player.rot.y += (g_player.rotDesh.y - g_player.rot.y) * 0.14f;
		}
	}
	/*if (GetKeyboardKey(DIK_RETURN) == true)
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		MotionChange(MOTIONTYPE_RETURN);
	}*/
	if (GetKeyboardKey(DIK_R) == true || GetGamePadButton(DIP_A) == true)
	{
		if (g_player.nNonOpe <= 0)
		{
			Reload();
		}
	}
	if (GetKeyboardKey(DIK_E) == true || GetGamePadButton(DIP_X) == true)
	{
		if (g_player.nItem > 0 && g_player.nNonOpe <= 0)
		{
			MotionChange(MOTIONTYPE_ITEM);
		}
	}
	if (GetMouseButton(DIM_L) == true || GetGamePadButton(DIP_R1) == true)
	{
		if (g_player.motionType != MOTIONTYPE_ACTION && g_player.nNonOpe <= 0)
		{
			if (g_player.nBullet > 0)
			{
				MotionChange(MOTIONTYPE_ACTION);
			}
			else
			{
				PlaySound(SOUND_LABEL_BULLETLOST);
			}
		}
	}
	if (GetMouseButton(DIM_W) == true || GetGamePadButton(DIP_RS) == true)
	{
		CameraRotReset(g_player.rot.y + D3DX_PI);
	}
	/*if (g_player.bMove == true)
	{
		CameraRot(g_player.rot.y + D3DX_PI);
	}*/
	if (g_player.nDamageTime <= 0)
	{
		g_player.move.y -= 0.4f;
	}
	PlayerMotion(); //�v���C���[�̃��[�V����
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;
	MoveShadow(g_player.nShadow, g_player.pos);
	g_player.nEnemy = RockOn(g_player.pos, g_player.rot.y);
	if (g_player.nEnemy == -1)
	{
		RemoveRockon();
	}
	g_player.bJump = CollisionField(&g_player.pos, &g_player.posOld, &g_player.move, g_player.fRadius); //�t�B�[���h�Ƃ̓����蔻��
	CollisionItem(g_player.pos, g_player.fRadius);
	CollisionObject(&g_player.pos, &g_player.posOld, &g_player.move, g_player.fRadius); //�I�u�W�F�N�g�Ƃ̓����蔻��(��ɏ�邱�Ƃ͂ł��Ȃ�)
	CoillisionEnemy(g_player.fRadius, &g_player.pos, g_player.move);
	CollisionWall(&g_player.pos, g_player.fRadius);
}

//�`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;		 //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			 //�}�e���A���f�[�^�ւ̃|�C���^
	int nCntModel;
	pDevice = GetDevice();		 //�f�o�C�X���擾����
	//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);
	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);
	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);
	//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);
	for (nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotParts, mtxTransParts; //�p�[�c�p�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
		//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);
		//�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotParts, g_player.aModel[nCntModel].rot.y + g_player.aModel[nCntModel].rotOri.y,
			g_player.aModel[nCntModel].rot.x + g_player.aModel[nCntModel].rotOri.x, g_player.aModel[nCntModel].rot.z + g_player.aModel[nCntModel].rotOri.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotParts);
		//�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransParts, g_player.aModel[nCntModel].pos.x + g_player.aModel[nCntModel].posOri.x,
			g_player.aModel[nCntModel].pos.y + g_player.aModel[nCntModel].posOri.y, g_player.aModel[nCntModel].pos.z + g_player.aModel[nCntModel].posOri.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransParts);
		//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld; //�v���C���[�̃}�g���b�N�X��ݒ�
		}
		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
			&g_player.aModel[nCntModel].mtxWorld,
			&mtxParent);
		//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);
		//�p�[�c�̌��݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);
		//�p�[�c�̃}�e���A���f�[�^�ւ̃|�C���^�̔��f
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();
		int nCntMat;
		for (nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			int nCntTex = 0;
			//�v���C���[�̃}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			//for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMat; nCntMat++)
			//{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_player.aModel[nCntModel].TextureModel[nCntTex]);
					nCntTex++;
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}
			//}
			//�v���C���[�̃��f���i�p�[�c�j�̕`��
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
	//PlayerOrbit();
	CollisionPos();
}

void PlayerLoad(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntParts = 0;
	int nCntModelParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	int nCntCol = 0;
	int nCntBullet = 0;
	int nCntOrbit = 0;
	char aFile[256];
	bool bChara = false;
	bool bParts = false;
	bool bMotion = false;
	bool bKey = false;
	bool bKeySet = false;
	bool bColSet = false;
	bool bCol = false;
	bool bBulletSet = false;
	bool bBullet = false;
	bool bOrbit = false;
	bool bOrbitSet = false;
	int nIndex;
	int nLoop;
	FILE *pFile;
	pFile = fopen(CHARAFILENAME, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f���t�@�C���ǂݍ���
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXLoadMeshFromX(&aFile[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_model[nCntParts].pBuffMat,
					NULL,
					&g_model[nCntParts].nNumMat,
					&g_model[nCntParts].pMesh);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET��
			{
				if (strcmp(&aFile[0], "NUM_PARTS") == 0) //�p�[�c��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_player.nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_player.fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_player.fJump);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_player.fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_player.fHeight);
				}
				if (strcmp(&aFile[0], "HP") == 0) //HP
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_player.nHP);
					g_player.nMaxHP = g_player.nHP;
				}
				if (strcmp(&aFile[0], "BULLET") == 0) //�e��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_player.nBullet);
					g_player.nMaxBullet = g_player.nBullet;
				}
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{
					bParts = false;
					nCntParts++;
				}
				if (bParts == true) //PARTSSET��
				{
					if (strcmp(&aFile[0], "MOVEPARTS") == 0) //���ꂪ������g_player��pos�������i����Ȃ������j
					{
						g_player.nMoveParts = nCntParts;
					}
					if (strcmp(&aFile[0], "INDEX") == 0) //���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						g_player.aModel[nCntParts].pBuffMat = g_model[nIndex].pBuffMat;
						g_player.aModel[nCntParts].nNumMat = g_model[nIndex].nNumMat;
						g_player.aModel[nCntParts].pMesh = g_model[nIndex].pMesh;
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_player.aModel[nCntParts].nIdxModelParent);
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_player.aModel[nCntParts].posOri.x, &g_player.aModel[nCntParts].posOri.y, &g_player.aModel[nCntParts].posOri.z);

					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_player.aModel[nCntParts].rotOri.x, &g_player.aModel[nCntParts].rotOri.y, &g_player.aModel[nCntParts].rotOri.z);
					}
				}
			}
			if (bMotion == true) //MOTIONSET��
			{
				if (strcmp(&aFile[0], "LOOP") == 0) //���̃��[�V���������[�v���邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
					if (nLoop == 0)
					{
						g_player.aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						g_player.aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "NON_OPE") == 0) //����s�\����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].nNonOpe);
				}
				if (strcmp(&aFile[0], "COLLISIONSET") == 0)
				{
					bColSet = true;
					nCntCol = 0;
				}
				if (strcmp(&aFile[0], "END_COLLISIONSET") == 0)
				{
					g_player.aMotionInfo[nCntMotion].nNumCol = nCntCol;
					bColSet = false;
				}
				if (strcmp(&aFile[0], "ORBITSET") == 0)
				{
					bOrbitSet = true;
					nCntOrbit = 0;
				}
				if (strcmp(&aFile[0], "END_ORBITSET") == 0)
				{
					g_player.aMotionInfo[nCntMotion].nNumOrbit = nCntOrbit;
					bOrbitSet = false;
				}
				if (strcmp(&aFile[0], "BULLET") == 0)
				{
					bBulletSet = true;
					nCntBullet = 0;
				}
				if (strcmp(&aFile[0], "END_BULLETSET") == 0)
				{
					g_player.aMotionInfo[nCntMotion].nNumBullet = nCntBullet;
					bBulletSet = false;
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)
				{
					bKeySet = true;
					nCntParts = 0;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)
				{
					bKeySet = false;
					nCntKey++;
				}
				if (bColSet == true) //COLLISIONSET��
				{
					if (strcmp(&aFile[0], "COLLISION") == 0)
					{
						bCol = true;
					}
					if (strcmp(&aFile[0], "END_COLLISION") == 0)
					{
						bCol = false;
						nCntCol++;
					}
					if (bCol == true)
					{
						if (strcmp(&aFile[0], "COL") == 0) //�����蔻��i�e�̃C���f�b�N�X�A�ꏊ�A�傫���A���ԁj
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %f %f %f %f %d %d", &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].nIdxModelParent,
								&g_player.aMotionInfo[nCntMotion].Collision[nCntCol].pos.x, &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].pos.y, &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].pos.z,
								&g_player.aMotionInfo[nCntMotion].Collision[nCntCol].fRadius, &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].nStarttime, &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].nFinishtime);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //�����蔻��i����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].fHClash, &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].fVClash,
								&g_player.aMotionInfo[nCntMotion].Collision[nCntCol].nDamage, &g_player.aMotionInfo[nCntMotion].Collision[nCntCol].nDamageTime);
						}
					}
				}
				if (bOrbitSet == true) //ORBITSET��
				{
					if (strcmp(&aFile[0], "ORBIT") == 0)
					{
						bOrbit = true;
					}
					if (strcmp(&aFile[0], "END_ORBIT") == 0)
					{
						bOrbit = false;
						nCntOrbit++;
					}
					if (strcmp(&aFile[0], "OBT") == 0) //�O�Ձi�ꏊ�A�\�����ԁA�������ԁj
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d %f %f %f %d %d %d", &g_player.aMotionInfo[nCntMotion].orbit[nCntOrbit].nIdxParent,
							&g_player.aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.x, &g_player.aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.y,
							&g_player.aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.z, &g_player.aMotionInfo[nCntMotion].orbit[nCntOrbit].nTime,
							&g_player.aMotionInfo[nCntMotion].orbit[nCntOrbit].nStartTime, &g_player.aMotionInfo[nCntMotion].orbit[nCntOrbit].nFinishTime);
					}
				}
				if (bBulletSet == true) //BULLETSET��
				{
					if (strcmp(&aFile[0], "BULLET") == 0)
					{
						bBullet = true;
					}
					if (strcmp(&aFile[0], "END_BULLET") == 0)
					{
						bBullet = false;
						nCntBullet++;
					}
					if (bBullet == true)
					{
						if (strcmp(&aFile[0], "BUL") == 0) //�e�ہi�e�̃C���f�b�N�X�A�ꏊ�A�傫���A���ԁj
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %f %f %f %d %d %d", &g_player.aMotionInfo[nCntMotion].bullet.nIdxParent,
								&g_player.aMotionInfo[nCntMotion].bullet.pos.x, &g_player.aMotionInfo[nCntMotion].bullet.pos.y,
								&g_player.aMotionInfo[nCntMotion].bullet.pos.z, &g_player.aMotionInfo[nCntMotion].bullet.nStartBul,
								&g_player.aMotionInfo[nCntMotion].bullet.nFinishBul, &g_player.aMotionInfo[nCntMotion].bullet.nLag);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //�e�ہi����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_player.aMotionInfo[nCntMotion].bullet.fHClash, &g_player.aMotionInfo[nCntMotion].bullet.fVClash,
								&g_player.aMotionInfo[nCntMotion].bullet.nDamage, &g_player.aMotionInfo[nCntMotion].bullet.nDamageTime);
						}
					}
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "MOVE") == 0) //�ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
					}
					if (strcmp(&aFile[0], "KEY") == 0)
					{
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)
					{
						bKey = false;
						nCntParts++;
					}
					if (bKey == true) //KEY��
					{
						if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX,
								&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX,
								&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
						}
					}
				}
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)
			{
				bChara = true;
				nCntParts = 0;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)
			{
				bChara = false;
			}
			if (strcmp(&aFile[0], "MOTIONSET") == 0)
			{
				bMotion = true;
				nCntKey = 0;
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)
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
	D3DXMATERIAL *pMat;
	//�uMOTIONTYPE_RETURN�v�́A�j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	g_player.aMotionInfo[MOTIONTYPE_RETURN].bLoop = false;
	g_player.aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].nFrame = 14;
	g_player.aMotionInfo[MOTIONTYPE_RETURN].nNumKey = 1;
	for (nCntParts = 0; nCntParts < g_player.nNumModel; nCntParts++)
	{
		g_player.aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosX = g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		g_player.aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosY = g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		g_player.aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		g_player.aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotX = g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		g_player.aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotY = g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		g_player.aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntParts].pBuffMat->GetBufferPointer();
		int nCntTex = 0;
		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_player.aModel[nCntParts].TextureModel[nCntTex]);
				nCntTex++;
			}
		}
	}
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, -300.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	g_player.rotDesh = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	g_player.bJump = true;
	g_player.bMove = false;
	g_player.nNeutralTime = 0;
	g_player.nTotalTime = 0;
	g_player.nEnemy = -1;
	MotionChange(MOTIONTYPE_RETURN);
	g_player.nShadow = SetShadow(g_player.pos, g_player.fRadius);
	g_player.nScore = 0;
	g_player.nSP = 0;
	g_player.nItem = 0;
	g_player.nDamageTime = 0;
	g_player.nBullet = g_player.nMaxBullet;
	g_player.nNonOpe = 0;
	g_player.nChainTime = 0;
	g_player.nChain = 0;
	g_player.fRate = 1.0f;
	g_player.bSP = false;
	g_player.bDie = false;
	MaxBulletUI(g_player.nMaxBullet);
	BulletUI(g_player.nBullet);
	ItemUI(g_player.nItem);
	ChainUI(g_player.nChain);
	ChainTimeUI(g_player.nChainTime);
}

//�ړ����x
void PlayerMove(void)
{
	if (g_player.bJump == true)
	{
		g_player.move.x -= (sinf(g_player.rotDesh.y) * g_player.fMove + g_player.move.x) * 0.1f;
	}
	else
	{
		g_player.move.x -= (sinf(g_player.rotDesh.y) * g_player.fMove + g_player.move.x) * 0.05f;
	}
	if (g_player.bJump == true)
	{
		g_player.move.z -= (cosf(g_player.rotDesh.y) * g_player.fMove + g_player.move.z) * 0.1f;
	}
	else
	{
		g_player.move.z -= (cosf(g_player.rotDesh.y) * g_player.fMove + g_player.move.z) * 0.05f;
	}
	g_player.nNeutralTime = 0;
	g_player.bMove = true;
}

//�ړ����x�ቺ
void PlayerSlow(void)
{
	if (g_player.bJump == true)
	{
		g_player.move.x -= g_player.move.x * 0.1f;
	}
	else
	{
		g_player.move.x -= g_player.move.x * 0.05f;
	}
	if (g_player.bJump == true)
	{
		g_player.move.z -= g_player.move.z * 0.1f;
	}
	else
	{
		g_player.move.z -= g_player.move.z * 0.05f;
	}
	g_player.nNeutralTime++;
	if (g_player.nNeutralTime > 10)
	{
		g_player.nNeutralTime = 10;
	}
	g_player.bMove = false;
}

//���[�V������؂�ւ���֐�
void MotionChange(MOTIONTYPE motiontype)
{
	g_player.motionType = motiontype;
	g_player.nCounterMotion = 0;
	g_player.MotionInfo = g_player.aMotionInfo[motiontype];
	g_player.nKey = 0;
	g_player.KeyMove.fPosX = 0.0f;
	g_player.KeyMove.fPosY = 0.0f;
	g_player.KeyMove.fPosZ = 0.0f;
	g_player.nTotalTime = 0;
	g_player.nNonOpe = g_player.aMotionInfo[motiontype].nNonOpe;
}

float GetPlayerHeight(void)
{
	return g_player.fHeight;
}

void PlayerMotion(void) //���[�V�����̓���
{
	int nCntParts;
	g_player.nCounterMotion++;
	g_player.nTotalTime++;
	for (nCntParts = 0; nCntParts < g_player.nNumModel; nCntParts++)
	{
		if (g_player.nCounterMotion == 1) //���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
		{
			if (nCntParts != g_player.nMoveParts)
			{
				g_player.aKeyDiff[nCntParts].fPosX = g_player.MotionInfo.aKeyInfo[g_player.nKey].aKey[nCntParts].fPosX - g_player.aModel[nCntParts].pos.x;
				g_player.aKeyDiff[nCntParts].fPosY = g_player.MotionInfo.aKeyInfo[g_player.nKey].aKey[nCntParts].fPosY - g_player.aModel[nCntParts].pos.y;
				g_player.aKeyDiff[nCntParts].fPosZ = g_player.MotionInfo.aKeyInfo[g_player.nKey].aKey[nCntParts].fPosZ - g_player.aModel[nCntParts].pos.z;
			}
			else
			{
				g_player.KeyMove.fPosX = sinf(D3DX_PI + g_player.rot.y) * g_player.MotionInfo.aKeyInfo[g_player.nKey].fMove;
				//g_player.KeyMove.fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fPosY;
				g_player.KeyMove.fPosZ = cosf(D3DX_PI + g_player.rot.y) * g_player.MotionInfo.aKeyInfo[g_player.nKey].fMove;
			}
			g_player.aKeyDiff[nCntParts].fRotX = g_player.MotionInfo.aKeyInfo[g_player.nKey].aKey[nCntParts].fRotX - g_player.aModel[nCntParts].rot.x;
			if (g_player.aKeyDiff[nCntParts].fRotX < -D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotX += D3DX_PI * 2;
			}
			else if (g_player.aKeyDiff[nCntParts].fRotX > D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotX -= D3DX_PI * 2;
			}
			g_player.aKeyDiff[nCntParts].fRotY = g_player.MotionInfo.aKeyInfo[g_player.nKey].aKey[nCntParts].fRotY - g_player.aModel[nCntParts].rot.y;
			if (g_player.aKeyDiff[nCntParts].fRotY < -D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotY += D3DX_PI * 2;
			}
			else if (g_player.aKeyDiff[nCntParts].fRotY > D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotY -= D3DX_PI * 2;
			}
			g_player.aKeyDiff[nCntParts].fRotZ = g_player.MotionInfo.aKeyInfo[g_player.nKey].aKey[nCntParts].fRotZ - g_player.aModel[nCntParts].rot.z;
			if (g_player.aKeyDiff[nCntParts].fRotZ < -D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotZ += D3DX_PI * 2;
			}
			else if (g_player.aKeyDiff[nCntParts].fRotZ > D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotZ -= D3DX_PI * 2;
			}
		}
		if (nCntParts != g_player.nMoveParts)
		{
			g_player.aModel[nCntParts].pos.x += g_player.aKeyDiff[nCntParts].fPosX / g_player.MotionInfo.aKeyInfo[g_player.nKey].nFrame;
			g_player.aModel[nCntParts].pos.y += g_player.aKeyDiff[nCntParts].fPosY / g_player.MotionInfo.aKeyInfo[g_player.nKey].nFrame;
			g_player.aModel[nCntParts].pos.z += g_player.aKeyDiff[nCntParts].fPosZ / g_player.MotionInfo.aKeyInfo[g_player.nKey].nFrame;
		}
		else
		{
			if (g_player.KeyMove.fPosX != 0.0f)
			{
				g_player.move.x = g_player.KeyMove.fPosX;
			}
			//g_player.pos.y += g_player.KeyMove.fPosY / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
			if (g_player.KeyMove.fPosZ != 0.0f)
			{
				g_player.move.z = g_player.KeyMove.fPosZ;
			}
		}
		g_player.aModel[nCntParts].rot.x += g_player.aKeyDiff[nCntParts].fRotX / g_player.MotionInfo.aKeyInfo[g_player.nKey].nFrame;
		g_player.aModel[nCntParts].rot.y += g_player.aKeyDiff[nCntParts].fRotY / g_player.MotionInfo.aKeyInfo[g_player.nKey].nFrame;
		g_player.aModel[nCntParts].rot.z += g_player.aKeyDiff[nCntParts].fRotZ / g_player.MotionInfo.aKeyInfo[g_player.nKey].nFrame;
	}
	if (g_player.motionType == MOTIONTYPE_ACTION && g_player.MotionInfo.bullet.nStartBul == g_player.nTotalTime)
	{
		Shoot();
	}
	if (g_player.motionType == MOTIONTYPE_ITEM && g_player.nKey == 2 && g_player.nCounterMotion == 1)
	{
		UseItem();
	}
	if (g_player.motionType == MOTIONTYPE_BUFF && g_player.nKey == 2 && g_player.nCounterMotion == 1)
	{
		g_player.bSP = true;
		PlaySound(SOUND_LABEL_BUFF);
	}
	if (g_player.nCounterMotion == g_player.MotionInfo.aKeyInfo[g_player.nKey].nFrame)
	{
		g_player.nCounterMotion = 0;
		g_player.nKey++;
		if (g_player.nKey == g_player.MotionInfo.nNumKey)
		{
			if (g_player.MotionInfo.bLoop == false)
			{
				if (g_player.motionType != MOTIONTYPE_RETURN)
				{
					MotionChange(MOTIONTYPE_RETURN);
				}
				else
				{
					MotionChange(MOTIONTYPE_NEUTRAL);
				}
			}
			g_player.nKey = 0;
		}
	}
}

void Shoot(void)
{
	float fRoty = 0.0f;
	float fGunRoty;
	D3DXVECTOR3 bpos;
	bpos = BulletPos();
	if (g_player.nEnemy != -1)
	{
		fGunRoty = RockBullet(bpos, g_player.nEnemy);
		fRoty = BulletMoveY(bpos);
	}
	else
	{
		fGunRoty = g_player.rotDesh.y;
	}
	PlaySound(SOUND_LABEL_GUN);
	SetBullet(bpos, D3DXVECTOR3(-30.0f * sinf(fGunRoty), -30.0f * sinf(fRoty), -30.0f * cosf(fGunRoty)),
		g_player.MotionInfo.bullet.nDamage, g_player.MotionInfo.bullet.nDamageTime);
	g_player.nBullet--;
	BulletUI(g_player.nBullet);
}

void Reload(void)
{
	g_player.nBullet = g_player.nMaxBullet;
	PlaySound(SOUND_LABEL_RELOAD);
	MotionChange(MOTIONTYPE_RELOAD);
	BulletUI(g_player.nBullet);
}

//�v���C���[�̏ꏊ
D3DXVECTOR3 PlayerPos(void)
{
	return g_player.pos;
}

//�v���C���[�̌���
float PlayerRot(void)
{
	return g_player.rot.y;
}

float ClashRot(D3DXVECTOR3 pos)
{
	float fRot = 0.0f;
	fRot = atan2f(pos.x - g_player.pos.x, pos.z - g_player.pos.z);
	return fRot;
}

float PlayerRotDesh(void)
{
	return g_player.rotDesh.y;
}

float GetPlayerRadius(void)
{
	return g_player.fRadius;
}

D3DXVECTOR3 PlayerGetMove(void)
{
	return g_player.move;
}

D3DXMATRIX CollisionPlayerPos(int nCntParts)
{
	return g_player.aModel[nCntParts].mtxWorld;
}

bool TargetRockon(void)
{
	return false;
}

int NumParts(void)
{
	return g_player.MotionInfo.nNumKey;
}

void CollisionPos(void)
{
	int nCntCol;
	for (nCntCol = 0; nCntCol < g_player.MotionInfo.nNumCol; nCntCol++)
	{
		if (g_player.MotionInfo.Collision[nCntCol].nStarttime <= g_player.nTotalTime &&
			g_player.nTotalTime < g_player.MotionInfo.Collision[nCntCol].nFinishtime)
		{
			D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
			//�����蔻��̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player.MotionInfo.Collision[nCntCol].mtxWorld);
			//�����蔻��̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_player.MotionInfo.Collision[nCntCol].pos.x, g_player.MotionInfo.Collision[nCntCol].pos.y, g_player.MotionInfo.Collision[nCntCol].pos.z);
			D3DXMatrixMultiply(&g_player.MotionInfo.Collision[nCntCol].mtxWorld, &g_player.MotionInfo.Collision[nCntCol].mtxWorld, &mtxTrans);
			//�e�̃}�g���b�N�X�擾
			mtxParent = g_player.aModel[g_player.MotionInfo.Collision[nCntCol].nIdxModelParent].mtxWorld;
			//�Z�o�����e�����蔻��̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_player.MotionInfo.Collision[nCntCol].mtxWorld,
				&g_player.MotionInfo.Collision[nCntCol].mtxWorld,
				&mtxParent);
			CollisionDamage(D3DXVECTOR3(g_player.MotionInfo.Collision[nCntCol].mtxWorld._41, g_player.MotionInfo.Collision[nCntCol].mtxWorld._42, g_player.MotionInfo.Collision[nCntCol].mtxWorld._43),
				g_player.MotionInfo.Collision[nCntCol].fRadius, D3DXVECTOR3(-sinf(g_player.rot.y) * g_player.MotionInfo.Collision[nCntCol].fHClash, g_player.MotionInfo.Collision[nCntCol].fVClash, -cosf(g_player.rot.y) * g_player.MotionInfo.Collision[nCntCol].fHClash),
				g_player.MotionInfo.Collision[nCntCol].nDamage, g_player.MotionInfo.Collision[nCntCol].nDamageTime);
		}
	}
}

float PlayerLookEnemy(void)
{
	float fRot = 0.0f;
	fRot = g_player.rot.y - atan2f(g_player.pos.x - EnemyPos(0, g_player.nEnemy), g_player.pos.z - EnemyPos(2, g_player.nEnemy));

	if (fRot > D3DX_PI)
	{
		fRot -= D3DX_PI * 2;
	}
	if (fRot < -D3DX_PI)
	{
		fRot += D3DX_PI * 2;
	}

	return fRot;
}

void PlayerReturn(void)
{
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bJump = true;
	g_player.bMove = false;
	g_player.nNeutralTime = 0;
	g_player.nTotalTime = 0;
	g_player.nEnemy = -1;
	MotionChange(MOTIONTYPE_RETURN);
}

D3DXVECTOR3 BulletPos(void)
{
	D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
	//�e�ۂ̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.MotionInfo.bullet.mtxWorld);
	//�e�ۂ̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.MotionInfo.bullet.pos.x, g_player.MotionInfo.bullet.pos.y, g_player.MotionInfo.bullet.pos.z);
	D3DXMatrixMultiply(&g_player.MotionInfo.bullet.mtxWorld, &g_player.MotionInfo.bullet.mtxWorld, &mtxTrans);
	//�e�̃}�g���b�N�X�擾
	mtxParent = g_player.aModel[g_player.MotionInfo.bullet.nIdxParent].mtxWorld;
	//�Z�o�����e�ۂ̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&g_player.MotionInfo.bullet.mtxWorld, &g_player.MotionInfo.bullet.mtxWorld, &mtxParent);
	return D3DXVECTOR3(g_player.MotionInfo.bullet.mtxWorld._41, g_player.MotionInfo.bullet.mtxWorld._42, g_player.MotionInfo.bullet.mtxWorld._43);
}

float BulletMoveY(D3DXVECTOR3 bpos)
{
	float fRotY;
	float fLenghtX;
	float fLenghtY;
	float fLenghtZ;
	float fDistance;
	fLenghtX = powf(bpos.x - EnemyPos(0, g_player.nEnemy), 2);
	fLenghtY = bpos.y - EnemyPos(1, g_player.nEnemy);
	fLenghtZ = powf(bpos.z - EnemyPos(2, g_player.nEnemy), 2);
	fDistance = sqrtf(fLenghtX + fLenghtZ);
	fRotY = atan2f(fLenghtY, fDistance);
	return fRotY;
}

void ScoreAdd(int nScore)
{
	g_player.nChain++;
	g_player.nChainTime = 480;
	if (g_player.nChain % 5 == 0)
	{
		g_player.fRate += 0.1f;
	}
	if (GetTuto() == false)
	{
		g_player.nScore += fabsf(nScore * g_player.fRate);
	}
	g_player.nSP += fabsf(nScore * g_player.fRate / 10);
	ChainTimeUI(g_player.nChainTime);
	ChainUI(g_player.nChain);
	ScoreUI(g_player.nScore);
}

void UseItem(void)
{
	g_player.nItem--;
	g_player.nHP = g_player.nMaxHP;
	ItemUI(g_player.nItem);
	HPUI(PlayerHPRate());
	PlaySound(SOUND_LABEL_HEAL);
}

float PlayerHPRate(void)
{
	float fRate;
	if (g_player.nHP > 0)
	{
		fRate = (float)g_player.nHP / (float)g_player.nMaxHP;
	}
	else
	{
		fRate = 0.0f;
	}
	return fRate;
}

float PlayerSPRate(void)
{
	float fRate;
	if (g_player.nHP > 0)
	{
		fRate = (float)g_player.nSP / (float)3600.0f;
	}
	else
	{
		fRate = 0.0f;
	}
	return fRate;
}

float PlayerDistance(D3DXVECTOR3 pos)
{
	float fLengthX;
	float fLengthZ;
	float fDistance;
	fLengthX = powf(pos.x - g_player.pos.x, 2);
	fLengthZ = powf(pos.z - g_player.pos.z, 2);
	fDistance = sqrtf(fLengthX + fLengthZ);
	return fDistance;
}

void PlayerDamage(int nDamage, int nDamageTime, D3DXVECTOR3 Clash, float fRot)
{

	if (g_player.bSP == true)
	{
		g_player.nHP -= nDamage / 2;
	}
	else
	{
		if (g_player.motionType != MOTIONTYPE_BUFF)
		{
			MotionChange(MOTIONTYPE_DAMAGE);
		}
		g_player.nHP -= nDamage;
	}
	g_player.nDamageTime = nDamageTime;
	g_player.move = Clash;
	g_player.nSP += nDamage * 4;
	if (g_player.nHP <= 0)
	{
		if (GetTuto() == true)
		{
			g_player.nHP = g_player.nMaxHP;
			PlaySound(SOUND_LABEL_DAMAGE);
		}
		else
		{
			g_player.rotDesh.y = fRot;
			g_player.rot.y = fRot;
			PlaySound(SOUND_LABEL_DEATH);
			g_player.nHP = 0;
			//SetFade(MODE_RESULT);
			g_player.bDie = true;
			PlayerDieCamera(g_player.rot.y);
			MotionChange(MOTIONTYPE_DIE);
		}
	}
	else
	{
		PlaySound(SOUND_LABEL_DAMAGE);
	}
	HPUI(PlayerHPRate());
	SPUI(PlayerSPRate());
}

bool PlayerDamage(D3DXVECTOR3 pos, float fRadius)
{
	if (g_player.nDamageTime > 0)
	{
		return false;
	}
	float fLengthX; //�����蔻��ƓG��X�����̒���
	float fLengthY; //�����蔻��ƓG��Y�����̒���
	float fLengthZ; //�����蔻��ƓG��Z�����̒���
	float fHDistance; //�����蔻��ƓG�̐��������̋���
	fLengthX = powf(pos.x - g_player.pos.x, 2);
	fLengthY = fabsf(pos.y - (g_player.pos.y + g_player.fHeight / 2));
	fLengthZ = powf(pos.z - g_player.pos.z, 2);
	fHDistance = sqrtf(fLengthX + fLengthZ);
	if (fHDistance <= fRadius + g_player.fRadius && fLengthY <= g_player.fHeight / 2 + fRadius)
	{
		return true;
	}
	return false;
}

float PlayerClashRot(D3DXVECTOR3 pos)
{
	float fRot = 0.0f;
	fRot = atan2f(g_player.pos.x - pos.x, g_player.pos.z - pos.z);
	return fRot;
}

void ResetPlayer(void)
{
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, -300.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	g_player.rotDesh = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	g_player.bJump = true;
	g_player.bMove = false;
	g_player.nNeutralTime = 0;
	g_player.nTotalTime = 0;
	g_player.nEnemy = -1;
	MotionChange(MOTIONTYPE_RETURN);
	g_player.nScore = 0;
	g_player.nItem = 0;
	g_player.nDamageTime = 0;
	g_player.nBullet = g_player.nMaxBullet;
	g_player.nNonOpe = 0;
	g_player.nChainTime = 0;
	g_player.nSP = 0;
	g_player.nHP = g_player.nMaxHP;
	g_player.nChain = 0;
	g_player.fRate = 1.0f;
	g_player.bSP = false;
	g_player.bDie = false;
	g_player.nShadow = SetShadow(g_player.pos, g_player.fRadius);
	MaxBulletUI(g_player.nMaxBullet);
	BulletUI(g_player.nBullet);
	ItemUI(g_player.nItem);
	ScoreUI(g_player.nScore);
	ChainUI(g_player.nChain);
	ChainTimeUI(g_player.nChainTime);
}

void AddItem(void)
{
	g_player.nItem++;
	ItemUI(g_player.nItem);
}

int PlayerScore(void)
{
	return g_player.nScore;
}

bool GetPlayerDie(void)
{
	return g_player.bDie;
}