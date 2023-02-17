//---------------------------
//Author:�O��q��
//�S�[��(goal.cpp)
//---------------------------
#include "goal.h"
#include "manager.h"
#include "renderer.h"

CGoal::CGoal(int nPriority) : CPlane::CPlane(nPriority)
{

}

CGoal::~CGoal()
{

}

//����������
HRESULT CGoal::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f));
	CScene::SetObjType(OBJCTTYPE_GOAL);
	return S_OK;
}

//�I������
void CGoal::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CGoal::Update()
{

}

//�`�揈��
void CGoal::Draw()
{
#ifdef _DEBUG
	CPlane::Draw();
#endif
}

//�쐬
CGoal *CGoal::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CGoal *pGoal;
	pGoal = new CGoal(4);
	if (pGoal != NULL)
	{
		pGoal->Init(size, pos);
		pGoal->SetTexture(4);
	}
	return pGoal;
}