//*****************************************************************************
// �w�i�֘A����(BG.h)
// Author : satou syusuke
//*****************************************************************************

#ifndef _BG_H_
#define _BG_H_

#include "Scene2D.h"

class CBG :public CScene2D
{
public:

	CBG(int nPriority);
	~CBG();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType);
	void Uninit();
	void Update();
	void Draw();

	static CBG *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType);		//�o���ʒu�A�T�C�YX�A�T�C�YY�A�e�N�X�`���j

private:

	D3DXVECTOR3 m_pos;		//���݈ʒu

	bool m_bUninit;			//������

};
#endif