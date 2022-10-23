//---------------------------
//Author:�O��q��
//���f��(player.cpp)
//---------------------------
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "gamepad.h"
#include "bullet.h"
#include "particle.h"
#include "meshfield.h"
#include "object.h"
#include "rockon.h"
#include "player.h"
#include "sound.h"
#include "wall.h"

//�}�N����`
#define CHARAFILENAME "data/motion_armoredge.txt"
#define CHARAFILENAME2 "data/motion_helipod.txt"
#define MAX_ENEMY (64)

//�v���g�^�C�v�錾
void EnemyMoveX(int nCntEnemy);
void EnemyMoveZ(int nCntEnemy);
void EnemySlowX(int nCntEnemy);
void EnemySlowZ(int nCntEnemy);
void EnemyMotionChange(int nCntEnemy, ENEMYMOTION enemymotion);
void EnemyMotion(int nCntEnemy);
void CollisionPos(int nCntEnemy);
void EnemyDamage(int nCntEnemy);
void EnemyAI(int nCntEnemy);
bool EnemyAtkNum(void);

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
	KEY aKey[8]; //�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
} KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop; //���[�v���邩�ǂ���
	int nNumKey; //�L�[�̑���
	Collision Collision[4];
	int nNumCol; //�����蔻��̋��̐�
	Orbit orbit[4];
	int nNumOrbit;
	Bang Bang[4];
	int nNumBul; //�e�̔��ˍ�
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
	Model aModel[8]; //���f���i�p�[�c�j
	int nNumModel; //���f���i�p�[�c�j��
	int nShadow; //�e�̔ԍ�
	bool bMove; //�����Ă��邩
	bool bLand;
	MOTION_INFO aMotionInfo[MAX_ENEMYMOTION]; //���[�V�������
	int nNumMotion; //���[�V������
	ENEMYMOTION enemymotion; //���[�V�����^�C�v
	bool bLoopMotion; //���[�v���邩�ǂ���
	int nNumKey; //�L�[��
	int nKey; //�L�[No.
	int nCounterMotion; //���[�V�����̃J�E���^�[
	KEY aKeyDiff[8]; //���� []���̓p�[�c��
	KEY KeyMove; //���[�V�����J�n����̂��ǂꂾ����������
	float fRadius; //���a
	float fHeight; //����
	float fMove; //�ő呬�x
	float fJump; //�W�����v��
	int nMoveParts; //���f���̊�ɂȂ镔��
	int nTotalTime; //���[�V�����J�n���獇�v�̎���
	int nDamageTime; //��e���Ă���̎���
	int nThinkTime; //�_��������
	D3DXVECTOR3 posDesh; //�ړI�ʒu
	MOTION_INFO motionInfo;
	int nHp;
	int nType;
	bool bUse;
} Enemy;

//�O���[�o���ϐ�
Enemy g_enemy[MAX_ENEMY]; //�G
Enemy g_enemymodel[4]; //�G�̏��
Model g_Emodel[8]; //���f���̏�� []���̓p�[�c��
int g_nNumEnemyModel; //�L�����Ɏg�����f��������ނ��邩

