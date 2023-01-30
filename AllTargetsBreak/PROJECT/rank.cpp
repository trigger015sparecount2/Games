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

//���C��
void Rankmain(int nTimeSec, int nTimeCom, bool bDemo)
{
	RankLoad();
	if (bDemo == false)
	{
		RankData(nTimeSec, nTimeCom, bDemo);
		RankSave();
	}
}

//�����L���O�Z�[�u
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

//�����L���O�ǂݍ���
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

//�����L���O����ւ�
void RankData(int nTimeSec, int nTimeCom, bool bDemo)
{
	int nCount1;
	int nCount2;
	int nRank = 0;
	int ntScore = 0;
	int ntKill = 0;
	int nSamerank = 0;
	//�c�莞�ԕ��ёւ�
	if (g_aTime[MAX_RANK - 1] > nTimeSec * TIME_LIMIT_COM + nTimeCom && bDemo == false)
	{
		g_aTime[MAX_RANK - 1] = nTimeSec * TIME_LIMIT_COM + nTimeCom;
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

//�e���ʂ̎��Ԏ擾
int TRankData(int nTRank)
{
	return g_aTime[nTRank];
}