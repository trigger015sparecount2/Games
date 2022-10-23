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
	SOUND_LABEL_BGM001,			// �X�e�[�WBGM
	SOUND_LABEL_BGM002,			// ����BGM
	SOUND_LABEL_BGM003,			// ���sBGM
	SOUND_LABEL_FOOTSTEP,		//����
	SOUND_LABEL_CANCEL,			// �L�����Z����
	SOUND_LABEL_TARGETBREAK,	//�I�j��
	SOUND_LABEL_THROW,			////�藠��������
	SOUND_LABEL_CROSSBLOCK,		//�藠�����u���b�N�Ɏh�������Ƃ��̉�
	SOUND_LABEL_WARP,			//���[�v��
	SOUND_LABEL_PAUSE,			// �|�[�Y��
	SOUND_LABEL_YES,			// ���艹
	SOUND_LABEL_JUMP,			// �W�����v��
	SOUND_LABEL_BLOCKCLASH,		// �u���b�N���ˉ�
	SOUND_LABEL_CHOICE,			//�I����
	SOUNT_LABEL_COUNTDOWN,		//���Ԃ����Ȃ��Ƃ�
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
