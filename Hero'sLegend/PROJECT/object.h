//---------------------------
//Author:�O��q��
//���f��(model.h)
//---------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
//�v���g�^�C�v�錾
HRESULT InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void CollisionObject(D3DXVECTOR3 *pPos, float fRadius, float fHeight);
void Setobject(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 rot);
#endif _OBJECT_H_