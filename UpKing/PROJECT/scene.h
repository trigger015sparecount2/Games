//=============================================================================
//
// シーン処理 [scene.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//マクロ定義
//#define POLYGON_SIZE (70.0f)
//#define PRIORITY (7)
//#define CIRCLE (float(rand() % 324) / 100.0f - float(rand() % 324) / 100.0f) //円

class CScene
{
public:
	//オブジェクトの種類
	typedef enum
	{
		OBJECTTYPE_NONE = 0,
		OBJECTTYPE_UI,
		OBJECTTYPE_PLAYER,
		OBJECTTYPE_ENEMY,
		OBJECTTYPE_FIELD,
		OBJECTTYPE_WALL,
		OBJECTTYPE_CAMERAPANEL,
		OBJECTTYPE_TUTORIAL,
		OBJECTTYPE_BLOCK,
		OBJECTTYPE_MAX
	} OBJTYPE;

	//当たり判定の種類
	typedef enum
	{
		COLLISION_SPHERE = 0,
		COLLISION_PALL,
		COLLISION_SQUARE,
		COLLISION_MAX
	} COLLISION;

	//優先順位
	typedef enum
	{
		PRIORITY_PLANE = 0,
		PRIORITY_OBJECT,
		PRIORITY_CHARA,
		PRIORITY_EFFECT,
		PRIORITY_ORBIT,
		PRIORITY_UIEFFECT,
		PRIORITY_UI,
		PRIORITY_PAUSEUI,
		PRIORITY_MAX
	} PRIORITY;

	CScene(PRIORITY Priority);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;	//初期化
	virtual void Uninit() = 0;	//終了
	virtual void Update() = 0;	//更新
	virtual void Draw() = 0;	//描画

	virtual OBJTYPE GetObjType() = 0;		//種類
	virtual D3DXVECTOR3 GetPos() = 0;		//pos取得
	virtual D3DXVECTOR3 GetRot() = 0;		//rot取得
	virtual D3DXVECTOR3 GetMove() = 0;		//移動量取得
	virtual float GetRadius() = 0;			//半径取得
	virtual float GetHeight() = 0;			//身長取得
	virtual COLLISION GetCollision() = 0;	//当たり判定取得
	virtual D3DXVECTOR3 GetVtxMax() = 0;	//サイズ最大値
	virtual D3DXVECTOR3 GetVtxMin() = 0;	//サイズ最小値
	virtual bool GetRotX() = 0;				//傾き
	virtual D3DXMATRIX GetMatrix() = 0;		//マトリックス取得
	virtual CScene *GetNext() { return m_pNext; }	//次のシーン追加

	static CScene *GetScene(PRIORITY Priority) { return m_pTop[Priority]; }	//先頭のシーン取得
	static void ReleaseAll();	//全消去
	static void UpdateAll();	//全更新
	static void DrawAll();		//全描画

	//消去するか設定
	void SetDeath(bool bDeath) { m_bDeath = bDeath; }
	bool GetDeath() { return m_bDeath; }

private:
	static CScene *m_pTop[PRIORITY_MAX];	//先頭のオブジェクトのポインタ
	static CScene *m_pCur[PRIORITY_MAX];	//現在(一番後ろ)のオブジェクトのポインタ
	CScene *m_pPrev;	//前のオブジェクトのポインタ
	CScene *m_pNext;	//後ろのオブジェクトのポインタ

	static int m_nNumAll;	//全体数
	bool m_bDeath;			//次のフレーム消すか

	PRIORITY m_Priority;	//優先順位

protected:
	void Release();			//消去
};
#endif