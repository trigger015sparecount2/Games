//---------------------------
//Author:�O��q��
//�A�C�e��(item.h)
//---------------------------
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitItem(void);			//������
void UninitItem(void);			//�I��
void UpdateItem(void);			//�X�V
void DrawItem(void);			//�`��
void SetItem(D3DXVECTOR3 pos);	//�ݒ�
void CollisionItem(D3DXVECTOR3 pos, float fRadius);	//�����蔻��
void ResetItem(void);			//���Z�b�g
#endif _ITEM_H_