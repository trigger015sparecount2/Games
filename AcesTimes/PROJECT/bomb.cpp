//=============================================================================
//
// �{������ [bomb.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "bomb.h"
#include "renderer.h"
#include "player.h"
#include "keyboard.h"

CBomb::CBomb(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CBomb::~CBomb(void)
{

}

//������
HRESULT CBomb::Init(D3DXVECTOR3 pos, float fRadius, int nCount)
{
	CScene2D::Init(pos);
	SetSize(D3DXVECTOR2(fRadius, fRadius));
	ColorChange(D3DXCOLOR(1.0f, 0.7f, 0.7f, 0.5f));
	Set();
	m_nCount = nCount;
	m_fClear = 0.5f;
	m_bClear = false;
	return S_OK;
}

//�I��
void CBomb::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CBomb::Update(void)
{
	//�|�[�Y������Ȃ�
	if (CManager::GetPause() == false)
	{
		//�J�E���g�i�߂�
		m_nCount--;
		if (m_nCount <= 120)
		{
			//�_�ł�����
			if (m_bClear == true)
			{
				m_fClear += 0.03f;
				if (m_fClear >= 0.5f)
				{
					m_fClear = 0.5f;
					m_bClear = false;
				}
			}
			else
			{
				m_fClear -= 0.03f;
				if (m_fClear <= 0.0f)
				{
					m_fClear = 0.0f;
					m_bClear = true;
				}
			}
			ColorChange(D3DXCOLOR(1.0f, 0.7f, 0.7f, m_fClear));
		}
		if (m_nCount <= 0)
		{
			SetDeath(true);
		}
	}
}

//�`��
void CBomb::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CBomb *CBomb::Create(D3DXVECTOR3 pos, float fRadius, int nCount)
{
	CBomb *pBomb;
	pBomb = new CBomb(CScene::PRIORITY_EFFECT);
	if (pBomb != NULL)
	{
		pBomb->Init(pos, fRadius, nCount);
		pBomb->SetTexture(4);
	}
	return pBomb;
}