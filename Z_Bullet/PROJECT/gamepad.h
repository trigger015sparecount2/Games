//--------------------------------------
//Author:三上航世
//ゲームパッドの入力情報(padinput.h)
//---------------------------------------
#ifndef _PADINPUT_H_
#define _PADINPUT_H_
#include "main.h"

//ゲームパッドのボタン
typedef enum
{
	DIP_X = 0,
	DIP_Y,
	DIP_A,
	DIP_B,
	DIP_L1,
	DIP_R1,
	DIP_L2,
	DIP_R2,
	DIP_LS,
	DIP_RS,
	DIP_BACK,
	DIP_START,
	DIP_GUIDE,
	DIP_MAX
}PadButton;

//プロトタイプ宣言
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);	//初期化
void UninitGamepad(void);		//終了
void UpdateGamepad(void);		//更新
float LeftStickX(void);			//左スティック横
float LeftStickY(void);			//左スティック縦
bool CrossKey(int nRot);		//十字キー押したか
bool PressCrossKey(int nRot);	//十字キー押してる
float RightStickX(void);		//右スティック横
float RightStickY(void);		//右スティック縦
bool GetGamePadPress(PadButton Button);		//ボタン押してる
bool GetGamePadTrigger(PadButton Button);	//ボタン入力変わった
bool GetGamePadRelease(PadButton Button);	//ボタン離した
bool GamePad(void);				//ゲームパッド繋がってるか
bool GetAnyButton(void);		//何かボタン押した
bool GetGamePadButton(PadButton Button);	//ボタン押した
int GetCrossKey(void);			//十字キーの入力情報
#endif _PADINPUT_H_
