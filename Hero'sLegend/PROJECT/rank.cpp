//-------------------------
//Autohr;�O��q��
//�����L���O����(rank.cpp)
//-------------------------
#include "rank.h"

//�}�N����`
#define MAX_RANK (5)
#define SAVEFILENAME "data/actionrank.txt"

//�O���[�o���ϐ�
int g_aScore[MAX_RANK];

//���C��
void Rankmain(int nScore)
{
	RankLoad(nScore);
	RankData();
	RankSave();
}

//�t�@�C����������
void RankSave(void)
{
	FILE *pFile;
	pFile = fopen(SAVEFILENAME, "w");
	int nCount;
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fprintf(pFile, "%d\n", g_aScore[nCount]);
		}
		fclose(pFile);
	}
}

//�t�@�C���ǂݍ���
void RankLoad(int nScore)
{
	FILE *pFile;
	int nCount;
	pFile = fopen(SAVEFILENAME, "r");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fscanf(pFile, "%d", &g_aScore[nCount]);
		}
		fclose(pFile);
	}
	if (g_aScore[MAX_RANK - 1] < nScore)
	{
		g_aScore[MAX_RANK - 1] = nScore;
	}
}

//�����L���O����ւ�
void RankData(void)
{
	int nCount1;
	int nCount2;
	int nRank = 0;
	int ntScore = 0;
	int ntKill = 0;
	int nSamerank = 0;
	//�X�R�A���ёւ�
	for (nCount1 = 0; nCount1 < MAX_RANK - 1; nCount1++)
	{
		for (nCount2 = nCount1 + 1; nCount2 < MAX_RANK; nCount2++)
		{
			if (g_aScore[nCount1] < g_aScore[nCount2])
			{
				nRank = g_aScore[nCount1];
				g_aScore[nCount1] = g_aScore[nCount2];
				g_aScore[nCount2] = nRank;
			}
		}
	}
}

//�e�����N�̃X�R�A�擾
int SRankData(int nSRank)
{
	return g_aScore[nSRank];
}