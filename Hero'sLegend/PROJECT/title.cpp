//--------------------------
//Author:�O��q��
//�^�C�g����ʂ̏���(title.cpp)
//--------------------------
#include "input.h"
#include "title.h"
#include "fade.h"
#include "mouse.h"
#include "gamepad.h"
#include "titleUi.h"
#include "sound.h"

//����������
void InitTitle(void)
{
	InittitleUi();
	PlaySound(SOUND_LABEL_BGM0);
}

//�^�C�g����ʂ̏I������
void UninitTitle(void)
{
	UninittitleUi();
}

//�^�C�g����ʂ̍X�V����
void UpdateTitle(void)
{
	UpdatetitleUi();
	if (GetAnyKey() == true || GetMouseButton(DIM_L) == true || GetAnyButton() == true)
	{
		if (GetFade() == FADE_NONE)
		{
			SetFade(MODE_TUTORIAL);
		}
	}
}

//�`�揈��
void DrawTitle(void)
{
	
}