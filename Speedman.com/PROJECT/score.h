//*****************************************************************************
// �X�R�A���� [Score.h]
// Author : satou syusuke
//*****************************************************************************

#ifndef _SCORE_H_
#define _SCORE_H_

#include "Scene.h"

#define MAX_SCORE (10)

class CScene2D;
class CScore : public CScene
{
public:

	typedef enum
	{
		NUMBER_LIFE,		//���C�t�\��
		NUMBER_TIME,		//�ŏI�X�R�A
		NUMBER_RANKING,		//�����L���O
		NUMBER_SCORE,		//�ŏI�X�R�A
		NUMBER_MAX,
	} NUMBER_TYPE;		//�\�����鐔��


	CScore();
	~CScore();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	//�Q�b�g�E�Z�b�g�֐�
	void SetScore(int nScore) { m_nScore = nScore; }
	void AddScore(int nValue) { m_nScore += nValue; }
	int GetScore() { return m_nScore; }

	//����
	void SetDigit(int nDigit) { m_nDigit = nDigit; }
	int GetDigit() { return m_nDigit; }

	//�e�N�X�`���ԍ�
	void SetTexNum(int nNumtex) { m_nNumtex = nNumtex; }
	int GetTexNum() { return m_nNumtex; }

	//�傫��X
	void SetSizeX(float fSizeX) { m_fSizeX = fSizeX; }
	float GetSizeX() { return m_fSizeX; }

	//�傫��Y
	void SetSizeY(float fSizeY) { m_fSizeY = fSizeY; }
	float GetSizeY() { return m_fSizeY; }

	//�\�����鐔��
	void SetNumtype(CScore::NUMBER_TYPE Numtype) { m_aNumbertype = Numtype; }
	CScore::NUMBER_TYPE GetNumtype() { return m_aNumbertype; }

	//���ʂ̃����N����
	void SetRankNum(int nRankNum) { m_nNumRank = nRankNum; }
	int GetRankNum() { return m_nNumRank; }

	//���ʂ����Z�b�g
	static void SetRankReset(void) { m_nNumRank = 0; }

	//�^�C�}�[�֘A
	static void SetTime(int nNum);				//�^�C�}�[�Z�b�g
	static int GetTime() { return m_nTime; }	//�^�C�}�[�擾

	static CScore * Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int nDigit, CScore::NUMBER_TYPE Numtype);		//�o���ʒu�A�T�C�YX�A�T�C�YY�A�e�N�X�`���A�����A�ԍ��^�C�v

private:
	CScene2D *m_apScene[MAX_SCORE];	//UI
	int m_aScoreNum[MAX_SCORE];		//�X�R�AUI�ɕ\�������鐔��

	int m_nScore;		//���݂̃X�R�A
	int m_AddScore;		//���X�ɑ��₵�Ă������

	int m_Num;			//�\�����鐔��

	int m_nDigit;		//����

	//�T�C�Y
	float m_fSizeX;
	float m_fSizeY;

	int m_nNumtex;						//�e�N�X�`���ԍ�

	CScore::NUMBER_TYPE m_aNumbertype;	//���̔ԍ���

	bool m_bUninit;				//�������т�����
	static int m_nTime;			//����
	static int m_nTimeCalc;		//�t���[���v�Z�p

	static int m_nNumRank;	//���Ԗڂ��w�肷�邽�߂ɗp��
	int m_RankNum;			//���Ԗڂ̃����N���ǂ���
};
#endif // !_SCORE_H_
