//---------------------------
//Author:�O��q��
//���C�g(light.h)
//---------------------------
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitLight(void);	//������
void UninitLight(void);		//�I��
void UpdateLight(void);		//�X�V
void SetLight(int nCntLight, D3DXCOLOR col, D3DXVECTOR3 vec);	//�ݒ�
#endif _LIGHT_H_