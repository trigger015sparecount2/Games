//--------------------------
//Author:�O��q��
//�e�ۂ̏���(bullet.h)
//--------------------------
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
//�v���g�^�C�v�錾
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nDamage, int nDamageTime);
int CountBullet(void);
bool CollisionBullet(D3DXVECTOR3 pos, float fRadius);
void ResetBullet(void);
#endif _BULLET_H_