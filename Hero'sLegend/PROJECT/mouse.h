//--------------------------------------
//Author:�O��q��
//�}�E�X�̓��͏��(mouse.h)
//---------------------------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "main.h"

//�}�E�X�̃{�^��
typedef enum
{
	DIM_L = 0,	//���N���b�N
	DIM_R,		//�E�N���b�N
	DIM_W,		//�z�C�[���{�^��
	DIM_MAX
}MouseButton ;

//�v���g�^�C�v�錾
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);	//������
void UninitMouse(void);						//�I��
void UpdateMouse(void);						//�X�V
bool GetMousePress(MouseButton Button);		//�{�^�������Ă邩
bool GetMouseTrigger(MouseButton Button);	//�{�^���������܂��͗��ꂽ
bool GetMouseRelease(MouseButton Button);	//�{�^��������
bool Mouse(void);	//�}�E�X�q�����Ă��邩
LONG MouseX(void);	//�}�E�X���ړ�
LONG MouseY(void);	//�}�E�X�c�ړ�
LONG MouseZ(void);	//�}�E�X�z�C�[��
bool GetMouseButton(MouseButton Button);	//�{�^����������
#endif _MOUSE_H_