//------------------------
//Author:�O��q��
//�����L���O����(rank.h)
//------------------------
#ifndef _RANK_H_
#define _RANK_H_
#include "main.h"

//�v���g�^�C�v�錾
void Rankmain(int nTimeSec, int nTimeCom, bool bDemo);	//���C������
void RankSave(void);	//�Z�[�u
void RankLoad(void);	//�ǂݍ���
void RankData(int nTimeSec, int nTimeCom, bool bDemo);	//�����L���O����ւ�
int TRankData(int nTRank);	//�e�����N�̐����擾
#endif _RANK_H_