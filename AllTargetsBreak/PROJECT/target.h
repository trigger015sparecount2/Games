//--------------------------
//Author:�O��q��
//�I�̏���(target.h)
//--------------------------
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitTarget(void);				//������
void UninitTarget(void);			//�I��
void UpdateTarget(void);			//�X�V
void DrawTarget(void);				//�`��
void SetTarget(D3DXVECTOR3 pos);	//�I�ݒ�
bool BreakTarget(D3DXVECTOR3 pos, float fHeight, float fWidth);	//�I���󂳂ꂽ��
void ResetTarget(void);				//�I�S������
int CountTarget(void);				//�I�̐�
#endif _TARGET_H_
