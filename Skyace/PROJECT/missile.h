//--------------------------
//Author:�O��q��
//�~�T�C���̏���(missile.h)
//--------------------------
#ifndef _MISSILE_H_
#define _MISSILE_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitMissile(void);		//������
void UninitMissile(void);	//�I��
void UpdateMissile(void);	//�X�V
void DrawMissile(void);		//�`��
void SetMissile(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);	//�ݒ�
void ResetMissile(void);	//���Z�b�g
#endif _MISSILE_H_
