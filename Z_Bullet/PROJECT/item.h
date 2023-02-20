//---------------------------
//Author:三上航世
//アイテム(item.h)
//---------------------------
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitItem(void);			//初期化
void UninitItem(void);			//終了
void UpdateItem(void);			//更新
void DrawItem(void);			//描画
void SetItem(D3DXVECTOR3 pos);	//設定
void CollisionItem(D3DXVECTOR3 pos, float fRadius);	//当たり判定
void ResetItem(void);			//リセット
#endif _ITEM_H_