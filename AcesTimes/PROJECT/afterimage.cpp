//=============================================================================
//
// �c������ [afterimage.h]
// Author : �O��q��
//
//=============================================================================
#include "afterimage.h"
#include "manager.h"

CAfterImage::CAfterImage(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CAfterImage::~CAfterImage(void)
{

}

//������
HRESULT CAfterImage::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CScene2D::Init(pos);
	CScene2D::SetSize(size);
	CScene2D::ColorChange(col);
	CScene2D::Set();
	m_Col = col;
	return S_OK;
}

//�I��
void CAfterImage::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CAfterImage::Update(void)
{
	if (CManager::GetPause() == false)
	{
		//���X�ɓ����x���グ�Ă���
		m_Col.a -= 0.08f;
		ColorChange(m_Col);
		if (m_Col.a <= 0.0f)
		{
			SetDeath(true);
		}
	}
}

//�`��
void CAfterImage::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CAfterImage *CAfterImage::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, int nTex)
{
	CAfterImage *pAfterImage;
	pAfterImage = new CAfterImage(PRIORITY_CHARA);
	if (pAfterImage != NULL)
	{
		pAfterImage->Init(pos, size, col);
		pAfterImage->SetTexture(nTex);
	}
	return pAfterImage;
}