//=============================================================================
//
// ���j���� [explosion.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "explosion.h"
#include "renderer.h"
#include "player.h"
#include "keyboard.h"

CExplosion::CExplosion(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CExplosion::~CExplosion(void)
{

}

//������
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fRadius, int nMaxCount)
{
	CScene2D::Init(pos);
	SetSize(D3DXVECTOR2(fRadius, fRadius));
	ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	SetTex(0, 0.125f);
	Set();
	m_nMax = nMaxCount;
	m_nTexPat = 0;
	return S_OK;
}

//�I��
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CExplosion::Update(void)
{
	//�|�[�Y������Ȃ�
	if (CManager::GetPause() == false)
	{
		//�J�E���g�i�߂�
		m_nCount++;
		if (m_nCount >= m_nMax)
		{
			//�e�N�X�`���p�^�[���i�߂�
			m_nCount = 0;
			m_nTexPat++;

			//�e�N�X�`���p�^�[����1������������A�����łȂ�������e�N�X�`����ݒ肷��
			if (m_nTexPat >= 8)
			{
				SetDeath(true);
			}
			else
			{
				SetTex(m_nTexPat, 0.125f);
			}
		}
	}
}

//�`��
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float fRadius, int nMaxCount)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion(CScene::PRIORITY_CHARA);
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, fRadius, nMaxCount);
		pExplosion->SetTexture(16);
	}
	return pExplosion;
}