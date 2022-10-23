//---------------------------
//Author:�O��q��
//�A�C�e��(item.h)
//---------------------------
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
//�v���g�^�C�v�錾
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos);
void CollisionItem(D3DXVECTOR3 pos, float fRadius);
void ResetItem(void);
#endif _ITEM_H_