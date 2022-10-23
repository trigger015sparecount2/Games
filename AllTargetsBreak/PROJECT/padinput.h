//--------------------------------------
//Author:�O��q��
//�Q�[���p�b�h�̓��͏��(padinput.h)
//---------------------------------------
#ifndef _PADINPUT_H_
#define _PADINPUT_H_
#include "main.h"
//�v���g�^�C�v�錾
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);
void UninitGamepad(void);
void UpdateGamepad(void);
float LeftStickX(void);
float LeftStickY(void);
float CrossKey(void);
float RightStickX(void);
float RightStickY(void);
bool GetGamePadPress(int nButton);
bool GetGamePadTrigger(int nButton);
bool GetGamePadRelease(int nButton);
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);
bool GamePad(void);
bool GetAnyButton(void);
bool GetGamePadButton(int nButton);
#endif _PADINPUT_H_
