//--------------------------
//Author:�O��q��
//�w�i�̏���(bg.h)
//--------------------------
#ifndef _BG_H_
#define _BG_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitBg(void);		//������
void UninitBg(void);	//�I��
void UpdateBg(void);	//�X�V
void DrawBg(void);		//�`��
void SetBg(int ntype, bool bscroll);	//�w�i�ݒ�
void ScrollBg(bool bscroll);			//�X�N���[���ݒ�
#endif _BG_H_
