//=============================================================================
// �Z���N�g�Ǘ�[select.cpp]
// Author : �O��q��
//=============================================================================
//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#if 1
#include "select.h"
#include "keyboard.h"
#include "ui.h"
#include "renderer.h"

#include "game.h"
#include "gamepad.h"
#include "fade.h"

#include "sound.h"
#endif

//*****************************************************************************
//�ÓI
//*****************************************************************************
CSelect::Aircraft CSelect::m_aAircraft[6] = {};

//*****************************************************************************
//�}�N��
//*****************************************************************************


#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CSelect::CSelect(PRIORITY Priority) : CScene(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CSelect::~CSelect()
{
}
#endif

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CSelect::Init(D3DXVECTOR3)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();
	Load();
	RankLoad();

	//SELECT
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.3f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	//�퓬�@
	//1�Ԗ�
	m_pUI[0] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 65.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[1] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 465.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[2] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 235.0f), 30, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[3] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 190.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), m_aAircraft[0].nHudTexType, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	//2�Ԗ�
	m_pUI[4] = CUI::Create(D3DXVECTOR3(1040.0f, 130.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[5] = CUI::Create(D3DXVECTOR3(1040.0f, 400.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[6] = CUI::Create(D3DXVECTOR3(1040.0f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 145.0f), 30, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[7] = CUI::Create(D3DXVECTOR3(1040.0f, 265.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), m_aAircraft[1].nHudTexType, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//3�Ԗ�
	m_pUI[8] = CUI::Create(D3DXVECTOR3(1440.0f, 130.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[9] = CUI::Create(D3DXVECTOR3(1440.0f, 400.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[10] = CUI::Create(D3DXVECTOR3(1440.0f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 145.0f), 30, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[11] = CUI::Create(D3DXVECTOR3(1440.0f, 265.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), m_aAircraft[2].nHudTexType, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//4�Ԗ�
	m_pUI[12] = CUI::Create(D3DXVECTOR3(-560.0f, 130.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[13] = CUI::Create(D3DXVECTOR3(-560.0f, 400.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[14] = CUI::Create(D3DXVECTOR3(-560.0f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 145.0f), 30, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[15] = CUI::Create(D3DXVECTOR3(-560.0f, 265.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), m_aAircraft[3].nHudTexType, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//5�Ԗ�
	m_pUI[16] = CUI::Create(D3DXVECTOR3(-160.0f, 130.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[17] = CUI::Create(D3DXVECTOR3(-160.0f, 400.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[18] = CUI::Create(D3DXVECTOR3(-160.0f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 145.0f), 30, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[19] = CUI::Create(D3DXVECTOR3(-160.0f, 265.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), m_aAircraft[4].nHudTexType, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	//6�Ԗ�
	m_pUI[20] = CUI::Create(D3DXVECTOR3(240.0f, 130.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[21] = CUI::Create(D3DXVECTOR3(240.0f, 400.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[22] = CUI::Create(D3DXVECTOR3(240.0f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 145.0f), 30, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[23] = CUI::Create(D3DXVECTOR3(240.0f, 265.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), m_aAircraft[5].nHudTexType, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X�e�[�^�X�Q�[�W
	m_pUI[24] = CUI::Create(D3DXVECTOR3(600.0f, 337.0f, 0.0f), D3DXVECTOR2(0.0f, 13.0f), 32, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[25] = CUI::Create(D3DXVECTOR3(600.0f, 363.0f, 0.0f), D3DXVECTOR2(0.0f, 13.0f), 32, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[26] = CUI::Create(D3DXVECTOR3(600.0f, 389.0f, 0.0f), D3DXVECTOR2(0.0f, 13.0f), 32, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[27] = CUI::Create(D3DXVECTOR3(600.0f, 415.0f, 0.0f), D3DXVECTOR2(0.0f, 13.0f), 32, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[28] = CUI::Create(D3DXVECTOR3(600.0f, 441.0f, 0.0f), D3DXVECTOR2(0.0f, 13.0f), 32, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���
	m_pUI[29] = CUI::Create(D3DXVECTOR3(440.0f, 270.0f, 0.0f), D3DXVECTOR2(40.0f, 60.0f), 31, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[30] = CUI::Create(D3DXVECTOR3(840.0f, 270.0f, 0.0f), D3DXVECTOR2(40.0f, 60.0f), 31, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//�X�e�[�W
	//1�Ԗ�
	m_pStageUI[0] = CUI::Create(D3DXVECTOR3(240.0f, 65.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pStageUI[1] = CUI::Create(D3DXVECTOR3(240.0f, 465.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[2] = CUI::Create(D3DXVECTOR3(240.0f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 235.0f), 30, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[3] = CUI::Create(D3DXVECTOR3(240.0f, 200.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), 33, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[4] = CUI::Create(D3DXVECTOR3(240.0f, 400.0f, 0.0f), D3DXVECTOR2(150.0f, 60.0f), 35, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//2�Ԗ�
	m_pStageUI[5] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 65.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pStageUI[6] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 465.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[7] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 235.0f), 30, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[8] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), 7, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[9] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 400.0f, 0.0f), D3DXVECTOR2(200.0f, 60.0f), 36, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//3�Ԗ�
	m_pStageUI[10] = CUI::Create(D3DXVECTOR3(1040.0f, 65.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pStageUI[11] = CUI::Create(D3DXVECTOR3(1040.0f, 465.0f, 0.0f), D3DXVECTOR2(240.0f, 50.0f), 29, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[12] = CUI::Create(D3DXVECTOR3(1040.0f, 265.0f, 0.0f), D3DXVECTOR2(240.0f, 235.0f), 30, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[13] = CUI::Create(D3DXVECTOR3(1040.0f, 200.0f, 0.0f), D3DXVECTOR2(170.0f, 170.0f), 34, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStageUI[14] = CUI::Create(D3DXVECTOR3(1040.0f, 400.0f, 0.0f), D3DXVECTOR2(150.0f, 60.0f), 37, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CUI::Create(D3DXVECTOR3(100.0f, 620.0f, 0.0f), D3DXVECTOR2(30.0f, 140.0f), 5, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CUI::Create(D3DXVECTOR3(1180.0f, 620.0f, 0.0f), D3DXVECTOR2(30.0f, 140.0f), 5, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	CUI::Create(D3DXVECTOR3(640.0f, 620.0f, 0.0f), D3DXVECTOR2(744.0f, 140.0f), 6, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CManager::SetPause(false);
	m_nSelect[0] = 0;
	m_nSelect[1] = 0;

	//�t�H���g����
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 40, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[0]);
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 26, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[1]);
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 26, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[2]);
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[3]);

	m_nClear = 0;
	m_bClear = true;
	m_nCntSelect = 0;
	m_nCntGauge = 10;
	m_fStageClear = 0.0f;
	m_Select = SELECT_NONE;
	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CSelect::Uninit()
{
	int nCnt;
	for (nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_pFont[nCnt] != NULL)
		{
			m_pFont[nCnt]->Release();
			m_pFont[nCnt] = NULL;
		}
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	for (nCnt = 0; nCnt < 15; nCnt++)
	{
		if (m_pStageUI[nCnt] != NULL)
		{
			m_pStageUI[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 31; nCnt++)
	{
		if (m_pUI[nCnt] != NULL)
		{
			m_pUI[nCnt] = NULL;
		}
	}
	CScene::Release();
}

//*****************************************************************************
// �X�V
//*****************************************************************************
void CSelect::Update()
{
	//�e�L�X�g�ύX�J�E���g�i�߂�B�i�񂾂�e�L�X�g�����ɖ߂�
	if (m_nCntChange > 0)
	{
		m_nCntChange--;
		if (m_nCntChange <= 0)
		{
			Text();
			m_nCntChange = 0;
		}
	}

	//�X�e�[�W�I�����F�������ꍇ�A�Z������
	if (m_bStage == true && m_fStageClear < 1.0f)
	{
		m_fStageClear += 0.1f;
		if (m_fStageClear > 1.0f)
		{
			m_fStageClear = 1.0f;
		}
		int nCntStage;
		for (nCntStage = 0; nCntStage < 15; nCntStage++)
		{
			if ((nCntStage + 2) % 5 == 0)
			{
				if (m_nSelect[1] * 5 <= nCntStage && nCntStage < (m_nSelect[1] + 1) * 5)
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fStageClear));
				}
				else
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.6f, 0.6f, 0.6f, m_fStageClear));
				}
			}
			else
			{
				if (m_nSelect[1] * 5 <= nCntStage && nCntStage < (m_nSelect[1] + 1) * 5)
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fStageClear));
				}
				else
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.0f, 0.6f, 0.0f, m_fStageClear));
				}
			}
		}
	}
	//�퓬�@�I�����F���Z���ꍇ�A��������
	else if(m_bStage == false && m_fStageClear > 0.0f)
	{
		m_fStageClear -= 0.1f;
		if (m_fStageClear < 0.0f)
		{
			m_pUI[29]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			m_pUI[30]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			m_fStageClear = 0.0f;
			m_nCntGauge = 10;
		}
		int nCntStage;
		for (nCntStage = 0; nCntStage < 15; nCntStage++)
		{
			if ((nCntStage + 2) % 5 == 0)
			{
				if (m_nSelect[1] * 5 <= nCntStage && nCntStage < (m_nSelect[1] + 1) * 5)
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fStageClear));
				}
				else
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.6f, 0.6f, 0.6f, m_fStageClear));
				}
			}
			else
			{
				if (m_nSelect[1] * 5 <= nCntStage && nCntStage < (m_nSelect[1] + 1) * 5)
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fStageClear));
				}
				else
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.0f, 0.6f, 0.0f, m_fStageClear));
				}
			}
		}
	}

	//�I�񂾃J�E���g��i�߂�
	if (m_nCntSelect > 0)
	{
		m_nCntSelect--;
		int nCntGroup;
		int nCntUI;
		switch (m_Select)
		{
		case SELECT_LEFT:	//��
			//�e�퓬�@
			for (nCntGroup = 0; nCntGroup < 6; nCntGroup++)
			{
				//�eUI�A�l�p��A���A�^�񒆁A�퓬�@�̃V���G�b�g
				for (nCntUI = 0; nCntUI < 4; nCntUI++)
				{
					D3DXVECTOR3 pos = m_pUI[nCntGroup * 4 + nCntUI]->GetPos();
					D3DXVECTOR2 size = m_pUI[nCntGroup * 4 + nCntUI]->GetSize();
					//�E�ɓ�����
					pos.x += 50.0f;
					if (pos.x > 1440.0f)
					{
						pos.x -= 2400.0f;
					}

					//�I�񂾐퓬�@�Ɠ����ꍇ�A�l�p���㉺�ɑ傫�����A�퓬�@��������ɓ�����
					if (nCntGroup == m_nSelect[0])
					{
						switch (nCntUI)
						{
						case 0: //�l�p��
							pos.y -= 9.0f;
							if (pos.y < 65.0f)
							{
								pos.y = 65.0f;
							}
							break;
						case 1: //�l�p��
							pos.y += 9.0f;
							if (pos.y > 465.0f)
							{
								pos.y = 465.0f;
							}
							break;
						case 2: //�l�p�^��
							size.y += 12.0f;
							if (size.y > 235.0f)
							{
								size.y = 235.0f;
							}
							break;
						case 3: //HUD�퓬�@
							pos.y -= 10.0f;
							if (pos.y < 190.0f)
							{
								pos.y = 190.0f;
							}
							break;
						default:
							break;
						}
					}
					//���X�I��ł����퓬�@�Ɠ����ꍇ�A�l�p���㉺�ɏ��������A�퓬�@���������ɓ�����
					else if ((m_nSelect[0] + 1) % 6 == nCntGroup)
					{
						switch (nCntUI)
						{
						case 0: //�l�p��
							pos.y += 9.0f;
							if (pos.y > 130.0f)
							{
								pos.y = 130.0f;
							}
							break;
						case 1: //�l�p��
							pos.y -= 9.0f;
							if (pos.y < 400.0f)
							{
								pos.y = 400.0f;
							}
							break;
						case 2: //�l�p�^��
							size.y -= 12.0f;
							if (size.y < 145.0f)
							{
								size.y = 145.0f;
							}
							break;
						case 3: //HUD�퓬�@
							pos.y += 10.0f;
							if (pos.y > 265.0f)
							{
								pos.y = 265.0f;
							}
							break;
						default:
							break;
						}
					}
					//pos��傫���̐ݒ�
					m_pUI[nCntGroup * 4 + nCntUI]->SetPos(pos);
					m_pUI[nCntGroup * 4 + nCntUI]->SetSize(size);
					m_pUI[nCntGroup * 4 + nCntUI]->Set();
				}
			}
			break;
		case SELECT_RIGHT:	//�E
			//�e�퓬�@����
			for (nCntGroup = 0; nCntGroup < 6; nCntGroup++)
			{
				//�eUI�A�l�p��A���A�^�񒆁A�퓬�@�̃V���G�b�g
				for (nCntUI = 0; nCntUI < 4; nCntUI++)
				{
					D3DXVECTOR3 pos = m_pUI[nCntGroup * 4 + nCntUI]->GetPos();
					D3DXVECTOR2 size = m_pUI[nCntGroup * 4 + nCntUI]->GetSize();
					//���ɓ�����
					pos.x -= 50.0f;
					if (pos.x < -560.0f)
					{
						pos.x += 2400.0f;
					}

					//�I�񂾐퓬�@�Ɠ����ꍇ�A�l�p���㉺�ɑ傫�����A�퓬�@��������ɓ�����
					if (nCntGroup == m_nSelect[0])
					{
						switch (nCntUI)
						{
						case 0: //�l�p��
							pos.y -= 9.0f;
							if (pos.y < 65.0f)
							{
								pos.y = 65.0f;
							}
							break;
						case 1: //�l�p��
							pos.y += 9.0f;
							if (pos.y > 465.0f)
							{
								pos.y = 465.0f;
							}
							break;
						case 2: //�l�p�^��
							size.y += 12.0f;
							if (size.y > 235.0f)
							{
								size.y = 235.0f;
							}
							break;
						case 3: //HUD�퓬�@
							pos.y -= 10.0f;
							if (pos.y < 190.0f)
							{
								pos.y = 190.0f;
							}
							break;
						default:
							break;
						}
					}
					//���X�I��ł����퓬�@�Ɠ����ꍇ�A�l�p���㉺�ɏ��������A�퓬�@���������ɓ�����
					else if (m_nSelect[0] == 0 && nCntGroup == 5 || m_nSelect[0] - 1 == nCntGroup)
					{
						switch (nCntUI)
						{
						case 0: //�l�p��
							pos.y += 9.0f;
							if (pos.y > 130.0f)
							{
								pos.y = 130.0f;
							}
							break;
						case 1: //�l�p��
							pos.y -= 9.0f;
							if (pos.y < 400.0f)
							{
								pos.y = 400.0f;
							}
							break;
						case 2: //�l�p�^��
							size.y -= 12.0f;
							if (size.y < 145.0f)
							{
								size.y = 145.0f;
							}
							break;
						case 3: //HUD�퓬�@
							pos.y += 10.0f;
							if (pos.y > 265.0f)
							{
								pos.y = 265.0f;
							}
							break;
						default:
							break;
						}
					}
					//pos��傫���̐ݒ�
					m_pUI[nCntGroup * 4 + nCntUI]->SetPos(pos);
					m_pUI[nCntGroup * 4 + nCntUI]->SetSize(size);
					m_pUI[nCntGroup * 4 + nCntUI]->Set();
				}
			}
			break;
		default:
			break;
		}

		if (m_nCntSelect <= 0)
		{
			m_nCntSelect = 0;
			m_nCntGauge = 10;
		}
	}

	//�Q�[�W�J�E���g�i�߂�
	if (m_nCntGauge > 0)
	{
		m_nCntGauge--;
		//�Q�[�W�L�΂��Ă���
		int nCntUI;
		for (nCntUI = 0; nCntUI < 5; nCntUI++)
		{
			D3DXVECTOR2 size = m_pUI[24 + nCntUI]->GetSize();
			switch (nCntUI)
			{
			case 0:
				size.x += 17.0f * (m_aAircraft[m_nSelect[0]].fSpeed / 10.0f);
				break;
			case 1:
				size.x += 17.0f * ((float)m_aAircraft[m_nSelect[0]].nHP / 10.0f);
				break;
			case 2:
				size.x += 17.0f * ((float)(m_aAircraft[m_nSelect[0]].ShotType + 1) / CPlayer::SHOTTYPE_MAX);
				break;
			case 3: 
				size.x += 17.0f * ((1000.0f - m_aAircraft[m_nSelect[0]].nMaxSlow) / 1000.0f);
				break;
			case 4:
				size.x += 17.0f * ((1500.0f - m_aAircraft[m_nSelect[0]].nMaxReturn) / 1500.0f);
				break;
			default:
				break;
			}
			m_pUI[24 + nCntUI]->SetHGauge(size);
		}
		if (m_nCntGauge <= 0)
		{
			m_nCntGauge = 0;
		}
	}

	//�Q�[���p�b�h�q�����Ă��邩
	if (m_pGamePad != NULL)
	{
		//�X�e�[�W�I��
		if (m_bStage == true)
		{
			if (m_pGamePad->TriggerCrossKey() == 27000.0f)
			{
				Select(-1);
			}
			else if (m_pGamePad->TriggerCrossKey() == 9000.0f)
			{
				Select(1);
			}
		}
		//�w�����Ȃ�(�퓬�@�I��)
		else if(m_bBuy == false)
		{
			if (m_pGamePad->PressCrossKey() == 27000.0f)
			{
				Select(-1);
			}
			else if (m_pGamePad->PressCrossKey() == 9000.0f)
			{
				Select(1);
			}
		}

		//����
		if (m_pGamePad->GetButton(CGamePad::DIP_B) == true)
		{
			//�t�F�[�h�������ĂȂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				//�I������Ă�퓬�@���w���ς݂ȏꍇ
				if (CManager::GetAircraft(m_nSelect[0]) == true)
				{
					//�X�e�[�W�I������
					if (m_bStage == true)
					{
						CManager::SetType(m_nSelect[0]);
						CManager::SetStage(m_nSelect[1]);
						CFade::SetFade(CManager::MODE_GAME);
						CSound::Play(CSound::SOUND_LABEL_YES);
					}
					//�X�e�[�W�I���J�n
					else
					{
						StageSelect();
					}

				}
				else
				{
					//�w��
					Buy();
				}
			}
		}

		//�L�����Z��
		if (m_pGamePad->GetButton(CGamePad::DIP_A) == true)
		{
			//�w�����邩
			if (m_bBuy == true)
			{
				//�L�����Z��
				m_bBuy = false;
				Text();
				CSound::Play(CSound::SOUND_LABEL_CANCEL);
			}
			//�X�e�[�W�I��
			else if (m_bStage == true)
			{
				StageCancel();
			}
			//�^�C�g���ɖ߂�
			else if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::SetFade(CManager::MODE_TITLE);
				CSound::Play(CSound::SOUND_LABEL_CANCEL);
			}
		}
	}
	//�L�[�{�[�h�q�����Ă�
	else if (m_pKeyboard != NULL)
	{
		//�X�e�[�W�I��
		if (m_bStage == true)
		{
			if (m_pKeyboard->GetKey(DIK_A) == true)
			{
				Select(-1);
			}
			else if (m_pKeyboard->GetKey(DIK_D) == true)
			{
				Select(1);
			}
		}
		//�w�����Ȃ�(�퓬�@�I��)
		else if (m_bBuy == false)
		{
			if (m_pKeyboard->GetPress(DIK_A) == true)
			{
				Select(-1);
			}
			else if (m_pKeyboard->GetPress(DIK_D) == true)
			{
				Select(1);
			}
		}

		//����
		if (m_pKeyboard->GetKey(DIK_J) == true)
		{
			//�t�F�[�h�������ĂȂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				//�I������Ă�퓬�@���w���ς݂ȏꍇ
				if (CManager::GetAircraft(m_nSelect[0]) == true)
				{
					//�X�e�[�W�I������
					if (m_bStage == true)
					{
						CManager::SetType(m_nSelect[0]);
						CManager::SetStage(m_nSelect[1]);
						CFade::SetFade(CManager::MODE_GAME);
						CSound::Play(CSound::SOUND_LABEL_YES);
					}
					//�X�e�[�W�I���J�n
					else
					{
						StageSelect();
					}
				}
				else
				{
					//�w��
					Buy();
				}
			}
		}

		//�L�����Z��
		if (m_pKeyboard->GetKey(DIK_I) == true)
		{
			//�w�����邩
			if (m_bBuy == true)
			{
				//�L�����Z��
				m_bBuy = false;
				Text();
				CSound::Play(CSound::SOUND_LABEL_CANCEL);
			}
			//�X�e�[�W�I��
			else if (m_bStage == true)
			{
				StageCancel();
			}
			//�^�C�g���ɖ߂�
			else if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::SetFade(CManager::MODE_TITLE);
				CSound::Play(CSound::SOUND_LABEL_CANCEL);
			}
		}
	}

	//�e�L�X�g�̓����x�B�������ĕ��͕ς���
	if (m_bClear == true)
	{
		m_nClear -= 26;
		if (m_nClear <= 0)
		{
			m_nClear = 0;
			m_bClear = false;
			m_nCntChange = 0;
			Text();
		}
	}
	//�Z�����Ă���
	else if (m_nClear < 255)
	{
		m_nClear += 26;
		if (m_nClear >= 255)
		{
			m_nClear = 255;
		}
	}
}

//*****************************************************************************
//�`��
//***************************************************************************** 
void CSelect::Draw()
{
	//�e�L�X�g�̘g
	RECT rect[4];
	rect[0] = { 110, 535, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 20 };
	rect[1] = { 110, 578, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 20 };
	rect[2] = { 400, 324, 600, SCREEN_HEIGHT - 20 };
	rect[3] = { 870, 470, 1160, SCREEN_HEIGHT - 20 };

	//�퓬�@�̕���
	char str[2][64];
	wsprintf(&str[0][0], "SPEED:\nDEFENSE:\nRANGE:\nSLOW:\nRETURN:");	//�X�e�[�^�X
	wsprintf(&str[1][0], "MONEY:%6d", CManager::GetMoney());			//����

	// �e�L�X�g�`��
	m_pFont[0]->DrawText(NULL, m_Name, -1, &rect[0], DT_WORDBREAK, D3DCOLOR_ARGB(m_nClear, 0, 255, 0));	//���O
	m_pFont[1]->DrawText(NULL, m_Str, -1, &rect[1], DT_WORDBREAK, D3DCOLOR_ARGB(m_nClear, 0, 255, 0));	//������
	if (m_nCntSelect <= 0 && m_bStage == false)
	{
		m_pFont[2]->DrawText(NULL, &str[0][0], -1, &rect[2], DT_RIGHT, D3DCOLOR_ARGB(255, 0, 255, 0));	//�X�e�[�^�X
	}
	if (m_fStageClear <= 0.0f && m_bStage == false)
	{
		m_pFont[3]->DrawText(NULL, &str[1][0], -1, &rect[3], DT_RIGHT, D3DCOLOR_ARGB(255, 0, 255, 0));	//������
	}
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CSelect *CSelect::Create()
{
	CSelect *pSelect = NULL;
	pSelect = new CSelect(PRIORITY_PAUSEUI);		//�������m��
													//NULL�`�F�b�N
	if (pSelect != NULL)
	{
		pSelect->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pSelect;
}

//�ǂݍ���
void CSelect::Load()
{
	//�t�@�C���ǂݍ���
	char aFile[256];
	FILE *pFile = fopen(FILE_AIRCRAFT, "r");

	bool bStatus;
	int nCntAircraft = 0;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "STATUS") == 0)	//�X�e�[�^�X�ǂݍ���
			{
				bStatus = true;
			}
			if (strcmp(&aFile[0], "END_STATUS") == 0)	//�X�e�[�^�X�ǂݍ��݉���
			{
				bStatus = false;
				nCntAircraft++;
			}
			if (bStatus == true)
			{
				if (strcmp(&aFile[0], "NAME") == 0)	//���O
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &m_aAircraft[nCntAircraft].aName[0]);
				}
				if (strcmp(&aFile[0], "NICKNAME") == 0)	//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &m_aAircraft[nCntAircraft].aNickName[0]);
				}
				if (strcmp(&aFile[0], "SPEED") == 0)	//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_aAircraft[nCntAircraft].fSpeed);
				}
				if (strcmp(&aFile[0], "HP") == 0)	//�̗�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nHP);
				}
				if (strcmp(&aFile[0], "SHOTTYPE") == 0)	//������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].ShotType);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0)	//�e�N�X�`�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nTexType);
				}
				if (strcmp(&aFile[0], "HUD_TEXTYPE") == 0)	//HUD�̃e�N�X�`�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nHudTexType);
				}
				if (strcmp(&aFile[0], "SHADOW_TEXTYPE") == 0)	//�e�̃e�N�X�`�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nShadowTex);
				}
				if (strcmp(&aFile[0], "MAX_SLOW") == 0)	//���e�̃C���^�[�o��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nMaxSlow);
				}
				if (strcmp(&aFile[0], "MAX_RETURN") == 0)	//�����߂��̃C���^�[�o��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nMaxReturn);
				}
				if (strcmp(&aFile[0], "MONEY") == 0)	//�w�����z
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nMoney);
				}
				if (strcmp(&aFile[0], "EXPLAIN_LINES") == 0)	//�����̕��͍s��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aAircraft[nCntAircraft].nExplainLines);
				}
				if (strcmp(&aFile[0], "EXPLAIN") == 0)	//�����̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					int nCntlines;
					for (nCntlines = 0; nCntlines < m_aAircraft[nCntAircraft].nExplainLines; nCntlines++)
					{
						fscanf(pFile, "%s", &m_aAircraft[nCntAircraft].aExplain[nCntlines][0]);
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)	//END_SCRIPT�̕��������������
			{
				break;
			}
		}
		fclose(pFile);
	}
}

//�����L���O�ǂݍ���
void CSelect::RankLoad()
{
	//�t�@�C���ǂݍ���
	FILE *pFile = fopen(FILE_RANK, "r");
	int nCnt;
	if (pFile != NULL)
	{
		for (nCnt = 0; nCnt < 3; nCnt++)
		{
			fscanf(pFile, "%d", &m_nRank[nCnt]);
		}
		fclose(pFile);
	}
}

//�X�e�[�W�I���J�n
void CSelect::StageSelect()
{
	//�t�F�[�h�����ĂȂ�
	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		int nCntStage;
		for (nCntStage = 0; nCntStage < 15; nCntStage++)
		{
			//�X�e�[�W�̔w�iUI�̏ꍇ�A�F�𕁒ʒʂ�ɂ���
			if ((nCntStage + 2) % 5 == 0)
			{
				if (nCntStage < 5)
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
				else
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.0f));
				}
			}
			//����ȊO�̏ꍇ�A�Ί�ɂ���
			else
			{
				if (nCntStage < 5)
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
				}
				else
				{
					m_pStageUI[nCntStage]->ColorChange(D3DXCOLOR(0.0f, 0.6f, 0.0f, 0.0f));
				}
			}
		}

		//�X�e�[�^�X�Q�[�W�A�y�і���UI������
		int nCntText;
		for (nCntText = 0; nCntText < 5; nCntText++)
		{
			m_pUI[24 + nCntText]->SetSize(D3DXVECTOR2(0.0f, 13.0f));
			m_pUI[24 + nCntText]->Set();
		}
		m_pUI[29]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pUI[30]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_bClear = true;
		m_bStage = true;
		CSound::Play(CSound::SOUND_LABEL_YES);
	}
}

//�X�e�[�W�I������
void CSelect::StageCancel()
{
	CSound::Play(CSound::SOUND_LABEL_CANCEL);
	m_bClear = true;
	m_bStage = false;
	m_nSelect[1] = 0;
}

//�Ⴄ�̑I��
void CSelect::Select(int nAdd)
{
	//�Q�[�W�L�т����Ă邩�I��Ŏ��Ԍo���Ă邩�t�F�[�h�����ĂȂ�
	if (m_nCntGauge <= 0 && m_nCntSelect <= 0 && CFade::GetFade() == CFade::FADE_NONE)
	{
		//�X�e�[�W�I��
		if (m_bStage == true)
		{
			//�I��ł��X�e�[�WUI���Â�����
			int nCntText;
			for (nCntText = 0; nCntText < 5; nCntText++)
			{
				if (nCntText == 3)
				{
					m_pStageUI[m_nSelect[1] * 5 + nCntText]->ColorChange(D3DXCOLOR(0.6f, 0.6f, 0.6f, m_fStageClear));
				}
				else
				{
					m_pStageUI[m_nSelect[1] * 5 + nCntText]->ColorChange(D3DXCOLOR(0.0f, 0.6f, 0.0f, m_fStageClear));
				}
			}

			//�I�����Ă鐔���𑝌�����
			m_nSelect[1] += nAdd;
			if (m_nSelect[1] < 0)
			{
				m_nSelect[1] = 2;
			}
			else if (m_nSelect[1] > 2)
			{
				m_nSelect[1] = 0;
			}

			//�I�񂾃X�e�[�WUI�𖾂邭����
			for (nCntText = 0; nCntText < 5; nCntText++)
			{
				if (nCntText == 3)
				{
					m_pStageUI[m_nSelect[1] * 5 + nCntText]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fStageClear));
				}
				else
				{
					m_pStageUI[m_nSelect[1] * 5 + nCntText]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fStageClear));
				}
			}
			m_bClear = true;
		}
		//�w����ʂ���Ȃ�
		else if (m_bBuy == false)
		{
			//�I��ł��I����UI���Â�����
			int nCntText;
			for (nCntText = 0; nCntText < 4; nCntText++)
			{
				m_pUI[m_nSelect[0] * 4 + nCntText]->ColorChange(D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f));
			}

			//�X�e�[�^�X�Q�[�W�Z������
			for (nCntText = 0; nCntText < 5; nCntText++)
			{
				m_pUI[24 + nCntText]->SetSize(D3DXVECTOR2(0.0f, 13.0f));
				m_pUI[24 + nCntText]->Set();
			}

			//�E�����������A���������������f����
			if (nAdd > 0)
			{
				m_Select = SELECT_RIGHT;
			}
			else
			{
				m_Select = SELECT_LEFT;
			}

			//�I���������𑝌�����
			m_nSelect[0] += nAdd;
			if (m_nSelect[0] < 0)
			{
				m_nSelect[0] = 5;
			}
			else if (m_nSelect[0] > 5)
			{
				m_nSelect[0] = 0;
			}

			m_bClear = true;
			//�I������UI���邭����
			for (nCntText = 0; nCntText < 4; nCntText++)
			{
				m_pUI[m_nSelect[0] * 4 + nCntText]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
			m_nCntSelect = 8;
		}
		CSound::Play(CSound::SOUND_LABEL_CHOICE);
	}
}

