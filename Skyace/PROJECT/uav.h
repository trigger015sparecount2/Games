//--------------------------
//Author:�O��q��
//�������l�@�̏���(uav.h)
//--------------------------
#ifndef _UAV_H_
#define _UAV_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitUav(void);		//������
void UninitUav(void);	//�I��
void UpdateUav(D3DXVECTOR3 pos, int nLag);		//�X�V
void DrawUav(void);		//�`��
void SetUav(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//�ݒ�
void ResetUav(void);	//���Z�b�g
#endif _UAV_H_
