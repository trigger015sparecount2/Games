//=============================================================================
//
// �}�E�X���͏��� [mouse.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "main.h"
#include "input.h"

class CMouse : CInput
{
public:
	//�}�E�X�̓���
	typedef enum
	{
		DIM_L = 0, //���N���b�N
		DIM_R,     //�E�N���b�N
		DIM_W,      //�z�C�[���{�^��
		DIM_MAX
	}MouseButton;

	//�v���g�^�C�v�錾
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit();	//�I��
	void Update();	//�X�V

	bool GetPress(MouseButton Button) { return (m_MouseState.rgbButtons[Button] & 0x80) ? true : false; }			//�����Ă�
	bool GetTrigger(MouseButton Button) { return (m_MouseStateTrigger.rgbButtons[Button] & 0x80) ? true : false; }	//�������܂��͗�����
	bool GetRelease(MouseButton Button) { return (m_MouseStateRelease.rgbButtons[Button] & 0x80) ? true : false; }	//������
	bool Mouse() { return m_bMouse; }				//�}�E�X�q�����Ă�
	float MouseX() { return m_MouseState.lX; }		//���ړ�
	float MouseY() { return m_MouseState.lY; }		//�c�ړ�
	float MouseZ() { return m_MouseState.lZ; }		//�}�E�X�z�C�[��
	bool GetMouseButton(MouseButton Button) const;	//������

private:
	DIMOUSESTATE m_MouseState;			//�}�E�X�̓��͏��(�v���X���)
	DIMOUSESTATE m_MouseStateTrigger;	//�}�E�X�̓��͏��(�g���K�[���)
	DIMOUSESTATE m_MouseStateRelease;	//�}�E�X�̓��͏��(�����[�X���)
	bool m_bMouse;	//�}�E�X�q�����Ă邩
};
#endif