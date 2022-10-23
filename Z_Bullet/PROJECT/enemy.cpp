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
#include "meshfield.h"
#include "object.h"
#include "rockon.h"
#include "player.h"
#include "wall.h"
#include "particle.h"
#include "fade.h"
#include "billboard.h"
#include "ui.h"
#include "sound.h"

//�}�N����`
#define CHARAFILENAME1 "data/motion_bird.txt"
#define CHARAFILENAME2 "data/motion_dog.txt"
#define CHARAFILENAME3 "data/motion_zombe.txt"
#define CHARAFILENAME4 "data/motion_spider.txt"
#define MAX_ENEMY (32)

//���[�V�����̎��
typedef enum
{
	ENEMYMOTION_NEUTRAL = 0,
	ENEMYMOTION_WALK,
	ENEMYMOTION_ACTION,
	ENEMYMOTION_JUMP,
	ENEMYMOTION_LANDING,
	ENEMYMOTION_DAMAGE,
	ENEMYMOTION_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
	MAX_ENEMYMOTION
} ENEMYMOTION;

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

//���[�V�������̍\����
typedef struct
{
	bool bLoop; //���[�v���邩�ǂ���
	int nNumKey; //�L�[�̑���
	Collision collision[4];
	int nNumCol;
	Orbit orbit[4];
	int nNumOrbit;
	Bang bang[4];
	int nNumBang;
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
	MOTION_INFO aMotionInfo[MAX_ENEMYMOTION]; //���[�V�������
	MOTION_INFO MotionInfo;
	int nNumMotion; //���[�V������
	ENEMYMOTION enemymotion; //���[�V�����^�C�v
	int nKey; //�L�[No.
	int nCounterMotion; //���[�V�����̃J�E���^�[
	KEY aKeyDiff[32]; //���� []���̓p�[�c��
	KEY KeyMove; //���[�V�����J�n����̂��ǂꂾ����������
	float fRadius; //���a
	float fHeight; //����
	float fMove; //�ő呬�x
	float fJump; //�W�����v��
	int nMoveParts; //���f���̊�ɂȂ镔��
	int nTotalTime; //���[�V�����J�n���獇�v�̎���
	int nDamageTime; //��e���Ă���̎���
	int nHP;
	int nMaxHP;
	int nScore;
	int nThinkTime;
	int nMoveTime;
	bool bAtk;
	float fATKRange;
	Enemytype enemytype;
	bool bUse;
} Enemy;

//�v���g�^�C�v�錾
void EnemyLoad(int nCntEnemy, const char *FileName);
void EnemyMove(int nCntEnemy);
void EnemySlow(int nCntEnemy);
void EnemyMotionChange(int nCntEnemy, ENEMYMOTION enemymotion);
void EnemyMotion(int nCntEnemy);
void HitDamage(D3DXVECTOR3 Clash, int nDamage, int nDamageTime, int nCntEnemy);
void EnemyAI(int nCntEnemy);
bool EnemyAtkOver(void);
void CollisionPos(int nCntEnemy);
void CollisionEnemy(int nEnemy, float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move);
float BossHPRate(int nCntEnemy);

//�O���[�o���ϐ�
Enemy g_enemy[MAX_ENEMY]; //�G�̏��
Enemy g_enemymodel[8];
Model g_Emodel[32]; //���f���̏��
int g_nNumEnemyModel; //�L�����Ɏg�����f��������ނ��邩

//����������
HRESULT InitEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].bUse = false;
	}
	EnemyLoad(0, CHARAFILENAME1);
	EnemyLoad(1, CHARAFILENAME2);
	EnemyLoad(2, CHARAFILENAME3);
	EnemyLoad(3, CHARAFILENAME4);
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
}

