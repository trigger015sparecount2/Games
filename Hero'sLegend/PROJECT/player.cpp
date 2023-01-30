//---------------------------
//Author:�O��q��
//�v���C���[(player.cpp)
//---------------------------
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "gamepad.h"
#include "bullet.h"
#include "particle.h"
#include "meshfield.h"
#include "object.h"
#include "enemy.h"
#include "orbit.h"
#include "rockon.h"
#include "sound.h"
#include "wall.h"

//�}�N����`
#define CHARAFILENAME "data/motion_flash.txt"

//�v���g�^�C�v�錾
void PlayerMoveX(void);
void PlayerMoveZ(void);
void PlayerSlowX(void);
void PlayerSlowZ(void);
void PlayerMotion(void);
void MotionChange(MOTIONTYPE motiontype);
void CollisionPos(void);
void PlayerOrbit(void);
MOTIONTYPE AttackType(float fDistance, float fHeight);

//���f���̏��
typedef struct
{
	LPD3DXMESH pMesh;		//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 TextureModel[4] = {};	//�e�N�X�`��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOri;		//���X�̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 rotOri;		//���X�̌���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
} Model;

//�����蔻��
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
	float fRadius;			//�����蔻��̑傫���̔��a
	int nStarttime;			//�����蔻�肪�������鎞��
	int nFinishtime;		//�����蔻�肪�����鎞��
	int nDamage;			//�_���[�W��
	int nDamageTime;		//�q�b�g�Ԋu
	float fHClash;			//���������̐�����΂���
	float fVClash;			//���������̐�����΂���
} Collision;

//�O�Րݒ�
typedef struct
{
	D3DXVECTOR3 pos;		//�O�Ղ̐�[�̈ʒu
	D3DXMATRIX TipmtxWorld;	//�O�Ր�[�̃}�g���b�N�X
	D3DXVECTOR3 TipposOld;	//�O�Ղ̐�[�̑O��ʒu
	D3DXVECTOR3 posOld;		//�O�Ղ̍����̑O��ʒu
	int nTime;				//������܂ł̎���
	int nStartTime;			//�������鎞��
	int nFinishTime;		//�I���̎���
	int nIdxParent;			//�e���f���̔ԍ�
} Orbit;

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
	int nFrame;		//�t���[��
	float fMove;	//���̃L�[�̐����ړ���
	float fHeight;	//���̃L�[�̐����ړ���
	KEY aKey[16];	//�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
} KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;		//���[�v���邩�ǂ���
	int nNumKey;	//�L�[�̑���
	Collision Collision[8];	//�����蔻��
	int nNumCol;	//�����蔻��̋��̐�
	int nComboTime;	//�R���{���q���鎞��
	Orbit orbit;	//�O��
	KEY_INFO aKeyInfo[16];	//�L�[��� []���̓L�[�̍ő吔
} MOTION_INFO;

//�v���C���[�̏��
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�O��ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 rotDesh;	//�ړI�̌���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 move;		//�ړ���
	Model aModel[16];		//���f���i�p�[�c�j
	int nNumModel;			//���f���i�p�[�c�j��
	int nShadow;			//�e�̔ԍ�
	bool bMove;				//�����Ă��邩
	bool bJump;				//�W�����v�ł��邩(=�n�ʂƐڂ��Ă邩)
	bool bRock;				//���b�N�I�����Ă邩
	MOTION_INFO aMotionInfo[MAX_MOTION];	//���[�V�������
	int nNumMotion;			//���[�V������
	MOTIONTYPE motionType;	//���[�V�����^�C�v
	int nKey;				//�L�[No.
	int nCounterMotion;		//���[�V�����̃J�E���^�[
	KEY aKeyDiff[32];		//���� []���̓p�[�c��
	KEY KeyMove;			//���[�V�����J�n����̂��ǂꂾ��������
	float fRadius;			//���a
	float fHeight;			//����
	float fMove;			//�ő呬�x
	float fJump;			//�W�����v��
	int nNeutralTime;		//�ړ��L�[���痣��������
	int nMoveParts;			//���f���̊�ɂȂ镔��
	int nTotalTime;			//���[�V�����J�n���獇�v�̎���
	MOTION_INFO MotionInfo;	//���[�V�����̏��
	int nCol;				//���Ԗڂ̓����蔻��Ƀq�b�g������
	int nEnemy;				//���Ԗڂ̓G�Ƀ��b�N�I�����Ă邩
	int nCombo;				//���̃R���{��
	int nComboTime;			//�U�����Ă���̎���
	int nHP;				//����HP
	int nDamageTime;		//�_���[�W�󂯂��J�E���g
	int nMaxHP;				//�ő�HP
	int nFoot;				//����
	int nKill;				//�|������
	MOTIONTYPE Oldmotion;	//�ߋ��̃��[�V����
} Player;

