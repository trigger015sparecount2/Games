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

//�쐬
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