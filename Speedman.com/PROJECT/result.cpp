//=============================================================================
//���U���g�Ǘ�[Result.cpp]
// Author : �����G��
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#if 1
#include "Result.h"
#include "keyboard.h"
#include "gamepad.h"
#include "UI.h"
#include "effect_ui.h"

#include "Fade.h"
#include "Score.h"
#include "Ranking.h"
#include "Bg.h"

#include "sound.h"
#endif
//*****************************************************************************
// �ÓI�����o�ϐ�
//***************************************************************************** 
bool CResult::m_bFade = NULL;

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResult::CResult()
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
HRESULT CResult::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();
	CRanking::LoadRanking();		//�����L���O�̃��[�h
	bool RankOnly = CManager::GetRankOnly();

	//�w�i
	CBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 15);

	//UI�̔z�u
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 190.0f, 0), 300.0f, 50.0f, 29);		//UI

																					//�����L���O�̔ԍ�UI�z�u
	CUI::Create(D3DXVECTOR3(520.0f, 270.0f, 0), 60.0f, 50.0f, 3);		//UI
	CUI::Create(D3DXVECTOR3(520.0f, 350.0f, 0), 60.0f, 50.0f, 4);		//UI
	CUI::Create(D3DXVECTOR3(520.0f, 430.0f, 0), 60.0f, 50.0f, 5);		//UI
	CUI::Create(D3DXVECTOR3(520.0f, 510.0f, 0), 60.0f, 50.0f, 6);		//UI
	CUI::Create(D3DXVECTOR3(520.0f, 590.0f, 0), 60.0f, 50.0f, 7);		//UI

	if (RankOnly == false)
	{
		CUI::Create(D3DXVECTOR3(640.0f, 50.0f, 0), 300.0f, 50.0f, 28);		//UI
		//�v���C���[�X�R�A
		CScore::Create(D3DXVECTOR3(700.0f, 100, 0), 30, 40, 2, 5, CScore::NUMBER_SCORE);
	}
	else
	{
		CSound::Play(CSound::SOUND_LABEL_RESULTBGM);
		CSound::ControlVoice(CSound::SOUND_LABEL_RESULTBGM, 1.3f);
	}

	//�G�t�F�N�g�z�u����UI(�e�X�g)
	CEffectUI::Create(D3DXVECTOR3(300.0f, SCREEN_HEIGHT, 0), 1, 1, 0, CEffectUI::EFFECT_RANKCYCLE);
	CEffectUI::Create(D3DXVECTOR3(980.0f, SCREEN_HEIGHT, 0), 1, 1, 0, CEffectUI::EFFECT_RANKCYCLE);

	//�����L���O�̏��Ԃ����Z�b�g�E�J��Ԃ��Ƒ����܂���
	CScore::SetRankReset();

	//�����L���O�ԍ��z�u
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 130.0f, 270.0f + 80.0f * nCnt, 0.0f), 40.0f, 50.0f, 2, 5, CScore::NUMBER_RANKING);
	}

	//�t�F�[�h
	CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	m_bFade = false;

	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CResult::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void CResult::Update()
{

	CFade::FADE Fade = CFade::GetFade();
	if (Fade == CFade::FADE_NONE)
	{
		if (m_pGamePad != NULL)
		{
			if (m_pGamePad->GetButton(CGamePad::DIP_A))
			{
				CFade::SetFade(CManager::MODE_TITLE);

				CManager::SetRankOnly(false);
				m_bFade = true;
				CSound::Stop(CSound::SOUND_LABEL_RESULTBGM);
			}
		}
		else if (m_pKeyboard != NULL)
		{
			if (m_pKeyboard->GetKey(DIK_RETURN) == true || m_pKeyboard->GetKey(DIK_SPACE) == true)
			{
				CFade::SetFade(CManager::MODE_TITLE);

				CManager::SetRankOnly(false);
				m_bFade = true;
				CSound::Stop(CSound::SOUND_LABEL_RESULTBGM);
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

}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CResult *CResult::Create()
{
	CResult *pResult = NULL;
	pResult = new CResult;		//�������m��
								//NULL�`�F�b�N
	if (pResult != NULL)
	{
		pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResult;
}
#endif
