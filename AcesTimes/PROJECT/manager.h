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

//�O���錾
class CRenderer;
class CKeyboard;
class CGamePad;

class CTitle;
class CSelect;
class CSave;
class CLoad;
class CGame;
class CResult;

class CManager
{
public:
	//���[�h�̎��
	typedef enum
	{
		MODE_TITLE,
		MODE_LOAD,
		MODE_SAVE,
		MODE_SELECT,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	static CRenderer *GetRenderer() { return m_pRenderer; }	//�����_���[�Ԃ�
	static CKeyboard *GetKeyboard() { return m_pKeyboard; }	//�L�[�{�[�h�Ԃ�
	static CGamePad *GetGamepad();							//�Q�[���p�b�h�Ԃ�

	//���[�h�i�[�E�擾
	static void SetMode(MODE mode);
	static MODE GetMode() { return m_aMode; }

	//�Q�[���I���̃t���O�i�[�E�擾
	static void SetGameEnd(bool GameEnd) { m_bGameEnd = GameEnd; }
	static bool GetGameEnd() { return m_bGameEnd; }

	//���ꂼ��̃��[�h�n�����
	static CTitle *GetTitle() { return m_pTitle; }
	static CGame *GetGame() { return m_pGame; }
	static CResult *GetResult() { return m_pResult; }
	static CSelect *GetSelect() { return m_pSelect; }
	static CLoad *GetLoad() { return m_pLoad; }
	static CSave *GetSave() { return m_pSave; }

	//Pause�����ǂ������Ƃ�����
	static void SetPause(bool bFlag) { m_bPause = bFlag; }
	static bool GetPause() { return m_bPause; };

	//���̊i�[�E�擾
	static int GetMoney() { return m_nMoney; }
	static void SetMoney(int nMoney) { m_nMoney = nMoney; }

	//�X�e�[�W���̋��̃��Z�b�g�A�����A�擾
	static void ResetMoney() { m_nGetMoney = 0; }
	static void AddMoney(int nMoney) { m_nGetMoney += nMoney; }
	static int GetStageMoney() { return m_nGetMoney; }

	//�X�R�A�̊i�[�E�擾
	static void SetScore(int nScore) { m_nScore = nScore; }
	static int GetScore() { return m_nScore; }

	//�퓬�@�̎g�p��Ԃ̊i�[�E�擾
	static bool GetAircraft(int nType) { return m_aAircraft[nType]; }
	static void SetAircraft(int nType,bool bAircraft) { m_aAircraft[nType] = bAircraft; }

	//�g�p�\�Ȑ퓬�@�̐��̊i�[�E�擾
	static int GetNumAircraft() { return m_nNumAircraft; }
	static void SetNumAircraft(int nNum) { m_nNumAircraft = nNum; }

	//�퓬�@�̎�ނ̊i�[�E�擾
	static int GetType() { return m_nType; }
	static void SetType(int nType) { m_nType = nType; }

	//�X�e�[�W�̎�ނ̊i�[�E�擾
	static int GetStage() { return m_nStage; }
	static void SetStage(int nStage) { m_nStage = nStage; }

private:
	static CRenderer *m_pRenderer;	//�����_���[
	static CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	static CGamePad *m_pGamepad;	//�Q�[���p�b�h

	static bool m_bGameEnd;			//�Q�[���I��������

	static MODE m_aMode;			//���݂̃��[�h

	//�e���[�h
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CSelect *m_pSelect;
	static CLoad *m_pLoad;
	static CSave *m_pSave;

	static bool m_bPause;		//Pause�����ǂ���

	static int m_nStage;		//�X�e�[�W�̎��
	static int m_nType;			//�퓬�@�̃^�C�v
	static int m_nMoney;		//������
	static int m_nScore;		//�X�R�A
	static int m_nGetMoney;		//�X�e�[�W���Ŋl��������
	static int m_nNumAircraft;	//�g����퓬�@�̐�
	static bool m_aAircraft[6];	//�ǂ̐퓬�@�g���邩

};

#endif