//---------------------------
//Author:�O��q��
//�`�F�b�N�|�C���g(checkpoint.cpp)
//---------------------------
#include "checkpoint.h"
#include "manager.h"
#include "renderer.h"

CCheckPoint::CCheckPoint(int nPriority) : CObject(nPriority)
{

}

CCheckPoint::~CCheckPoint()
{

}

//����������
HRESULT CCheckPoint::Init(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot)
{
	CObject::Init(pos, nType, collision, rot, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CScene::SetObjType(CScene::OBJCTTYPE_CHECKPOINT);
	return S_OK;
}

//�I������
void CCheckPoint::Uninit()
{
	CObject::Uninit();
}

//�X�V����
void CCheckPoint::Update()
{

}

//�`�揈��
void CCheckPoint::Draw()
{
	CObject::Draw();
}

//�쐬
CCheckPoint *CCheckPoint::Create(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot)
{
	CCheckPoint *pCheckPoint;
	pCheckPoint = new CCheckPoint(2);
	if (pCheckPoint != NULL)
	{
		pCheckPoint->Init(pos, nType, collision, rot);
	}
	return pCheckPoint;
}