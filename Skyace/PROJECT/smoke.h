//--------------------------
//Author:�O��q��
//���̏���(smoke.h)
//--------------------------
#ifndef _SMOKE_H_
#define _SMOKE_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitSmoke(void);			//������
void UninitSmoke(void);			//�I��
void UpdateSmoke(void);			//�X�V
void DrawSmoke(void);			//�`��
void SetSmoke(D3DXVECTOR3 pos);	//�ݒ�
void ResetSmoke(void);			//���Z�b�g
#endif _SMOKE_H_
