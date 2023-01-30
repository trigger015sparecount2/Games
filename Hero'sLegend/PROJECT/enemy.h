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
	ENEMYMOTION_NEUTRAL = 0,	//�j���[�g����
	ENEMYMOTION_WALK,			//����
	ENEMYMOTION_ACTION,			//�U��
	ENEMYMOTION_DAMAGE,			//�_���[�W
	ENEMYMOTION_LANDING,		//���n
	ENEMYMOTION_RETURN,			//�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
	MAX_ENEMYMOTION
} ENEMYMOTION;

//�v���g�^�C�v�錾
HRESULT InitEnemy(void);	//������
void UninitEnemy(void);		//�I��
void UpdateEnemy(void);		//�X�V
void DrawEnemy(void);		//�`��
void CoillisionEnemy(float fRadius, D3DXVECTOR3 *pPos, float fHeight);	//�G�Ƃ̓����蔻��
float EnemyPos(int nRot, int nCntEnemy);			//�G�̏ꏊ�擾
int RockOn(D3DXVECTOR3 pos);						//���b�N�I������
float RockAttack(D3DXVECTOR3 pos, int nCntEnemy);	//���b�N�I�����̍U��
void SetEnemy(D3DXVECTOR3 pos, int nType);			//�G�ݒ�
bool EndBattle(void);		//�킢�I��
float RockHDistance(D3DXVECTOR3 pos, int nEnemy);	//���������̋���
float RockVDistance(D3DXVECTOR3 pos, int nEnemy, float fHeight);		//���������̋���
float RockEnemyHeight(int nCntEnemy);				//�G�̐g��
bool EnemyNear(D3DXVECTOR3 pos, float fHeight);		//�G���߂��ɂ��邩
D3DXVECTOR3 ECollisionPos(void);	//�G�̍U���̓����蔻��̃}�g���b�N�X�擾
void ResetEnemy(void);		//�G���Z�b�g
int EnemyNum(void);			//�G�̐�
#endif _ENEMY_H_