//=============================================================================
// ���[�h���[load.cpp]
// Author : �O��q��
//=============================================================================
//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#if 1
#include "load.h"
#include "keyboard.h"
#include "ui.h"
#include "manager.h"
#include "renderer.h"

#include "game.h"
#include "gamepad.h"
#include "fade.h"

#include "sound.h"
#endif

//*****************************************************************************
//�ÓI
//*****************************************************************************
//int CTitle::m_SerectNam = 1;

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CLoad::CLoad(PRIORITY Priority) : CScene(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CLoad::~CLoad()
{
}
#endif

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CLoad::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();
	Load();
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.3f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 50.0f, 0.0f), D3DXVECTOR2(110.0f, 50.0f), 19, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//1�Ԗ�
	m_pUI[0] = CUI::Create(D3DXVECTOR3(370.0f, 210.0f, 0.0f), D3DXVECTOR2(25.0f, 80.0f), 25, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[1] = CUI::Create(D3DXVECTOR3(910.0f, 210.0f, 0.0f), D3DXVECTOR2(25.0f, 80.0f), 25, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[2] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 210.0f, 0.0f), D3DXVECTOR2(365.0f, 80.0f), 26, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[3] = CUI::Create(D3DXVECTOR3(405.0f, 210.0f, 0.0f), D3DXVECTOR2(34.0f, 60.0f), 3, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[4] = CUI::Create(D3DXVECTOR3(470.0f, 220.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[0], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[5] = CUI::Create(D3DXVECTOR3(550.0f, 220.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[1], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[6] = CUI::Create(D3DXVECTOR3(630.0f, 220.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[2], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[7] = CUI::Create(D3DXVECTOR3(710.0f, 220.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[3], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[8] = CUI::Create(D3DXVECTOR3(790.0f, 220.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[4], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[9] = CUI::Create(D3DXVECTOR3(870.0f, 220.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[5], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//2�Ԗ�
	m_pUI[10] = CUI::Create(D3DXVECTOR3(370.0f, 330.0f, 0.0f), D3DXVECTOR2(20.0f, 80.0f), 25, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[11] = CUI::Create(D3DXVECTOR3(910.0f, 330.0f, 0.0f), D3DXVECTOR2(20.0f, 80.0f), 25, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[12] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 330.0f, 0.0f), D3DXVECTOR2(365.0f, 80.0f), 26, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[13] = CUI::Create(D3DXVECTOR3(405.0f, 330.0f, 0.0f), D3DXVECTOR2(34.0f, 60.0f), 3, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[14] = CUI::Create(D3DXVECTOR3(470.0f, 340.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[0], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[15] = CUI::Create(D3DXVECTOR3(550.0f, 340.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[1], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[16] = CUI::Create(D3DXVECTOR3(630.0f, 340.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[2], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[17] = CUI::Create(D3DXVECTOR3(710.0f, 340.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[3], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[18] = CUI::Create(D3DXVECTOR3(790.0f, 340.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[4], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[19] = CUI::Create(D3DXVECTOR3(870.0f, 340.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[5], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//3�Ԗ�
	m_pUI[20] = CUI::Create(D3DXVECTOR3(370.0f, 450.0f, 0.0f), D3DXVECTOR2(20.0f, 80.0f), 25, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[21] = CUI::Create(D3DXVECTOR3(910.0f, 450.0f, 0.0f), D3DXVECTOR2(20.0f, 80.0f), 25, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pUI[22] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 450.0f, 0.0f), D3DXVECTOR2(365.0f, 80.0f), 26, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[23] = CUI::Create(D3DXVECTOR3(405.0f, 450.0f, 0.0f), D3DXVECTOR2(34.0f, 60.0f), 3, D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[24] = CUI::Create(D3DXVECTOR3(470.0f, 460.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[0], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[25] = CUI::Create(D3DXVECTOR3(550.0f, 460.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[1], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[26] = CUI::Create(D3DXVECTOR3(630.0f, 460.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[2], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[27] = CUI::Create(D3DXVECTOR3(710.0f, 460.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[3], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[28] = CUI::Create(D3DXVECTOR3(790.0f, 460.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[4], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[29] = CUI::Create(D3DXVECTOR3(870.0f, 460.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), m_nTexAircraft[5], D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���̃e�L�X�g
	CUI::Create(D3DXVECTOR3(235.0f, 610.0f, 0.0f), D3DXVECTOR2(26.0f, 100.0f), 5, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CUI::Create(D3DXVECTOR3(1045.0f, 610.0f, 0.0f), D3DXVECTOR2(26.0f, 100.0f), 5, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 610.0f, 0.0f), D3DXVECTOR2(550.0f, 100.0f), 6, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pUI[3]->SetTex(1, 0.1f);
	m_pUI[13]->SetTex(2, 0.1f);
	m_pUI[23]->SetTex(3, 0.1f);
	m_nClear[0] = 255;
	m_nClear[1] = 180;
	m_nClear[2] = 180;

	int nCntGroup;
	int nCntAir;
	for (nCntGroup = 0; nCntGroup < 3; nCntGroup++)
	{
		if (m_aData[nCntGroup] == true)
		{
			D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 26, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[nCntGroup]);
			for (nCntAir = 0; nCntAir < 6; nCntAir++)
			{
				if (m_aAircraft[nCntAir][nCntGroup] == false)
				{
					m_pUI[nCntGroup * 10 + nCntAir + 4]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
				}
			}
		}
		else
		{
			D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 90, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[nCntGroup]);
			for (nCntAir = 0; nCntAir < 6; nCntAir++)
			{
				m_pUI[nCntGroup * 10 + nCntAir + 4]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			}
		}
	}

	D3DXCreateFont(CManager::GetRenderer()->CRenderer::GetDevice(), 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont[3]);

	CManager::SetPause(false);
	m_nSelect = 0;
	m_bLoad = false;
	TextChange(TEXTTYPE_NONE);
	m_nCntChange = 0;
	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CLoad::Uninit()
{
	int nCnt;
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	for (nCnt = 0; nCnt < 30; nCnt++)
	{
		if (m_pUI[nCnt] != NULL)
		{
			m_pUI[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_pFont[nCnt] != NULL)
		{
			m_pFont[nCnt]->Release();
			m_pFont[nCnt] = NULL;
		}
	}
	CScene::Release();
}

//*****************************************************************************
// �X�V
//***************************************************************************** 
void CLoad::Update()
{
	//�e�L�X�g�ύX�J�E���g�i�߂�B�i�񂾂�e�L�X�g�����ɖ߂�
	if (m_nCntChange > 0)
	{
		m_nCntChange--;
		if (m_nCntChange <= 0)
		{
			TextChange(TEXTTYPE_NONE);
		}
	}

	//�Q�[���p�b�h�q�����Ă��邩
	if (m_pGamePad != NULL)
	{
		//�\���L�[�őI��
		if (m_pGamePad->TriggerCrossKey() == 0.0f)
		{
			Select(-1);
		}
		else if (m_pGamePad->TriggerCrossKey() == 18000.0f)
		{
			Select(1);
		}

		//����{�^��
		if (m_pGamePad->GetButton(CGamePad::DIP_B) == true)
		{
			//�t�F�[�h�������ĂȂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				//���[�h����ĂȂ�
				if (m_bLoad == false)
				{
					//�f�[�^���[�h�ɐ�������
					if (DataLoad() == S_OK)
					{
						//���[�h�����e�L�X�g�ɕς��Č��艹����
						TextChange(TEXTTYPE_LOAD);
						if (m_nCntChange > 0)
						{
							m_nCntChange = 0;
						}
						CSound::Play(CSound::SOUND_LABEL_YES);
					}
					else
					{
						//�f�[�^�Ȃ��e�L�X�g�ɕς���
						TextChange(TEXTTYPE_NODATA);
						CSound::Play(CSound::SOUND_LABEL_CANCEL);
					}
				}
				//���[�h����
				else
				{
					//�^�C�g���ɖ߂�A���艹����
					CFade::SetFade(CManager::MODE_TITLE);
					CSound::Play(CSound::SOUND_LABEL_YES);
				}
			}
		}

		//�L�����Z���{�^��
		if (m_pGamePad->GetButton(CGamePad::DIP_A) == true)
		{
			//���[�h���ĂȂ�
			if (m_bLoad == false)
			{
				//�t�F�[�h�����ĂȂ�
				if (CFade::GetFade() == CFade::FADE_NONE)
				{
					//�^�C�g���ɖ߂�
					CFade::SetFade(CManager::MODE_TITLE);
					CSound::Play(CSound::SOUND_LABEL_CANCEL);
				}
			}
		}
	}
	//�L�[�{�[�h���q�����Ă�
	else if (m_pKeyboard != NULL)
	{
		//�I��
		if (m_pKeyboard->GetKey(DIK_W) == true)
		{
			Select(-1);
		}
		else if (m_pKeyboard->GetKey(DIK_S) == true)
		{
			Select(1);
		}

		//����{�^��
		if (m_pKeyboard->GetKey(DIK_J) == true)
		{
			//�t�F�[�h�����ĂȂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				//���[�h���ĂȂ�
				if (m_bLoad == false)
				{
					//�f�[�^���[�h����
					if (DataLoad() == S_OK)
					{
						//���[�h�e�L�X�g�ɕύX�A���艹����
						TextChange(TEXTTYPE_LOAD);
						if (m_nCntChange > 0)
						{
							m_nCntChange = 0;
						}
						CSound::Play(CSound::SOUND_LABEL_YES);
					}
					else
					{
						//�f�[�^���Ȃ��e�L�X�g�ɕύX
						TextChange(TEXTTYPE_NODATA);
						CSound::Play(CSound::SOUND_LABEL_CANCEL);
					}
				}
				else
				{
					//�^�C�g���ɖ߂�
					CFade::SetFade(CManager::MODE_TITLE);
					CSound::Play(CSound::SOUND_LABEL_YES);
				}
			}
		}

		//�L�����Z���{�^��
		if (m_pKeyboard->GetKey(DIK_I) == true)
		{
			//���[�h���ĂȂ�
			if (m_bLoad == false)
			{
				//�t�F�[�h�����ĂȂ�
				if (CFade::GetFade() == CFade::FADE_NONE)
				{
					CFade::SetFade(CManager::MODE_TITLE);
					CSound::Play(CSound::SOUND_LABEL_CANCEL);
				}
			}
		}
	}
}

//*****************************************************************************
//�`��
//***************************************************************************** 
void CLoad::Draw()
{
	RECT rect[4];
	rect[0] = { 450, 165, 900, SCREEN_HEIGHT - 20 };	//1�Ԗ�
	rect[1] = { 450, 285, 900, SCREEN_HEIGHT - 20 };	//2�Ԗ�
	rect[2] = { 450, 405, 900, SCREEN_HEIGHT - 20 };	//3�Ԗ�
	rect[3] = { 240, 555, SCREEN_WIDTH - 240, SCREEN_HEIGHT - 20 };	//���̐���

	char str[256];
	int nCntText;
	for (nCntText = 0; nCntText < 3; nCntText++)
	{
		memset(&str[0], 0, sizeof(str));
		if (m_aData[nCntText] == true)
		{
			wsprintf(&str[0], "MONEY:%6d       AIRCRAFT:%d\n", m_nMoney[nCntText], m_nNumAircraft[nCntText]);
		}
		else
		{
			wsprintf(&str[0], "NO DATA\n");
			rect[nCntText].left += 20;
		}

		// �e�L�X�g�`��
		m_pFont[nCntText]->DrawText(NULL, str, -1, &rect[nCntText], DT_WORDBREAK, D3DCOLOR_ARGB(255, 0, m_nClear[nCntText], 0));
	}
	m_pFont[3]->DrawText(NULL, m_Str, -1, &rect[3], DT_WORDBREAK, D3DCOLOR_ARGB(255, 0, 255, 0));
}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CLoad *CLoad::Create()
{
	CLoad *pLoad = NULL;
	pLoad = new CLoad(PRIORITY_PAUSEUI);	//�������m��
											//NULL�`�F�b�N
	if (pLoad != NULL)
	{
		pLoad->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pLoad;
}

//�t�@�C���ǂݍ���
void CLoad::Load()
{
	//�t�@�C���ǂݍ���
	char aFile[256];
	FILE *pFile;
	int nCntLoad;
	int nAircraft;
	int nCntAir = 0;
	bool bStatus = false;
	for (nCntLoad = 0; nCntLoad < 3; nCntLoad++)
	{
		m_aData[nCntLoad] = true;
		switch (nCntLoad)
		{
		case 0:
			pFile = fopen(FILE_SAVE1, "r");
			break;
		case 1:
			pFile = fopen(FILE_SAVE2, "r");
			break;
		case 2:
			pFile = fopen(FILE_SAVE3, "r");
			break;
		default:
			pFile = fopen(FILE_SAVE1, "r");
			break;
		}
		if (pFile != NULL)
		{
			while (true)
			{
				fscanf(pFile, "%s", &aFile[0]);
				if (strcmp(&aFile[0], "NO_DATA") == 0) //NO_DATA�̕�����
				{
					m_aData[nCntLoad] = false;
					break;
				}
				if (strcmp(&aFile[0], "MANEY") == 0) //MANEY�̕�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_nMoney[nCntLoad]);
				}
				if (strcmp(&aFile[0], "NUM_AIRCRAFT") == 0) //NUM_AIRCRAFT�̕�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_nNumAircraft[nCntLoad]);
				}
				if (strcmp(&aFile[0], "AIRCRAFT") == 0) //AIRCRAFT�̕�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nAircraft);
					if (nAircraft == -1)
					{
						m_aAircraft[nCntAir][nCntLoad] = false;
					}
					else
					{
						m_aAircraft[nCntAir][nCntLoad] = true;
					}
					nCntAir++;
				}
				if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
				{
					nCntAir = 0;
					break;
				}
			}
			fclose(pFile);
		}
	}
	nCntAir = 0;
	pFile = fopen(FILE_AIRCRAFT, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "STATUS") == 0) //STATUS�̕�����
			{
				bStatus = true;
			}
			if (strcmp(&aFile[0], "END_STATUS") == 0) //END_STATUS�̕�����
			{
				bStatus = false;
				nCntAir++;
			}
			if (bStatus == true)
			{
				if (strcmp(&aFile[0], "HUD_TEXTYPE") == 0) //HUD_TEXTYPE�̕�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_nTexAircraft[nCntAir]);
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
		fclose(pFile);
	}
}

//�f�[�^���[�h
HRESULT CLoad::DataLoad()
{
	if (m_aData[m_nSelect] == true)
	{
		CManager::SetMoney(m_nMoney[m_nSelect]);
		CManager::SetNumAircraft(m_nNumAircraft[m_nSelect]);
		int nCnt;
		for (nCnt = 0; nCnt < 6; nCnt++)
		{
			CManager::SetAircraft(nCnt, m_aAircraft[nCnt][m_nSelect]);
		}
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}

//���[�h�f�[�^�I��
void CLoad::Select(int nAdd)
{
	if (m_bLoad == false)
	{
		int nCntSelect;
		for (nCntSelect = 0; nCntSelect < 10; nCntSelect++)
		{
			if (nCntSelect > 3)
			{
				if (m_aAircraft[nCntSelect - 4][m_nSelect] == true)
				{
					m_pUI[m_nSelect * 10 + nCntSelect]->ColorChange(D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f));
				}
			}
			else
			{
				m_pUI[m_nSelect * 10 + nCntSelect]->ColorChange(D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f));
			}
		}
		m_nClear[m_nSelect] = 180;
		m_nSelect += nAdd;
		if (m_nSelect < 0)
		{
			m_nSelect = 2;
		}
		else if (m_nSelect > 2)
		{
			m_nSelect = 0;
		}
		for (nCntSelect = 0; nCntSelect < 10; nCntSelect++)
		{
			if (nCntSelect > 3)
			{
				if (m_aAircraft[nCntSelect - 4][m_nSelect] == true)
				{
					m_pUI[m_nSelect * 10 + nCntSelect]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				}
			}
			else
			{
				m_pUI[m_nSelect * 10 + nCntSelect]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
		}
		m_nClear[m_nSelect] = 255;
		CSound::Play(CSound::SOUND_LABEL_CHOICE);
	}
}

//�e�L�X�g�ς���
void CLoad::TextChange(TEXTTYPE Texttype)
{
	memset(&m_Str[0], 0, sizeof(m_Str));
	switch (Texttype)
	{
	case TEXTTYPE_NONE:
		wsprintf(&m_Str[0], "���[�h����t�@�C����I��ł�������\n");
		if (m_pGamePad != NULL)
		{
			wsprintf(&m_Str[strlen(m_Str)], "�I��:�����L�[   ����:B   �^�C�g���ɖ߂�:A\n");
		}
		else
		{
			wsprintf(&m_Str[strlen(m_Str)], "�I��:W,S   ����:J   �^�C�g���ɖ߂�:I\n");
		}
		break;
	case TEXTTYPE_LOAD:
		wsprintf(&m_Str[0], "�t�@�C�������[�h���܂���\n");
		m_bLoad = true;
		break;
	case TEXTTYPE_NODATA:
		wsprintf(&m_Str[0], "���̃t�@�C���̓��[�h�o���܂���\n");
		m_nCntChange = 100;
		break;
	default:
		break;
	}
}