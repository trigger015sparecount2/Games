//---------------------------
//Author:�O��q��
//�c������(orbit.h)
//---------------------------
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "main.h"

#define MAX_ORBIT (256)	//�ő�c��

//�v���g�^�C�v�錾
HRESULT InitOrbit(void);	//������
void UninitOrbit(void);		//�I��
void UpdateOrbit(void);		//�X�V
void DrawOrbit(void);		//�`��
void SetOrbit(D3DXVECTOR3 pos, D3DXVECTOR3 Tippos, D3DXVECTOR3 posOld, D3DXVECTOR3 TipposOld, int nTime);	//�ݒ�
#endif _ORBIT_H_