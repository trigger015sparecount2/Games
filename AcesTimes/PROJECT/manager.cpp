//=============================================================================
//
// �}�l�[�W�� [Manager.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

#include "keyboard.h"
#include "gamepad.h"

#include "title.h"
#include "game.h"
#include "result.h"
#include "select.h"
#include "save.h"
#include "load.h"
#include "sound.h"

//�ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CGamePad *CManager::m_pGamepad = NULL;

CManager::MODE CManager::m_aMode = CManager::MODE_TITLE;

CTitle *CManager::m_pTitle = NULL;
CSelect *CManager::m_pSelect = NULL;
CSave *CManager::m_pSave = NULL;
CLoad *CManager::m_pLoad = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;

bool CManager::m_bGameEnd = false;
bool CManager::m_bPause = false;

int CManager::m_nStage = 0;
int CManager::m_nType = 0;
int CManager::m_nMoney = 0;
int CManager::m_nScore = 0;
int CManager::m_nGetMoney = 0;
int CManager::m_nNumAircraft = 1;
bool CManager::m_aAircraft[6] = {};

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pKeyboard = new CKeyboard;
	m_pKeyboard->Init(hInstance, hWnd);
	m_pGamepad = new CGamePad;
	m_pGamepad->Init(hInstance, hWnd);
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�e�N�X�`���ǂݍ���	
	CScene2D::CreateTexture();

	SetMode(m_aMode);

	m_nNumAircraft = 1;
	m_aAircraft[0] = true;
	int nCnt;
	for (nCnt = 1; nCnt < 6; nCnt++)
	{
		m_aAircraft[nCnt] = false;
	}

	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CManager::Uninit()
{
	CScene2D::UninitTexture();

	CScene::ReleaseAll();
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
		delete m_pGamepad;
		m_pGamepad = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pTitle != NULL)
	{
		m_pTitle = NULL;
	}
	if (m_pLoad != NULL)
	{
		m_pLoad = NULL;
	}
	if (m_pSave != NULL)
	{
		m_pSave = NULL;
	}
	if (m_pSelect != NULL)
	{
		m_pSelect = NULL;
	}
	if (m_pGame != NULL)
	{
		m_pGame = NULL;
	}
	if (m_pResult != NULL)
	{
		m_pResult = NULL;
	}
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CManager::Update()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	if (m_pGamepad != NULL && CGamePad::GetGamePad() == true)
	{
		m_pGamepad->Update();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CManager::Draw()
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
//	�Q�[���p�b�h�擾
//=============================================================================
CGamePad *CManager::GetGamepad()
{
	bool bGamepad = CGamePad::GetGamePad();

	if (bGamepad == true)
	{
		return m_pGamepad;
	}
	else
	{
		return NULL;
	}
}

//=============================================================================
//���[�h�Z�b�g
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	CSound::Stop();
	CScene::ReleaseAll();
	switch (m_aMode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle = NULL;
		}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect = NULL;
		}
		break;
	case MODE_LOAD:
		if (m_pLoad != NULL)
		{
			m_pLoad = NULL;
		}
		break;
	case MODE_SAVE:
		if (m_pSave != NULL)
		{
			m_pSave = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult = NULL;
		}
		break;

	default:
		break;
	}
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_SELECT:
		m_pSelect = CSelect::Create();
		break;
	case MODE_LOAD:
		m_pLoad = CLoad::Create();
		break;
	case MODE_SAVE:
		m_pSave = CSave::Create();
		break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;

	default:
		break;
	}
	SetPause(false);
	m_aMode = mode;
}