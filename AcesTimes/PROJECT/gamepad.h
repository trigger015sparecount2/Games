//=============================================================================
//
// ���͏��� [gamepad.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"
#include "input.h"

class CGamePad : CInput
{
public:
	//�Q�[���p�b�h�̃{�^��
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

	CGamePad();
	~CGamePad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	bool GetPress(PadButton Button) { return (m_aPadState.rgbButtons[Button] & 0x80) ? true : false; }	//���������Ă邩
	bool GetAnyButton();				//������������
	bool GetTrigger(PadButton Button) { return (m_aPadStateTrigger.rgbButtons[Button] & 0x80) ? true : false; }	//�����ꂽ�܂��͗����ꂽ��
	bool GetRelease(PadButton Button) { return (m_aPadStateRelease.rgbButtons[Button] & 0x80) ? true : false; }	//�����ꂽ
	bool GetButton(PadButton Button);	//�����ꂽ��
	float LeftStickX();			//���X�e�B�b�N��
	float LeftStickY();			//���X�e�B�b�N�c
	float TriggerCrossKey();	//�ォ�玞�v����0.0f,4500.0f,9000.0f,13500.0f,18000.0f,22500.0f,27000.0f,31500.0f
	float PressCrossKey();		//�ォ�玞�v����0.0f,4500.0f,9000.0f,13500.0f,18000.0f,22500.0f,27000.0f,31500.0f
	float RightStickX();		//�E�X�e�B�b�N��
	float RightStickY();		//�E�X�e�B�b�N�c
	static bool GetGamePad() { return m_bGamePad; }	//�Q�[���p�b�h�q�����Ă��邩

private:
	static bool m_bGamePad;			//�Q�[���p�b�h�q�����Ă��邩
	DIJOYSTATE m_aPadState;			//�Q�[���p�b�h�̓��͏��(�v���X���)
	DIJOYSTATE m_aPadStateTrigger;	//�g���K�[���
	DIJOYSTATE m_aPadStateRelease;	//�����[�X���
};
#endif