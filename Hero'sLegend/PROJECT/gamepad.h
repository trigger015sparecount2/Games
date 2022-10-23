//--------------------------------------
//Author:�O��q��
//�Q�[���p�b�h�̓��͏��(padinput.h)
//---------------------------------------
#ifndef _PADINPUT_H_
#define _PADINPUT_H_
#include "main.h"
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
}PadButton ;
//�v���g�^�C�v�錾
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);
void UninitGamepad(void);
void UpdateGamepad(void);
float LeftStickX(void);
float LeftStickY(void);
float CrossKey(void);
float RightStickX(void);
float RightStickY(void);
bool GetGamePadPress(PadButton Button);
bool GetGamePadTrigger(PadButton Button);
bool GetGamePadRelease(PadButton Button);
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);
bool GamePad(void);
bool GetAnyButton(void);
bool GetGamePadButton(PadButton Button);
#endif _PADINPUT_H_
