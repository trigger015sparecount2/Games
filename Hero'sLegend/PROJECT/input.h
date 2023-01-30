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
bool GetKeyboardPress(int nKey);	//�L�[�����Ă邩
bool GetKeyboardTrigger(int nKey);	//�L�[�����ꂽ�������ꂽ
bool GetKeyboardRelease(int nKey);	//�L�[�����ꂽ
bool GetAnyKey(void);				//�L�[������������
bool GetKeyboardKey(int nKey);		//�L�[�����ꂽ��
#endif _INPUT_H_