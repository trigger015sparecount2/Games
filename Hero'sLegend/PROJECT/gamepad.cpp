//--------------------------------------
//Author:�O��q��
//�Q�[���p�b�h�̓��͏��(padinput.cpp)
//---------------------------------------
#include "gamepad.h"

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pPadInput = NULL;             //DirectInput�I�u�W�F�N�g�̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevGamepad = NULL; //���̓f�o�C�X(�Q�[���p�b�h)�ւ̃|�C���^
DIJOYSTATE g_aPadState;              //�L�[�{�[�h�̓��͏��(�v���X���)
DIJOYSTATE g_aPadStateTrigger;
DIJOYSTATE g_aPadStateRelease;
bool g_bGamepad;


//����������
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInit�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&g_pPadInput, NULL)))
	{
		return E_FAIL;
	}
	//�ڑ�����Ă�Q�[���p�b�h�̗�
	if (FAILED(g_pPadInput->EnumDevices(DI8DEVCLASS_GAMECTRL, DeviceFindCallBack, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(g_pPadInput->CreateDevice(GUID_Joystick, &g_pDevGamepad, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevGamepad->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}
	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;

	// �����[�h��ύX
	if (FAILED(g_pDevGamepad->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// X���̒l�͈̔͐ݒ�
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(g_pDevGamepad->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return E_FAIL;
	}

	// Y���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(g_pDevGamepad->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevGamepad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevGamepad->Acquire();
	//�����𓯊�������
	g_pDevGamepad->Poll();
	g_bGamepad = true;
	return S_OK;
}

//�I������
void UninitGamepad(void)
{
	//���̓f�o�C�X�̊J��
	if (g_pDevGamepad != NULL)
	{
		g_pDevGamepad->Unacquire();
		g_pDevGamepad->Release();
		g_pDevGamepad = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̊J��
	if (g_pPadInput != NULL)
	{
		g_pPadInput->Release();
		g_pPadInput = NULL;
	}
}

//�X�V����
void UpdateGamepad(void)
{
	DIJOYSTATE aPadState;
	int nCntPad;
	//���̓f�o�C�X����f�[�^���擾����
	if (SUCCEEDED(g_pDevGamepad->GetDeviceState(sizeof(aPadState), &aPadState)))
	{
		for (nCntPad = 0; nCntPad < DIP_MAX; nCntPad++)
		{
			g_aPadStateTrigger.rgbButtons[nCntPad] = g_aPadState.rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad] & aPadState.rgbButtons[nCntPad];
			g_aPadStateRelease.rgbButtons[nCntPad] = (g_aPadState.rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad]) & g_aPadState.rgbButtons[nCntPad];
			g_aPadState.rgbButtons[nCntPad] = aPadState.rgbButtons[nCntPad]; //�L�[�{�[�h�̓��͏��ۑ�
		}
		g_aPadState.lX = aPadState.lX;
		g_aPadState.lY = aPadState.lY;
		g_aPadState.lZ = aPadState.lZ;
		g_aPadState.lRz = aPadState.lRz;
		g_aPadStateTrigger.rgdwPOV[0] = g_aPadState.rgdwPOV[0];
		g_aPadState.rgdwPOV[0] = aPadState.rgdwPOV[0];
	}
	else
	{
		g_pDevGamepad->Acquire();
	}
}

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef)
{
	return DIENUM_CONTINUE;
}

//���X�e�B�b�N������
float LeftStickX(void)
{
	float length = 1000.0f;
	float LeftX = 0.0f;
	if (g_aPadState.lX < 0)
	{
		LeftX = (float)g_aPadState.lX / length; //���X�e�B�b�N�����ɌX�����Ƃ�
	}
	else if (g_aPadState.lX > 0)
	{
		LeftX = (float)g_aPadState.lX / length; //���X�e�B�b�N���E�ɌX�����Ƃ�
	}
	return LeftX;
}

//���X�e�B�b�N�c����
float LeftStickY(void)
{
	float length = 1000.0f;
	float LeftY = 0.0f;
	if (g_aPadState.lY < 0)
	{
		LeftY = (float)g_aPadState.lY / length; //���X�e�B�b�N�����ɌX�����Ƃ�
	}
	else if (g_aPadState.lY > 0)
	{
		LeftY = (float)g_aPadState.lY / length; //���X�e�B�b�N����ɌX�����Ƃ�
	}
	return LeftY;
}

//�E�X�e�B�b�N������
float RightStickX(void)
{
	float length = 32767.0f;
	float RightX = 0.0f;
	if (g_aPadState.lZ < 32767)
	{
		RightX = (float)(g_aPadState.lZ - length) / length; //�E�X�e�B�b�N�����ɌX�����Ƃ�
	}
	else if (g_aPadState.lZ > 32767)
	{
		RightX = (float)(g_aPadState.lZ - length) / length; //�E�X�e�B�b�N���E�ɌX�����Ƃ�
	}
	return RightX;
}

//�E�X�e�B�b�N�c����
float RightStickY(void)
{
	float length = 32767.0f;
	float RightY = 0.0f;
	if (g_aPadState.lRz < 32767)
	{
		RightY = (float)(g_aPadState.lRz - length) / length; //�E�X�e�B�b�N����ɌX�����Ƃ�
	}
	else if (g_aPadState.lRz > 32767)
	{
		RightY = (float)(g_aPadState.lRz - length) / length; //�E�X�e�B�b�N�����ɌX�����Ƃ�
	}
	return RightY;
}

//�\���L�[��������Ă邩�i�ォ�玞�v����0.0f, 4500.0f, 9000.0f, 13500.0f, 18000.0f, 22500.0f, 27000.0f, 31500.0f�j
float CrossKey(void)
{
	//�\���L�[�����͂���Ă邩
	if (g_aPadState.rgdwPOV[0] != 0xFFFFFFFF)
	{
		//���O�ɉ����ꂽ�����ƈႤ���i�����������疳������j
		if (g_aPadStateTrigger.rgdwPOV[0] != g_aPadState.rgdwPOV[0])
		{
			return g_aPadState.rgdwPOV[0];
		}
	}
	return 10.0f; //����������ĂȂ������Ƃ��p
}

//�L�[�{�[�h�̓��͏����擾
bool GetGamePadPress(PadButton Button)
{
	return (g_aPadState.rgbButtons[Button] & 0x80) ? true : false;
}

bool GetGamePadTrigger(PadButton Button)
{
	return (g_aPadStateTrigger.rgbButtons[Button] & 0x80) ? true : false;

}

bool GetGamePadRelease(PadButton Button)
{
	return (g_aPadStateRelease.rgbButtons[Button] & 0x80) ? true : false;
}

//�Q�[���p�b�h���q�����Ă邩�ǂ���
bool GamePad(void)
{
	return g_bGamepad;
}

//�����{�^���������Ƃ�
bool GetAnyButton(void)
{
	int nCntPad;
	for (nCntPad = 0; nCntPad < DIP_MAX; nCntPad++)
	{
		if ((g_aPadStateTrigger.rgbButtons[nCntPad] & 0x80) != 0 && (g_aPadStateRelease.rgbButtons[nCntPad] & 0x80) == 0)
		{
			return true;
		}
	}
	return false;
}

//����̃{�^���������ꂽ��
bool GetGamePadButton(PadButton Button)
{
	if ((g_aPadStateTrigger.rgbButtons[Button] & 0x80) != 0 && (g_aPadStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}