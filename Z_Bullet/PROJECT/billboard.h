//---------------------------
//Author:三上航世
//ビルボード(billbaurd.h)
//---------------------------
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitBillboard(void);		//初期化
void UninitBillboard(void);			//終了
void UpdateBillboard(void);			//更新
void DrawBillboard(void);			//描画
void SetBillboard(D3DXVECTOR3 pos);	//設定
int CountBoard(void);				//使用中カウント
D3DXMATRIX Boardmat(void);			//マトリックス
void ResetBillbourd(void);			//リセット
void MoveBourd(D3DXVECTOR3 pos);	//移動させる
#endif _BILLBOARD_H_