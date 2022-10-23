//--------------------------------------
//Author:�O��q��
//�L�[�{�[�h�̓��͏��(mouse.cpp)
//---------------------------------------
#include "mouse.h"

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pMouseInput = NULL;             //DirectInput�I�u�W�F�N�g�̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL; //���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
DIMOUSESTATE g_aMouseState;              //�}�E�X�̓��͏��(�v���X���)
DIMOUSESTATE g_aMouseStateTrigger;
DIMOUSESTATE g_aMouseStateRelease;
bool g_bMouse;


//����������
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInit�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&g_pMouseInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(g_pMouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�����𓯊�������
	g_pDevMouse->Poll();

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevMouse->Acquire();
	g_bMouse = true;
	return S_OK;
}

//�I������
void UninitMouse(void)
{
	//���̓f�o�C�X�̊J��
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̊J��
	if (g_pMouseInput != NULL)
	{
		g_pMouseInput->Release();
		g_pMouseInput = NULL;
	}
}

//�X�V����
void UpdateMouse(void)
{
	DIMOUSESTATE aMouseState;
	int nCntBut;
	//���̓f�o�C�X����f�[�^���擾����
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(aMouseState), &aMouseState)))
	{
		for (nCntBut = 0; nCntBut < DIM_MAX; nCntBut++)
		{
			g_aMouseStateTrigger.rgbButtons[nCntBut] = g_aMouseState.rgbButtons[nCntBut] ^ aMouseState.rgbButtons[nCntBut] & aMouseState.rgbButtons[nCntBut];
			g_aMouseStateRelease.rgbButtons[nCntBut] = (g_aMouseState.rgbButtons[nCntBut] ^ aMouseState.rgbButtons[nCntBut]) & g_aMouseState.rgbButtons[nCntBut];
			g_aMouseState.rgbButtons[nCntBut] = aMouseState.rgbButtons[nCntBut]; //�}�E�X�̓��͏��ۑ�
		}
		g_aMouseState.lX = aMouseState.lX;
		g_aMouseState.lY = aMouseState.lY;
		g_aMouseState.lZ = aMouseState.lZ;
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}

//�}�E�X�̓��͏����擾
bool GetMousePress(MouseButton Button)
{
	return (g_aMouseState.rgbButtons[Button] & 0x80) ? true : false;
}

bool GetMouseTrigger(MouseButton Button)
{
	return (g_aMouseStateTrigger.rgbButtons[Button] & 0x80) ? true : false;

}

bool GetMouseRelease(MouseButton Button)
{
	return (g_aMouseStateRelease.rgbButtons[Button] & 0x80) ? true : false;
}

float MouseX(void) //�}�E�X��(�E���ƃv���X�A�����ƃ}�C�i�X)
{
	return g_aMouseState.lX;
}

float MouseY(void) //�}�E�X�c(�ゾ�ƃ}�C�i�X�A�����ƃv���X)
{
	return g_aMouseState.lY;
}

float MouseZ(void) //�}�E�X�̃z�C�[��(��ɓ]�����ƃv���X�A�����ƃ}�C�i�X)
{
	return g_aMouseState.lZ;
}

bool Mouse(void)
{
	return g_bMouse;
}

//����̃{�^���������ꂽ��
bool GetMouseButton(MouseButton Button)
{
	if ((g_aMouseStateTrigger.rgbButtons[Button] & 0x80) != 0 && (g_aMouseStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}