//�O���[�o���ϐ�
Player g_player;	//�v���C���[�̏��
Model g_model[16];	//���f���̏��
int g_nNumModel;	//�L�����Ɏg�����f��������ނ��邩

//����������
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	int nCntCol = 0;
	char aFile[256];
	bool bChara = false;
	bool bParts = false;
	bool bMotion = false;
	bool bKey = false;
	bool bKeySet = false;
	bool bColSet = false;
	bool bCol = false;
	int nIndex;
	int nLoop;
	FILE *pFile;
	g_player.fRadius = 20.0f;
	g_player.fJump = 10.0f;
	g_player.fMove = 5.0f;
	g_player.nMoveParts = -1;
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
				if (strcmp(&aFile[0], "HP") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_player.nHP);
					g_player.nMaxHP = g_player.nHP;
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
				if (strcmp(&aFile[0], "ORBIT") == 0) //�O�Ձi�ꏊ�A�\�����ԁA�������ԁj
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %f %f %f %d %d %d", &g_player.aMotionInfo[nCntMotion].orbit.nIdxParent, &g_player.aMotionInfo[nCntMotion].orbit.pos.x, &g_player.aMotionInfo[nCntMotion].orbit.pos.y, &g_player.aMotionInfo[nCntMotion].orbit.pos.z,
						&g_player.aMotionInfo[nCntMotion].orbit.nTime, &g_player.aMotionInfo[nCntMotion].orbit.nStartTime, &g_player.aMotionInfo[nCntMotion].orbit.nFinishTime);
				}
				if (strcmp(&aFile[0], "COMBO_TIME") == 0) //�R���{���ł���܂ł̎���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].nComboTime);
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
					if (strcmp(&aFile[0], "HEIGHT") == 0) //�����ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fHeight);
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
							fscanf(pFile, "%f %f %f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX, &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX, &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
				nCntCol = 0;
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
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bJump = true;
	g_player.bMove = false;
	g_player.nNeutralTime = 0;
	g_player.nTotalTime = 0;
	g_player.nEnemy = -1;
	g_player.nDamageTime = 0;
	g_player.nKill = 0;
	MotionChange(MOTIONTYPE_RETURN);
	g_player.nShadow = SetShadow(g_player.pos, g_player.fRadius);
	g_player.nCombo = 0;
	g_player.nComboTime = 0;
	g_player.nFoot = 0;
	g_player.bRock = false;
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
	//�U�����ĂȂ����_���[�W������ĂȂ�
	if (g_player.nComboTime == 0 && g_player.nDamageTime == 0)
	{
		//�ړ�
		if (GetKeyboardPress(DIK_A) == true || LeftStickX() < 0.0f)
		{
			if (GetKeyboardPress(DIK_W) == true || LeftStickY() < 0.0f)
			{
				g_player.rotDesh.y = D3DX_PI * 0.75f + CameraRot();
			}
			else if (GetKeyboardPress(DIK_S) == true || LeftStickY() > 0.0f)
			{
				g_player.rotDesh.y = D3DX_PI * 0.25f + CameraRot();
			}
			else
			{
				g_player.rotDesh.y = D3DX_PI * 0.5f + CameraRot();
			}
			PlayerMoveX();
			PlayerMoveZ();
		}
		else if (GetKeyboardPress(DIK_D) == true || LeftStickX() > 0.0f)
		{
			if (GetKeyboardPress(DIK_W) == true || LeftStickY() < 0.0f)
			{
				g_player.rotDesh.y = D3DX_PI * -0.75f + CameraRot();
			}
			else if (GetKeyboardPress(DIK_S) == true || LeftStickY() > 0.0f)
			{
				g_player.rotDesh.y = D3DX_PI * -0.25f + CameraRot();
			}
			else
			{
				g_player.rotDesh.y = D3DX_PI * -0.5f + CameraRot();
			}
			PlayerMoveX();
			PlayerMoveZ();
		}
		else if (GetKeyboardPress(DIK_W) == true || LeftStickY() < 0.0f)
		{
			g_player.rotDesh.y = D3DX_PI + CameraRot();
			PlayerMoveX();
			PlayerMoveZ();
		}
		else if (GetKeyboardPress(DIK_S) == true || LeftStickY() > 0.0f)
		{
			g_player.rotDesh.y = CameraRot();
			PlayerMoveX();
			PlayerMoveZ();
		}
		else
		{
			//�ړ����x�ቺ
			PlayerSlowX();
			PlayerSlowZ();
		}
	}
	else
	{
		//�ړ����x�ቺ
		PlayerSlowX();
		PlayerSlowZ();
	}

	//�����Ă邩���[�V�����������ĂȂ������n���Ă�
	if (g_player.bMove == true && g_player.motionType != MOTIONTYPE_WALK && g_player.bJump == true)
	{
		MotionChange(MOTIONTYPE_WALK);
	}

	//�����łȂ������[�V�����������Ă邩�����̂�߂Ă���J�E���g�o���Ă�
	if(g_player.bMove == false && g_player.nNeutralTime == 8 && g_player.motionType == MOTIONTYPE_WALK)
	{
		MotionChange(MOTIONTYPE_RETURN);
	}

	//����������Ȃ��悤�ɂ���
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

	//�������Z
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

	//�W�����v
	if (GetKeyboardKey(DIK_I) == true || GetGamePadButton(DIP_A) == true)
	{
		//���n���Ă邩�R���{���ĂȂ�
		if (g_player.bJump == true && g_player.nComboTime == 0)
		{
			//�W�����v������
			g_player.move.y += g_player.fJump;
			MotionChange(MOTIONTYPE_JUMP);
			g_player.nCombo = 0;
		}
	}

	//�U�����ĂȂ�������A�d�͓�������
	if (g_player.motionType == MOTIONTYPE_NEUTRAL || g_player.motionType == MOTIONTYPE_JUMP || g_player.motionType == MOTIONTYPE_LANDING ||
		g_player.motionType == MOTIONTYPE_RETURN || g_player.motionType == MOTIONTYPE_WALK)
	{
		g_player.move.y -= 0.4f;
	}
	else
	{
		g_player.move.y = 0.0f;
	}

	PlayerMotion(); //�v���C���[�̃��[�V����

	//�ړ�
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;
	MoveShadow(g_player.nShadow, g_player.pos);

	//���b�N�I�����ĂȂ�
	if (g_player.bRock == false)
	{
		//�I�[�g���b�N�I��������
		g_player.nEnemy = RockOn(g_player.pos);
	}

	//���b�N�I��
	if (GetKeyboardKey(DIK_E) == true || GetGamePadButton(DIP_R1) == true)
	{
		if (g_player.bRock == true)
		{
			g_player.bRock = false;
		}
		else if(g_player.nEnemy != -1)
		{
			g_player.bRock = true;
		}
	}

	//���b�N�I�����Ă�G���Ȃ������b�N�I�����ĂȂ����b�N�I���O��
	if (g_player.nEnemy == -1 && g_player.bRock == false)
	{
		RemoveRockon();
	}

	//�J�E���g�ސi�߂�
	if (g_player.nDamageTime > 0)
	{
		g_player.nDamageTime--;
	}
	if (g_player.nComboTime > 0)
	{
		g_player.nComboTime--;
	}
	//�_���[�W�J�E���g�i��ł�
	else if (g_player.nDamageTime == 0)
	{
		//�U��
		if (GetKeyboardKey(DIK_J) == true || GetGamePadButton(DIP_B) == true)
		{
			//�G�����b�N�I�����Ă�
			if (g_player.nEnemy != -1)
			{
				//�G�̕���������
				g_player.rotDesh.y = RockAttack(g_player.pos, g_player.nEnemy);
				if (g_player.nCombo < 2)
				{
					//�G�Ƃ̈ʒu�֌W�ɉ����čU���ς��
					MotionChange(AttackType(RockHDistance(g_player.pos, g_player.nEnemy), RockVDistance(g_player.pos, g_player.nEnemy, g_player.fHeight)));
				}
				else
				{
					//�R���{�t�B�j�b�V��
					MotionChange(MOTIONTYPE_FINISH);
					g_player.nCombo = 0;
				}
			}
			//���b�N�I�����ĂȂ�
			else
			{
				//�R���{���ɉ����čU���ς��
				switch (g_player.nCombo)
				{
				case 0:
					MotionChange(MOTIONTYPE_NORMAL);	//�ߋ���
					g_player.nCombo++;
					break;
				case 1:
					MotionChange(MOTIONTYPE_RUSH);		//�ːi
					g_player.nCombo++;
					break;
				case 2:
					MotionChange(MOTIONTYPE_FINISH);	//�t�B�j�b�V��
					g_player.nCombo = 0;
					break;
				}
			}
		}
	}

	//�����蔻��
	g_player.bJump = CollisionField(&g_player.pos, &g_player.posOld, &g_player.move, g_player.fRadius); //�t�B�[���h�Ƃ̓����蔻��
	CollisionObject(&g_player.pos, g_player.fRadius, g_player.fHeight); //�I�u�W�F�N�g�Ƃ̓����蔻��(��ɏ�邱�Ƃ͂ł��Ȃ�)
	CoillisionEnemy(g_player.fRadius, &g_player.pos, g_player.fHeight);
	CollisionWall(&g_player.pos, g_player.fRadius);
	//�e�Ƃ̓����蔻��
	if (CollisionBullet(&g_player.pos, &g_player.move, g_player.fRadius, g_player.nDamageTime, &g_player.rotDesh.y) == true)
	{
		//HP���炷
		g_player.rot.y = g_player.rotDesh.y;
		g_player.nHP -= BulletDamage();

		//�܂������Ă�
		if (g_player.nHP > 0)
		{
			//�_���[�W���[�V����
			PlaySound(SOUND_LABEL_DAMAGE);
			MotionChange(MOTIONTYPE_DAMAGE);
		}
		else
		{
			//���ꂽ
			MotionChange(MOTIONTYPE_DIE);
		}
	}

	//�O�t���[���Œ��n���ĂȂ������t���[���Œ��n����
	if (bLand == false && g_player.bJump == true)
	{
		if (g_player.motionType == MOTIONTYPE_NEUTRAL || g_player.motionType == MOTIONTYPE_JUMP || g_player.motionType == MOTIONTYPE_RETURN || g_player.motionType == MOTIONTYPE_WALK)
		{
			MotionChange(MOTIONTYPE_LANDING);
			g_player.nCombo = 0;
		}
	}
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
		D3DXMatrixRotationYawPitchRoll(&mtxRotParts, g_player.aModel[nCntModel].rot.y + g_player.aModel[nCntModel].rotOri.y, g_player.aModel[nCntModel].rot.x + g_player.aModel[nCntModel].rotOri.x, g_player.aModel[nCntModel].rot.z + g_player.aModel[nCntModel].rotOri.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotParts);
		
		//�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransParts, g_player.aModel[nCntModel].pos.x + g_player.aModel[nCntModel].posOri.x, g_player.aModel[nCntModel].pos.y + g_player.aModel[nCntModel].posOri.y, g_player.aModel[nCntModel].pos.z + g_player.aModel[nCntModel].posOri.z);
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
			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMat; nCntMat++)
			{
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
			}
			//�v���C���[�̃��f���i�p�[�c�j�̕`��
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
	//�v���C���[�̋O��
	PlayerOrbit();

	//�U���̓����蔻��̏ꏊ�ݒ�
	CollisionPos();
}

