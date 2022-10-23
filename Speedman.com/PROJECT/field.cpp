//---------------------------
//Author:�O��q��
//�t�B�[���h(field.cpp)
//---------------------------
#include "field.h"
#include "manager.h"
#include "renderer.h"

CField::CField(int nPriority) : CPlane::CPlane(nPriority)
{

}

CField::~CField()
{

}

//����������
HRESULT CField::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
{
	CPlane::Init(size, pos, Tex);
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CScene::SetObjType(CScene::OBJECTTYPE_FIELD);
	return S_OK;
}

//�I������
void CField::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CField::Update()
{

}

//�`�揈��
void CField::Draw()
{
	CPlane::Draw();
}

CField *CField::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nTex, D3DXVECTOR2 Tex)
{
	CField *pField;
	pField = new CField(0);
	if (pField != NULL)
	{
		pField->Init(size, pos, Tex);
		pField->SetTexture(nTex);
	}
	return pField;
}