//�X�V����
void UpdateEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			g_enemy[nCntEnemy].posOld = g_enemy[nCntEnemy].pos;
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
			EnemyAI(nCntEnemy);
			if (g_enemy[nCntEnemy].enemytype == ENEMYTYPE_BIRD)
			{
				if (g_enemy[nCntEnemy].pos.y < 80.0f)
				{
					g_enemy[nCntEnemy].move.y = 0.3f;
				}
				else if(g_enemy[nCntEnemy].pos.y > 120.0f)
				{
					g_enemy[nCntEnemy].move.y = -0.3f;
				}
			}
			else
			{
				g_enemy[nCntEnemy].move.y -= 0.4f;
			}
			g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;
			g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;
			g_enemy[nCntEnemy].pos.z += g_enemy[nCntEnemy].move.z;
			if (g_enemy[nCntEnemy].nDamageTime > 0)
			{
				g_enemy[nCntEnemy].nDamageTime--;
			}
			if (g_enemy[nCntEnemy].nMoveTime <= 0)
			{
				EnemySlow(nCntEnemy);
				if (g_enemy[nCntEnemy].enemymotion == ENEMYMOTION_WALK)
				{
					EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
				}
			}
			if (nCntEnemy == RockNumber())
			{
				MoveRockon(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y + g_enemy[nCntEnemy].fHeight / 2, g_enemy[nCntEnemy].pos.z));
			}
			MoveShadow(g_enemy[nCntEnemy].nShadow, g_enemy[nCntEnemy].pos);
			EnemyMotion(nCntEnemy); //�G�̃��[�V����
			CollisionField(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posOld, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fRadius);
			CollisionWall(&g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fRadius);
			CollisionEnemy(nCntEnemy, g_enemy[nCntEnemy].fRadius, &g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].move);
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
		if (g_enemy[nCntEnemy].bUse == true)
		{
			if (PlayerDistance(g_enemy[nCntEnemy].pos) < 1800.0f)
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
					D3DXMatrixRotationYawPitchRoll(&mtxRot, g_enemy[nCntEnemy].aModel[nCntModel].rot.y + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.y,
						g_enemy[nCntEnemy].aModel[nCntModel].rot.x + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.x, g_enemy[nCntEnemy].aModel[nCntModel].rot.z + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.z);
					D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRot);
					//�p�[�c�̈ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].aModel[nCntModel].pos.x + g_enemy[nCntEnemy].aModel[nCntModel].posOri.x, g_enemy[nCntEnemy].aModel[nCntModel].pos.y + g_enemy[nCntEnemy].aModel[nCntModel].posOri.y, g_enemy[nCntEnemy].aModel[nCntModel].pos.z + g_enemy[nCntEnemy].aModel[nCntModel].posOri.z);
					D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTrans);
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
						//for (int nCntMat = 0; nCntMat < (int)g_enemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
						//{
						if (pMat[nCntMat].pTextureFilename != NULL)
						{
							pDevice->SetTexture(0, g_enemy[nCntEnemy].aModel[nCntModel].TextureModel[nCntTex]);
							nCntTex++;
						}
						else
						{
							//�e�N�X�`���̐ݒ�
							pDevice->SetTexture(0, NULL);
						}
						//}
						//�G�̃��f���i�p�[�c�j�̕`��
						g_enemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
					}
				}
				//�ۑ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
				CollisionPos(nCntEnemy);
			}
		}
	}
}

