//------------------------
//Author:�O��q��
//�����L���O����(rank.h)
//------------------------
#ifndef _RANK_H_
#define _RANK_H_
#include "main.h"
//�v���g�^�C�v�錾
void Rankmain(int nScore,int nKill);	//�����L���O����
void RankSave(void);					//��������
void RankLoad(int nScore, int nKill);	//�ǂݍ���
void RankData(void);					//�����L���O����ւ�
int SRankData(int nSRank);				//�X�R�A�����L���O
int KRankData(int nKRank);				//���Đ������L���O
#endif _RANK_H_
