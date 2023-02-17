//=============================================================================
// �����L���O�Ǘ�[ranking.cpp]
// Author : satou syusuke
//=============================================================================
#include "ranking.h"

//=============================================================================
// �}�N��
//=============================================================================
#define RANK_TEXT "data/Rank.txt"	//�����L���O�t�@�C��

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
int CRanking::m_nRank[MAX_RANKING] = {};	//�����L���O�̂������i�[
int CRanking::m_Score = 0;					//����X�R�A

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CRanking::CRanking()
{
	m_nRank[MAX_RANKING] = 0;
	m_Score = 0;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CRanking::~CRanking()
{

}

//*****************************************************************************
//�����L���O�̔�r�E�Z�[�u
//*****************************************************************************
void CRanking::SaveRanking(int nScore)
{
	int nCntRank, nCntRank2, SubData;
	//int nCntNum = 0;		//���Ԗڂ̃����N��

							//�����L���O���[�h
	LoadRanking();
	m_Score = nScore;

	//�X�R�A��r
	for (nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		for (nCntRank2 = nCntRank; nCntRank2 < MAX_RANKING; nCntRank2++)
		{
			if (m_nRank[nCntRank] < m_Score)
			{
				SubData = m_Score;
				m_Score = m_nRank[nCntRank];
				m_nRank[nCntRank] = SubData;
			}
		}
	}

	FILE *pFile = fopen(RANK_TEXT, "w");
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fprintf(pFile, "RANK_NUMBER = %d\n", m_nRank[nCnt]);
		}
		fprintf(pFile, "\n");
		fprintf(pFile, "END_SCRIPT");
	}
	fclose(pFile);
}

//*****************************************************************************
//�����L���O�̃��[�h
//*****************************************************************************
void CRanking::LoadRanking()
{
	int nCntNum = 0;		//���Ԗڂ̃����N��

							//�t�@�C���ǂݍ���
	char aFile[256];
	FILE *pFile = fopen(RANK_TEXT, "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "RANK_NUMBER") == 0) //TEXTURE_FILENAME�̕�����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nRank[nCntNum]);
				nCntNum++;		//���Ԗڂ̃����N��

			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
	}
	fclose(pFile);

}

//*****************************************************************************
//�����L���O�擾
//*****************************************************************************
int CRanking::GetRank(int nNum)
{
	return m_nRank[nNum];
}