void EnemyLoad(int nCntEnemy, const char *FileName)
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
	pFile = fopen(FileName, "r");
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
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fJump);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fHeight);
				}
				if (strcmp(&aFile[0], "HP") == 0) //HP
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].nHP);
					g_enemymodel[nCntEnemy].nMaxHP = g_enemymodel[nCntEnemy].nHP;
				}
				if (strcmp(&aFile[0], "SCORE") == 0) //�X�R�A
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].nScore);
				}
				if (strcmp(&aFile[0], "ATKRANGE") == 0) //�U���͈�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fATKRange);
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
						g_enemy[0].nMoveParts = nCntParts;
					}
					if (strcmp(&aFile[0], "INDEX") == 0) //���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						g_enemymodel[nCntEnemy].aModel[nCntParts].pBuffMat = g_Emodel[nIndex].pBuffMat;
						g_enemymodel[nCntEnemy].aModel[nCntParts].nNumMat = g_Emodel[nIndex].nNumMat;
						g_enemymodel[nCntEnemy].aModel[nCntParts].pMesh = g_Emodel[nIndex].pMesh;
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].aModel[nCntParts].nIdxModelParent);
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aModel[nCntParts].posOri.x, &g_enemymodel[nCntEnemy].aModel[nCntParts].posOri.y, &g_enemymodel[nCntEnemy].aModel[nCntParts].posOri.z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aModel[nCntParts].rotOri.x, &g_enemymodel[nCntEnemy].aModel[nCntParts].rotOri.y, &g_enemymodel[nCntEnemy].aModel[nCntParts].rotOri.z);
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
						g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "COLLISIONSET") == 0)
				{
					bColSet = true;
					nCntCol = 0;
				}
				if (strcmp(&aFile[0], "END_COLLISIONSET") == 0)
				{
					g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumCol = nCntCol;
					bColSet = false;
				}
				if (strcmp(&aFile[0], "ORBITSET") == 0)
				{
					bOrbitSet = true;
					nCntOrbit = 0;
				}
				if (strcmp(&aFile[0], "END_ORBITSET") == 0)
				{
					g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumOrbit = nCntOrbit;
					bOrbitSet = false;
				}
				if (strcmp(&aFile[0], "BULLET") == 0)
				{
					bBulletSet = true;
					nCntBullet = 0;
				}
				if (strcmp(&aFile[0], "END_BULLETSET") == 0)
				{
					g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumBang = nCntBullet;
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
							fscanf(pFile, "%d %f %f %f %f %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nIdxModelParent,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].pos.x, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].pos.y, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].pos.z,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].fRadius, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nStarttime, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nFinishtime);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //�����蔻��i����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].fHClash, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].fVClash,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nDamage, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nDamageTime);
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
						fscanf(pFile, "%d %f %f %f %d %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nIdxParent,
							&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.x, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.y,
							&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.z, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nTime,
							&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nStartTime, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nFinishTime);
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
							fscanf(pFile, "%d %f %f %f %d %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nIdxParent,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].pos.x, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].pos.y,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].pos.z, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nStartBul,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nFinishBul, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nLag);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //�e�ہi����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].fHClash, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].fVClash,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nDamage, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nDamageTime);
						}
					}
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "MOVE") == 0) //�ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
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
							fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
	g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].bLoop = false;
	g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].nFrame = 14;
	g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].nNumKey = 1;
	g_enemymodel[nCntEnemy].KeyMove.fPosX = 0.0f;
	g_enemymodel[nCntEnemy].KeyMove.fPosY = 0.0f;
	g_enemymodel[nCntEnemy].KeyMove.fPosZ = 0.0f;
	g_enemymodel[nCntEnemy].nDamageTime = 0;
	for (nCntParts = 0; nCntParts < g_enemymodel[nCntEnemy].nNumModel; nCntParts++)
	{
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosX = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosY = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotX = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotY = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_enemymodel[nCntEnemy].aModel[nCntParts].pBuffMat->GetBufferPointer();
		int nCntTex = 0;
		for (int nCntMat = 0; nCntMat < (int)g_enemymodel[nCntEnemy].aModel[nCntParts].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_enemymodel[nCntEnemy].aModel[nCntParts].TextureModel[nCntTex]);
				nCntTex++;
			}
		}
	}
	g_enemymodel[nCntEnemy].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].rotDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].nTotalTime = 0;
	g_enemymodel[nCntEnemy].nDamageTime = 0;
	g_enemymodel[nCntEnemy].nThinkTime = 100;
	g_enemymodel[nCntEnemy].nMoveTime = 0;
	g_enemymodel[nCntEnemy].bAtk = false;
	g_enemymodel[nCntEnemy].bUse = true;
}

