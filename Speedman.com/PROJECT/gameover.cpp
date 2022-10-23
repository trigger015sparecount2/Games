//=============================================================================
//�Q�[���I�[�o�[����[GameOver.cpp]
// Author : �����G��
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#if 1
#include "GameOver.h"
#include "keyboard.h"
#include "gamepad.h"

#include "UI.h"
#include "Effect_UI.h"
#include "Select_UI.h"
#include "change_ui.h"

#include "Fade.h"
#include "Bg.h"
#include "Score.h"

#include "sound.h"

#endif
//*****************************************************************************
// �ÓI�����o�ϐ�
//***************************************************************************** 
bool CGameOver::m_bFade = NULL;
int CGameOver::m_SerectNam = NULL;

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define MAX_GAMEOVER_SERECT (3)


#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGameOver::CGameOver()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CGameOver::~CGameOver()
{

}
#endif
//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CGameOver::Init(D3DXVECTOR3 /*pos*/)
{
	//�L�[�{�[�h����
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	//�w�i
	CBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 14);

	//���S�̔z�u
	CChangeUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -100, 0.0f),
		D3DXVECTOR2(600.0f,90.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		17,
		D3DXCOLOR(255,255,255,255),
		D3DXCOLOR(0, 0, 0, 0),
		CChangeUI::CHANGE_BOUNCE,
		1, D3DXVECTOR2(SCREEN_WIDTH / 2, 200.0f),
		D3DXVECTOR2(0.0f, 10.0f));

	//�ꂵ���l
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 520.0f, 0.0f), 450.0f, 350.0f, 16);

	//�I����UI
	CSelectUI::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), 270.0f, 50.0f, 19, 1, CSelectUI::SELECT_UI_NOMAL);
	CSelectUI::Create(D3DXVECTOR3(1040.0f, 600.0f, 0.0f), 180.0f, 60.0f, 18, 2, CSelectUI::SELECT_UI_NOMAL);

	//�t�F�[�h
	CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	m_bFade = false;
	m_SerectNam = 1;
	SetSerectNum(m_SerectNam);
	CSound::Play(CSound::SOUND_LABEL_GAMEOVER);

	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CGameOver::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void CGameOver::Update()
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
						m_SerectNam = MAX_GAMEOVER_SERECT - 1;
					}
					CSound::Play(CSound::SOUND_LABEL_SELECT);
				}
				else if (CrossKey == 18000.0f)
				{
					m_SerectNam += 1;
					if (m_SerectNam >= MAX_GAMEOVER_SERECT)
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
				m_bFade = true;
				CSound::Play(CSound::SOUND_LABEL_SELECT);
			}
			else if (m_pGamePad->GetButton(CGamePad::DIP_A) == true && m_SerectNam == 2)
			{
				CFade::SetFade(CManager::MODE_TITLE);
				m_bFade = true;
				CSound::Play(CSound::SOUND_LABEL_SELECT);
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
						m_SerectNam = MAX_GAMEOVER_SERECT - 1;
					}
					CSound::Play(CSound::SOUND_LABEL_SELECT);
				}
				else if (m_pKeyboard->GetKey(DIK_DOWN) == true || m_pKeyboard->GetKey(DIK_S) == true)
				{
					m_SerectNam += 1;
					if (m_SerectNam >= MAX_GAMEOVER_SERECT)
					{
						m_SerectNam = 1;
					}
					CSound::Play(CSound::SOUND_LABEL_SELECT);
				}
			}

			////�V�[���J��
			//if (m_bFade == false)
			//{
			//�V�[���J��
			if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_SerectNam == 1)
			{
				CFade::SetFade(CManager::MODE_GAME);
				CScore::SetTime(TIME_LIMIT);
				m_bFade = true;
				CSound::Play(CSound::SOUND_LABEL_SELECT);
			}
			else if ((m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true) && m_SerectNam == 2)
			{
				CFade::SetFade(CManager::MODE_TITLE);
				m_bFade = true;
				CSound::Play(CSound::SOUND_LABEL_SELECT);
			}
			//}
		}
	}
}

//�`��E�쐬
#if 1
//*****************************************************************************
//�`��
//***************************************************************************** 
void CGameOver::Draw()
{

}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CGameOver *CGameOver::Create()
{
	CGameOver *pGameOver = NULL;
	pGameOver = new CGameOver;		//�������m��
									//NULL�`�F�b�N
	if (pGameOver != NULL)
	{
		pGameOver->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pGameOver;
}
#endif

//*****************************************************************************
//�I��ԍ��Z�b�g
//***************************************************************************** 
void CGameOver::SetSerectNum(int nNumSerect)
{
	m_SerectNam = nNumSerect;
}