//�@�̔���
void CSelect::Buy()
{
	int nMoney = CManager::GetMoney();
	//�w�����
	if (m_bBuy == true)
	{
		//���������炷�A�@�̎g����悤�ɂ���A���͕ς���
		nMoney -= m_aAircraft[m_nSelect[0]].nMoney;
		CManager::SetMoney(nMoney);
		CManager::SetAircraft(m_nSelect[0], true);
		memset(&m_Name[0], 0, sizeof(m_Name));
		memset(&m_Str[0], 0, sizeof(m_Str));
		wsprintf(&m_Name[0], "NAME:%-10sNICKNAME:%-22s�w���ς�\n", &m_aAircraft[m_nSelect[0]].aName, &m_aAircraft[m_nSelect[0]].aNickName, m_aAircraft[m_nSelect[0]].nMoney);
		int nCntlines;
		for (nCntlines = 0; nCntlines < m_aAircraft[m_nSelect[0]].nExplainLines; nCntlines++)
		{
			wsprintf(&m_Str[strlen(m_Str)], "%s\n", &m_aAircraft[m_nSelect[0]].aExplain[nCntlines][0]);
		}
		m_bBuy = false;
		CSound::Play(CSound::SOUND_LABEL_BUY);
	}
	else
	{
		//������������Ȃ��ꍇ
		if (m_aAircraft[m_nSelect[0]].nMoney > nMoney)
		{
			//���͕ύX
			memset(&m_Str[0], 0, sizeof(m_Str));
			wsprintf(&m_Str[0], "����������܂���\n");
			m_nCntChange = 100;
			CSound::Play(CSound::SOUND_LABEL_CANCEL);
		}
		//����������Ă�
		else
		{
			//���͕ύX
			memset(&m_Str[0], 0, sizeof(m_Str));
			if (m_pGamePad == NULL)
			{
				wsprintf(&m_Str[0], "���̋@�̂��w�����܂����H\n����:J    �L�����Z��:I\n");
			}
			else
			{
				wsprintf(&m_Str[0], "���̋@�̂��w�����܂����H\n����:B    �L�����Z��:A\n");
			}
			m_bBuy = true;
			CSound::Play(CSound::SOUND_LABEL_YES);
		}
	}
}

