//------------------------
//Author:三上航世
//UI処理(ui.h)
//------------------------
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitUi(void);				//初期化
void UninitUi(void);				//終了
void UpdateUi(void);				//更新
void DrawUi(void);					//描画
void MaxBulletUI(int nMaxBullet);	//最大弾数UI
void BulletUI(int nBullet);			//現在弾数UI
void ScoreUI(int nScore);			//スコアUI
void ItemUI(int nItem);				//アイテム数UI
void ChainUI(int nChain);			//チェインUI
void ChainTimeUI(int nChainTime);	//チェインの時間経過
void HPUI(float fRate);				//HPのUI
void SPUI(float fRate);				//SPのUI
void BossHPUI(float fRate);			//ボスのUI
void BossHPUISet(void);				//ボスのUI設定
void ResetUI(void);					//リセット
#endif _UI_H_