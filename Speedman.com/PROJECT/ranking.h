//=============================================================================
// �����L���O�Ǘ�[Ranking.h]
// Author : satou syusuke
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"


//=============================================================================
// �}�N��
//=============================================================================
#define MAX_RANKING (5)	//����

class CRanking
{
public:
	CRanking();
	~CRanking();

	static void SaveRanking(int nScore);	//�����L���O�̔�r�E�Z�[�u
	static void LoadRanking();				//�����L���O�̓ǂݍ���

	static int GetRank(int nNum);			//�����Ԗڂ̔ԍ���Ԃ�
private:

	static int m_nRank[MAX_RANKING];		//�����L���O�̂������i�[
	static int m_Score;						//����X�R�A
};

#endif // !_RANKING_H_
