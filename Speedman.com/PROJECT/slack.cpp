//---------------------------
//Author:�O��q��
//�I�u�W�F�N�g(object.cpp)
//---------------------------
#include "slack.h"
#include "manager.h"
#include "renderer.h"

CSlack::CSlack(int nPriority) : CObject(nPriority)
{

}

CSlack::~CSlack()
{

}

//����������
HRESULT CSlack::Init(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot, int nSlack)
{
	CObject::Init(pos, nType, collision, rot, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CScene::SetObjType(CScene::OBJCTTYPE_SLACKLINE);
	CScene::SetSlack(nSlack);
	D3DXVECTOR3 VtxMax;
	D3DXVECTOR3 VtxMin;
	VtxMax = GetVtxMax();
	VtxMin = GetVtxMin();
	float fRadius = VtxMax.x - VtxMin.x;
	if (fRadius > VtxMax.z - VtxMin.z)
	{
		fRadius = VtxMax.z - VtxMin.z;
	}
	SetRadius(fRadius);
	return S_OK;
}

//�I������
void CSlack::Uninit()
{
	CObject::Uninit();
}

//�X�V����
void CSlack::Update()
{

}

//�`�揈��
void CSlack::Draw()
{
	CObject::Draw();
}

CSlack *CSlack::Create(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot, int nSlack)
{
	CSlack *pSlack;
	pSlack = new CSlack(3);
	if (pSlack != NULL)
	{
		pSlack->Init(pos, nType, collision, rot, nSlack);
	}
	return pSlack;
}