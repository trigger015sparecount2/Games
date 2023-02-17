//---------------------------
//Author:�O��q��
//���񂾂�J�����̕������؂�ւ��(kamerapanel.cpp)
//---------------------------
#include "camerapanel.h"
#include "manager.h"
#include "renderer.h"

CCameraPanel::CCameraPanel(int nPriority) : CPlane::CPlane(nPriority)
{

}

CCameraPanel::~CCameraPanel()
{

}

//����������
HRESULT CCameraPanel::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f));
	CScene::SetObjType(OBJCTTYPE_CAMERAPANEL);
	CScene::SetCameraPosR(posR);
	CScene::SetCameraPosV(posV);
	return S_OK;
}

//�I������
void CCameraPanel::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CCameraPanel::Update()
{

}

//�`�揈��
void CCameraPanel::Draw()
{
#ifdef _DEBUG
	CPlane::Draw();
#endif
}

//�쐬
CCameraPanel *CCameraPanel::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	CCameraPanel *pPanel;
	pPanel = new CCameraPanel(2);
	if (pPanel != NULL)
	{
		pPanel->Init(size, pos, posV, posR);
		pPanel->SetTexture(4);
	}
	return pPanel;
}