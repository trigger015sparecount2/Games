//---------------------------
//Author:三上航世
//メッシュフィールド(mesufield.h)
//---------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitMeshfield(void);	//初期化
void UninitMeshfield(void);		//終了
void UpdateMeshfield(void);		//更新
void DrawMeshfield(void);		//描画
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlock[2], int nSize[2]);					//設定
bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius);	//当たり判定
void ResetField(void);			//リセット
#endif _MESHFIELD_H_