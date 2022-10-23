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
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��BGM
	SOUND_LABEL_BGM001,			// �{�XBGM
	SOUND_LABEL_BGM002,			// �{�XBGM
	SOUND_LABEL_BGM003,			// �{�XBGM
	SOUND_LABEL_BGM004,			// ����BGM
	SOUND_LABEL_BGM005,			// ����BGM
	SOUND_LABEL_BGM006,			// ����BGM
	SOUND_LABEL_SHOT000,		// �V���b�g��
	SOUND_LABEL_BARRIER000,		// �o���A��
	SOUND_LABEL_CANCEL000,		// �L�����Z����
	SOUND_LABEL_ENEMYDOWN000,	// �G�@���ĉ�
	SOUND_LABEL_EXPLOSION000,	// �唚����
	SOUND_LABEL_LASER000,		// ���[�U�[��
	SOUND_LABEL_MISSILE000,		// �~�T�C��������
	SOUND_LABEL_PAUSE000,		// �|�[�Y��
	SOUND_LABEL_RAILGUN000,		// ���[���K����
	SOUND_LABEL_YES000,		    // ���艹
	SOUND_LABEL_CHOICE000,
	SOUND_LABEL_ITEM000,
	SOUND_LABEL_PINCH000,
	SOUND_LABEL_DAMAGE000,
	SOUND_LABEL_MAX,
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
