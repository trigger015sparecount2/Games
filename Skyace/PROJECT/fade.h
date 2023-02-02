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
	FADE_NONE = 0,	//�ʏ�
	FADE_IN,		//�t�F�[�h�C��
	FADE_OUT,		//�t�F�[�h�A�E�g
	FADE_MAX
} FADE;

//�v���g�^�C�v�錾
void InitFade(MODE modeNext);				//������
void UninitFade(void);						//�I��
void UpdateFade(void);						//�X�V
void DrawFade(void);						//�`��
void SetFade(MODE modeNext, bool bSetMode);	//�ݒ�
#endif _FADE_H_