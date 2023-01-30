//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
// �T�E���h���� [sound.h]
// Author :�O��q��
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// �^�C�g��BGM
		SOUND_LABEL_STAGE1BGM,		// ����
		SOUND_LABEL_STAGE2BGM,		// ����
		SOUND_LABEL_STAGE3BGM,		// ����
		SOUND_LABEL_BOSS1BGM,		// �{�X
		SOUND_LABEL_BOSS2BGM,		// �{�X
		SOUND_LABEL_BOSS3BGM,		// �{�X
		SOUND_LABEL_RESULTBGM,		// ���U���g
		SOUND_LABEL_AIRCRAFTDAMAGE,	// �v���C���[�̃_���[�W
		SOUND_LABEL_BOMB,			// �w����
		SOUND_LABEL_BUY,			// �{����
		SOUND_LABEL_CANCEL,			// �L�����Z����
		SOUND_LABEL_CHOICE,			// �I����
		SOUND_LABEL_ENEMYDAMAGE,	// �G�̃_���[�W
		SOUND_LABEL_ENEMYSHATDOWN,	// �G���Ŏ�
		SOUND_LABEL_GUN,			// �U����
		SOUND_LABEL_PAUSE,			// �|�[�Y
		SOUND_LABEL_PINCH,			// �s���`��
		SOUND_LABEL_RETURNSET,		// �����߂��Z�b�g
		SOUND_LABEL_RETURN,			// �����߂�
		SOUND_LABEL_YES,			// ���艹
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();

	static HRESULT Init(HWND hWnd);			//������
	static void Uninit();					//�I��
	static HRESULT Play(SOUND_LABEL label);	//�Đ�
	static void Stop(SOUND_LABEL label);	//�I�������Ȓ�~
	static void Stop();						//�S��~

	//���ʒ���
	static void ControlVoice(SOUND_LABEL label, float fVolume)
	{
		m_apSourceVoice[label]->SetVolume(fVolume);
	}

private:
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;
	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

																	// �e���f�ނ̃p�����[�^
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif
