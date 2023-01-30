//---------------------------
//Author:�O��q��
//���b�N�I��(rockon.h)
//---------------------------
#ifndef _ROCKON_H_
#define _ROCKON_H_
#include "main.h"

//���b�N�I���\����
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nNumber;
	bool bUse;
} Rockon;

//�v���g�^�C�v�錾
HRESULT InitRockon(void);	//������
void UninitRockon(void);	//�I��
void UpdateRockon(void);	//�X�V
void DrawRockon(void);		//�`��
void SetRockon(D3DXVECTOR3 pos, int nNumber);	//�ݒ肷��
void MoveRockon(D3DXVECTOR3 pos);	//�ړ�
int RemoveRockon(void);		//���b�N�I���O��
int RockNumber(void);		//���b�N�I�����Ă�G�̔ԍ�
#endif _ROCKON_H_