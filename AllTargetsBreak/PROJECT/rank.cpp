//-------------------------
//Autohr;�O��q��
//�����L���O����(rank.cpp)
//-------------------------
#include "rank.h"
#include "gameui.h"

//�}�N����`
#define MAX_RANK (5)
#define SAVEFILENAME "actionrank.txt"

//�O���[�o���ϐ�
int g_aTime[MAX_RANK];

void Rankmain(int nTimeMin, int nTimeSec, bool bDemo)
{
	RankLoad();
	if (bDemo == false)
	{
		RankData(nTimeMin, nTimeSec, bDemo);
		RankSave();
	}
}

void RankSave(void)
{
	FILE *pFile;
	pFile = fopen(SAVEFILENAME, "w");
	int nCount;
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fprintf(pFile, "%d\n", g_aTime[nCount]);
		}
		fclose(pFile);
	}
}

void RankLoad(void)
{
	FILE *pFile;
	int nCount;
	pFile = fopen(SAVEFILENAME, "r");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fscanf(pFile, "%d", &g_aTime[nCount]);
		}
		fclose(pFile);
	}
}

void RankData(int nTimeMin, int nTimeSec, bool bDemo)
{
	int nCount1;
	int nCount2;
	int nRank = 0;
	int ntScore = 0;
	int ntKill = 0;
	int nSamerank = 0;
	//�c�莞�ԕ��ёւ�
	if (g_aTime[MAX_RANK - 1] > nTimeMin * TIME_LIMIT_SEC + nTimeSec && bDemo == false)
	{
		g_aTime[MAX_RANK - 1] = nTimeMin * TIME_LIMIT_SEC + nTimeSec;
	}
	for (nCount1 = 0; nCount1 < MAX_RANK - 1; nCount1++)
	{
		for (nCount2 = nCount1 + 1; nCount2 < MAX_RANK; nCount2++)
		{
			if (g_aTime[nCount1] > g_aTime[nCount2])
			{
				nRank = g_aTime[nCount1];
				g_aTime[nCount1] = g_aTime[nCount2];
				g_aTime[nCount2] = nRank;
			}
		}
	}
}

int TRankData(int nTRank)
{
	return g_aTime[nTRank];
}