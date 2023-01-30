//--------------------------
//Author:�O��q��
//�t�F�[�h�A�E�g�̏���(fade.h)
//--------------------------
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
} FADE;

//�v���g�^�C�v�錾
void InitFade(MODE modeNext);	//������
void UninitFade(void);			//�I��
void UpdateFade(void);			//�X�V
void DrawFade(void);			//�`��
void SetFade(MODE modeNext);	//�t�F�[�h�ݒ�
FADE GetFade(void);				//�t�F�[�h�̏�Ԏ擾
#endif _FADE_H_