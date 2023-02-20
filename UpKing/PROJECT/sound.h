//＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋
// サウンド処理 [sound.h]
// Author :三上航世
//＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋＋
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#define MAX_SOUND (64)

class CSound
{
public:
	CSound();
	~CSound();

	static HRESULT Init(HWND hWnd);		//初期化
	static void Uninit();				//終了
	static HRESULT Play(int nlabel);	//再生
	static void Stop(int nlabel);		//1曲停止
	static void Stop();					//全停止
	static HRESULT SetParamData(char aSoundName[64], int nLoop, int nLabel);	//曲読み込み
	static void SetSoundNum(int nSound);	//何曲か設定

	//音量調整
	static void ControlVoice(int nlabel, float fVolume) { m_apSourceVoice[nlabel]->SetVolume(fVolume); }

private:
	//音声の情報
	typedef struct
	{
		char filename[64];		// ファイル名
		int nCntLoop;		// ループカウント 0でループしない　-1で無限ループ
	} PARAM;

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	//チェックチャンク
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	//チャンクデータ読む
	//static HRESULT LoadSoundFile(const char *aFileName);
	static IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[MAX_SOUND];		// ソースボイス
	static BYTE *m_apDataAudio[MAX_SOUND];						// オーディオデータ
	static DWORD m_aSizeAudio[MAX_SOUND];						// オーディオデータサイズ
	static int m_nNumSound;

	// 各音素材のパラメータ
	static PARAM m_aParam[MAX_SOUND];
};
#endif
