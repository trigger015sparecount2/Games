//---------------------------
//Author:三上航世
//フィールド(field.h)
//---------------------------
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitField(void);	//初期化
void UninitField(void);		//終了
void UpdateField(void);		//更新
void DrawField(void);		//描画
bool LandField(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove, float fRadius);	//当たり判定
#endif _FIELD_H_