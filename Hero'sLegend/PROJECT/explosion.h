//---------------------------
//Author:�O��q��
//��������(explosion.h)
//---------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#define MAX_EXPLOSION (512)

//�����G�t�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nTime;				//����
	float fTex;				//�e�N�X�`�����W
	bool bUse;				//�g�p����
} Explosion;

//�v���g�^�C�v�錾
HRESULT InitExplosion(void);		//������
void UninitExplosion(void);			//�I��
void UpdateExplosion(void);			//�X�V
void DrawExplosion(void);			//�`��
void SetExplosion(D3DXVECTOR3 pos);	//�����ݒ�
#endif _EXPLOSION_H_