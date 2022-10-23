//--------------------------
//Author:�O��q��
//���U���g��ʂ̏���(result.cpp)
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

//����������
void InitResult(void)
{
	Rankmain(PlayerScore());
	InitresultUi();
	PlaySound(SOUND_LABEL_BGM2);
}

//���U���g��ʂ̏I������
void UninitResult(void)
{
	UninitresultUi();
}

//���U���g��ʂ̍X�V����
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

//�`�揈��
void DrawResult(void)
{
	DrawresultUi();
}