//����������
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntParts = 0;
	int nCntModelParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	int nCntCol = 0;
	int nCntBullet = 0;
	int nNumEnemy = 0;
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
				fscanf(pFile, "%d", &g_nNumEnemyModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f���t�@�C���ǂݍ���
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXLoadMeshFromX(&aFile[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_Emodel[nCntParts].pBuffMat,
					NULL,
					&g_Emodel[nCntParts].nNumMat,
					&g_Emodel[nCntParts].pMesh);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET��
			{
				if (strcmp(&aFile[0], "NUM_PARTS") == 0) //�p�[�c��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fJump);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fHeight);
				}
				if (strcmp(&aFile[0], "HP") == 0) //�̗�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].nHp);
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
						g_enemymodel[nNumEnemy].nMoveParts = nCntParts;
					}
					if (strcmp(&aFile[0], "INDEX") == 0) //���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						g_enemymodel[nNumEnemy].aModel[nCntParts].pBuffMat = g_Emodel[nIndex].pBuffMat;
						g_enemymodel[nNumEnemy].aModel[nCntParts].nNumMat = g_Emodel[nIndex].nNumMat;
						g_enemymodel[nNumEnemy].aModel[nCntParts].pMesh = g_Emodel[nIndex].pMesh;
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].aModel[nCntParts].nIdxModelParent);
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aModel[nCntParts].posOri.x, &g_enemymodel[nNumEnemy].aModel[nCntParts].posOri.y, &g_enemymodel[nNumEnemy].aModel[nCntParts].posOri.z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aModel[nCntParts].rotOri.x, &g_enemymodel[nNumEnemy].aModel[nCntParts].rotOri.y, &g_enemymodel[nNumEnemy].aModel[nCntParts].rotOri.z);
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
						g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "COLLISIONSET") == 0)
				{
					bColSet = true;
					nCntCol = 0;
				}
				if (strcmp(&aFile[0], "END_COLLISIONSET") == 0)
				{
					g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].nNumCol = nCntCol;
					bColSet = false;
				}
				if (strcmp(&aFile[0], "ORBITSET") == 0)
				{
					bOrbitSet = true;
					nCntCol = 0;
				}
				if (strcmp(&aFile[0], "END_ORBITSET") == 0)
				{
					g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].nNumOrbit = nCntOrbit;
					bOrbitSet = false;
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
							fscanf(pFile, "%d %f %f %f %f %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nIdxModelParent,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].pos.x, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].pos.y, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].pos.z,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].fRadius, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nStarttime, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nFinishtime);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //�����蔻��i����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].fHClash, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].fVClash,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nDamage, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nDamageTime);
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
						fscanf(pFile, "%d %f %f %f %d %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nIdxParent,
							&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.x, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.y,
							&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.z, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nTime,
							&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nStartTime, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nFinishTime);
					}
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "MOVE") == 0) //�ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
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
							fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
	g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].bLoop = false;
	g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].nFrame = 14;
	g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].nNumKey = 1;
	g_enemymodel[nNumEnemy].KeyMove.fPosX = 0.0f;
	g_enemymodel[nNumEnemy].KeyMove.fPosY = 0.0f;
	g_enemymodel[nNumEnemy].KeyMove.fPosZ = 0.0f;
	g_enemymodel[nNumEnemy].nDamageTime = 0;
	for (nCntParts = 0; nCntParts < g_enemymodel[nNumEnemy].nNumModel; nCntParts++)
	{
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosX = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosY = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotX = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotY = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_enemymodel[nNumEnemy].aModel[nCntParts].pBuffMat->GetBufferPointer();
		int nCntTex = 0;
		for (int nCntMat = 0; nCntMat < (int)g_enemymodel[nNumEnemy].aModel[nCntParts].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_enemymodel[nNumEnemy].aModel[nCntParts].TextureModel[nCntTex]);
				nCntTex++;
			}
		}
	}
	g_enemymodel[nNumEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].rotDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].bMove = false;
	g_enemymodel[nNumEnemy].bLand = true;
	g_enemymodel[nNumEnemy].nTotalTime = 0;
	g_enemymodel[nNumEnemy].nThinkTime = 120;
	g_enemymodel[nNumEnemy].posDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].bUse = true;

	nNumEnemy++;
	nCntParts = 0;
	nCntMotion = 0;
	nCntKey = 0;
	nCntCol = 0;
	nCntOrbit = 0;
	bOrbit = false;
	bOrbitSet = false;
	bChara = false;
	bParts = false;
	bMotion = false;
	bKey = false;
	bKeySet = false;
	bColSet = false;
	bCol = false;

	pFile = fopen(CHARAFILENAME2, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_nNumEnemyModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f���t�@�C���ǂݍ���
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXLoadMeshFromX(&aFile[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_Emodel[nCntParts].pBuffMat,
					NULL,
					&g_Emodel[nCntParts].nNumMat,
					&g_Emodel[nCntParts].pMesh);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET��
			{
				if (strcmp(&aFile[0], "NUM_PARTS") == 0) //�p�[�c��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fJump);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].fHeight);
				}
				if (strcmp(&aFile[0], "HP") == 0) //�̗�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].nHp);
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
						g_enemymodel[nNumEnemy].nMoveParts = nCntParts;
					}
					if (strcmp(&aFile[0], "INDEX") == 0) //���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						g_enemymodel[nNumEnemy].aModel[nCntParts].pBuffMat = g_Emodel[nIndex].pBuffMat;
						g_enemymodel[nNumEnemy].aModel[nCntParts].nNumMat = g_Emodel[nIndex].nNumMat;
						g_enemymodel[nNumEnemy].aModel[nCntParts].pMesh = g_Emodel[nIndex].pMesh;
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].aModel[nCntParts].nIdxModelParent);
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aModel[nCntParts].posOri.x, &g_enemymodel[nNumEnemy].aModel[nCntParts].posOri.y, &g_enemymodel[nNumEnemy].aModel[nCntParts].posOri.z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aModel[nCntParts].rotOri.x, &g_enemymodel[nNumEnemy].aModel[nCntParts].rotOri.y, &g_enemymodel[nNumEnemy].aModel[nCntParts].rotOri.z);
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
						g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "COLLISIONSET") == 0)
				{
					bColSet = true;
					nCntCol = 0;
				}
				if (strcmp(&aFile[0], "END_COLLISIONSET") == 0)
				{
					g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].nNumCol = nCntCol;
					bColSet = false;
				}
				if (strcmp(&aFile[0], "ORBITSET") == 0)
				{
					bOrbitSet = true;
					nCntCol = 0;
				}
				if (strcmp(&aFile[0], "END_ORBITSET") == 0)
				{
					g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].nNumOrbit = nCntOrbit;
					bOrbitSet = false;
				}
				if (strcmp(&aFile[0], "BULLETSET") == 0)
				{
					bBulletSet = true;
					nCntBullet = 0;
				}
				if (strcmp(&aFile[0], "END_BULLETSET") == 0)
				{
					g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].nNumBul = nCntBullet;
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
							fscanf(pFile, "%d %f %f %f %f %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nIdxModelParent,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].pos.x, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].pos.y, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].pos.z,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].fRadius, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nStarttime, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nFinishtime);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //�����蔻��i����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].fHClash, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].fVClash,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nDamage, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Collision[nCntCol].nDamageTime);
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
						fscanf(pFile, "%d %f %f %f %d %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nIdxParent,
							&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.x, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.y,
							&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.z, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nTime,
							&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nStartTime, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nFinishTime);
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
							fscanf(pFile, "%d %f %f %f %d %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].nIdxParent,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].pos.x, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].pos.y,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].pos.z, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].nStartBul,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].nFinishBul, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].nLag);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //�e�ہi����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].fHClash, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].fVClash,
								&g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].nDamage, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].Bang[nCntBullet].nDamageTime);
						}
					}
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "MOVE") == 0) //�ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
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
							fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &g_enemymodel[nNumEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
	//�uMOTIONTYPE_RETURN�v�́A�j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].bLoop = false;
	g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].nFrame = 14;
	g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].nNumKey = 1;
	g_enemymodel[nNumEnemy].KeyMove.fPosX = 0.0f;
	g_enemymodel[nNumEnemy].KeyMove.fPosY = 0.0f;
	g_enemymodel[nNumEnemy].KeyMove.fPosZ = 0.0f;
	g_enemymodel[nNumEnemy].nDamageTime = 0;
	for (nCntParts = 0; nCntParts < g_enemymodel[nNumEnemy].nNumModel; nCntParts++)
	{
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosX = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosY = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotX = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotY = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = g_enemymodel[nNumEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_enemymodel[nNumEnemy].aModel[nCntParts].pBuffMat->GetBufferPointer();
		int nCntTex = 0;
		for (int nCntMat = 0; nCntMat < (int)g_enemymodel[nNumEnemy].aModel[nCntParts].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_enemymodel[nNumEnemy].aModel[nCntParts].TextureModel[nCntTex]);
				nCntTex++;
			}
		}
	}
	g_enemymodel[nNumEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].rotDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].bMove = false;
	g_enemymodel[nNumEnemy].bLand = true;
	g_enemymodel[nNumEnemy].nTotalTime = 0;
	g_enemymodel[nNumEnemy].nThinkTime = 120;
	g_enemymodel[nNumEnemy].posDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nNumEnemy].bUse = true;
	return S_OK;
}