//�ړ����x��
void PlayerMoveX(void)
{
	if (g_player.bJump == true)
	{
		g_player.move.x -= (sinf(g_player.rotDesh.y) * g_player.fMove + g_player.move.x) * 0.1f;
	}
	else
	{
		g_player.move.x -= (sinf(g_player.rotDesh.y) * g_player.fMove + g_player.move.x) * 0.05f;
	}

	//�R���{0�ɂ���
	g_player.nCombo = 0;

	//�J�E���g�i�߂�A�i�񂾂瑫���炷
	g_player.nFoot++;
	if (g_player.nFoot == 20)
	{
		PlaySound(SOUND_LABEL_FOOTSTEP);
		g_player.nFoot = 0;
	}
	g_player.nNeutralTime = 0;
	g_player.bMove = true;
}

//�ړ����x��
void PlayerMoveZ(void)
{
	if (g_player.bJump == true)
	{
		g_player.move.z -= (cosf(g_player.rotDesh.y) * g_player.fMove + g_player.move.z) * 0.1f;
	}
	else
	{
		g_player.move.z -= (cosf(g_player.rotDesh.y) * g_player.fMove + g_player.move.z) * 0.05f;
	}
}

//�ړ����x�ቺ��
void PlayerSlowX(void)
{
	if (g_player.bJump == true)
	{
		g_player.move.x -= g_player.move.x * 0.1f;
	}
	else
	{
		g_player.move.x -= g_player.move.x * 0.05f;
	}

	//�j���[�g�����J�E���g�i�߂�
	g_player.nNeutralTime++;
	if (g_player.nNeutralTime > 100)
	{
		g_player.nNeutralTime = 100;
	}
	g_player.bMove = false;
}

