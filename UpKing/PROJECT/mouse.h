//=============================================================================
//
// マウス入力処理 [mouse.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "main.h"
#include "input.h"

class CMouse : CInput
{
public:
	//マウスの入力
	typedef enum
	{
		DIM_L = 0, //左クリック
		DIM_R,     //右クリック
		DIM_W,      //ホイールボタン
		DIM_MAX
	}MouseButton;

	//プロトタイプ宣言
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化
	void Uninit();	//終了
	void Update();	//更新

	bool GetPress(MouseButton Button) { return (m_MouseState.rgbButtons[Button] & 0x80) ? true : false; }			//押してる
	bool GetTrigger(MouseButton Button) { return (m_MouseStateTrigger.rgbButtons[Button] & 0x80) ? true : false; }	//押したまたは離した
	bool GetRelease(MouseButton Button) { return (m_MouseStateRelease.rgbButtons[Button] & 0x80) ? true : false; }	//離した
	bool Mouse() { return m_bMouse; }				//マウス繋がってる
	float MouseX() { return m_MouseState.lX; }		//横移動
	float MouseY() { return m_MouseState.lY; }		//縦移動
	float MouseZ() { return m_MouseState.lZ; }		//マウスホイール
	bool GetMouseButton(MouseButton Button) const;	//押した

private:
	DIMOUSESTATE m_MouseState;			//マウスの入力情報(プレス情報)
	DIMOUSESTATE m_MouseStateTrigger;	//マウスの入力情報(トリガー情報)
	DIMOUSESTATE m_MouseStateRelease;	//マウスの入力情報(リリース情報)
	bool m_bMouse;	//マウス繋がってるか
};
#endif