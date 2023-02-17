//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
// �T�E���h���� [sound.h]
// Author :�O��q��
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#define MAX_SOUND (64)

class CSound
{
public:
	CSound();
	~CSound();

	static HRESULT Init(HWND hWnd);		//������
	static void Uninit();				//�I��
	static HRESULT Play(int nlabel);	//�Đ�
	static void Stop(int nlabel);		//1�Ȓ�~
	static void Stop();					//�S��~
	static HRESULT SetParamData(char aSoundName[64], int nLoop, int nLabel);	//�ȓǂݍ���
	static void SetSoundNum(int nSound);	//���Ȃ��ݒ�

	//���ʒ���
	static void ControlVoice(int nlabel, float fVolume) { m_apSourceVoice[nlabel]->SetVolume(fVolume); }

private:
	//�����̏��
	typedef struct
	{
		char filename[64];		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g 0�Ń��[�v���Ȃ��@-1�Ŗ������[�v
	} PARAM;

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	//�`�F�b�N�`�����N
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	//�`�����N�f�[�^�ǂ�
	//static HRESULT LoadSoundFile(const char *aFileName);
	static IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[MAX_SOUND];		// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[MAX_SOUND];						// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[MAX_SOUND];						// �I�[�f�B�I�f�[�^�T�C�Y
	static int m_nNumSound;

	// �e���f�ނ̃p�����[�^
	static PARAM m_aParam[MAX_SOUND];
};
#endif
