//=============================================================================
//���U���g�Ǘ�[Result.cpp]
// Author : �O��q��
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#include "result.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"
#include "fade.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//***************************************************************************** 


#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResult::CResult(PRIORITY Priority) :CScene(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CResult::~CResult()
{

}
#endif
//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CResult::Init(D3DXVECTOR3)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.2f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 80.0f, 0.0f), D3DXVECTOR2(200.0f, 50.0f), 62, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), D3DXVECTOR2(400.0f, 40.0f), 24, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	RankLoad();
	RankSave();
	int nMoney = CManager::GetMoney();
	nMoney += CManager::GetStageMoney();
	if (nMoney > 999999)
	{
		nMoney = 999999;
	}
	CSound::Play(CSound::SOUND_LABEL_RESULTBGM);
	CManager::SetMoney(nMoney);
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 90, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[0]);
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 90, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[1]);
	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 90, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[2]);

	return S_OK;
}

//*****************************************************************************
// �I��
//*****************************************************************************
void CResult::Uninit()
{
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	CScene::Release();
}

//*****************************************************************************
// �X�V
//***************************************************************************** 
void CResult::Update()
{
	//Press�̓_��
	if (m_bClear == true)
	{
		//��������
		m_fClear -= 0.05f;
		m_pUI->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fClear));
		if (m_fClear <= 0.0f)
		{
			m_fClear = 0.0f;
			m_bClear = false;
		}
	}
	else
	{
		//�Z������
		m_fClear += 0.05f;
		m_pUI->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fClear));
		if (m_fClear >= 1.0f)
		{
			m_fClear = 1.0f;
			m_bClear = true;
		}
	}
	//�Q�[���p�b�h�q�����Ă��邩
	if (m_pGamePad != NULL)
	{
		//���������ꂽ��^�C�g���Ɉڍs
		if (m_pGamePad->GetAnyButton() == true)
		{
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::SetFade(CManager::MODE_TITLE);
				CSound::Play(CSound::SOUND_LABEL_YES);
			}
		}
	}
	//�L�[�{�[�h���q�����Ă�
	else if (m_pKeyboard != NULL)
	{
		//���������ꂽ��^�C�g���Ɉڍs
		if (m_pKeyboard->GetAnyKey() == true)
		{
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::SetFade(CManager::MODE_TITLE);
				CSound::Play(CSound::SOUND_LABEL_YES);
			}
		}
	}
}

//�`��E�쐬
#if 1
//*****************************************************************************
//�`��
//***************************************************************************** 
void CResult::Draw()
{
	RECT rect[3];
	rect[0] = { 350, 160, SCREEN_WIDTH - 110, SCREEN_HEIGHT - 20 };	//�X�e�[�W
	rect[1] = { 350, 310, SCREEN_WIDTH - 110, SCREEN_HEIGHT - 20 };	//����̃X�R�A
	rect[2] = { 350, 410, SCREEN_WIDTH - 110, SCREEN_HEIGHT - 20 };	//�l���܋�
	char str[3][32];

	wsprintf(&str[0][0], "STAGE     :%d", CManager::GetStage() + 1);
	wsprintf(&str[1][0], "YOUR SCORE:%-8d", CManager::GetScore());
	wsprintf(&str[2][0], " GET MONEY:%-8d", CManager::GetStageMoney());

	// �e�L�X�g�`��
	m_pFont[0]->DrawText(NULL, &str[0][0], -1, &rect[0], DT_LEFT, D3DCOLOR_ARGB(255, 0, 255, 0));	//�X�e�[�W
	m_pFont[1]->DrawText(NULL, &str[1][0], -1, &rect[1], DT_LEFT, D3DCOLOR_ARGB(255, 0, 255, 0));	//����̃X�R�A
	m_pFont[2]->DrawText(NULL, &str[2][0], -1, &rect[2], DT_LEFT, D3DCOLOR_ARGB(255, 0, 255, 0));	//�l���܋�
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CResult *CResult::Create()
{
	CResult *pResult = NULL;
	pResult = new CResult(PRIORITY_PAUSEUI);		//�������m��
												//NULL�`�F�b�N
	if (pResult != NULL)
	{
		pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResult;
}
#endif

//�����L���O�ǂݍ���
void CResult::RankLoad()
{
	//�t�@�C���ǂݍ���
	FILE *pFile = fopen(FILE_RANK, "r");
	int nCnt;
	if (pFile != NULL)
	{
		for (nCnt = 0; nCnt < 3; nCnt++)
		{
			fscanf(pFile, "%d", &m_nScore[nCnt]);
		}
		fclose(pFile);
	}
}

//�����L���O�Z�[�u
void CResult::RankSave()
{
	if (m_nScore[CManager::GetStage()] < CManager::GetScore())
	{
		m_nScore[CManager::GetStage()] = CManager::GetScore();
		//�t�@�C���ǂݍ���
		FILE *pFile = fopen(FILE_RANK, "w");
		int nCnt;
		if (pFile != NULL)
		{
			for (nCnt = 0; nCnt < 3; nCnt++)
			{
				fprintf(pFile, "%d\n", m_nScore[nCnt]);
			}
			fclose(pFile);
		}
	}
}