//�I������
void UninitEnemy(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < g_nNumEnemyModel; nCntModel++)
	{
		//�e�N�X�`���̔j��
		if (g_Emodel[nCntModel].pMesh != NULL)
		{
			g_Emodel[nCntModel].pMesh->Release();
			g_Emodel[nCntModel].pMesh = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_Emodel[nCntModel].pBuffMat != NULL)
		{
			g_Emodel[nCntModel].pBuffMat->Release();
			g_Emodel[nCntModel].pBuffMat = NULL;
		}
	}
	for (nCntModel = 0; nCntModel < MAX_ENEMY; nCntModel++)
	{
		if (g_enemy[nCntModel].bUse == true)
		{
			g_enemy[nCntModel].bUse = false;
		}
	}
}

//�X�V����
void UpdateEnemy(void)
{
	int nCntEnemy;
	bool bLand;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			g_enemy[nCntEnemy].posOld = g_enemy[nCntEnemy].pos;
			bLand = g_enemy[nCntEnemy].bLand;
			EnemyAI(nCntEnemy);
			if (g_enemy[nCntEnemy].rot.y >= D3DX_PI)
			{
				g_enemy[nCntEnemy].rot.y -= D3DX_PI * 2;
			}
			if (g_enemy[nCntEnemy].rot.y < -D3DX_PI)
			{
				g_enemy[nCntEnemy].rot.y += D3DX_PI * 2;
			}
			if (g_enemy[nCntEnemy].rotDesh.y >= D3DX_PI)
			{
				g_enemy[nCntEnemy].rotDesh.y -= D3DX_PI * 2;
			}
			if (g_enemy[nCntEnemy].rotDesh.y < -D3DX_PI)
			{
				g_enemy[nCntEnemy].rotDesh.y += D3DX_PI * 2;
			}
			if (g_enemy[nCntEnemy].rot.y != g_enemy[nCntEnemy].rotDesh.y)
			{
				if (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y < -3.14f)
				{
					g_enemy[nCntEnemy].rot.y += (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y + 6.28f) * 0.14f;
				}
				else if (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y > 3.14f)
				{
					g_enemy[nCntEnemy].rot.y += (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y - 6.28f) * 0.14f;
				}
				else
				{
					g_enemy[nCntEnemy].rot.y += (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y) * 0.14f;
				}
			}
			if (g_enemy[nCntEnemy].bMove == false)
			{
				EnemySlowX(nCntEnemy);
				EnemySlowZ(nCntEnemy);
			}
			EnemyMotion(nCntEnemy); //�G�̃��[�V����
			g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;
			g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;
			g_enemy[nCntEnemy].pos.z += g_enemy[nCntEnemy].move.z;
			if (g_enemy[nCntEnemy].nType == 0)
			{
				g_enemy[nCntEnemy].move.y -= 0.4f;
			}
			else if(g_enemy[nCntEnemy].pos.y <= 120.0f)
			{
				g_enemy[nCntEnemy].move.y = 0.2f;
			}
			else if (g_enemy[nCntEnemy].pos.y >= 130.0f)
			{
				g_enemy[nCntEnemy].move.y = -0.2f;
			}
			if (g_enemy[nCntEnemy].nDamageTime > 0)
			{
				g_enemy[nCntEnemy].nDamageTime--;
			}
			else if(CollisionDamage(g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fHeight) == true)
			{
				EnemyDamage(nCntEnemy);
			}
			if (nCntEnemy == RockNumber())
			{
				MoveRockon(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y + g_enemy[nCntEnemy].fHeight / 2, g_enemy[nCntEnemy].pos.z));
			}
			MoveShadow(g_enemy[nCntEnemy].nShadow, g_enemy[nCntEnemy].pos);
			CollisionWall(&g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fRadius);
			if (g_enemy[nCntEnemy].nType == 0)
			{
				g_enemy[nCntEnemy].bLand = CollisionField(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posOld, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fRadius);
			}
			if (bLand == false && g_enemy[nCntEnemy].bLand == true)
			{
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_LANDING);
			}
		}
	}
}

