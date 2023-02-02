//--------------------------
//Author:�O��q��
//�{�X�̏���(boss.h)
//--------------------------
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"

//�}�N����`
#define MAX_BOSS (16)   //�G�̍ő吔

//�{�X�̎��
typedef enum
{
	BOSS_XU_44 = 0,	//�ŏ��̃{�X
	BOSS_SEAGULL,	//2�Ԗڂ̃{�X�{��
	BOSS_XU_80,		//�Ō�̃{�X
	BOSS_ENGINE,	//2�Ԗڂ̃{�X�G���W��
	MAX_BOSS_TYPE
} BOSSTYPE;

//�{�X�̏��
typedef enum
{
	BOSSSTATE_NORMAL = 0,	//�ʏ�
	BOSSSTATE_DAMAGE,		//�_���[�W�H�����
	BOSSSTATE_BARRIER,		//�o���A
	BOSSSTATE_DEATH,		//���ꂽ
	BOSSSTATE_MAX
} BOSSSTATE;

//�G�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	BOSSTYPE type;		//���
	BOSSSTATE state;	//�G�̏��
	int nCounterState;	//��ԊǗ��̃J�E���^�[
	int nfire;			//�G���W���̃o�b�N�t�@�C�A
	int nLife;			//�̗�
	int nScore;			//���_
	int nTime;			//�ŏ��̓o�ꎞ�̎���
	int nBulletTime;	//���܂ł̎���
	int nLaserTime;		//���[�U�[���܂ł̎���
	float fSmall;		//�傫��
	bool bLeft;			//���ɍs����
	bool bUp;			//��ɍs����
	bool bUse;			//�g�p�����ۂ�
	bool bMissile;		//�~�T�C���ǔ��t���O
	bool bBarrier;		//�o���A�g������
} Boss;

//�v���g�^�C�v�錾
void InitBoss(void);	//������
void UninitBoss(void);	//�I��
void UpdateBoss(void);	//�X�V
void DrawBoss(void);	//�`��
void SetBoss(D3DXVECTOR3 pos, BOSSTYPE enemytype);		//�ݒ�
Boss *GetBoss(void);	//�|�C���^�擾
void HitBoss(int nCntBoss, int nDamage, bool bSpecail);	//��������
void ResetBoss(void);	//���Z�b�g
#endif _BOSS_H_