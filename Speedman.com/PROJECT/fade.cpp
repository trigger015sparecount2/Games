//*****************************************************************************
// �t�F�[�h�֘A����(Fade.cpp)
// Author : satou syusuke
//*****************************************************************************
#include "Fade.h"
#include "Scene2D.h"
#include "manager.h"
#include "Title.h"

//*****************************************************************************
//�ÓI
//*****************************************************************************
CFade::FADE CFade::m_afade = CFade::FADE_NONE;
CManager::MODE CFade::m_modenext = CManager::MODE_TITLE;
int CFade::m_ncolorFade = 255;
bool CFade::m_bUninit = false;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CFade::CFade(int nPriority) : CScene2D(nPriority)
{
	m_afade = CFade::FADE_IN;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CFade::~CFade()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CFade::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType)
{
	CScene2D::Init(pos);

	m_afade = CFade::FADE_IN;
	m_bUninit = false;

	CScene2D::SetTexture(nType);
	CScene2D::SetWidth(SizeX);
	CScene2D::SetHeight(SizeY);

	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CFade::Uninit()
{
	CScene2D::Uninit();
}
//*****************************************************************************
//�X�V
//*****************************************************************************
void CFade::Update()
{
	if (m_afade != FADE_NONE)
	{
		if (m_afade == FADE_IN)
		{
			m_ncolorFade -= 10;
			if (m_ncolorFade <= 0)
			{
				m_ncolorFade = 0;
				m_afade = FADE_NONE;
			}
		}
		else if (m_afade == FADE_OUT)
		{
			m_ncolorFade += 10;
			if (m_ncolorFade >= 255)
			{
				m_ncolorFade = 255;
				m_afade = FADE_IN;
				m_bUninit = true;
			}
		}
	}
	CScene2D::FadeColorChange(m_ncolorFade);

	if (m_bUninit == true)
	{
		//Uninit();
		//SetDeath(true);
		CManager::SetMode(m_modenext);
	}

}

//*****************************************************************************
//�`��
//*****************************************************************************
void CFade::Draw()
{
	CScene2D::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CFade *CFade::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType)
{
	CFade * pFade = NULL;
	pFade = new CFade(6);
	if (pFade != NULL)
	{
		pFade->Init(pos, SizeX, SizeY, nType);
	}
	return pFade;
}

//*****************************************************************************
// �t�F�[�h�Z�b�g
//*****************************************************************************
void CFade::SetFade(CManager::MODE ModeNext)
{
	if (m_afade == FADE_NONE)
	{
		m_afade = FADE_OUT;
		m_modenext = ModeNext;
		m_ncolorFade = 0;
		m_bUninit = false;
	}
}
