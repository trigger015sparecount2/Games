//---------------------------
//Author:�O��q��
//�e(shadow.h)
//---------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#define MAX_SHADOW (128)
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 rot; //����
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nLength;
	float fRadius;
	bool bUse;
}Shadow ;
//�v���g�^�C�v�錾
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, float fRadius);
void MoveShadow(int nShadow, D3DXVECTOR3 pos);
void RemoveShadow(int nShadow);
void ResetShadow(void);
#endif _SHADOW_H_