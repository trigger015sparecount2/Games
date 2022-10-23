//---------------------------
//Author:�O��q��
//�J����(camera.cpp)
//---------------------------
#include "camera.h"
#include "input.h"
#include "gamepad.h"
#include "mouse.h"
#include "player.h"
#include "fade.h"

//�J�����̍\����
typedef struct
{
	D3DXVECTOR3 posV;     //���݂̎��_
	D3DXVECTOR3 posVDest; //�ړI�̎��_
	D3DXVECTOR3 posR;     //���݂̒����_
	D3DXVECTOR3 posRDest; //�ړI�̒����_
	D3DXVECTOR3 vecU;     //������x�N�g��
	D3DXVECTOR3 rot;     //�J�����̌���
	float fLength;
	bool bDie;
	int nDieTime;
	D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X
} Camera;

//�O���[�o���ϐ�
Camera g_camera; //�J�����̏��

//����������
HRESULT InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 140.0f, -200.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 140.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fLength = 400.0f;
	g_camera.nDieTime = 0;
	g_camera.bDie = false;
	return S_OK;
}

//�I������
void UninitCamera(void)
{

}

//�X�V����
void UpdateCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	if (g_camera.bDie == false)
	{
		g_camera.rot.y += MouseX() * 0.003f;
		if (GamePad() == true)
		{
			g_camera.rot.y += RightStickX() * 0.05f;
		}
		g_camera.posRDest = D3DXVECTOR3(PlayerPos().x + PlayerGetMove().x * 8.0f, PlayerPos().y + GetPlayerHeight(), PlayerPos().z + PlayerGetMove().z * 8.0f);
		g_camera.posVDest.x = PlayerPos().x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = PlayerPos().y + g_camera.fLength;
		g_camera.posVDest.z = PlayerPos().z - cosf(g_camera.rot.y) * g_camera.fLength;
		if (g_camera.posRDest.x != g_camera.posR.x)
		{
			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.2f;
		}
		if (g_camera.posRDest.y != g_camera.posR.y)
		{
			g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.2f;
		}
		if (g_camera.posRDest.z != g_camera.posR.z)
		{
			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.2f;
		}
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2;
		}
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.y = g_camera.posR.y + g_camera.fLength * (1.0f / 10.0f);
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	else
	{
		g_camera.nDieTime++;
		if (g_camera.nDieTime >= 200)
		{
			SetFade(MODE_RESULT);
		}
		g_camera.posR = D3DXVECTOR3(PlayerPos().x, PlayerPos().y + 50.0f, PlayerPos().z);
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * 250.0f;
		g_camera.posV.y = g_camera.posR.y + 100.0f;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * 250.0f;
	}
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//�ݒ菈��
void SetCamera(D3DXVECTOR3 ref, float fDistance)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	g_camera.posR = ref;
	g_camera.bDie = false;
	g_camera.nDieTime = 0;
	if (fDistance > 100.0f)
	{
		g_camera.fLength = fDistance;
	}
	g_camera.rot.y = 0.0f;
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 3000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//�J�����̕���
float CameraRot(void)
{
	return g_camera.rot.y;
}

//���_�̏ꏊ
float CameraPosV(int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_camera.posV.x;
		break;
	case 1:
		return g_camera.posV.y;
		break;
	case 2:
		return g_camera.posV.z;
		break;
	}
	return 0.0f;
}

//�����_�̏ꏊ
D3DXVECTOR3 CameraPosR(void)
{
	return g_camera.posR;
}

//���_�ƒ����_�̋���
float CameraDistance(void)
{
	float fDistance;
	float fHDistance;
	float fLengthX;
	float fLengthY;
	float fLengthZ;
	fLengthX = powf(g_camera.posR.x - g_camera.posV.x, 2);
	fLengthY = powf(g_camera.posR.y - g_camera.posV.y, 2);
	fLengthZ = powf(g_camera.posR.z - g_camera.posV.z, 2);
	fHDistance = fLengthX + fLengthZ;
	fDistance = sqrtf(fLengthY + fHDistance);
	return fDistance;
}

D3DXVECTOR3 CameraVector(void)
{
	return g_camera.vecU;
}

void CameraRotReset(float fRoty)
{
	g_camera.rot.y = fRoty;
}

void CameraRot(float fRot)
{
	if (fRot - g_camera.rot.y < -3.14f)
	{
		g_camera.rot.y += (fRot - g_camera.rot.y + 6.28f) * 0.01f;
	}
	else if (fRot - g_camera.rot.y > 3.14f)
	{
		g_camera.rot.y += (fRot - g_camera.rot.y - 6.28f) * 0.01f;
	}
	else
	{
		g_camera.rot.y += (fRot - g_camera.rot.y) * 0.01f;
	}
}

void PlayerDieCamera(float fRot)
{
	g_camera.bDie = true;
	g_camera.rot.y = fRot + 0.8f;
}