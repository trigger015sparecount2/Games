//--------------------------
//Author:�O��q��
//�藠���̏���(cross.h)
//--------------------------
#ifndef _CROSS_H_
#define _CROSS_H_
#include "main.h"

//�藠���̕���
typedef enum
{
	CROSS_UP = 0,
	CROSS_RIGHT,
	CROSS_DOWN,
	CROSS_LEFT,
	MAX_CROSS_ROT
} CROSSROT;

//�v���g�^�C�v�錾
void InitCross(void);	//������
void UninitCross(void);	//�I��
void UpdateCross(void);	//�X�V
void DrawCross(void);	//�`��
void SetCross(D3DXVECTOR3 pos, CROSSROT CrossRot);	//�藠���ݒ�
void ResetCross(void);	//�S������
#endif _CROSS_H_
