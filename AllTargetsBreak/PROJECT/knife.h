//--------------------------
//Author:�O��q��
//�藠���̏���(knife.h)
//--------------------------
#ifndef _KNIFE_H_
#define _KNIFE_H_
#include "main.h"
typedef enum
{
	KNIFE_UP = 0,
	KNIFE_RIGHT,
	KNIFE_DOWN,
	KNIFE_LEFT,
	MAX_KNIFE_ROT
} KNIFEROT;

//�v���g�^�C�v�錾
void InitKnife(void);
void UninitKnife(void);
void UpdateKnife(void);
void DrawKnife(void);
void SetKnife(D3DXVECTOR3 pos, KNIFEROT KnifeRot);
void ResetKnife(void);
#endif _KNIFE_H_
