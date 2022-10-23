//---------------------------
//Author:�O��q��
//�r���{�[�h(billbaurd.h)
//---------------------------
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#define MAX_BILLBOURD (32)
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	bool bUse;
} Billboard;
//�v���g�^�C�v�錾
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos);
int CountBoard(void);
#endif _BILLBOARD_H_