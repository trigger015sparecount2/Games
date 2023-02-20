//=============================================================================
//
// 背景処理 [bg.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"

class CBg : public CScene
{
public:
	CBg(PRIORITY Priority);
	~CBg();
	HRESULT Init(D3DXVECTOR3 pos);	//初期化
	void Uninit(void);	//終了
	void Update(void);	//更新
	void Draw(void);	//描画

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }	//種類

	//↓--------------使わない----------------↓
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return m_mtxWorld; }
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }
	//↑--------------使わない----------------↑

	void SetTexture(LPDIRECT3DTEXTURE9 *pTexture) { m_pTexture = *pTexture; }			//テクスチャ設定
	void SetScroll(float fScroll) { m_fScroll = fScroll; }								//スクロール設定
	static CBg *Create(D3DXVECTOR3 pos, float fScroll, LPDIRECT3DTEXTURE9 *Texture);	//作成

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//インデックスバッファ
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 m_pos;		//場所
	D3DXVECTOR3 m_rot;		//方向

	float m_fScroll;
};

#endif