//=============================================================================
//
// �}�l�[�W�� [Manager.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
//=============================================================================
//�}�N��
//=============================================================================
#define TIME_LIMIT (300)
#define MAX_LIFE (10)

//�O���錾
class CRenderer;
class CKeyboard;
class CMouse;
class CGamePad;

class CTitle;
class CGame;
class CResult;
class CTutorial;
class CGameOver;

class CManager
{
public:

	typedef enum
	{
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_GAMEOVER,
		MODE_MAX,
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer *GetRenderer();
	static CKeyboard *GetKeyboard();
	static CMouse *GetMouse();
	static CGamePad *GetGamepad();

	//���[�h�i�[�E�擾
	static void SetMode(MODE mode);
	static MODE GetMode();

	//�Q�[���I���̃t���O�i�[�E�擾
	static void SetGameEnd(bool GameEnd);
	static bool GetGameEnd() { return m_bGameEnd; }


	//���ꂼ��̃��[�h�n�����
	static CTitle *GetTitle() { return m_pTitle; }
	static CGame *GetGame() { return m_pGame; }
	static CResult *GetResult() { return m_pResult; }
	static CTutorial *GetTutorial() { return m_pTutorial; }
	static CGameOver *GetGameOver() { return m_pGameOver; }


	//�X�R�A�v�Z�p
	static int GetGameTime() { return m_nTime; }
	static void SetGameTime(int nScore);

	//�����L���O���݂̂��ǂ���
	static bool GetRankOnly() { return m_bRankOnly; }
	static void SetRankOnly(bool Set);

	//�����L���O�X�V�֌W
	static bool GetSaveRankOne() { return m_bSaveRankOne; }
	static void SetSaveRankOne(bool Set);

	//�Q�[���N���A�֌W
	static bool GetGameClear() { return m_bGameClear; }
	static void SetGameClear(bool Set);

	//Pause�����ǂ������Ƃ�����
	static void SetPause(bool bFlag);
	static bool GetPause() { return m_bPause; };

private:
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CGamePad *m_pGamepad;

	static int m_nTime;		//�Q�[���I����̃X�R�A���ꎞ�I�Ɋi�[
	static bool m_bGameEnd;		//�Q�[���I��������

	static MODE m_aMode;		//���݂̃��[�h

								//�n�����
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CTutorial *m_pTutorial;
	static CGameOver *m_pGameOver;

	static bool m_bRankOnly;	//�����L���O����
	static bool m_bSaveRankOne;	//�����L���O��񂾂��ʂ��悤��

	static bool m_bGameClear;	//�Q�[���N���A�������ǂ���
	static bool m_bPause;		//Pause�����ǂ���

};

#endif