//---------------------------
//Author:三上航世
//3D関係(scene3d.cpp)
//---------------------------
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

CScene3D::CScene3D(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CScene3D::~CScene3D()
{

}


//初期化処理
HRESULT CScene3D::Init(D3DXVECTOR3 /*pos*/)
{
	return S_OK;
}

//終了処理
void CScene3D::Uninit()
{
	Release();
}

//更新処理
void CScene3D::Update()
{

}

//描画処理
void CScene3D::Draw()
{

}

//作成
CScene3D *CScene3D::Create(const D3DXVECTOR3& pos)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D(PRIORITY_OBJECT);
	if (pScene3D != NULL)
	{
		pScene3D->Init(pos);
	}
	return pScene3D;
}