//�ړ����x�ቺ�c
void PlayerSlowZ(void)
{
	if (g_player.bJump == true)
	{
		g_player.move.z -= g_player.move.z * 0.1f;
	}
	else
	{
		g_player.move.z -= g_player.move.z * 0.05f;
	}
}

//���[�V������؂�ւ���֐�
void MotionChange(MOTIONTYPE motiontype)
{
	g_player.Oldmotion = g_player.motionType;
	g_player.motionType = motiontype;
	g_player.MotionInfo = g_player.aMotionInfo[motiontype];
	g_player.nCounterMotion = 0;
	g_player.nKey = 0;
	g_player.KeyMove.fPosX = 0.0f;
	g_player.KeyMove.fPosY = 0.0f;
	g_player.KeyMove.fPosZ = 0.0f;
	g_player.nTotalTime = 0;
	g_player.nComboTime = g_player.aMotionInfo[motiontype].nComboTime;
}

//���[�V�����̓���
void PlayerMotion(void)
{
	int nCntParts;
	float fDistance;
	float fHeight;
	g_player.nCounterMotion++;
	g_player.nTotalTime++;
	for (nCntParts = 0; nCntParts < g_player.nNumModel; nCntParts++)
	{
		if (g_player.nCounterMotion == 1) //���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
		{
			if (nCntParts != g_player.nMoveParts)
			{
				g_player.aKeyDiff[nCntParts].fPosX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fPosX - g_player.aModel[nCntParts].pos.x;
				g_player.aKeyDiff[nCntParts].fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fPosY - g_player.aModel[nCntParts].pos.y;
				g_player.aKeyDiff[nCntParts].fPosZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fPosZ - g_player.aModel[nCntParts].pos.z;
			}
			else
			{
				//���b�N�I�����Ă�
				if (g_player.nEnemy != -1)
				{
					//���������̋����v�Z
					fDistance = RockHDistance(g_player.pos, g_player.nEnemy);
					if (fDistance * 1.2f < g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fMove)
					{
						g_player.KeyMove.fPosX = sinf(D3DX_PI + g_player.rot.y) * (fDistance * 1.2f);
						g_player.KeyMove.fPosZ = cosf(D3DX_PI + g_player.rot.y) * (fDistance * 1.2f);
					}
					else
					{
						g_player.KeyMove.fPosX = sinf(D3DX_PI + g_player.rot.y) * g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fMove;
						g_player.KeyMove.fPosZ = cosf(D3DX_PI + g_player.rot.y) * g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fMove;
					}

					//���������̋����v�Z
					fHeight = RockVDistance(g_player.pos, g_player.nEnemy, g_player.fHeight);
					if (fabsf(fHeight) < g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fHeight)
					{
						g_player.KeyMove.fPosY = -fHeight;
					}
					else if(fHeight < 0.0f)
					{
						g_player.KeyMove.fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fHeight;
					}
					else
					{
						g_player.KeyMove.fPosY = -g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fHeight;
					}
				}
				else
				{
					g_player.KeyMove.fPosX = sinf(D3DX_PI + g_player.rot.y) * g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fMove;
					g_player.KeyMove.fPosY = 0.0f;
					g_player.KeyMove.fPosZ = cosf(D3DX_PI + g_player.rot.y) * g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].fMove;
				}
			}
			//�����v�Z
			g_player.aKeyDiff[nCntParts].fRotX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fRotX - g_player.aModel[nCntParts].rot.x;
			if (g_player.aKeyDiff[nCntParts].fRotX <= -D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotX += D3DX_PI * 2;
			}
			else if (g_player.aKeyDiff[nCntParts].fRotX > D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotX -= D3DX_PI * 2;
			}
			g_player.aKeyDiff[nCntParts].fRotY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fRotY - g_player.aModel[nCntParts].rot.y;
			if (g_player.aKeyDiff[nCntParts].fRotY <= -D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotY += D3DX_PI * 2;
			}
			else if (g_player.aKeyDiff[nCntParts].fRotY > D3DX_PI)
			{
				g_player.aKeyDiff[nCntParts].fRotY -= D3DX_PI * 2;
			}
			g_player.aKeyDiff[nCntParts].fRotZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fRotZ - g_player.aModel[nCntParts].rot.z;
			if (g_player.aKeyDiff[nCntParts].fRotZ <= -D3DX_PI)
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
			g_player.aModel[nCntParts].pos.x += g_player.aKeyDiff[nCntParts].fPosX / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
			g_player.aModel[nCntParts].pos.y += g_player.aKeyDiff[nCntParts].fPosY / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
			g_player.aModel[nCntParts].pos.z += g_player.aKeyDiff[nCntParts].fPosZ / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
		}
		else
		{
			if (g_player.KeyMove.fPosX != 0.0f)
			{
				g_player.move.x = g_player.KeyMove.fPosX / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
			}
			if (g_player.KeyMove.fPosY != 0.0f)
			{
				g_player.move.y = g_player.KeyMove.fPosY / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
			}
			if (g_player.KeyMove.fPosZ != 0.0f)
			{
				g_player.move.z = g_player.KeyMove.fPosZ / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
			}
		}
		//�������Z
		g_player.aModel[nCntParts].rot.x += g_player.aKeyDiff[nCntParts].fRotX / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
		g_player.aModel[nCntParts].rot.y += g_player.aKeyDiff[nCntParts].fRotY / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
		g_player.aModel[nCntParts].rot.z += g_player.aKeyDiff[nCntParts].fRotZ / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
		if (g_player.aModel[nCntParts].rot.x >= D3DX_PI)
		{
			g_player.aModel[nCntParts].rot.x -= D3DX_PI * 2;
		}
		else if (g_player.aModel[nCntParts].rot.x < -D3DX_PI)
		{
			g_player.aModel[nCntParts].rot.x += D3DX_PI * 2;
		}
		if (g_player.aModel[nCntParts].rot.y >= D3DX_PI)
		{
			g_player.aModel[nCntParts].rot.y -= D3DX_PI * 2;
		}
		else if (g_player.aModel[nCntParts].rot.y < -D3DX_PI)
		{
			g_player.aModel[nCntParts].rot.y += D3DX_PI * 2;
		}
		if (g_player.aModel[nCntParts].rot.z >= D3DX_PI)
		{
			g_player.aModel[nCntParts].rot.z -= D3DX_PI * 2;
		}
		else if (g_player.aModel[nCntParts].rot.z < -D3DX_PI)
		{
			g_player.aModel[nCntParts].rot.z += D3DX_PI * 2;
		}
	}

	//�L�[�̃t���[�������
	if (g_player.nCounterMotion == g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame)
	{
		//�L�[�̃��[�V���������Z�b�g�A�L�[���Z
		g_player.nCounterMotion = 0;
		g_player.nKey++;

		//�L�[���
		if (g_player.nKey == g_player.MotionInfo.nNumKey)
		{
			//���[�v���Ȃ�
			if (g_player.MotionInfo.bLoop == false)
			{
				//���^�[�����[�V��������Ȃ�
				if (g_player.motionType != MOTIONTYPE_RETURN)
				{
					MotionChange(MOTIONTYPE_RETURN);
				}
				//���^�[�����[�V����
				else
				{
					MotionChange(MOTIONTYPE_NEUTRAL);
					g_player.nCombo = 0;
				}
			}
			//�L�[�����Z�b�g
			g_player.nKey = 0;
		}
	}
}

