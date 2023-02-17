//=============================================================================
// タイトル管理[Title.h]
// Author : 三上航世
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "manager.h"
#include "scene.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
//class CGamePad;
class CKeyboard;
//class CMouse;
class CUI;

class CTitle : public CScene
{
public:
	CTitle(PRIORITY Priority);
	~CTitle();

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

	static CTitle *Create();	//作成

	//int GetSerectNum();
	//void SetSerectNum(int SerectNum);

private:
	void FadeIn();	//フェードイン

	//static int m_SerectNam;
	CKeyboard *m_pKeyboard;	//キーボード
	//CGamePad *m_pGamePad;
	//CMouse *m_pMouse;
	CUI *m_pUI;			//UI
	float m_fClear;		//透明度
	bool m_bClear;		//透過させるか否か
	bool m_bButton;		//押したか
	D3DXVECTOR2 m_size;	//UIのサイズ
};

#endif // _TITLE_H_
