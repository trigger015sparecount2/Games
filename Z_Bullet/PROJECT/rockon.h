//---------------------------
//Author:三上航世
//ロックオン(rockon.h)
//---------------------------
#ifndef _ROCKON_H_
#define _ROCKON_H_
#include "main.h"

//ロックオンの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nNumber;			//敵の番号
	bool bUse;				//使用中か
} Rockon;

//プロトタイプ宣言
HRESULT InitRockon(void);	//初期化
void UninitRockon(void);	//終了
void UpdateRockon(void);	//更新
void DrawRockon(void);		//描画
void SetRockon(D3DXVECTOR3 pos, int nNumber);	//設定
void MoveRockon(D3DXVECTOR3 pos);	//移動
int RemoveRockon(void);		//外す
int RockNumber(void);		//ロックオンの敵の番号
#endif _ROCKON_H_