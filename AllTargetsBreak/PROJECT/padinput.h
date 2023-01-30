//--------------------------------------
//Author:�O��q��
//�Q�[���p�b�h�̓��͏��(padinput.h)
//---------------------------------------
#ifndef _PADINPUT_H_
#define _PADINPUT_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);	//������
void UninitGamepad(void);				//�I��
void UpdateGamepad(void);				//�X�V
float LeftStickX(void);					//���X�e�B�b�N��
float LeftStickY(void);					//���X�e�B�b�N�c
float CrossKey(void);					//�\���L�[
float RightStickX(void);				//�E�X�e�B�b�N��
float RightStickY(void);				//�E�X�e�B�b�N�c
bool GetGamePadPress(int nButton);		//�v���X���
bool GetGamePadTrigger(int nButton);	//�g���K�[���
bool GetGamePadRelease(int nButton);	//�����[�X���
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);	//�R�[���o�b�N�֐�
bool GamePad(void);					//�q�����Ă��邩�擾
bool GetAnyButton(void);			//���������ꂽ��
bool GetGamePadButton(int nButton);	//�����ꂽ��
#endif _PADINPUT_H_