//�`�揈��
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;		 //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			 //�}�e���A���f�[�^�ւ̃|�C���^
	int nCntModel;
	pDevice = GetDevice();		 //�f�o�C�X���擾����
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true && CameraDistance() < 3000.0f)
		{
			//�G�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_enemy[nCntEnemy].mtxWorld);
			//�G�̌����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_enemy[nCntEnemy].rot.y, g_enemy[nCntEnemy].rot.x, g_enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].mtxWorld, &g_enemy[nCntEnemy].mtxWorld, &mtxRot);
			//�G�̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].mtxWorld, &g_enemy[nCntEnemy].mtxWorld, &mtxTrans);
			//�G�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_enemy[nCntEnemy].mtxWorld);
			for (nCntModel = 0; nCntModel < g_enemy[nCntEnemy].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotParts, mtxTransParts; //�p�[�c�p�v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
				//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld);
				//�p�[�c�̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotParts, g_enemy[nCntEnemy].aModel[nCntModel].rot.y + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.y,
					g_enemy[nCntEnemy].aModel[nCntModel].rot.x + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.x, g_enemy[nCntEnemy].aModel[nCntModel].rot.z + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.z);
				D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotParts);
				//�p�[�c�̈ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransParts, g_enemy[nCntEnemy].aModel[nCntModel].pos.x + g_enemy[nCntEnemy].aModel[nCntModel].posOri.x, g_enemy[nCntEnemy].aModel[nCntModel].pos.y + g_enemy[nCntEnemy].aModel[nCntModel].posOri.y, g_enemy[nCntEnemy].aModel[nCntModel].pos.z + g_enemy[nCntEnemy].aModel[nCntModel].posOri.z);
				D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransParts);
				//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
				if (g_enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_enemy[nCntEnemy].aModel[g_enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_enemy[nCntEnemy].mtxWorld; //�G�̃}�g���b�N�X��ݒ�
				}
				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&mtxParent);
				//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld);
				//�p�[�c�̌��݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);
				//�p�[�c�̃}�e���A���f�[�^�ւ̃|�C���^�̔��f
				pMat = (D3DXMATERIAL*)g_enemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();
				int nCntMat;
				for (nCntMat = 0; nCntMat < (int)g_enemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
				{
					int nCntTex = 0;
					//�G�̃}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					for (int nCntMat = 0; nCntMat < (int)g_enemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
					{
						if (pMat[nCntMat].pTextureFilename != NULL)
						{
							//�e�N�X�`���̐ݒ�
							pDevice->SetTexture(0, g_enemy[nCntEnemy].aModel[nCntModel].TextureModel[nCntTex]);
							nCntTex++;
						}
						else
						{
							//�e�N�X�`���̐ݒ�
							pDevice->SetTexture(0, NULL);
						}
					}
					//�G�̃��f���i�p�[�c�j�̕`��
					g_enemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}
			if (g_enemy[nCntEnemy].nType == 1)
			{
				int nCntBullet;
				for (nCntBullet = 0; nCntBullet < g_enemy[nCntEnemy].motionInfo.nNumBul; nCntBullet++)
				{
					if (g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nStartBul < g_enemy[nCntEnemy].nTotalTime &&
						g_enemy[nCntEnemy].nTotalTime <= g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nFinishBul)
					{
						g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nBullet--;
						if (g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nBullet <= 0)
						{
							D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
							D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
							//�����蔻��̃��[���h�}�g���b�N�X�̏�����
							D3DXMatrixIdentity(&g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld);
							//�����蔻��̈ʒu�𔽉f
							D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].pos.x, g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].pos.y, g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].pos.z);
							D3DXMatrixMultiply(&g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld, &g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld, &mtxTrans);
							//�e�̃}�g���b�N�X�擾
							mtxParent = g_enemy[nCntEnemy].aModel[g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nIdxParent].mtxWorld;
							//�Z�o�����e�����蔻��̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
							D3DXMatrixMultiply(&g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld,
								&g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld,
								&mtxParent);
							SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld._41, g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld._42, g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].mtxWorld._43),
								D3DXVECTOR3(sinf(g_enemy[nCntEnemy].rot.y) * -10.0f, sinf(g_enemy[nCntEnemy].aModel[g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nIdxParent].rot.x) * 10.0f, cosf(g_enemy[nCntEnemy].rot.y) * -10.0f),
								g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nDamage, g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nDamageTime, g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].fVClash,
								g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].fHClash, g_enemy[nCntEnemy].rot.y);
							g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nBullet = g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nLag;
						}
					}
				}
			}
			CollisionPos(nCntEnemy);
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//�ړ����x��
void EnemyMoveX(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.x -= (sinf(g_enemy[nCntEnemy].rotDesh.y) * g_enemy[nCntEnemy].fMove + g_enemy[nCntEnemy].move.x) * 0.1f;
}

