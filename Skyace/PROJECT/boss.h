//--------------------------
//Author:�O��q��
//�{�X�̏���(boss.h)
//--------------------------
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"

//�}�N����`
#define MAX_BOSS (16)   //�G�̍ő吔

typedef enum
{
	BOSS_XU_44 = 0,
	BOSS_SEAGULL,
	BOSS_XU_80,
	BOSS_ENGINE,
	MAX_BOSS_TYPE
} BOSSTYPE;

typedef enum
{
	BOSSSTATE_NORMAL = 0,
	BOSSSTATE_DAMAGE,
	BOSSSTATE_BARRIER,
	BOSSSTATE_DEATH,
	BOSSSTATE_MAX
} BOSSSTATE;

//�G�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;   //�ʒu
	BOSSTYPE type;     //���
	BOSSSTATE state;   //�G�̏��
	int nCounterState; //��ԊǗ��̃J�E���^�[
	int nfire;
	int nLife;         //�̗�
	int nScore;        //���_
	int nTime;
	int nBulletTime;
	int nLaserTime;
	float fSmall;
	bool bLeft;
	bool bUp;
	bool bUse;         //�g�p�����ۂ�
	bool bMissile;     //�~�T�C���ǔ��t���O
	bool bBarrier;
} Boss;

//�v���g�^�C�v�錾
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, BOSSTYPE enemytype);
Boss *GetBoss(void);
void HitBoss(int nCntBoss, int nDamage, bool bSpecail);
void ResetBoss(void);
#endif _BOSS_H_