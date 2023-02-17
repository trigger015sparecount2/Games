//---------------------------
//Author:�O��q��
//�G�i�K�w�\������j(enemy.h)
//---------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//�G�̎��
typedef enum
{
	ENEMYTYPE_BIRD = 0,
	ENEMYTYPE_DOG,
	ENEMYTYPE_ZOMBE,
	ENEMYTYPE_SPIDER,
	ENEMYTYPE_MAX
} Enemytype;

//�v���g�^�C�v�錾
HRESULT InitEnemy(void);	//������
void UninitEnemy(void);		//�I��
void UpdateEnemy(void);		//�X�V
void DrawEnemy(void);		//�`��
void CoillisionEnemy(float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move);	//�G�Ƃ̓����蔻��
bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, D3DXVECTOR3 Clash, int nDamage, int nDamageTime);	//�_���[�W�Ƃ̓����蔻��
float EnemyPos(int nRot, int nCntEnemy);				//�G�̏ꏊ
int RockOn(D3DXVECTOR3 pos, float fRotY);				//�ǂ̃��b�N�I�����邩
float RockBullet(D3DXVECTOR3 pos, int nCntEnemy);		//���b�N�I�����̒e�̓���
void SetEnemy(D3DXVECTOR3 pos, Enemytype enemyType);	//�G�ݒ�
void ResetEnemy(void);	//���Z�b�g
int EnemyNum(void);		//�G�̐�
#endif _ENEMY_H_