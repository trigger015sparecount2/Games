//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "model.h"
#include "scene3d.h"

class CObject : public CScene3D
{
public:
	CObject(PRIORITY Priority);
	~CObject();
	HRESULT Init(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	OBJTYPE GetObjType() { return OBJECTTYPE_BLOCK; }			//種類
	D3DXVECTOR3 GetPos() { return m_pos; }						//pos取得
	//D3DXVECTOR3 GetMove() { return m_move; }
	float GetRadius() { return m_fRadius; }						//半径取得
	COLLISION GetCollision() { return m_Collision; }			//コリジョンの種類取得
	D3DXVECTOR3 GetVtxMax() { return m_pModel->GetMaxSize(); }	//サイズ最大取得
	D3DXVECTOR3 GetVtxMin() { return m_pModel->GetMinSize(); }	//サイズ最小取得
	D3DXMATRIX GetMatrix() { return m_pModel->GetMatrix(); }	//マトリックス取得

	static CObject *Create(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot);	//作成
	static void Load(int nCnt, const char *aModelName);	//モデル読み込み
	static void UnLoad();	//モデル破棄

private:
	CModel *m_pModel;				//モデル
	D3DXVECTOR3 m_pos;				//pos
	CScene::COLLISION m_Collision;	//当たり判定
	float m_fRadius;				//半径
	bool m_bDraw;					//描画するか

	static CModel *m_paModel[8];	//モデル原型
};

#endif