//�ړ����x
void EnemyMove(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.x -= (sinf(g_enemy[nCntEnemy].rotDesh.y) * g_enemy[nCntEnemy].fMove + g_enemy[nCntEnemy].move.x) * 0.1f;
	g_enemy[nCntEnemy].move.z -= (cosf(g_enemy[nCntEnemy].rotDesh.y) * g_enemy[nCntEnemy].fMove + g_enemy[nCntEnemy].move.z) * 0.1f;
}

//�ړ����x�ቺ
void EnemySlow(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.x -= g_enemy[nCntEnemy].move.x * 0.1f;
	g_enemy[nCntEnemy].move.z -= g_enemy[nCntEnemy].move.z * 0.1f;
}

//���[�V������؂�ւ���֐�
void EnemyMotionChange(int nCntEnemy, ENEMYMOTION enemymotion)
{
	g_enemy[nCntEnemy].enemymotion = enemymotion;
	g_enemy[nCntEnemy].nCounterMotion = 0;
	g_enemy[nCntEnemy].MotionInfo = g_enemy[nCntEnemy].aMotionInfo[enemymotion];
	g_enemy[nCntEnemy].nKey = 0;
	g_enemy[nCntEnemy].KeyMove.fPosX = 0.0f;
	g_enemy[nCntEnemy].KeyMove.fPosY = 0.0f;
	g_enemy[nCntEnemy].KeyMove.fPosZ = 0.0f;
	g_enemy[nCntEnemy].nTotalTime = 0;
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
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosX = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosX - g_enemy[nCntEnemy].aModel[nCntParts].pos.x;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosY - g_enemy[nCntEnemy].aModel[nCntParts].pos.y;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosZ = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosZ - g_enemy[nCntEnemy].aModel[nCntParts].pos.z;
			}
			else
			{
				g_enemy[nCntEnemy].KeyMove.fPosX = sinf(D3DX_PI + g_enemy[nCntEnemy].rot.y) * g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].fMove;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosY - g_enemy[nCntEnemy].aModel[nCntParts].pos.y;
				g_enemy[nCntEnemy].KeyMove.fPosZ = cosf(D3DX_PI + g_enemy[nCntEnemy].rot.y) * g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].fMove;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotX - g_enemy[nCntEnemy].aModel[nCntParts].rot.x;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX -= 6.28f;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotY - g_enemy[nCntEnemy].aModel[nCntParts].rot.y;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY -= 6.28f;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotZ - g_enemy[nCntEnemy].aModel[nCntParts].rot.z;
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
			g_enemy[nCntEnemy].aModel[nCntParts].pos.x += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosX / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.z += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosZ / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		}
		else
		{
			g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].KeyMove.fPosX / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].pos.z += g_enemy[nCntEnemy].KeyMove.fPosZ / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		}
		g_enemy[nCntEnemy].aModel[nCntParts].rot.x += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		g_enemy[nCntEnemy].aModel[nCntParts].rot.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		g_enemy[nCntEnemy].aModel[nCntParts].rot.z += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
	}
	if (g_enemy[nCntEnemy].nCounterMotion == g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame)
	{
		g_enemy[nCntEnemy].nCounterMotion = 0;
		g_enemy[nCntEnemy].nKey++;
		if (g_enemy[nCntEnemy].nKey == g_enemy[nCntEnemy].MotionInfo.nNumKey)
		{
			if (g_enemy[nCntEnemy].MotionInfo.bLoop == false)
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

void EnemyAI(int nCntEnemy)
{
	if (g_enemy[nCntEnemy].nThinkTime <= 0)
	{
		//�v���C���[�Ƌ���������Ă���ꍇ�A�v���C���[�̂Ƃ���Ɉړ�����
		if (PlayerDistance(g_enemy[nCntEnemy].pos) > 700.0f + g_enemy[nCntEnemy].fRadius)
		{
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
			g_enemy[nCntEnemy].nMoveTime = 120;
			g_enemy[nCntEnemy].nThinkTime = 120;
			g_enemy[nCntEnemy].bAtk = false;
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
		else if (EnemyAtkOver() == false && g_enemy[nCntEnemy].enemytype != ENEMYTYPE_SPIDER) //�U������G��2�̈ȉ��̏ꍇ
		{
			if (rand() % 3 == 0)
			{
				//�U������
				g_enemy[nCntEnemy].bAtk = true;
				g_enemy[nCntEnemy].nThinkTime = 240;
				g_enemy[nCntEnemy].nMoveTime = 240;
				g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
			}
			else
			{
				//�K���ȕ����Ɉړ�
				g_enemy[nCntEnemy].bAtk = false;
				g_enemy[nCntEnemy].rotDesh.y = D3DX_PI * (float)(rand() % 361 - 180) / 180.0f;
				g_enemy[nCntEnemy].nThinkTime = 120 + (rand() % 10) * 20;
				g_enemy[nCntEnemy].nMoveTime = g_enemy[nCntEnemy].nThinkTime / 2;
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
			}
		}
		else if(g_enemy[nCntEnemy].enemytype != ENEMYTYPE_SPIDER)
		{
			//�K���ȕ����Ɉړ�
			g_enemy[nCntEnemy].bAtk = false;
			g_enemy[nCntEnemy].rotDesh.y = D3DX_PI * (float)(rand() % 361 - 180) / 180.0f;
			g_enemy[nCntEnemy].nThinkTime = 120 + (rand() % 10) * 20;
			g_enemy[nCntEnemy].nMoveTime = g_enemy[nCntEnemy].nThinkTime / 2;
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
		else
		{
			g_enemy[nCntEnemy].bAtk = true;
			g_enemy[nCntEnemy].nThinkTime = 600;
			g_enemy[nCntEnemy].nMoveTime = 420;
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
	}
	else
	{
		g_enemy[nCntEnemy].nThinkTime--;
		g_enemy[nCntEnemy].nMoveTime--;
		if (g_enemy[nCntEnemy].bAtk == true)
		{
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
			if (PlayerDistance(g_enemy[nCntEnemy].pos) < g_enemy[nCntEnemy].fATKRange + g_enemy[nCntEnemy].fRadius + GetPlayerRadius())
			{
				g_enemy[nCntEnemy].bAtk = false;
				g_enemy[nCntEnemy].nMoveTime = 0;
				g_enemy[nCntEnemy].nThinkTime = 420;
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_ACTION);
			}
		}
		if (g_enemy[nCntEnemy].nMoveTime > 0)
		{
			EnemyMove(nCntEnemy);
		}
	}
}

//�����U������̂����̂���̂����ׂ�
bool EnemyAtkOver(void)
{
	int nCntEnemy;
	int nAtkEnemy = 0;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true && g_enemy[nCntEnemy].bAtk == true)
		{
			nAtkEnemy++;
			if (nAtkEnemy > 3)
			{
				return true;
			}
		}
	}
	return false;
}

void CoillisionEnemy(float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move)
{
	float fLengthX; //�N���ƃI�u�W�F�N�g��X�����̒���
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
				g_enemy[nCntEnemy].pos.x += move.x / 5.0f;
				g_enemy[nCntEnemy].pos.z += move.z / 5.0f;
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

bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, D3DXVECTOR3 Clash, int nDamage, int nDamageTime)
{
	int nCntEnemy;
	float fLengthX; //�����蔻��ƓG��X�����̒���
	float fLengthY; //�����蔻��ƓG��Y�����̒���
	float fLengthZ; //�����蔻��ƓG��Z�����̒���
	float fHDistance; //�����蔻��ƓG�̐��������̋���
	float fDistance; //�����蔻��ƓG�̋���
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true && g_enemy[nCntEnemy].nDamageTime <= 0)
		{
			fLengthX = powf(pos.x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthY = powf(pos.y - (g_enemy[nCntEnemy].pos.y + g_enemy[nCntEnemy].fHeight / 2), 2);
			fLengthZ = powf(pos.z - g_enemy[nCntEnemy].pos.z, 2);
			fHDistance = fLengthX + fLengthZ;
			fDistance = sqrtf(fLengthY + fHDistance);
			if (fDistance <= fRadius + g_enemy[nCntEnemy].fHeight / 2)
			{
				HitDamage(Clash, nDamage, nDamageTime, nCntEnemy);
				return true;
			}
		}
	}
	return false;
}

float EnemyPos(int nRot, int nCntEnemy)
{
	switch (nRot)
	{
	case 0:
		return g_enemy[nCntEnemy].pos.x;
		break;
	case 1:
		return g_enemy[nCntEnemy].pos.y + (g_enemy[nCntEnemy].fHeight / 2);
		break;
	case 2:
		return g_enemy[nCntEnemy].pos.z;
		break;
	}
	return 0.0f;
}

int RockOn(D3DXVECTOR3 pos, float fRotY)
{
	int nCntEnemy;
	int nEnemy = -1;
	float fRot;
	float fLengthX;
	float fLengthZ;
	float fDistance;
	float fMinDistance = 20000.0f;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			fRot = fRotY - atan2f(pos.x - g_enemy[nCntEnemy].pos.x, pos.z - g_enemy[nCntEnemy].pos.z);
			if (fRot > D3DX_PI)
			{
				fRot -= D3DX_PI * 2;
			}
			if (fRot < -D3DX_PI)
			{
				fRot += D3DX_PI * 2;
			}
			fLengthX = powf(pos.x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthZ = powf(pos.z - g_enemy[nCntEnemy].pos.z, 2);
			fDistance = sqrtf(fLengthX + fLengthZ);
			if (fabsf(fRot) < D3DX_PI * (15.0f / 180.0f) && 50.0f < fDistance && fDistance < fMinDistance)
			{
				nEnemy = nCntEnemy;
				fMinDistance = fDistance;
			}
		}
	}
	if (nEnemy > -1)
	{
		SetRockon(D3DXVECTOR3(g_enemy[nEnemy].pos.x, g_enemy[nEnemy].pos.y + g_enemy[nEnemy].fHeight / 2, g_enemy[nEnemy].pos.z), nEnemy);
		return nEnemy;
	}
	return -1;
}