//�v���C���[�̏ꏊ
D3DXVECTOR3 PlayerPos(void)
{
	return g_player.pos;
}

//�v���C���[�̌���
float PlayerRot(void)
{
	float fRoty;
	fRoty = g_player.rot.y + D3DX_PI;
	if (fRoty > D3DX_PI)
	{
		fRoty -= D3DX_PI * 2;
	}
	return fRoty;
}

//�v���C���[�̖ړI�̌���
float PlayerRotDesh(void)
{
	return g_player.rotDesh.y;
}

//�v���C���[�̈ړ��ʎ擾
float PlayerMove(int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_player.move.x;
		break;
	case 1:
		return g_player.move.y;
		break;
	case 2:
		return g_player.move.z;
		break;
	}
	return 0.0f;
}

//�v���C���[�̃}�g���b�N�X�擾
D3DXMATRIX Playermtx(void)
{
	return g_player.mtxWorld;
}

//�v���C���[�̍U���̓����蔻��̏ꏊ�擾
float CollisionPos(int nNumber, int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_player.MotionInfo.Collision[nNumber].mtxWorld._41;
		break;
	case 1:
		return g_player.MotionInfo.Collision[nNumber].mtxWorld._42;
		break;
	case 2:
		return g_player.MotionInfo.Collision[nNumber].mtxWorld._43;
		break;
	}
	return 0.0f;
}

