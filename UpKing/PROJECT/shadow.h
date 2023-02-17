//=============================================================================
//
// 影処理 [shadow.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "plane.h"

class CShadow : public CPlane
{
public:
	CShadow(PRIORITY Priority);
	~CShadow();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	void Move(float fHeight);	//移動
	void MoveY(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//移動

	static CShadow *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//作成

private:
	float m_fPosY;		//高さ
	float m_fLength;	//距離
	D3DXVECTOR3 m_size;	//サイズ
};

#endif