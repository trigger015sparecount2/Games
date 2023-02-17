//---------------------------
//Author:�O��q��
//�J����(camera.cpp)
//---------------------------
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

//����������
HRESULT CCamera::Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	m_camera.posV = ref;
	m_camera.posVDest = ref;
	m_camera.posR = pos;
	m_camera.posRDest = pos;
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rot = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_camera.fLength = fDistance;		//��������

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 25000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
	/*m_pKeyboard = CManager::GetKeyboard();
	m_pMouse = CManager::GetMouse();*/
	return S_OK;
}

//�I������
void CCamera::Uninit()
{

}

//�X�V����
void CCamera::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	//if (m_pMouse != NULL)
	//{
	//	m_camera.rot.y += m_pMouse->MouseX() * 0.003f;
	//	//m_camera.rot.x += m_pMouse->MouseY() * 0.003f;
	//}
	/*if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetPress(DIK_W) == true)
		{
			m_camera.posRDest.x += sinf(m_camera.rot.y) * 3.0f;
			m_camera.posRDest.z += cosf(m_camera.rot.y) * 3.0f;
		}
		else if (m_pKeyboard->GetPress(DIK_S) == true)
		{
			m_camera.posRDest.x += sinf(m_camera.rot.y + D3DX_PI) * 3.0f;
			m_camera.posRDest.z += cosf(m_camera.rot.y + D3DX_PI) * 3.0f;
		}
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_camera.posRDest.x += sinf(m_camera.rot.y - D3DX_PI * 0.5f) * 3.0f;
			m_camera.posRDest.z += cosf(m_camera.rot.y - D3DX_PI * 0.5f) * 3.0f;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_camera.posRDest.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * 3.0f;
			m_camera.posRDest.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * 3.0f;
		}
	}*/
	/*m_camera.posVDest.x = m_camera.posRDest.x - sinf(m_camera.rot.y) * m_camera.fLength;
	m_camera.posVDest.y = m_camera.posRDest.y + m_camera.fLength;
	m_camera.posVDest.z = m_camera.posRDest.z - cosf(m_camera.rot.y) * m_camera.fLength;
	if (m_camera.posRDest.x != m_camera.posR.x)
	{
		m_camera.posR.x += (m_camera.posRDest.x - m_camera.posR.x) * 0.2f;
	}
	if (m_camera.posRDest.y != m_camera.posR.y)
	{
		m_camera.posR.y += (m_camera.posRDest.y - m_camera.posR.y) * 0.2f;
	}
	if (m_camera.posRDest.z != m_camera.posR.z)
	{
		m_camera.posR.z += (m_camera.posRDest.z - m_camera.posR.z) * 0.2f;
	}
	if (m_camera.rot.y >= D3DX_PI)
	{
		m_camera.rot.y -= D3DX_PI * 2;
	}
	if (m_camera.rot.y < -D3DX_PI)
	{
		m_camera.rot.y += D3DX_PI * 2;
	}
	*/
	m_camera.posV.x = m_camera.posR.x - sinf(m_camera.rot.y) * m_camera.fLength;
	m_camera.posV.y = m_camera.posR.y + m_camera.fLength * (m_camera.rot.x + (4.0f / 10.0f));
	m_camera.posV.z = m_camera.posR.z - cosf(m_camera.rot.y) * m_camera.fLength;

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}

//�ݒ菈��
CCamera *CCamera::Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	CCamera *pCamera;
	pCamera = new CCamera;
	if (pCamera != NULL)
	{
		pCamera->Init(ref, fDistance, pos);
	}
	return pCamera;
}

//���_�ݒ�
void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_camera.posVDest = pos;
	m_camera.posV = pos;
}

//�����_�ݒ�
void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_camera.posRDest = pos;
	m_camera.posR = pos;
}

//Y�������Z
void CCamera::AddRotY(float fRotY)
{
	m_camera.rot.y += fRotY;
	if (m_camera.rot.y > D3DX_PI)
	{
		m_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_camera.rot.y < -D3DX_PI)
	{
		m_camera.rot.y += D3DX_PI * 2.0f;
	}
}

//X�������Z
void CCamera::AddRotX(float fRotX)
{
	m_camera.rot.x += fRotX;
	//�J������������
	if (m_camera.rot.x >= 1.5f)
	{
		m_camera.rot.x = 1.5f;
	}
	else if (m_camera.rot.x <= -1.4f)
	{
		m_camera.rot.x = -1.4f;
	}
}