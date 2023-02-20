//------------------------
//Author:三上航世
//ポーズUI処理(pauseui.h)
//------------------------
#ifndef _PAUSEUI_H_
#define _PAUSEUI_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitpauseUi(void);	//初期化
void UninitpauseUi(void);	//終了
void UpdatepauseUi(void);	//更新
void DrawpauseUi(void);		//描画
int GetSelect(void);		//選択肢番号取得
void ResetpauseUi(void);	//リセット
#endif _PAUSEUI_H_