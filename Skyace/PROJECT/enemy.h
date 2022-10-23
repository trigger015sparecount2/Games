//--------------------------
//Author:�O��q��
//�G�̏���(enemy.h)
//--------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//�}�N����`
#define MAX_ENEMY (128)   //�G�̍ő吔
#define ENEMY_BLOCK (80)  //�G�̑傫��
#define SHADOW_ENEMY_BLOCK (30)  //�G�̉e�̑傫��

typedef enum
{
	ENEMY_XU_5 = 0,
	ENEMY_XU_17,
	ENEMY_XU_37,
	ENEMY_XU_57,
	MAX_ENEMY_TYPE
} ENEMYTYPE;

typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
} ENEMYSTATE;

typedef enum
{
	WAY_UP = 0,
	WAY_RIGHT,
	WAY_DOWN,
	WAY_LEFT,
	WAY_MAX
} WAY;

//�G�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;   //�ʒu
	ENEMYTYPE type;    //���
	D3DXVECTOR3 move;  //������
	ENEMYSTATE state;  //�G�̏��
	float fRoll[4];           //����
	int nCounterState; //��ԊǗ��̃J�E���^�[
	int nLife;         //�̗�
	int nScore;        //���_
	bool bPrize;       //�v���C�Y�������Ă��邩
	bool bUse;         //�g�p�����ۂ�
	bool bMissile;     //�~�T�C���ǔ��t���O
} Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE enemytype, D3DXVECTOR3 move, bool bPrize, WAY way);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage, bool bSpecail);
void ResetEnemy(void);
#endif _ENEMY_H_