float RockBullet(D3DXVECTOR3 pos, int nCntEnemy)
{
	float fRot = 0.0f;
	fRot = atan2f(pos.x - g_enemy[nCntEnemy].pos.x, pos.z - g_enemy[nCntEnemy].pos.z);
	return fRot;
}

void SetEnemy(D3DXVECTOR3 pos, Enemytype enemyType)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == false)
		{
			g_enemy[nCntEnemy] = g_enemymodel[enemyType];
			g_enemy[nCntEnemy].enemytype = enemyType;
			g_enemy[nCntEnemy].pos = pos;
			if (enemyType == ENEMYTYPE_BIRD)
			{
				g_enemy[nCntEnemy].pos.y += 90.0f;
			}
			if (enemyType == ENEMYTYPE_SPIDER)
			{
				BossHPUISet();
				BossHPUI(BossHPRate(nCntEnemy));
			}
			g_enemy[nCntEnemy].nShadow = SetShadow(pos, g_enemymodel[enemyType].fRadius);
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
			PlaySound(SOUND_LABEL_RESPORN);
			SetParticle(g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fHeight);
			break;
		}
	}
}

void HitDamage(D3DXVECTOR3 Clash, int nDamage, int nDamageTime, int nCntEnemy)
{
	g_enemy[nCntEnemy].move = Clash;
	g_enemy[nCntEnemy].nHP -= nDamage;
	g_enemy[nCntEnemy].nDamageTime = nDamageTime;
	g_enemy[nCntEnemy].rot.y = ClashRot(g_enemy[nCntEnemy].pos);
	g_enemy[nCntEnemy].rotDesh.y = g_enemy[nCntEnemy].rot.y;
	EnemyMotionChange(nCntEnemy, ENEMYMOTION_DAMAGE);
	g_enemy[nCntEnemy].nMoveTime = 0;
	g_enemy[nCntEnemy].nThinkTime = 9000;
	if (g_enemy[nCntEnemy].enemytype == ENEMYTYPE_SPIDER)
	{
		BossHPUI(BossHPRate(nCntEnemy));
	}
	if (g_enemy[nCntEnemy].nHP <= 0)
	{
		PlaySound(SOUND_LABEL_DEATH);
		ScoreAdd(g_enemy[nCntEnemy].nScore);
		g_enemy[nCntEnemy].bUse = false;
		RemoveShadow(g_enemy[nCntEnemy].nShadow);
		SetParticle(g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fHeight);
		if (g_enemy[nCntEnemy].enemytype == ENEMYTYPE_SPIDER)
		{
			SetFade(MODE_RESULT);
		}
	}
}

