//---------------------------
//Author:�O��q��
//�e(shadow.h)
//---------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"

#define MAX_SHADOW (128)	//�ő吔�̉e

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 rot; //����
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nLength;
	float fRadius;
	bool bUse;
}Shadow;

//�v���g�^�C�v�錾
HRESULT InitShadow(void);	//������
void UninitShadow(void);	//�I��
void UpdateShadow(void);	//�X�V
void DrawShadow(void);		//�`��
int SetShadow(D3DXVECTOR3 pos, float fRadius);	//�ݒ�
void MoveShadow(int nShadow, D3DXVECTOR3 pos);	//�ړ�
void RemoveShadow(int nShadow);	//�O��
void ResetShadow(void);		//���Z�b�g
#endif _SHADOW_H_