//--------------------------
//Author:�O��q��
//�I�̏���(target.h)
//--------------------------
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"
//�v���g�^�C�v�錾
void InitTarget(void);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);
void SetTarget(D3DXVECTOR3 pos);
bool BreakTarget(D3DXVECTOR3 pos, float fHeight, float fWidth);
void ResetTarget(void);
int CountTarget(void);
#endif _TARGET_H_
