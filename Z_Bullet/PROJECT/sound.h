//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
// �T�E���h���� [sound.h]
// Author :�O��q��
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=================================
// �T�E���h�t�@�C��
//=================================
typedef enum
{
	SOUND_LABEL_BGM0 = 0,
	SOUND_LABEL_BGM1,
	SOUND_LABEL_BGM2,
	SOUND_LABEL_GUN,
	SOUND_LABEL_BULLETLOST,
	SOUND_LABEL_DAMAGE,
	SOUND_LABEL_RELOAD,
	SOUND_LABEL_CANCEL,
	SOUND_LABEL_MENU,
	SOUND_LABEL_BUFF,
	SOUND_LABEL_OK,
	SOUND_LABEL_SELECT,
	SOUND_LABEL_RESPORN,
	SOUND_LABEL_DEATH,
	SOUND_LABEL_HEAL,
	SOUND_LABEL_ITEM,
	SOUND_LABEL_MAX
} SOUND_LABEL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
