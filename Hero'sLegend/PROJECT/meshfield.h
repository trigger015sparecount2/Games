//---------------------------
//Author:�O��q��
//���b�V���t�B�[���h(mesufield.h)
//---------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitMeshfield(void);	//������
void UninitMeshfield(void);		//�I��
void UpdateMeshfield(void);		//�X�V
void DrawMeshfield(void);		//�`��
bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius);	//�����蔻��
#endif _MESHFIELD_H_