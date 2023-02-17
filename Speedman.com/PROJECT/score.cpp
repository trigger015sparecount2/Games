//*****************************************************************************
// �X�R�A���� [Score.cpp]
// Author : satou syusuke
//*****************************************************************************

#include "Score.h"
#include "Scene2D.h"
#include "Ranking.h"
#include "Game.h"
#include "sound.h"
#include "player.h"
#include "fade.h"

#include <assert.h>

//*****************************************************************************
//�ÓI
//*****************************************************************************
int CScore::m_nNumRank = 0;
int CScore::m_nTimeCalc = 0;
int CScore::m_nTime = TIME_LIMIT;

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define TIME_FLAME (140)		//�P�b�J�E���g�p�i����60����Ȃ��񂷂���...�H�j

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScore::CScore()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apScene[nCnt] = NULL;
	}

	m_nScore = 0;
	m_AddScore = 0;
	m_nDigit = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScore::~CScore()
{

}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	int nDigit = GetDigit();

	float fSizeX = GetSizeX();
	float fSizeY = GetSizeY();
	int TexNum = GetTexNum();

	for (int nCnt = 0; nCnt < nDigit; nCnt++)
	{
		if (m_apScene[nCnt] == NULL)
		{
			m_apScene[nCnt] = new CScene2D(5);
			m_apScene[nCnt]->Init(D3DXVECTOR3(pos.x - fSizeX * nCnt, pos.y, 0));

			m_apScene[nCnt]->SetWidth(fSizeX);
			m_apScene[nCnt]->SetHeight(fSizeY);
			m_apScene[nCnt]->SetTexture(TexNum);
		}
	}
	m_bUninit = false;
	return S_OK;
}

//*****************************************************************************
// �I��
//*****************************************************************************
void CScore::Uninit()
{
	//CManager::MODE Mode = CManager::GetMode();
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apScene[nCnt] != NULL)
		{
			m_apScene[nCnt]->Uninit();
			m_apScene[nCnt] = NULL;
		}
	}
	Release();

}

//*****************************************************************************
// �X�V
//*****************************************************************************
void CScore::Update()
{
	CManager::MODE Scene = CManager::GetMode();

	int nDigit = GetDigit();
	int nPlayerLife = CPlayer::GetLife();
	bool ContFlag = CGame::GetCountFlag();
	bool bGameEnd = CManager::GetGameEnd();
	bool bRankOne = CManager::GetSaveRankOne();
	bool Pause = CManager::GetPause();

	if (Scene == CManager::MODE_GAME)
	{
		//�|�[�Y������Ȃ�
		if (Pause == false)
		{
			//�Q�[���I�����ĂȂ�
			if (bGameEnd == false)
			{
				//�^�C�}�[�J�E���g����
				if (ContFlag == true)
				{
					//�^�C�}�[����
					m_nTimeCalc++;
					if (m_nTimeCalc >= TIME_FLAME)
					{
						//���Ԍ��炷
						m_nTime--;
						m_nTimeCalc = 0;

						if (m_nTime <= 10 && m_nTime > 0)
						{
							CSound::Play(CSound::SOUND_LABEL_SIREN);
						}
					}
				}
			}
		}
	}

	//�Q�[���N���A���Ɉ�x�����ʂ�
	if (bGameEnd == true && bRankOne == false)
	{
		int nResulutScore = CManager::GetGameTime() * 2 * (3 * 10) + 100 * (10 * nPlayerLife);
		CRanking::SaveRanking(nResulutScore);
		CManager::SetSaveRankOne(true);
	}

	//�^�C��0
	if (m_nTime <= 0/* && m_bFade == false*/)
	{
		CFade::SetFade(CManager::MODE_GAMEOVER);
		CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
		//m_bFade = true;
	}
	//���C�t0
	if (nPlayerLife <= 0)
	{
		CFade::SetFade(CManager::MODE_GAMEOVER);
		CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
	}

	//�^�C�v���ƂɍX�V
	switch (m_aNumbertype)
	{
		//�ԍ��^�C�v���X�R�A
	case(CScore::NUMBER_SCORE):	//�X�R�A
		m_Num = CManager::GetGameTime() * 2 * (3 * 10) + 100 * (10 * nPlayerLife);
		break;

		//�ԍ��^�C�v�������L���O
	case(CScore::NUMBER_RANKING):
		m_Num = CRanking::GetRank(m_RankNum);
		break;

		//�ԍ��^�C�v�����C�t
	case(CScore::NUMBER_LIFE):
		m_Num = nPlayerLife;
		break;

		//�ԍ��^�C�v���^�C��
	case(CScore::NUMBER_TIME):
		m_Num = m_nTime;
		break;

	default:
		assert(false);
		break;
	}

#if 1
	//�X�R�A
	int score = m_Num;
	for (int i = 0; i < 10; ++i)
	{
		m_aScoreNum[i] = score % 10;
		score /= 10;
	}
#else
	m_aScoreNum[9] = m_Num % 10000000000 / 1000000000;
	m_aScoreNum[8] = m_Num % 1000000000 / 100000000;
	m_aScoreNum[7] = m_Num % 100000000 / 10000000;
	m_aScoreNum[6] = m_Num % 10000000 / 1000000;
	m_aScoreNum[5] = m_Num % 1000000 / 100000;
	m_aScoreNum[4] = m_Num % 100000 / 10000;
	m_aScoreNum[3] = m_Num % 10000 / 1000;
	m_aScoreNum[2] = m_Num % 1000 / 100;
	m_aScoreNum[1] = m_Num % 100 / 10;
	m_aScoreNum[0] = m_Num % 10 / 1;
#endif

	CManager::SetGameTime(m_nTime);

	//�X�R�A��UI�ݒ�
	for (int nCnt = 0; nCnt < nDigit; nCnt++)
	{
		m_apScene[nCnt]->SetTex(m_aScoreNum[nCnt], 0.1f);
	}

	if (m_bUninit == true)
	{
		SetDeath(true);
	}
}

//*****************************************************************************
// �`��
//*****************************************************************************
void CScore::Draw()
{
	int nDigit = GetDigit();

	for (int nCnt = 0; nCnt < nDigit; nCnt++)
	{
		if (m_apScene[nCnt] != NULL)
		{
			m_apScene[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// �쐬
//*****************************************************************************
CScore *CScore::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int nDigit, CScore::NUMBER_TYPE Numtype)
{
	CScore *pScore = NULL;
	pScore = new CScore;

	pScore->SetDigit(nDigit);
	pScore->SetNumtype(Numtype);

	pScore->SetSizeX(SizeX);
	pScore->SetSizeY(SizeY);
	pScore->SetTexNum(nType);


	if (Numtype == CScore::NUMBER_RANKING)
	{
		pScore->SetRankNum(m_nNumRank);
		m_nNumRank++;
	}
	if (pScore != NULL)
	{
		pScore->Init(pos);
	}

	return pScore;
}

//*****************************************************************************
// ���ԃZ�b�g
//*****************************************************************************
void CScore::SetTime(int nNum)
{
	m_nTime = nNum;		//���ԃZ�b�g
	m_nTimeCalc = 0;	//�t���[�����Z�b�g

}