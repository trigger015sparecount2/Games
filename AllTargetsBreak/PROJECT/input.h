//--------------------------------------
//Author:�O��q��
//�L�[�{�[�h�̓��͏��(input.h)
//---------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//������
void UninitKeyboard(void);			//�I��
void UpdateKeyboard(void);			//�X�V
bool GetKeyboardPress(int nKey);	//�v���X���
bool GetKeyboardTrigger(int nKey);	//�g���K�[���
bool GetKeyboardRelease(int nKey);	//�����[�X���
bool GetAnyKey(void);				//���������ꂽ��
bool GetKeyboardKey(int nKey);		//�����ꂽ���
#endif _INPUT_H_