//���͕ύX
void CSelect::Text()
{
	memset(&m_Name[0], 0, sizeof(m_Name));
	memset(&m_Str[0], 0, sizeof(m_Str));
	if (m_bStage == true)
	{
		//�X�e�[�W�I��
		switch (m_nSelect[1])
		{
		case 0:
			wsprintf(&m_Name[0], "STAGE:���w     EASY     HIGH SCORE:%8d\n", m_nRank[0]);
			wsprintf(&m_Str[0], "����2100�N�A�Ȋw�͑啝�ɔ��W���A���Ԃ���������悤�ɂȂ����B\n����Ȓ��A�����Ƃ��푈���d�|���Ă����B��X�͓P�ނ��邵���Ȃ������B\n");
			wsprintf(&m_Str[strlen(m_Str)], "����ŋ}篁A�b���������ĕҐ������B���̗b�������̒���'��'�������B\n'��'�ɂƂ��Ă̏��C���B������������A'��'�̕���͎n�܂�B\n");
			break;
		case 1:
			wsprintf(&m_Name[0], "STAGE:�˔j     NORMAL   HIGH SCORE:%8d\n", m_nRank[1]);
			wsprintf(&m_Str[0], "�b�������̈�l�Ƃ��ĂƂĂ��Ȃ����������'��'�B\n����Ȃ�푈�I���̓����߂����낤�Ɗy�ώ�����l���������Ȃ��Ȃ������B\n");
			wsprintf(&m_Str[strlen(m_Str)], "����Ȏ��A�ꕔ�̖����������G�̍U���ŉ�ł������ɂȂ��Ă���Ƃ����񍐂��󂯂��B\n'��'�͂�����1�l�A����������P�ނ����邽�߂̓a�Ƃ��ĎQ������B");
			break;
		case 2:
			wsprintf(&m_Name[0], "STAGE:�p�Y     HARD     HIGH SCORE:%8d\n", m_nRank[2]);
			wsprintf(&m_Str[0], "�����ɕ����̓P�ނɐ��������A��������͑���Ȏx�����󂯂�'��'�B\n����Ȓ��A�Ƃ����񂪓���ꂽ�B����́A�G�̊�n�Ɋւ�����̂������B\n");
			wsprintf(&m_Str[strlen(m_Str)], "���������͋��͂ȓG������Ƃ����B'��'�͂�����1�l�œG��n����ł����邱�ƂƂȂ����B\n���̔C�������Ȃ�����푈�͏I���B���s�͋�����Ȃ��B");
			break;
		default:
			break;
		}
	}
	//�@�̑I��
	else
	{
		//�I��ł�@�̂��g����ꍇ�̕���
		if (CManager::GetAircraft(m_nSelect[0]) == true)
		{
			wsprintf(&m_Name[0], "NAME:%-10sNICKNAME:%-22s�w���ς�\n", &m_aAircraft[m_nSelect[0]].aName, &m_aAircraft[m_nSelect[0]].aNickName);
		}
		//�I��ł�@�̂��g���Ȃ��ꍇ�̕���
		else
		{
			wsprintf(&m_Name[0], "NAME:%-10sNICKNAME:%-22sMONEY:%6d\n", &m_aAircraft[m_nSelect[0]].aName, &m_aAircraft[m_nSelect[0]].aNickName, m_aAircraft[m_nSelect[0]].nMoney);
		}
		int nCntlines;
		for (nCntlines = 0; nCntlines < m_aAircraft[m_nSelect[0]].nExplainLines; nCntlines++)
		{
			wsprintf(&m_Str[strlen(m_Str)], "%s\n", &m_aAircraft[m_nSelect[0]].aExplain[nCntlines][0]);
		}
	}
}