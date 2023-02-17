//---------------------------
//Author:�O��q��
//�e(shadow.h)
//---------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitShadow(void);		//������
void UninitShadow(void);		//�I��
void UpdateShadow(void);		//�X�V
void DrawShadow(void);			//�`��
int SetShadow(D3DXVECTOR3 pos, float fRadius);	//�ݒ�
void MoveShadow(int nShadow, D3DXVECTOR3 pos);	//�e�̈ړ�
void RemoveShadow(int nShadow);	//�e�O��
void ResetShadow(void);			//���Z�b�g
#endif _SHADOW_H_