void CollisionPos(int nCntEnemy)
{
	int nCntCol;
	for (nCntCol = 0; nCntCol < g_enemy[nCntEnemy].MotionInfo.nNumCol; nCntCol++)
	{
		if (g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nStarttime <= g_enemy[nCntEnemy].nTotalTime &&
			g_enemy[nCntEnemy].nTotalTime < g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nFinishtime)
		{
			D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X
			//�����蔻��̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld);
			//�����蔻��̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].pos.x, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].pos.y, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].pos.z);
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld, &g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld, &mtxTrans);
			//�e�̃}�g���b�N�X�擾
			mtxParent = g_enemy[nCntEnemy].aModel[g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nIdxModelParent].mtxWorld;
			//�Z�o�����e�����蔻��̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld,
				&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld,
				&mtxParent);
			if (PlayerDamage(D3DXVECTOR3(g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld._41, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld._42, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld._43),
				g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fRadius) == true)
			{
				float fRoty;
				D3DXVECTOR3 Clash;
				fRoty = PlayerClashRot(g_enemy[nCntEnemy].pos);
				Clash.x = sinf(fRoty) * g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fHClash;
				Clash.y = g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fVClash;
				Clash.z = cosf(fRoty) * g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fHClash;
				PlayerDamage(g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nDamage, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nDamageTime, Clash, fRoty);
			}

		}
	}
}

void ResetEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].bUse = false;
	}
}

void CollisionEnemy(int nEnemy, float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move)
{
	float fLengthX; //�N���ƃI�u�W�F�N�g��X�����̒���
	float fLengthZ; //�N���ƃI�u�W�F�N�g��Z�����̒���
	bool bPlusX; //fLengthX���v���X��
	bool bPlusZ; //fLengthZ���v���X��
	float fDistance; //�N���ƃI�u�W�F�N�g�̋���
	float fshort; //�N���ƃI�u�W�F�N�g���������Ă���ꍇ�́A����Ȃ������̔{��
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true && nCntEnemy != nEnemy)
		{
			fLengthX = powf(pPos->x - g_enemy[nCntEnemy].pos.x, 2);
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
				g_enemy[nCntEnemy].pos.x += move.x / 10.0f;
				g_enemy[nCntEnemy].pos.z += move.z / 10.0f;
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

int EnemyNum(void)
{
	int nEnemy = 0;
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_enemy[nCntEnemy].bUse == true)
		{
			nEnemy++;
		}
	}
	return nEnemy;
}

float BossHPRate(int nCntEnemy)
{
	float fRate;
	if (g_enemy[nCntEnemy].nHP > 0)
	{
		fRate = (float)g_enemy[nCntEnemy].nHP / (float)g_enemy[nCntEnemy].nMaxHP;
	}
	else
	{
		fRate = 0.0f;
	}
	return fRate;
}