//�ړ����x��
void EnemyMoveZ(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.z -= (cosf(g_enemy[nCntEnemy].rotDesh.y) * g_enemy[nCntEnemy].fMove + g_enemy[nCntEnemy].move.z) * 0.1f;
}

//�ړ����x�ቺ��
void EnemySlowX(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.x -= g_enemy[nCntEnemy].move.x * 0.1f;
}

//�ړ����x�ቺ�c
void EnemySlowZ(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.z -= g_enemy[nCntEnemy].move.z * 0.1f;
}

//���[�V������؂�ւ���֐�
void EnemyMotionChange(int nCntEnemy, ENEMYMOTION enemymotion)
{
	int nCntBullet;
	g_enemy[nCntEnemy].enemymotion = enemymotion;
	g_enemy[nCntEnemy].nNumKey = g_enemy[nCntEnemy].aMotionInfo[enemymotion].nNumKey;
	g_enemy[nCntEnemy].nCounterMotion = 0;
	g_enemy[nCntEnemy].bLoopMotion = g_enemy[nCntEnemy].aMotionInfo[enemymotion].bLoop;
	g_enemy[nCntEnemy].KeyMove.fPosX = 0.0f;
	g_enemy[nCntEnemy].KeyMove.fPosY = 0.0f;
	g_enemy[nCntEnemy].KeyMove.fPosZ = 0.0f;
	g_enemy[nCntEnemy].nTotalTime = 0;
	g_enemy[nCntEnemy].motionInfo = g_enemy[nCntEnemy].aMotionInfo[enemymotion];
	g_enemy[nCntEnemy].nKey = 0;
	for (nCntBullet = 0; nCntBullet < g_enemy[nCntEnemy].aMotionInfo[enemymotion].nNumBul; nCntBullet++)
	{
		g_enemy[nCntEnemy].motionInfo.Bang[nCntBullet].nBullet = 0;
	}
}