//���b�N�I�����Ă邩�擾
bool TargetRockon(void)
{
	return g_player.bRock;
}

//���b�N�I���O��
void RemovePlayerRock(void)
{
	g_player.bRock = false;
}

//�v���C���[�̍U���̓����蔻�艽���擾
int NumParts(void)
{
	return g_player.MotionInfo.nNumCol;
}

//�U���̓����蔻��̏ꏊ�ݒ�
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
		}
	}
}

//�U���̓����蔻��
bool CollisionDamage(D3DXVECTOR3 pos, float fRadius)
{
	int nCntCol;
	float fLengthX; //�����蔻��ƓG��X�����̒���
	float fLengthY; //�����蔻��ƓG��Y�����̒���
	float fLengthZ; //�����蔻��ƓG��Z�����̒���
	float fHDistance; //�����蔻��ƓG�̐��������̋���
	float fDistance; //�����蔻��ƓG�̋���
	for (nCntCol = 0; nCntCol < g_player.MotionInfo.nNumCol; nCntCol++)
	{
		if (g_player.MotionInfo.Collision[nCntCol].nStarttime <= g_player.nTotalTime &&
			g_player.nTotalTime < g_player.MotionInfo.Collision[nCntCol].nFinishtime)
		{
			fLengthX = powf(pos.x - g_player.MotionInfo.Collision[nCntCol].mtxWorld._41, 2);
			fLengthY = powf(pos.y + (fRadius / 2) - g_player.MotionInfo.Collision[nCntCol].mtxWorld._42, 2);
			fLengthZ = powf(pos.z - g_player.MotionInfo.Collision[nCntCol].mtxWorld._43, 2);
			fHDistance = fLengthX + fLengthZ;
			fDistance = sqrtf(fLengthY + fHDistance);

			//�����v�Z�A���a���Z��
			if (fDistance <= fRadius + g_player.MotionInfo.Collision[nCntCol].fRadius)
			{
				g_player.nCol = nCntCol;
				return true;
			}
		}
	}
	return false;
}

