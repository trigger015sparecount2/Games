//--------------------------------------
//Author:三上航世
//マウスの入力情報(mouse.h)
//---------------------------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "main.h"

typedef enum
{
	DIM_L = 0, //左クリック
	DIM_R,     //右クリック
	DIM_W,      //ホイールボタン
	DIM_MAX
}MouseButton;

//プロトタイプ宣言
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);	//初期化
void UninitMouse(void);	//終了
void UpdateMouse(void);	//更新
bool GetMousePress(MouseButton Button);		//ボタン押す
bool GetMouseTrigger(MouseButton Button);	//ボタン押したまたは離した
bool GetMouseRelease(MouseButton Button);	//ボタン離した
bool Mouse(void);		//マウス繋がってるか
float MouseX(void);		//マウス横移動
float MouseY(void);		//マウス縦移動
float MouseZ(void);		//マウスカーソル
bool GetMouseButton(MouseButton Button);	//ボタン押した
#endif _MOUSE_H_