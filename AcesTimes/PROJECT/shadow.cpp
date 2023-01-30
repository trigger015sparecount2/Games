//---------------------------
// Author:�O��q��
// �e(shadow.cpp)
//---------------------------
#include "shadow.h"
#include "manager.h"
#include "renderer.h"

CShadow::CShadow(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CShadow::~CShadow()
{

}

//����������
HRESULT CShadow::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CScene2D::Init(pos);
	CScene2D::SetSize(D3DXVECTOR2(size.x, size.y));
	CScene2D::Set();
	return S_OK;
}

//�I������
void CShadow::Uninit()
{
	CScene2D::Uninit();
}

//�X�V����
void CShadow::Update()
{

}

//�`�揈��
void CShadow::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	//���Z�����̐ݒ�
	/*pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);*/
	CScene2D::Draw();
	//�ʏ퍇���ɖ߂�
	/*pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/
}

CShadow *CShadow::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nType)
{
	CShadow *pShadow;
	pShadow = new CShadow(PRIORITY_SHADOW);
	if (pShadow != NULL)
	{
		pShadow->Init(size, pos);
		pShadow->SetTexture(nType);
	}
	return pShadow;
}