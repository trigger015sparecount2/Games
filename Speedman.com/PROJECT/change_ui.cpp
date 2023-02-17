//*****************************************************************************
// UI�i��������ω�����j�֘A����(Change_UI.cpp)
// Author : satou syusuke
//*****************************************************************************
#include "change_ui.h"
#include "falleffect.h"

#include "Game.h"

#include "sound.h"
//*****************************************************************************
//�ÓI
//*****************************************************************************
int CChangeUI::m_nCountDown = 3;

//=============================================================================
// �}�N��
//=============================================================================
#define MAX_COLOR (255)
#define RAND_MOVE_Y (float(rand() % 3) - float(rand() % 3))

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CChangeUI::CChangeUI(int nPriority) : CUI(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aChangeType = CChangeUI::CHANGE_NONE;
	m_nLife = 0;

	m_nextpos = D3DXVECTOR2(0.0f, 0.0f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_moveSpeed = D3DXVECTOR2(0.0f, 0.0f);

	m_Distanse = D3DXVECTOR2(0.0f, 0.0f);

	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_MinSize = D3DXVECTOR2(0.0f, 0.0f);

	m_bUninit = false;
	m_fAngle = 0;

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CChangeUI::~CChangeUI()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CChangeUI::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nType, D3DCOLORVALUE color, D3DCOLORVALUE MinColor, CChangeUI::CHANGE_TYPE ChangeType, int nLife, D3DXVECTOR2 Nextpos, D3DXVECTOR2 move)
{
	CUI::Init(pos, Size.x, Size.y, nType);

	m_aChangeType = ChangeType;
	m_pos = pos;

	m_Size = Size;
	m_MinSize = MinSize;

	m_nextpos = Nextpos;
	m_move = move;
	m_moveSpeed = move;

	m_Color = color;
	m_MinColor = MinColor;

	m_nLife = nLife;

	m_fAngle = 0;
	m_nCntBounce = 0;
	m_bUninit = false;
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CChangeUI::Uninit()
{
	CUI::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CChangeUI::Update()
{
	bool Pause = CManager::GetPause();
	switch (m_aChangeType)
	{
	case(CChangeUI::CHANGE_COUNTDOWN):		//�J�E���g�_�E��
		if (Pause == false)
		{
			m_nLife--;
		}
		if (m_nLife <= 0)
		{
			if (m_nCountDown == 3)
			{
				//�J�E���g�_�E��UI
				CChangeUI::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f),
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(-1.0f, -1.0f),
					23,
					D3DXCOLOR(255, 255, 255, 255), D3DXCOLOR(0, 0, 0, -3),
					CChangeUI::CHANGE_COUNTDOWN,
					60,
					D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
				CSound::Play(CSound::SOUND_LABEL_COUNTDOWN);
			}
			else if (m_nCountDown == 2)
			{
				//�J�E���g�_�E��UI
				CChangeUI::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f),
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(-1.0f, -1.0f),
					22,
					D3DXCOLOR(255, 255, 255, 255), D3DXCOLOR(0, 0, 0, -3),
					CChangeUI::CHANGE_COUNTDOWN,
					60,
					D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
				CSound::Play(CSound::SOUND_LABEL_COUNTDOWN);
			}
			else if (m_nCountDown == 1)
			{
				//�J�E���g�_�E��UI
				CChangeUI::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f),
					D3DXVECTOR2(600.0f, 300.0f), D3DXVECTOR2(-1.0f, -1.0f),
					25,
					D3DXCOLOR(255, 255, 255, 255), D3DXCOLOR(0, 0, 0, -3),
					CChangeUI::CHANGE_COUNTDOWN,
					120,
					D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));

				//�J�E���g�_�E���I���t���OTrue
				CGame::SetCountFlag(true);

				CSound::Play(CSound::SOUND_LABEL_COUNTDOWNLAST);
				CSound::Play(CSound::SOUND_LABEL_GAMEBGM);
				CSound::ControlVoice(CSound::SOUND_LABEL_GAMEBGM, 0.5);
			}

			m_nCountDown--;
			m_bUninit = true;
		}
		break;
	case(CChangeUI::CHANGE_TARGETMOVE):		//�ڕW�Ɍ������ē����z
		//�p�x�v�Z�p
		m_Distanse.x = m_pos.x - m_nextpos.x;
		m_Distanse.y = m_pos.y - m_nextpos.y;
		m_fAngle = atan2f(m_Distanse.x, m_Distanse.y);

		if (m_Distanse.x <= 0 && m_Distanse.y <= 0)
		{
			m_move = D3DXVECTOR2(0.0f, 0.0f);
		}
		else
		{
			m_move = D3DXVECTOR2(sinf(m_fAngle) * m_moveSpeed.x, cosf(m_fAngle) * m_moveSpeed.y);
			//for (int nCnt = 0; nCnt < 3; nCnt++)
			//{
			//	float randy = RAND_MOVE_Y;
			//	float randx = RAND_MOVE_Y;
			//	CFallEffect::Create(D3DXVECTOR3(m_pos.x - 290, m_pos.y, m_pos.z),
			//		D3DXVECTOR2(randx * 1.2, randy),
			//		D3DXCOLOR(255, 255, 0, 255),
			//		D3DXCOLOR(0, -4, 0, 0),
			//		D3DXVECTOR2(20.0f, 20.0f),
			//		D3DXVECTOR2(0.0f, 0.0f),
			//		90, 8,
			//		D3DXVECTOR2(0.1f, 0.0f));
			//}
		}
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		//�T���ڂ�
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			float randy = RAND_MOVE_Y;
			float randx = RAND_MOVE_Y;

			CFallEffect::Create(D3DXVECTOR3(m_pos.x - 290.0f, m_pos.y, m_pos.z),
				D3DXVECTOR2(randx * 1.2f, randy),
				D3DXCOLOR(255, 255, 255, 255),
				D3DXCOLOR(0, -4, -2, 0),
				D3DXVECTOR2(20.0f, 20.0f),
				D3DXVECTOR2(0.0f, 0.0f),
				90, 8,
				D3DXVECTOR2(0.1f, 0.0f));
		}

		break;
	case(CChangeUI::CHANGE_PAUSE):		//�|�[�Y
		if (Pause == false)
		{
			m_bUninit = true;
		}
		break;

	case(CChangeUI::CHANGE_BOUNCE):
		if (m_nCntBounce <= 2)
		{
			m_move.y += 0.6f;
			m_pos.y += m_move.y;
		}

		if (m_pos.y >= m_nextpos.y)
		{
			m_move *= -1.0f;
			m_move *= 0.7f;
			m_nCntBounce++;
		}

		break;
	}
	if (Pause == false)
	{

		m_Color.r += m_MinColor.r;
		m_Color.g += m_MinColor.g;
		m_Color.b += m_MinColor.b;
		m_Color.a += m_MinColor.a;

		//�J���[��0�ȉ��̎�
		if (m_Color.r < 0)
		{
			m_Color.r = 0;
		}
		if (m_Color.g < 0)
		{
			m_Color.g = 0;
		}
		if (m_Color.b < 0)
		{
			m_Color.b = 0;
		}
		if (m_Color.a < 0)
		{
			m_Color.a = 0;
		}

		//�J���[�l��MAX_COLOR�����肻��
		if (m_Color.r >= MAX_COLOR)
		{
			m_Color.r = MAX_COLOR;
		}
		if (m_Color.g >= MAX_COLOR)
		{
			m_Color.g = MAX_COLOR;
		}
		if (m_Color.b >= MAX_COLOR)
		{
			m_Color.b = MAX_COLOR;
		}
		if (m_Color.a >= MAX_COLOR)
		{
			m_Color.a = MAX_COLOR;
		}
		m_Size += m_MinSize;
	}

	CScene2D::ColorChange(m_Color);
	CScene2D::SetPosition(m_pos);
	CScene2D::SetWidth(m_Size.x);		//�T�C�Y�̓K��
	CScene2D::SetHeight(m_Size.y);

	//�폜
	if (m_bUninit == true)
	{
		SetDeath(true);
	}
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CChangeUI::Draw()
{
	CUI::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CChangeUI *CChangeUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nType, D3DCOLORVALUE color, D3DCOLORVALUE MinColor, CChangeUI::CHANGE_TYPE ChangeType, int nLife, D3DXVECTOR2 Nextpos, D3DXVECTOR2 move)
{
	CChangeUI * pChangeUI = NULL;
	pChangeUI = new CChangeUI(5);

	if (pChangeUI != NULL)
	{
		pChangeUI->Init(pos, Size, MinSize, nType, color, MinColor, ChangeType, nLife, Nextpos, move);
	}
	return pChangeUI;
}

//*****************************************************************************
//�J�E���^�[���Z�b�g
//*****************************************************************************
void CChangeUI::SetCountDown()
{
	m_nCountDown = 3;
}