//�v���C���[�̋O�Րݒ�
void PlayerOrbit(void)
{
	if (g_player.MotionInfo.orbit.nStartTime <= g_player.nTotalTime &&
		g_player.nTotalTime < g_player.MotionInfo.orbit.nFinishTime)
	{
		D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
		//�����蔻��̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.MotionInfo.orbit.TipmtxWorld);

		//�����蔻��̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player.MotionInfo.orbit.pos.x, g_player.MotionInfo.orbit.pos.y, g_player.MotionInfo.orbit.pos.z);
		D3DXMatrixMultiply(&g_player.MotionInfo.orbit.TipmtxWorld, &g_player.MotionInfo.orbit.TipmtxWorld, &mtxTrans);
		
		//�e�̃}�g���b�N�X�擾
		mtxParent = g_player.aModel[g_player.MotionInfo.orbit.nIdxParent].mtxWorld;
		
		//�Z�o�����e�����蔻��̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.MotionInfo.orbit.TipmtxWorld,
			&g_player.MotionInfo.orbit.TipmtxWorld,
			&mtxParent);
		
		//�O�Ղ�ݒ肷�鎞�Ԃ�������
		if (g_player.MotionInfo.orbit.nStartTime < g_player.nTotalTime &&
			g_player.nTotalTime < g_player.MotionInfo.orbit.nFinishTime)
		{
			//�O�Րݒ�
			SetOrbit(D3DXVECTOR3(g_player.aModel[g_player.MotionInfo.orbit.nIdxParent].mtxWorld._41, g_player.aModel[g_player.MotionInfo.orbit.nIdxParent].mtxWorld._42, g_player.aModel[g_player.MotionInfo.orbit.nIdxParent].mtxWorld._43),
				D3DXVECTOR3(g_player.MotionInfo.orbit.TipmtxWorld._41, g_player.MotionInfo.orbit.TipmtxWorld._42, g_player.MotionInfo.orbit.TipmtxWorld._43),
				g_player.MotionInfo.orbit.posOld, g_player.MotionInfo.orbit.TipposOld, g_player.MotionInfo.orbit.nTime);
		}
		g_player.MotionInfo.orbit.posOld = D3DXVECTOR3(g_player.aModel[g_player.MotionInfo.orbit.nIdxParent].mtxWorld._41, g_player.aModel[g_player.MotionInfo.orbit.nIdxParent].mtxWorld._42, g_player.aModel[g_player.MotionInfo.orbit.nIdxParent].mtxWorld._43);
		g_player.MotionInfo.orbit.TipposOld = D3DXVECTOR3(g_player.MotionInfo.orbit.TipmtxWorld._41, g_player.MotionInfo.orbit.TipmtxWorld._42, g_player.MotionInfo.orbit.TipmtxWorld._43);
	}
}

