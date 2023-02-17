//=============================================================================
//
// カメラゾーン処理 [camerazone.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _CAMERAZONE_H_
#define _CAMERAZONE_H_

#include "main.h"
#include "plane.h"

class CCameraZone : public CPlane
{
public:
	CCameraZone(PRIORITY Priority);
	~CCameraZone();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	OBJTYPE GetObjType() { return OBJECTTYPE_CAMERAPANEL; }	//種類
	D3DXVECTOR3 GetVtxMax() { return m_VtxMax; }			//最大値
	D3DXVECTOR3 GetVtxMin() { return m_VtxMin; }			//最小値

	static CCameraZone *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//作成

private:
	D3DXVECTOR3 m_VtxMax;	//最大値
	D3DXVECTOR3 m_VtxMin;	//最小値
};

#endif