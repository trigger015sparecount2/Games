//---------------------------
//Author:�O��q��
//�p�[�e�B�N������(particle.h)
//---------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitParticle(void);	//������
void UninitParticle(void);	//�I��
void UpdateParticle(void);	//�X�V
void DrawParticle(void);	//�`��
void SetParticle(D3DXVECTOR3 pos, float fHeight);	//�ݒ�
void ResetParticle(void);	//���Z�b�g
#endif _PARTICLE_H_