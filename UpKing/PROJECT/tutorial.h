//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "plane.h"

class CTutorial : public CPlane
{
public:
	//�������̍\����
	typedef struct
	{
		D3DXVECTOR2 move;	//�ړ���
		int nMaxTime;		//�ړ�����
	} Pattern;

	CTutorial(PRIORITY Priority);
	~CTutorial();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, CTutorial::Pattern Pattern[6], int nLoop, int nMaxPattern);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_TUTORIAL; }	//���

	static CTutorial *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, CTutorial::Pattern Pattern[6], int nLoop, int nMaxPattern, int nTex);	//�쐬

private:
	D3DXVECTOR3 m_Move;		//�ړ���
	int m_nLoop;			//���[�v�J�n�̐��l
	int m_nTime;			//�ړ��J�E���g
	int m_nStopTime;		//��~����
	int m_nCntPattern;		//���݈ړ��p�^�[��
	int m_nMaxPattern;		//�ő�ړ��p�^�[��
	Pattern m_Pattern[6];	//�ړ��p�^�[��
};

#endif