//�G�̕�������
float PlayerLookEnemy(void)
{
	float fRot = 0.0f;
	fRot = RockCamera() - atan2f(g_player.pos.x - EnemyPos(0, g_player.nEnemy), g_player.pos.z - EnemyPos(2, g_player.nEnemy));
	
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

//�G������΂�
D3DXVECTOR3 EnemyClash(D3DXVECTOR3 pos)
{
	float fRot = 0.0f;
	D3DXVECTOR3 clash;
	fRot = atan2f(pos.x - g_player.pos.x, pos.z - g_player.pos.z);
	clash.x = sinf(fRot) * g_player.MotionInfo.Collision[g_player.nCol].fHClash;
	clash.y = g_player.MotionInfo.Collision[g_player.nCol].fVClash;
	clash.z = cosf(fRot) * g_player.MotionInfo.Collision[g_player.nCol].fHClash;
	return clash;
}

//������΂�����
float ClashRot(D3DXVECTOR3 pos)
{
	float fRot = 0.0f;
	fRot = atan2f(pos.x - g_player.pos.x, pos.z - g_player.pos.z);
	return fRot;
}

//�v���C���[��������ԕ���
float PlayerClashRot(D3DXVECTOR3 pos)
{
	float fRot = 0.0f;
	fRot = atan2f(g_player.pos.x - pos.x, g_player.pos.z - pos.z);
	return fRot;
}

//�����蔻��̎���
int DamageTime(void)
{
	return g_player.MotionInfo.Collision[g_player.nCol].nDamageTime;
}

//�_���[�W��
int Damage(void)
{
	return g_player.MotionInfo.Collision[g_player.nCol].nDamage;
}

//���b�N�I�����Ă�G
int PlayerRockEnemy(void)
{
	return g_player.nEnemy;
}

//�ʒu�֌W�ɉ����čU�����ς��
MOTIONTYPE AttackType(float fDistance, float fHeight)
{
	g_player.nCombo++;

	//��������
	if (fDistance > 120.0f)
	{
		//���O�̃��[�V�������ːi
		if (g_player.Oldmotion == MOTIONTYPE_RUSH)
		{
			return MOTIONTYPE_NORMAL;
		}
		//����ȊO
		else
		{
			return MOTIONTYPE_RUSH;
		}
	}
	//��ɂ���
	else if(fHeight < -60.0f)
	{
		return MOTIONTYPE_ARIAIL;
	}
	//���ɂ���
	else if (fHeight > 100.0f)
	{
		return MOTIONTYPE_GROUND;
	}
	//���ӂɓG������
	else if (EnemyNear(g_player.pos, g_player.fHeight) == true)
	{
		//���O�̍U�������ӍU��
		if (g_player.Oldmotion == MOTIONTYPE_ROUND)
		{
			return MOTIONTYPE_NORMAL;
		}
		//����ȊO
		else
		{
			return MOTIONTYPE_ROUND;
		}
	}
	//�ǂ̏������������Ȃ�
	else
	{
		//���O�̃��[�V����������
		if (g_player.Oldmotion == MOTIONTYPE_NORMAL)
		{
			return MOTIONTYPE_RUSH;
		}
		//����ȊO
		else
		{
			return MOTIONTYPE_NORMAL;
		}
	}
	return MOTIONTYPE_NORMAL;
}

//�v���C���[�̑̂̌���
float PlayerPartsRot(void)
{
	return g_player.aModel[0].rot.y;
}

//�v���C���[�̌��݃L�[
int PlayerKey(void)
{
	return g_player.nKey;
}

//�v���C���[�Ƃ̋���
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

//�v���C���[�̍���
float PlayerHeight(void)
{
	return g_player.fHeight;
}

//�v���C���[�̖��G���Ԑݒ�
void PlayerDamageTime(int nDamageTime)
{
	g_player.nDamageTime = nDamageTime;
}

//�v���C���[�̃_���[�W����
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
	float fDistance; //�����蔻��ƓG�̋���
	fLengthX = powf(pos.x - g_player.pos.x, 2);
	fLengthY = powf(pos.y - g_player.pos.y + (g_player.fHeight / 2), 2);
	fLengthZ = powf(pos.z - g_player.pos.z, 2);
	fHDistance = fLengthX + fLengthZ;
	fDistance = sqrtf(fLengthY + fHDistance);
	if (fDistance <= fRadius + g_player.fRadius)
	{
		return true;
	}
	return false;
}

//�_���[�W����
void PlayerDamage(int nDamage, int nDamageTime, float fRoty, D3DXVECTOR3 Clash)
{
	g_player.nHP -= nDamage;
	g_player.nDamageTime = nDamageTime;
	g_player.rot.y = fRoty;
	g_player.rotDesh.y = fRoty;
	g_player.move = Clash;
	if (g_player.nHP > 0)
	{
		MotionChange(MOTIONTYPE_DAMAGE);
	}
	else
	{
		MotionChange(MOTIONTYPE_DIE);
	}
}

//����HP
int PlayerHP(void)
{
	return g_player.nHP;
}

//�ő�HP�ƌ���HP�̊���
float PlayerHPRate(void)
{
	float fHPRate;
	fHPRate = (float)g_player.nHP / (float)g_player.nMaxHP;
	if (fHPRate <= 0)
	{
		return 0.0f;
	}
	return fHPRate;
}

//�|���������Z
void PlayerKillAdd(void)
{
	g_player.nKill++;
}

//�|�������擾
int PlayerKill(void)
{
	return g_player.nKill;
}