void EnemyMotion(int nCntEnemy) //���[�V�����̓���
{
	int nCntParts;
	g_enemy[nCntEnemy].nCounterMotion++;
	g_enemy[nCntEnemy].nTotalTime++;
	for (nCntParts = 0; nCntParts < g_enemy[nCntEnemy].nNumModel; nCntParts++)
	{
		if (g_enemy[nCntEnemy].nCounterMotion == 1) //���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
		{
			if (nCntParts != g_enemy[nCntEnemy].nMoveParts)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosX = g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosX - g_enemy[nCntEnemy].aModel[nCntParts].pos.x;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY = g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosY - g_enemy[nCntEnemy].aModel[nCntParts].pos.y;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosZ = g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosZ - g_enemy[nCntEnemy].aModel[nCntParts].pos.z;
			}
			else
			{
				g_enemy[nCntEnemy].KeyMove.fPosX = sinf(D3DX_PI + g_enemy[nCntEnemy].rot.y) * g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].fMove;
				g_enemy[nCntEnemy].KeyMove.fPosZ = cosf(D3DX_PI + g_enemy[nCntEnemy].rot.y) * g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].fMove;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX = g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotX - g_enemy[nCntEnemy].aModel[nCntParts].rot.x;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX -= 6.28f;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY = g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotY - g_enemy[nCntEnemy].aModel[nCntParts].rot.y;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY -= 6.28f;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ = g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotZ - g_enemy[nCntEnemy].aModel[nCntParts].rot.z;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ -= 6.28f;
			}
		}
		if (nCntParts != g_enemy[nCntEnemy].nMoveParts)
		{
			g_enemy[nCntEnemy].aModel[nCntParts].pos.x += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosX / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.z += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosZ / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		}
		else
		{
			g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].KeyMove.fPosX / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].pos.z += g_enemy[nCntEnemy].KeyMove.fPosZ / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		}
		g_enemy[nCntEnemy].aModel[nCntParts].rot.x += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		g_enemy[nCntEnemy].aModel[nCntParts].rot.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		g_enemy[nCntEnemy].aModel[nCntParts].rot.z += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ / g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
	}
	if (g_enemy[nCntEnemy].nType == 1)
	{
		g_enemy[nCntEnemy].aModel[1].rot.y += 0.6f;
		if (g_enemy[nCntEnemy].aModel[1].rot.y > D3DX_PI)
		{
			g_enemy[nCntEnemy].aModel[1].rot.y -= D3DX_PI * 2;
		}
	}
	if (g_enemy[nCntEnemy].nCounterMotion == g_enemy[nCntEnemy].aMotionInfo[g_enemy[nCntEnemy].enemymotion].aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame)
	{
		g_enemy[nCntEnemy].nCounterMotion = 0;
		g_enemy[nCntEnemy].nKey++;
		if (g_enemy[nCntEnemy].nKey == g_enemy[nCntEnemy].nNumKey)
		{
			if (g_enemy[nCntEnemy].bLoopMotion == false)
			{
				if (g_enemy[nCntEnemy].enemymotion != ENEMYMOTION_RETURN)
				{
					EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
				}
				else
				{
					EnemyMotionChange(nCntEnemy, ENEMYMOTION_NEUTRAL);
				}
			}
			g_enemy[nCntEnemy].nKey = 0;
		}
	}
}

void CoillisionEnemy(float fRadius, D3DXVECTOR3 *pPos, float fHeight)
{
	float fLengthX; //�N���ƃI�u�W�F�N�g��X�����̒���
	float fLengthY;
	float fLengthZ; //�N���ƃI�u�W�F�N�g��Z�����̒���
	bool bPlusX; //fLengthX���v���X��
	bool bPlusZ; //fLengthZ���v���X��
	float fDistance; //�N���ƃI�u�W�F�N�g�̋���
	float fshort; //�N���ƃI�u�W�F�N�g���������Ă���ꍇ�́A����Ȃ������̔{��
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			fLengthX = powf(pPos->x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthY = pPos->y + (fHeight / 2) - g_enemy[nCntEnemy].pos.y + g_enemy[nCntEnemy].fHeight;
			fLengthZ = powf(pPos->z - g_enemy[nCntEnemy].pos.z, 2);
			if (pPos->x - g_enemy[nCntEnemy].pos.x < 0.0f)
			{
				bPlusX = false;
			}
			else
			{
				bPlusX = true;
			}
			if (pPos->z - g_enemy[nCntEnemy].pos.z < 0.0f)
			{
				bPlusZ = false;
			}
			else
			{
				bPlusZ = true;
			}
			fDistance = sqrtf(fLengthX + fLengthZ);
			if (fDistance <= fRadius + g_enemy[nCntEnemy].fRadius) //�I�u�W�F�N�g�ɓ��������Ƃ�
			{
				if (pPos->y + fHeight > g_enemy[nCntEnemy].pos.y && g_enemy[nCntEnemy].pos.y + g_enemy[nCntEnemy].fHeight > pPos->y)
				{
					fLengthX = sqrtf(fLengthX);
					fLengthZ = sqrtf(fLengthZ);
					fshort = (fRadius + g_enemy[nCntEnemy].fRadius) / fDistance - 1.0f;
					fLengthX *= fshort;
					fLengthZ *= fshort;
					if (bPlusX == true)
					{
						pPos->x += fLengthX;
					}
					else
					{
						pPos->x -= fLengthX;
					}
					if (bPlusZ == true)
					{
						pPos->z += fLengthZ;
					}
					else
					{
						pPos->z -= fLengthZ;
					}
				}
			}
		}
	}
}

