//=============================================================================
//�J�nUI�Ǘ�[startui.h]
// Author : �O��@�q��
//=============================================================================
#ifndef _STARTUI_H_
#define _STARTUI_H_

#include "ui.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CStartUI : public CUI
{
public:
	CStartUI(PRIORITY Priority);
	~CStartUI();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col, int nUIType);
	void Uninit();
	void Update();
	void Draw();

	static CStartUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col, int nUIType);

private:
	int m_nUIType;
	int m_nTime;
	bool m_bStop;
	int m_nFade;
	D3DXVECTOR2 size;
};

#endif
