//---------------------------
//Author:�O��q��
//�p�[�e�B�N������(particle.h)
//---------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"
#define MAX_PARTICLE (256)
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nTime;
	bool bUse;
} Particle;
//�v���g�^�C�v�錾
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos);
#endif _PARTICLE_H_