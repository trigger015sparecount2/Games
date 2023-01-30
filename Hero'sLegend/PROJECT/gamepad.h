//--------------------------------------
//Author:�O��q��
//�Q�[���p�b�h�̓��͏��(padinput.h)
//---------------------------------------
#ifndef _PADINPUT_H_
#define _PADINPUT_H_
#include "main.h"

//�{�^���̎��
typedef enum
{
	DIP_X = 0,	//X
	DIP_Y,		//Y
	DIP_A,		//A
	DIP_B,		//B
	DIP_L1,		//LB
	DIP_R1,		//RB
	DIP_L2,		//LT
	DIP_R2,		//RT
	DIP_LS,		//���X�e�B�b�N
	DIP_RS,		//�E�X�e�B�b�N
	DIP_BACK,	//BACK
	DIP_START,	//START
	DIP_GUIDE,	//GUIDE
	DIP_MAX
}PadButton;

//�v���g�^�C�v�錾
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);	//������
void UninitGamepad(void);	//�I��
void UpdateGamepad(void);	//�X�V
float LeftStickX(void);		//���X�e�B�b�N��
float LeftStickY(void);		//���X�e�B�b�N�c
float CrossKey(void);		//�\���L�[
float RightStickX(void);	//�E�X�e�B�b�N��
float RightStickY(void);	//�E�X�e�B�b�N�c
bool GetGamePadPress(PadButton Button);		//�{�^�������Ă�
bool GetGamePadTrigger(PadButton Button);	//�{�^���������܂��͗��ꂽ
bool GetGamePadRelease(PadButton Button);	//�{�^��������
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);	//�R�[���o�b�N�֐�
bool GamePad(void);							//�Q�[���p�b�h�q�����Ă��邩
bool GetAnyButton(void);					//�{�^��������������
bool GetGamePadButton(PadButton Button);	//�{�^����������
#endif _PADINPUT_H_
