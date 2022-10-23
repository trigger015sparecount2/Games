//---------------------------
//Author:�O��q��
//���f��(player.cpp)
//---------------------------
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

CScene3D::CScene3D(int nPriority) : CScene::CScene(nPriority)
{

}

CScene3D::~CScene3D()
{

}


//����������
HRESULT CScene3D::Init(D3DXVECTOR3 /*pos*/)
{
	return S_OK;
}

//�I������
void CScene3D::Uninit()
{
	Release();
}

//�X�V����
void CScene3D::Update()
{
	
}

//�`�揈��
void CScene3D::Draw()
{
	
}

D3DXMATRIX CScene3D::GetMatrix() const
{
	return m_mtxWorld;
}

D3DXVECTOR3 CScene3D::GetRot() const
{
	return m_rot;
}

void CScene3D::SetRot(const D3DXVECTOR3& rot)
{
	m_rot = rot;
}

void CScene3D::SetMatrix(const D3DXMATRIX& mtx)
{
	m_mtxWorld = mtx;
}

CScene3D *CScene3D::Create(const D3DXVECTOR3& pos)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D(3);
	if (pScene3D != NULL)
	{
		pScene3D->Init(pos);
	}
	return pScene3D;
}