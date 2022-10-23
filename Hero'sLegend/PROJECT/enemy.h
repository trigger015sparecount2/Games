//---------------------------
//Author:�O��q��
//�G�i�K�w�\������j(enemy.h)
//---------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//���[�V�����̎��
typedef enum
{
	ENEMYMOTION_NEUTRAL = 0,
	ENEMYMOTION_WALK,
	ENEMYMOTION_ACTION,
	ENEMYMOTION_DAMAGE,
	ENEMYMOTION_LANDING,
	ENEMYMOTION_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
	MAX_ENEMYMOTION
} ENEMYMOTION;

//�v���g�^�C�v�錾
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void CoillisionEnemy(float fRadius, D3DXVECTOR3 *pPos, float fHeight);
float EnemyPos(int nRot, int nCntEnemy);
int RockOn(D3DXVECTOR3 pos);
float RockAttack(D3DXVECTOR3 pos, int nCntEnemy);
void SetEnemy(D3DXVECTOR3 pos, int nType);
bool EndBattle(void);
float RockHDistance(D3DXVECTOR3 pos, int nEnemy);
float RockVDistance(D3DXVECTOR3 pos, int nEnemy, float fHeight);
float RockEnemyHeight(int nCntEnemy);
bool EnemyNear(D3DXVECTOR3 pos, float fHeight);
D3DXVECTOR3 ECollisionPos(void);
void ResetEnemy(void);
int EnemyNum(void);
#endif _ENEMY_H_