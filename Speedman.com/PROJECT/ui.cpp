//*****************************************************************************
// UI関連処理(UI.cpp)
// Author : 佐藤秀亮
//こやつは何も変化なしのUI
// 10/24 丸ごと自分の奴に書き換えました（ヘッダーも同様）
//*****************************************************************************
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "UI.h"
#include "Scene2D.h"
#include "manager.h"


//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************
#define MAX_SPEED (4.0f)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CUI::CUI(int nPriority) : CScene2D(nPriority)
{
	m_bUninit = false;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CUI::~CUI()
{

}
#endif

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CUI::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType)
{
	CScene2D::Init(pos);

	SetObjType(CScene::OBJECTTYPE_UI);

	m_pos = pos;
	m_bUninit = false;

	//m_nLife = nLife;

	CScene2D::SetTexture(nType);	//選択した番号のテクスチャを貼る
	CScene2D::SetWidth(SizeX);		//サイズの適応
	CScene2D::SetHeight(SizeY);
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CUI::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CUI::Update()
{

	m_Color.r = 255;
	m_Color.g = 255;
	m_Color.b = 255;
	m_Color.a = 255;
	CScene2D::ColorChange(m_Color);

	CScene2D::SetPosition(m_pos);

	//削除
	if (m_bUninit == true)
	{
		SetDeath(true);
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//*****************************************************************************
void CUI::Draw()
{
	CScene2D::Draw();
}

//*****************************************************************************
//作成
//*****************************************************************************
CUI *CUI::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType)
{
	CUI * pUI = NULL;
	pUI = new CUI(5);
	if (pUI != NULL)
	{
		pUI->Init(pos, SizeX, SizeY, nType);
	}
	return pUI;
}
#endif
