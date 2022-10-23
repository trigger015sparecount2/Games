//*****************************************************************************
// UI�i�I�����j�֘A����(Select_UI.cpp)
// Author : �����G��
//
//UI�N���X����剻�������ߏ����ɂ��N���X�������s���܂���
//*****************************************************************************
#include "Select_UI.h"

#include "Title.h"
#include "Game.h"
#include "GameOver.h"
#include "tutorial.h"

#include "keyboard.h"
#include "Fade.h"
#include "Player.h"


//*****************************************************************************
//�ÓI�����o
//*****************************************************************************
int CSelectUI::m_PauseSelect = 1;
bool CSelectUI::m_bFade = false;
CKeyboard *CSelectUI::m_pKeyboard = NULL;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CSelectUI::CSelectUI(int nPriority) : CUI(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UINum = -1;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CSelectUI::~CSelectUI()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CSelectUI::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int SelectNum, SELECT_UI_TYPE UIType)
{
	CUI::Init(pos, SizeX, SizeY, nType);
	CScene2D::SetObjType(CScene::OBJECTTYPE_SERECTUI);

	m_pos = pos;
	m_UINum = SelectNum;

	m_nType = UIType;

	m_fSizeX = SizeX;
	m_fSizeY = SizeY;

	m_pKeyboard = CManager::GetKeyboard();
	m_bUninit = false;
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CSelectUI::Uninit()
{
	CUI::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CSelectUI::Update()
{
	CManager::MODE Mode = CManager::GetMode();
	bool bPause = CManager::GetPause();
	int nControl = CPlayer::GetControlNum();

	switch (m_nType)
	{
	case(CSelectUI::SELECT_UI_NOMAL):
		switch (Mode)
		{
		case(CManager::MODE_TITLE):
			CTitle *pTitle;
			pTitle = CManager::GetTitle();
			if (pTitle != NULL)
			{
				int nSerectNum = ((CTitle*)pTitle)->GetSerectNum();	//�Z���N�g�ԍ��擾
				if (m_UINum == nSerectNum)
				{
					m_color.r = 255;
					m_color.g = 255;
					m_color.b = 255;
					m_color.a = 255;

					CScene2D::ColorChange(m_color);

					CScene2D::SetWhidth(m_fSizeX + 20);
					CScene2D::SetHight(m_fSizeY + 10);

				}
				else
				{
					m_color.r = 100;
					m_color.g = 100;
					m_color.b = 100;
					m_color.a = 100;

					CScene2D::ColorChange(m_color);
					CScene2D::SetWhidth(m_fSizeX);
					CScene2D::SetHight(m_fSizeY);
				}
			}
			break;

		case(CManager::MODE_GAME):
			CGame *pGame;
			pGame = CManager::GetGame();
			if (pGame != NULL)
			{
				int nSerectNum = ((CGame*)pGame)->GetSelectNum();	//�Z���N�g�ԍ��擾
				if (m_UINum == nSerectNum)
				{
					m_color.r = 255;
					m_color.g = 255;
					m_color.b = 255;
					m_color.a = 255;

					CScene2D::ColorChange(m_color);

					CScene2D::SetWhidth(m_fSizeX + 20);
					CScene2D::SetHight(m_fSizeY + 10);

				}
				else
				{
					m_color.r = 100;
					m_color.g = 100;
					m_color.b = 100;
					m_color.a = 100;

					CScene2D::ColorChange(m_color);
					CScene2D::SetWhidth(m_fSizeX);
					CScene2D::SetHight(m_fSizeY);
				}
			}
			if (bPause == false)
			{
				m_bUninit = true;
			}
			break;
		case(CManager::MODE_TUTORIAL):
			CTutorial *pTutorial;
			pTutorial = CManager::GetTutorial();
			if (pTutorial != NULL)
			{
				int nSerectNum = ((CTutorial*)pTutorial)->GetSelectNum();	//�Z���N�g�ԍ��擾
				if (m_UINum == nSerectNum)
				{
					m_color.r = 255;
					m_color.g = 255;
					m_color.b = 255;
					m_color.a = 255;

					CScene2D::ColorChange(m_color);

					CScene2D::SetWhidth(m_fSizeX + 20);
					CScene2D::SetHight(m_fSizeY + 10);

				}
				else
				{
					m_color.r = 100;
					m_color.g = 100;
					m_color.b = 100;
					m_color.a = 100;

					CScene2D::ColorChange(m_color);
					CScene2D::SetWhidth(m_fSizeX);
					CScene2D::SetHight(m_fSizeY);
				}
			}
			if (bPause == false)
			{
				m_bUninit = true;
			}
			break;

		case(CManager::MODE_GAMEOVER):
			CGameOver *pGameOver;
			pGameOver = CManager::GetGameOver();

			if (pGameOver != NULL)
			{
				int nSerectNum = ((CGameOver*)pGameOver)->GetSerectNum();	//�Z���N�g�ԍ��擾
				if (m_UINum == nSerectNum)
				{
					m_color.r = 255;
					m_color.g = 255;
					m_color.b = 255;
					m_color.a = 255;

					CScene2D::ColorChange(m_color);
				}
				else
				{
					m_color.r = 100;
					m_color.g = 100;
					m_color.b = 100;
					m_color.a = 100;

					CScene2D::ColorChange(m_color);
				}
			}
			break;
		}
		break;
	case(CSelectUI::SELECT_UI_CONTROL):
		if (nControl == m_UINum)
		{
			m_color.r = 255;
			m_color.g = 255;
			m_color.b = 255;
			m_color.a = 255;
		}
		else if (nControl != m_UINum)
		{
			m_color.r = 0;
			m_color.g = 0;
			m_color.b = 0;
			m_color.a = 0;
		}
		CScene2D::ColorChange(m_color);
		CScene2D::SetWhidth(m_fSizeX);
		CScene2D::SetHight(m_fSizeY);
		break;
	}

	if (m_bUninit == true)
	{
		SetDeath(true);
	}

}

//*****************************************************************************
//�`��
//*****************************************************************************
void CSelectUI::Draw()
{
	CUI::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CSelectUI *CSelectUI::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int SelectNum, SELECT_UI_TYPE UIType)
{
	CSelectUI * pSelectUI = NULL;
	pSelectUI = new CSelectUI(5);
	if (pSelectUI != NULL)
	{
		pSelectUI->Init(pos, SizeX, SizeY, nType, SelectNum, UIType);
	}
	return pSelectUI;
}

//*****************************************************************************
//�I��ԍ����Z�b�g
//*****************************************************************************
void CSelectUI::SetPauseSelect(int nPause)
{
	m_PauseSelect = nPause;
}