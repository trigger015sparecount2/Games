//---------------------------
//Author:三上航世
//壁(wall.h)
//---------------------------
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitWall(void);	//初期化
void UninitWall(void);	//終了
void UpdateWall(void);	//更新
void DrawWall(void);	//描画
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlock[2], int nSize[2], int nWall);	//設定
void CollisionWall(D3DXVECTOR3 *pPos, float fRadius);	//当たり判定
void ResetWall(void);	//リセット
#endif _WALL_H_