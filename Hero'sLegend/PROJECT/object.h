//---------------------------
//Author:�O��q��
//���f��(object.h)
//---------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitObject(void);	//������
void UninitObject(void);	//�I��
void UpdateObject(void);	//�X�V
void DrawObject(void);		//�`��
void CollisionObject(D3DXVECTOR3 *pPos, float fRadius, float fHeight);	//�����蔻��
void Setobject(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 rot);			//�ݒu
#endif _OBJECT_H_