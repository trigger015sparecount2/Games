//---------------------------
//Author:�O��q��
//���C�g(light.cpp)
//---------------------------
#include "light.h"

//�O���[�o���ϐ�
D3DLIGHT9 g_light[3]; //���C�g�̏��

//����������
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXVECTOR3 vecDir; //�ݒ�p�����x�N�g��
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	//���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL; //�Ό�����
	//���C�g�̊g�U��i�F�j��ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir); //���K������
	g_light[0].Direction = vecDir;
	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[0]);
	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	//���C�g�̎�ނ�ݒ�
	g_light[1].Type = D3DLIGHT_DIRECTIONAL; //�Ό�����
	//���C�g�̊g�U��i�F�j��ݒ�
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.5f, -0.4f, 0.5f);
	D3DXVec3Normalize(&vecDir, &vecDir); //���K������
	g_light[1].Direction = vecDir;
	//���C�g��ݒ肷��
	pDevice->SetLight(1, &g_light[1]);
	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);
	//���C�g�̎�ނ�ݒ�
	g_light[2].Type = D3DLIGHT_DIRECTIONAL; //�Ό�����
	//���C�g�̊g�U��i�F�j��ݒ�
	g_light[2].Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(-0.5f, -0.4f, -0.5f);
	D3DXVec3Normalize(&vecDir, &vecDir); //���K������
	g_light[2].Direction = vecDir;
	//���C�g��ݒ肷��
	pDevice->SetLight(2, &g_light[2]);
	//���C�g��L���ɂ���
	pDevice->LightEnable(2, TRUE);
	return S_OK;
}

void UninitLight(void)
{

}

void UpdateLight(void)
{

}

void SetLight(int nCntLight, D3DXCOLOR col, D3DXVECTOR3 vec)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXVECTOR3 vecDir; //�ݒ�p�����x�N�g��
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	//���C�g�̎�ނ�ݒ�
	g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL; //�Ό�����
	//���C�g�̊g�U��i�F�j��ݒ�
	g_light[nCntLight].Diffuse = D3DXCOLOR(col.r, col.g, col.b, 1.0f);
	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(vec.x, vec.y, vec.z);
	D3DXVec3Normalize(&vecDir, &vecDir); //���K������
	g_light[nCntLight].Direction = vecDir;
	//���C�g��ݒ肷��
	pDevice->SetLight(nCntLight, &g_light[nCntLight]);
	//���C�g��L���ɂ���
	pDevice->LightEnable(nCntLight, TRUE);
}