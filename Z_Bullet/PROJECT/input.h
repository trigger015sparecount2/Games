//--------------------------------------
//Author:三上航世
//キーボードの入力情報(input.h)
//---------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//初期化
void UninitKeyboard(void);			//終了
void UpdateKeyboard(void);			//更新
bool GetKeyboardPress(int nKey);	//押してる
bool GetKeyboardTrigger(int nKey);	//押したまたは離した
bool GetKeyboardRelease(int nKey);	//離した
bool GetAnyKey(void);				//何か押した
bool GetKeyboardKey(int nKey);		//押した
#endif _INPUT_H_