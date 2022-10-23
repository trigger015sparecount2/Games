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
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext, bool bSetMode);
#endif _FADE_H_