//------------------------
//Author:�O��q��
//UI����(ui.h)
//------------------------
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitUi(void);			//������
void UninitUi(void);		//�I��
void UpdateUi(void);		//�X�V
void DrawUi(void);			//�`��
void AddScore(int nValue);	//�X�R�A���Z
void AddKill(void);			//���Đ����Z
void ResetUi(void);			//���Z�b�g
int Score(void);			//�X�R�A�擾
int Kill(void);				//���Đ��擾
void NextStage(void);		//���̃X�e�[�W�Ɉڍs����
#endif _UI_H_