void EnemyDamage(int nCntEnemy)
{
	g_enemy[nCntEnemy].move = EnemyClash(g_enemy[nCntEnemy].pos);
	g_enemy[nCntEnemy].rotDesh.y = ClashRot(g_enemy[nCntEnemy].pos);
	g_enemy[nCntEnemy].rot.y = ClashRot(g_enemy[nCntEnemy].pos);
	EnemyMotionChange(nCntEnemy, ENEMYMOTION_DAMAGE);
	g_enemy[nCntEnemy].nDamageTime = DamageTime();
	g_enemy[nCntEnemy].bMove = false;
	g_enemy[nCntEnemy].nThinkTime = 80;
	g_enemy[nCntEnemy].nHp -= Damage();
	PlaySound(SOUND_LABEL_DAMAGE);
	if (g_enemy[nCntEnemy].nHp <= 0)
	{
		SetParticle(g_enemy[nCntEnemy].pos);
		RemoveShadow(g_enemy[nCntEnemy].nShadow);
		PlaySound(SOUND_LABEL_DEATH);
		g_enemy[nCntEnemy].bUse = false;
		if (PlayerRockEnemy() == nCntEnemy)
		{
			RemoveRockon();
		}
	}
}

float EnemyPos(int nRot, int nCntEnemy)
{
	switch (nRot)
	{
	case 0:
		return g_enemy[nCntEnemy].pos.x;
		break;
	case 1:
		return g_enemy[nCntEnemy].pos.y;
		break;
	case 2:
		return g_enemy[nCntEnemy].pos.z;
		break;
	}
	return 0.0f;
}

int RockOn(D3DXVECTOR3 pos)
{
	int nCntEnemy;
	int nMinEnemy = -1;
	int nMaxEnemy = -1;
	float fRot;
	float fMinRot = 30.0f;
	float fMaxRot = 0.0f;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			fRot = RockCamera() - atan2f(pos.x - g_enemy[nCntEnemy].pos.x, pos.z - g_enemy[nCntEnemy].pos.z);
			if (fRot > D3DX_PI)
			{
				fRot -= D3DX_PI * 2;
			}
			if (fRot < -D3DX_PI)
			{
				fRot += D3DX_PI * 2;
			}
			if (fabsf(fRot) < fMinRot)
			{
				fMinRot = fabsf(fRot);
				nMinEnemy = nCntEnemy;
			}
			if (fabsf(fRot) > fMaxRot)
			{
				fMaxRot = fabsf(fRot);
				nMaxEnemy = nCntEnemy;
			}
		}
	}

	if (fMinRot < D3DX_PI * (20.0f / 180.0f))
	{
		SetRockon(D3DXVECTOR3(g_enemy[nMinEnemy].pos.x, g_enemy[nMinEnemy].pos.y + g_enemy[nMinEnemy].fHeight / 2, g_enemy[nMinEnemy].pos.z), nMinEnemy);
		return nMinEnemy;
	}
	
	if (fMaxRot > D3DX_PI * (160.0f / 180.0f))
	{
		SetRockon(D3DXVECTOR3(g_enemy[nMaxEnemy].pos.x, g_enemy[nMaxEnemy].pos.y + g_enemy[nMaxEnemy].fHeight / 2, g_enemy[nMaxEnemy].pos.z), nMaxEnemy);
		return nMaxEnemy;
	}
	
	return -1;
}

float RockAttack(D3DXVECTOR3 pos, int nCntEnemy)
{
	float fRot = 0.0f;
	fRot = atan2f(pos.x - g_enemy[nCntEnemy].pos.x, pos.z - g_enemy[nCntEnemy].pos.z);
	return fRot;
}

void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == false)
		{
			g_enemy[nCntEnemy] = g_enemymodel[nType];
			g_enemy[nCntEnemy].pos = pos;
			g_enemy[nCntEnemy].nShadow = SetShadow(pos, g_enemymodel[nType].fRadius);
			g_enemy[nCntEnemy].nType = nType;
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
			break;
		}
	}
}

bool EndBattle(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			return false;
		}
	}
	return true;
}

float RockHDistance(D3DXVECTOR3 pos, int nEnemy)
{
	float fLengthX;
	float fLengthZ;
	float fDistance;
	fLengthX = powf(pos.x - g_enemy[nEnemy].pos.x, 2);
	fLengthZ = powf(pos.z - g_enemy[nEnemy].pos.z, 2);
	fDistance = sqrtf(fLengthX + fLengthX);
	return fDistance;
}

float RockVDistance(D3DXVECTOR3 pos, int nEnemy, float fHeight)
{
	float fLengthY;
	fLengthY = pos.y + (fHeight / 2) - g_enemy[nEnemy].pos.y + (g_enemy[nEnemy].fHeight / 2);
	return fLengthY;
}

float RockEnemyHeight(int nCntEnemy)
{
	return g_enemy[nCntEnemy].fHeight;
}

