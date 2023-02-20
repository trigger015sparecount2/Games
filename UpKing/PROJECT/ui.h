//*****************************************************************************
// UI関連処理(UI.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _UI_H_
#define _UI_H_

#include "Scene2d.h"

class CUI :public CScene2D
{
public:

	CUI(PRIORITY Priority);
	~CUI();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }	//種類

	static CUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col);	//作成
private:

	D3DXVECTOR3 m_pos;			//現在位置

	D3DCOLORVALUE m_Color;		//カラー
	bool m_bUninit;				//消すか

	//大きさ情報
	float m_fSizeX;
	float m_fSizeY;

};
#endif