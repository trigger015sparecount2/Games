//--------------------------
//Author:�O��q��
//�����̏���(explosion.h)
//--------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitExplosion(void);			//������
void UninitExplosion(void);			//�I��
void UpdateExplosion(void);			//�X�V
void DrawExplosion(void);			//�`��
void SetExplosion(D3DXVECTOR3 pos);	//�ݒ�
void ResetExplosion(void);			//���Z�b�g
#endif _EXPLOSION_H_
