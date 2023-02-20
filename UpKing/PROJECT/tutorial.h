//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "plane.h"

class CTutorial : public CPlane
{
public:
	//動き方の構造体
	typedef struct
	{
		D3DXVECTOR2 move;	//移動量
		int nMaxTime;		//移動時間
	} Pattern;

	CTutorial(PRIORITY Priority);
	~CTutorial();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, CTutorial::Pattern Pattern[6], int nLoop, int nMaxPattern);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	OBJTYPE GetObjType() { return OBJECTTYPE_TUTORIAL; }	//種類

	static CTutorial *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, CTutorial::Pattern Pattern[6], int nLoop, int nMaxPattern, int nTex);	//作成

private:
	D3DXVECTOR3 m_Move;		//移動量
	int m_nLoop;			//ループ開始の数値
	int m_nTime;			//移動カウント
	int m_nStopTime;		//停止時間
	int m_nCntPattern;		//現在移動パターン
	int m_nMaxPattern;		//最大移動パターン
	Pattern m_Pattern[6];	//移動パターン
};

#endif