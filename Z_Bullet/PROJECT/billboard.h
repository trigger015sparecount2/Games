//---------------------------
//Author:�O��q��
//�r���{�[�h(billbaurd.h)
//---------------------------
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitBillboard(void);		//������
void UninitBillboard(void);			//�I��
void UpdateBillboard(void);			//�X�V
void DrawBillboard(void);			//�`��
void SetBillboard(D3DXVECTOR3 pos);	//�ݒ�
int CountBoard(void);				//�g�p���J�E���g
D3DXMATRIX Boardmat(void);			//�}�g���b�N�X
void ResetBillbourd(void);			//���Z�b�g
void MoveBourd(D3DXVECTOR3 pos);	//�ړ�������
#endif _BILLBOARD_H_