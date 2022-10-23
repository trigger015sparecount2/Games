//=============================================================================
//
// ���͏��� [input.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;             //DirectInput�I�u�W�F�N�g�̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice; //���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
};

class CInputKeyboard : CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetAnyKey(void);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetKey(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];        //�L�[�{�[�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

class CInputGamePad : CInput
{
public:
	typedef enum
	{
		DIP_X = 0,
		DIP_Y,
		DIP_A,
		DIP_B,
		DIP_L1,
		DIP_R1,
		DIP_L2,
		DIP_R2,
		DIP_LS,
		DIP_RS,
		DIP_BACK,
		DIP_START,
		DIP_GUIDE,
		DIP_MAX
	} PadButton;
	CInputGamePad();
	~CInputGamePad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(PadButton Button);
	bool GetAnyButton(void);
	bool GetTrigger(PadButton Button);
	bool GetRelease(PadButton Button);
	bool GetButton(PadButton Button);
	float LeftStickX(void);
	float LeftStickY(void);
	float TriggerCrossKey(void);
	float PressCrossKey(void);
	float RightStickX(void);
	float RightStickY(void);
	static bool GetGamePad(void);

private:
	static bool m_bGamePad;
	DIJOYSTATE m_aPadState;              //�Q�[���p�b�h�̓��͏��(�v���X���)
	DIJOYSTATE m_aPadStateTrigger;
	DIJOYSTATE m_aPadStateRelease;
	//BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);
};
#endif