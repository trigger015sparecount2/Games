//---------------------------
// Author:�O��q��
// �e(shadow.cpp)
//---------------------------
#include "shadow.h"
#include "manager.h"
#include "renderer.h"

CShadow::CShadow(int nPriority) : CPlane::CPlane(nPriority)
{

}

CShadow::~CShadow()
{

}

//����������
HRESULT CShadow::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f));
	m_size = size;
	CScene::SetObjType(OBJECTTYPE_EFFECT);
	m_fLength = 0.0f;
	return S_OK;
}

//�I������
void CShadow::Uninit()
{
	CPlane::Uninit();
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
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CPlane::Draw();
	//�ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//�쐬
CShadow *CShadow::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CShadow *pShadow;
	pShadow = new CShadow(4);
	if (pShadow != NULL)
	{
		pShadow->Init(size, pos);
		pShadow->SetTexture(4);
	}
	return pShadow;
}

//�ړ�����
void CShadow::Move(float fHeight)
{
	D3DXVECTOR3 size;
	size = CPlane::GetSize();
	m_fLength = (fHeight - m_fPosY) * 0.04f;
	size.x += m_fLength;
	size.z += m_fLength;
	SetSize(size);
	ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - m_fLength * 0.1f));
}

//�ړ�
void CShadow::MoveY(D3DXVECTOR3 pos, float fRotX)
{
	m_fPosY = pos.y + 1.0f;
	SetSize(m_size);
	SetPos(D3DXVECTOR3(pos.x, m_fPosY, pos.z));
	SetRot(D3DXVECTOR3(fRotX, 0.0f, 0.0f));
}