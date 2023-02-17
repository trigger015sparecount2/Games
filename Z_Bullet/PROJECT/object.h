//---------------------------
//Author:三上航世
//障害物(object.h)
//---------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitObject(void);	//初期化
void UninitObject(void);	//終了
void UpdateObject(void);	//更新
void DrawObject(void);		//描画
void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius);	//当たり判定
void Setobject(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 rot);	//設定
#endif _OBJECT_H_