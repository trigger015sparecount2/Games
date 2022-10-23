//--------------------------
//Author:三上航世
//リザルト画面の処理(result.cpp)
//--------------------------
#include "input.h"
#include "result.h"
#include "fade.h"
#include "ui.h"
#include "resultui.h"
#include "mouse.h"
#include "gamepad.h"
#include "rank.h"
#include "player.h"
#include "sound.h"

//初期化処理
void InitResult(void)
{
	Rankmain(PlayerScore());
	InitresultUi();
	PlaySound(SOUND_LABEL_BGM2);
}

//リザルト画面の終了処理
void UninitResult(void)
{
	UninitresultUi();
}

//リザルト画面の更新処理
void UpdateResult(void)
{
	UpdateresultUi();
	if (GetAnyKey() == true || GetMouseButton(DIM_L) == true || GetAnyButton() == true)
	{
		if (GetFade() == FADE_NONE)
		{
			PlaySound(SOUND_LABEL_OK);
			SetFade(MODE_TITLE);
		}
	}
}

//描画処理
void DrawResult(void)
{
	DrawresultUi();
}