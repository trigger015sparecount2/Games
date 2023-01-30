//=============================================================================
//
// UI�̃e�L�X�g�������� [textui.h]
// Author : �O��q��
//
//=============================================================================
#include "textui.h"
#include "manager.h"
#include "renderer.h"

CTextUI::CTextUI(CScene::PRIORITY Priority) :CScene2D(Priority)
{

}

CTextUI::~CTextUI(void)
{

}

//������
HRESULT CTextUI::Init(int nSize, int nColor[4], TEXTTYPE texttype, char aText[128], RECT rect)
{
	memset(&m_aText[0], 0, sizeof(m_aText));
	strcpy(&m_aText[0], &aText[0]);
	int nCnt;
	for (nCnt = 0; nCnt < 4; nCnt++)
	{
		m_nColor[nCnt] = nColor[nCnt];
	}
	m_texttype = texttype;
	m_rect = rect;
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), nSize, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont);
	return S_OK;
}

//�I��
void CTextUI::Uninit(void)
{
	memset(&m_aText[0], 0, sizeof(m_aText));
	//���_�o�b�t�@�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
	Release();
}

//�X�V
void CTextUI::Update(void)
{
	
}

//�`��
void CTextUI::Draw(void)
{
	// �e�L�X�g�`��
	switch (m_texttype)
	{
	case TEXT_WORDBREAK:
		m_pFont->DrawText(NULL, &m_aText[0], -1, &m_rect, DT_WORDBREAK, D3DCOLOR_ARGB(m_nColor[0], m_nColor[1], m_nColor[2], m_nColor[3]));
		break;
	case TEXT_RIGHT:
		m_pFont->DrawText(NULL, &m_aText[0], -1, &m_rect, DT_RIGHT, D3DCOLOR_ARGB(m_nColor[0], m_nColor[1], m_nColor[2], m_nColor[3]));
		break;
	default:
		break;
	}
}

//�쐬
CTextUI *CTextUI::Create(int nSize, int nColor[4], TEXTTYPE texttype, char aText[128], RECT rect)
{
	CTextUI *pTextUI;
	pTextUI = new CTextUI(PRIORITY_PAUSEUI);
	if (pTextUI != NULL)
	{
		pTextUI->Init(nSize, nColor, texttype, aText, rect);
	}
	return pTextUI;
}

//���̓Z�b�g
void CTextUI::SetText(char aText[128])
{
	memset(&m_aText[0], 0, sizeof(m_aText));
	strcpy(&m_aText[0], &aText[0]);
}

//�F�ς���
void CTextUI::SetColor(int nColor[4])
{
	int nCnt;
	for (nCnt = 0; nCnt < 4; nCnt++)
	{
		m_nColor[nCnt] = nColor[nCnt];
	}
}