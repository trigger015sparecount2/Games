//--------------------------------------
//Author:�O��q��
//�Q�[���p�b�h�̓��͏��(padinput.h)
//---------------------------------------
#ifndef _PADINPUT_H_
#define _PADINPUT_H_
#include "main.h"

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
}PadButton;

//�v���g�^�C�v�錾
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);	//������
void UninitGamepad(void);		//�I��
void UpdateGamepad(void);		//�X�V
float LeftStickX(void);			//���X�e�B�b�N��
float LeftStickY(void);			//���X�e�B�b�N�c
bool CrossKey(int nRot);		//�\���L�[��������
bool PressCrossKey(int nRot);	//�\���L�[�����Ă�
float RightStickX(void);		//�E�X�e�B�b�N��
float RightStickY(void);		//�E�X�e�B�b�N�c
bool GetGamePadPress(PadButton Button);		//�{�^�������Ă�
bool GetGamePadTrigger(PadButton Button);	//�{�^�����͕ς����
bool GetGamePadRelease(PadButton Button);	//�{�^��������
bool GamePad(void);				//�Q�[���p�b�h�q�����Ă邩
bool GetAnyButton(void);		//�����{�^��������
bool GetGamePadButton(PadButton Button);	//�{�^��������
int GetCrossKey(void);			//�\���L�[�̓��͏��
#endif _PADINPUT_H_