bool EnemyNear(D3DXVECTOR3 pos, float fHeight)
{
	int nCntEnemy;
	float fLengthX;
	float fLengthY;
	float fLengthZ;
	float fHDistance;
	int nEnemy = 0;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			fLengthX = powf(pos.x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthY = fabsf(pos.y + (fHeight / 2) - g_enemy[nCntEnemy].pos.y + (g_enemy[nCntEnemy].fHeight / 2));
			fLengthZ = powf(pos.z - g_enemy[nCntEnemy].pos.z, 2);
			fHDistance = sqrtf(fLengthX + fLengthZ);
			if (fHDistance < 120.0f && fLengthY < 50.0f)
			{
				nEnemy++;
				if (nEnemy == 2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void EnemyAI(int nCntEnemy)
{
	g_enemy[nCntEnemy].nThinkTime--;
	if (g_enemy[nCntEnemy].nThinkTime <= 0)
	{
		if (g_enemy[nCntEnemy].nType == 0 && PlayerDistance(g_enemy[nCntEnemy].pos) > 200.0f)
		{
			g_enemy[nCntEnemy].posDesh = PlayerPos();
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].posDesh.x, g_enemy[nCntEnemy].pos.z - g_enemy[nCntEnemy].posDesh.z);
			g_enemy[nCntEnemy].bMove = true;
			g_enemy[nCntEnemy].nThinkTime = 600;
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
		else if (g_enemy[nCntEnemy].nType == 1 && PlayerDistance(g_enemy[nCntEnemy].pos) > 600.0f)
		{
			g_enemy[nCntEnemy].posDesh = PlayerPos();
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].posDesh.x, g_enemy[nCntEnemy].pos.z - g_enemy[nCntEnemy].posDesh.z);
			g_enemy[nCntEnemy].bMove = true;
			g_enemy[nCntEnemy].nThinkTime = 600;
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
		else
		{
			if (EnemyAtkNum() == false)
			{
				g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
				g_enemy[nCntEnemy].nThinkTime = 900 + (rand() % 80) * 2;
				if (g_enemy[nCntEnemy].nType == 1)
				{
					g_enemy[nCntEnemy].nThinkTime += 160;
				}
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_ACTION);
			}
			else
			{
				g_enemy[nCntEnemy].nThinkTime = 100 + rand() % 100;
			}
		}
	}
	else
	{
		if (g_enemy[nCntEnemy].bMove == true)
		{
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
			g_enemy[nCntEnemy].posDesh = PlayerPos();
			EnemyMoveX(nCntEnemy);
			EnemyMoveZ(nCntEnemy);
			if (PlayerDistance(g_enemy[nCntEnemy].pos) < 150.0f)
			{
				g_enemy[nCntEnemy].bMove = false;
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
				g_enemy[nCntEnemy].nThinkTime = 700 + (rand() % 40) * 2;
			}
		}
	}
}

void CollisionPos(int nCntEnemy)
{
	int nCntCol;
	for (nCntCol = 0; nCntCol < g_enemy[nCntEnemy].motionInfo.nNumCol; nCntCol++)
	{
		if (g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].nStarttime <= g_enemy[nCntEnemy].nTotalTime &&
			g_enemy[nCntEnemy].nTotalTime < g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].nFinishtime)
		{
			D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
			//�����蔻��̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld);
			//�����蔻��̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].pos.x, g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].pos.y, g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].pos.z);
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld, &g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld, &mtxTrans);
			//�e�̃}�g���b�N�X�擾
			mtxParent = g_enemy[nCntEnemy].aModel[g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].nIdxModelParent].mtxWorld;
			//�Z�o�����e�����蔻��̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld,
				&g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld,
				&mtxParent);
			if (PlayerDamage(D3DXVECTOR3(g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld._41, g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld._42, g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].mtxWorld._43),
				g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].fRadius) == true)
			{
				float fRoty;
				D3DXVECTOR3 Clash;
				fRoty = PlayerClashRot(g_enemy[nCntEnemy].pos);
				Clash.x = sinf(fRoty) * g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].fHClash;
				Clash.y = g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].fVClash;
				Clash.z = cosf(fRoty) * g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].fHClash;
				PlaySound(SOUND_LABEL_DAMAGE);
				PlayerDamage(g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].nDamage, g_enemy[nCntEnemy].motionInfo.Collision[nCntCol].nDamageTime, fRoty, Clash);
			}

		}
	}
}

D3DXVECTOR3 ECollisionPos(void)
{
	return D3DXVECTOR3(g_enemy[0].motionInfo.Collision[1].mtxWorld._41, g_enemy[0].motionInfo.Collision[1].mtxWorld._42, g_enemy[0].motionInfo.Collision[1].mtxWorld._43);
}

bool EnemyAtkNum(void)
{
	int nCntEnemy;
	int nAtkEnemy = 0;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true && g_enemy[nCntEnemy].enemymotion == ENEMYMOTION_ACTION)
		{
			nAtkEnemy++;
			if (nAtkEnemy >= 3)
			{
				return true;
			}
		}
	}
	return false;
}

void ResetEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].bUse = false;
	}
}

int EnemyNum(void)
{
	int nCntEnemy;
	int nEnemy = 0;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			nEnemy++;
		}
	}
	return nEnemy;
}