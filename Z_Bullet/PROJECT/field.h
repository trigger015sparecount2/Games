//---------------------------
//Author:�O��q��
//�t�B�[���h(field.h)
//---------------------------
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitField(void);	//������
void UninitField(void);		//�I��
void UpdateField(void);		//�X�V
void DrawField(void);		//�`��
bool LandField(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove, float fRadius);	//�����蔻��
#endif _FIELD_H_