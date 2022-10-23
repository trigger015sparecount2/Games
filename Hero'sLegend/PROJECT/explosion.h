//---------------------------
//Author:�O��q��
//��������(explosion.h)
//---------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#define MAX_EXPLOSION (512)
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nTime;
	float fTex;
	bool bUse;
} Explosion;
//�v���g�^�C�v�錾
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
#endif _EXPLOSION_H_