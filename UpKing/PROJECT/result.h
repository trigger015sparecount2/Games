//=============================================================================
//リザルト管理[Result.h]
// Author : 三上航世
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "manager.h"
#include "scene.h"
//*****************************************************************************
//前方宣言
//*****************************************************************************
class CGamePad;

class CResult : public CScene
{
public:
	CResult(PRIORITY Priority);
	~CResult();

	HRESULT Init(D3DXVECTOR3 pos);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	//↓--------------使わない----------------↓
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXMATRIX GetMatrix() { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	//↑--------------使わない----------------↑

	static CResult *Create();

private:
	CKeyboard *m_pKeyboard;	//キーボード
	CGamePad *m_pGamePad;	//ゲームパッド
};

#endif // _RESULT_H_
