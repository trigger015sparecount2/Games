//--------------------------
//Author:�O��q��
//�e�ۂ̏���(bullet.h)
//--------------------------
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitBullet(void);	//������
void UninitBullet(void);	//�I��
void UpdateBullet(void);	//�X�V
void DrawBullet(void);		//�`��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nDamage, int nDamageTime);	//�ݒ�
int CountBullet(void);		//�g�p���J�E���g
bool CollisionBullet(D3DXVECTOR3 pos, float fRadius);	//�����蔻��
void ResetBullet(void);		//���Z�b�g
#endif _BULLET_H_