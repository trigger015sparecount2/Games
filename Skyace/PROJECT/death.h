//--------------------------
//Author:�O��q��
//���ꂽ�Ƃ��̏���(death.h)
//--------------------------
#ifndef _DEATH_H_
#define _DEATH_H_
#include "main.h"
//�v���g�^�C�v�錾
void InitDeath(void);
void UninitDeath(void);
void UpdateDeath(void);
void DrawDeath(void);
void SetDeath(D3DXVECTOR3 pos, bool bSound);
void ResetDeath(void);
#endif _DEATH_H_
