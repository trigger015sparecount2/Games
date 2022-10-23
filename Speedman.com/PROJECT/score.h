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
		NUMBER_LIFE,	//���C�t�\��
		NUMBER_TIME,	//�ŏI�X�R�A
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
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore();

	//����
	void SetDigit(int nDigit);
	int GetDigit();

	//�e�N�X�`���ԍ�
	void SetTexNum(int nNumtex);
	int GetTexNum();

	//�傫��X
	void SetSizeX(float nSizeX);
	float GetSizeX();

	//�傫��Y
	void SetSizeY(float nSizeY);
	float GetSizeY();

	//�\�����鐔��
	void SetNumtype(CScore::NUMBER_TYPE Numtype);
	CScore::NUMBER_TYPE GetNumtype();

	//���ʂ̃����N����
	void SetRankNum(int nRankNum);
	int GetRankNum();

	//���ʂ����Z�b�g
	static void SetRankReset(void);

	//�^�C�}�[�֘A
	static void SetTime(int nNum);	//�^�C�}�[�Z�b�g
	static int GetTime();		//�^�C�}�[�擾

	static CScore * Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int nDigit, CScore::NUMBER_TYPE Numtype);		//�o���ʒu�A�T�C�YX�A�T�C�YY�A�e�N�X�`���A�����A�ԍ��^�C�v

private:
	CScene2D *m_apScene[MAX_SCORE];
	int m_aScoreNum[MAX_SCORE];

	int m_nScore;		//���݂̃X�R�A
	int m_AddScore;		//���X�ɑ��₵�Ă������

	int m_Num;			//�\�����鐔��

	int m_nDigit;		//����

	float m_fSizeX;
	float m_fSizeY;

	int m_nNumtex;

	CScore::NUMBER_TYPE m_aNumbertype;	//���̔ԍ���

	bool m_bUninit;		//�������т�����
	static int m_nTime;			//����
	static int m_nTimeCalc;		//�t���[���v�Z�p

	static int m_nNumRank;	//���Ԗڂ��w�肷�邽�߂ɗp��
	int m_RankNum;		//���Ԗڂ̃����N���ǂ���
};
#endif // !_SCORE_H_
