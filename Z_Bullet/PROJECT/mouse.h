//--------------------------------------
//Author:�O��q��
//�}�E�X�̓��͏��(mouse.h)
//---------------------------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "main.h"
typedef enum
{
	DIM_L = 0, //���N���b�N
	DIM_R,     //�E�N���b�N
	DIM_W,      //�z�C�[���{�^��
	DIM_MAX
}MouseButton;
//�v���g�^�C�v�錾
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
bool GetMousePress(MouseButton Button);
bool GetMouseTrigger(MouseButton Button);
bool GetMouseRelease(MouseButton Button);
bool Mouse(void);
float MouseX(void);
float MouseY(void);
float MouseZ(void);
bool GetMouseButton(MouseButton Button);
#endif _MOUSE_H_