//=============================================================================
// �^�C�g���Ǘ�[Title.cpp]
// Author : �����G��
//=============================================================================
//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#if 1
#include "Title.h"
#include "keyboard.h"
#include "UI.h"

#include "Effect_UI.h"
#include "Select_UI.h"
#include "change_ui.h"

#include "Bg.h"
#include "score.h"
#include "game.h"
#include "gamepad.h"

#include "player.h"
#include "light.h"
#include "Fade.h"

#include "sound.h"
#endif

//*****************************************************************************
//�ÓI
//*****************************************************************************
int CTitle::m_SerectNam = 1;
bool CTitle::m_bFade = false;

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define MAX_TITLESERECT (4)

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTitle::CTitle()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTitle::~CTitle()
{
}
#endif

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CTitle::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();
	//�w�i
	CBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 13);

	//�^�C�g�����S
	CChangeUI::Create(D3DXVECTOR3(1580.0f, 230.0f, 0.0f),
		D3DXVECTOR2(600.0f,230.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		9,
		D3DXCOLOR(255,255,255,255),
		D3DXCOLOR(0, 0, 0, 0),
		CChangeUI::CHANGE_TARGETMOVE,
		0,
		D3DXVECTOR2(410.0f, 230.0f),
		D3DXVECTOR2(-30.0f, 0.0f));

	//�I����UI�̐ݒu
	CSelectUI::Create(D3DXVECTOR3(1000.0f, 430.0f, 0.0f), 220.0f, 50.0f, 10, 1, CSelectUI::SELECT_UI_NOMAL);
	CSelectUI::Create(D3DXVECTOR3(1000.0f, 530.0f, 0.0f), 220.0f, 50.0f, 11, 2, CSelectUI::SELECT_UI_NOMAL);
	CSelectUI::Create(D3DXVECTOR3(1000.0f, 620.0f, 0.0f), 220.0f, 50.0f, 12, 3, CSelectUI::SELECT_UI_NOMAL);

	//�G�t�F�N�g�z�u����
	CEffectUI::Create(D3DXVECTOR3(380.0f, 230.0f, 0), 1, 1, 0, CEffectUI::EFFECT_CYCLE);
	//CEffectUI::Create(D3DXVECTOR3(380.0f, 230.0f, 0), 1, 1, 0, CEffectUI::EFFECT_FIRE);

	//�t�F�[�h
	CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

	m_SerectNam = 1;
	m_bFade = false;
	SetSerectNum(m_SerectNam);
	CManager::SetPause(false);
	CSound::Play(CSound::SOUND_LABEL_TITLEBGM);
	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CTitle::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void CTitle::Update()
{
	CFade::FADE Fade = CFade::GetFade();
	if (Fade == CFade::FADE_NONE)
	{
		if (m_pGamePad != NULL)
		{
			float CrossKey = m_pGamePad->TriggerCrossKey();
			if (m_bFade == false)
			{
				if (CrossKey == 0.0f)
				{
					m_SerectNam -= 1;
					if (m_SerectNam <= 0)
					{
						m_SerectNam = MAX_TITLESERECT - 1;
					}
					CSound::Play(CSound::SOUND_LABEL_SELECT);
				}
				else if (CrossKey == 18000.0f)
				{
					m_SerectNam += 1;
					if (m_SerectNam >= MAX_TITLESERECT)
					{
						m_SerectNam = 1;
					}
					CSound::Play(CSound::SOUND_LABEL_SELECT);
				}
			}
			if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_SerectNam == 1)
			{
				CFade::SetFade(CManager::MODE_GAME);
				CScore::SetTime(TIME_LIMIT);
				CManager::SetGameEnd(false);
				CManager::SetSaveRankOne(false);
				CManager::SetGameClear(false);
				CSound::Play(CSound::SOUND_LABEL_CLICK);
				CSound::Stop(CSound::SOUND_LABEL_TITLEBGM);
				m_bFade = true;
			}
			else if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_SerectNam == 2)
			{
				CFade::SetFade(CManager::MODE_TUTORIAL);
				CManager::SetGameEnd(false);
				CManager::SetSaveRankOne(false);
				CManager::SetGameClear(false);
				CGame::SetCountFlag(true);
				CSound::Play(CSound::SOUND_LABEL_CLICK);
				CSound::Stop(CSound::SOUND_LABEL_TITLEBGM);

				m_bFade = true;
			}
			else if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_SerectNam == 3)
			{
				m_bFade = true;
				CFade::SetFade(CManager::MODE_RESULT);
				CManager::SetGameEnd(false);
				CManager::SetRankOnly(true);
				CManager::SetSaveRankOne(false);
				CSound::Play(CSound::SOUND_LABEL_CLICK);
				CSound::Stop(CSound::SOUND_LABEL_TITLEBGM);
				CPlayer::SetLife(MAX_LIFE);
				CScore::SetTime(TIME_LIMIT);

			}
		}
		//�L�[�{�[�h����
		else if (m_pKeyboard != NULL)
		{
			if (m_bFade == false)
			{
				//�I��ԍ��̕ω�
				if (m_pKeyboard->GetKey(DIK_UP) == true || m_pKeyboard->GetKey(DIK_W) == true)
				{
					m_SerectNam -= 1;
					if (m_SerectNam <= 0)
					{
						m_SerectNam = MAX_TITLESERECT - 1;
					}
					CSound::Play(CSound::SOUND_LABEL_SELECT);
				}
				else if (m_pKeyboard->GetKey(DIK_DOWN) == true || m_pKeyboard->GetKey(DIK_S) == true)
				{
					m_SerectNam += 1;
					if (m_SerectNam >= MAX_TITLESERECT)
					{
						m_SerectNam = 1;
					}
					CSound::Play(CSound::SOUND_LABEL_SELECT);
				}
			}

			//if (m_bFade == false)
			//{
			//�V�[���J��
			if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_SerectNam == 1)
			{
				CFade::SetFade(CManager::MODE_GAME);
				CScore::SetTime(TIME_LIMIT);
				CManager::SetGameEnd(false);
				CManager::SetSaveRankOne(false);
				CManager::SetGameClear(false);
				CSound::Play(CSound::SOUND_LABEL_CLICK);
				CSound::Stop(CSound::SOUND_LABEL_TITLEBGM);
				m_bFade = true;
			}
			else if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_SerectNam == 2)
			{
				CFade::SetFade(CManager::MODE_TUTORIAL);
				CManager::SetGameEnd(false);
				CManager::SetSaveRankOne(false);
				CManager::SetGameClear(false);
				CGame::SetCountFlag(true);
				CSound::Play(CSound::SOUND_LABEL_CLICK);
				CSound::Stop(CSound::SOUND_LABEL_TITLEBGM);

				m_bFade = true;
			}
			else if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_SerectNam == 3)
			{
				m_bFade = true;
				CFade::SetFade(CManager::MODE_RESULT);
				CManager::SetGameEnd(false);
				CManager::SetRankOnly(true);
				CManager::SetSaveRankOne(false);
				CSound::Play(CSound::SOUND_LABEL_CLICK);
				CSound::Stop(CSound::SOUND_LABEL_TITLEBGM);
				CPlayer::SetLife(MAX_LIFE);

				CScore::SetTime(TIME_LIMIT);
			}

			////�Ƃ肠�����Q�[���I�[�o�[��ʂ�
			//else if (m_pKeyboard->GetKey(DIK_V) == true)
			//{
			//	m_bFade = true;
			//	CFade::SetFade(CManager::MODE_GAMEOVER);
			//}

			//}
		}
	}
}

#if 1
//*****************************************************************************
//�`��
//***************************************************************************** 
void CTitle::Draw()
{

}

//*****************************************************************************
//�`��
//***************************************************************************** 
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle;		//�������m��
								//NULL�`�F�b�N
	if (pTitle != NULL)
	{
		pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pTitle;
}
#endif

#if 1
//*****************************************************************************
//�I��ԍ��擾
//***************************************************************************** 
int CTitle::GetSerectNum()
{
	return m_SerectNam;
}

//*****************************************************************************
//�I��ԍ��Z�b�g
//***************************************************************************** 
void CTitle::SetSerectNum(int nNumSerect)
{
	m_SerectNam = nNumSerect;
}
#endif
