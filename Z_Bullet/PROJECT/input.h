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
bool GetKeyboardPress(int nKey);	//�����Ă�
bool GetKeyboardTrigger(int nKey);	//�������܂��͗�����
bool GetKeyboardRelease(int nKey);	//������
bool GetAnyKey(void);				//����������
bool GetKeyboardKey(int nKey);		//������
#endif _INPUT_H_