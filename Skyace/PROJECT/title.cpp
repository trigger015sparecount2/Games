//--------------------------
//Author:�O��q��
//�^�C�g����ʂ̏���(title.cpp)
//--------------------------
#include "input.h"
#include "title.h"
#include "fade.h"
#include "sound.h"
#include "bg.h"
#include "titleUi.h"

//����������
void InitTitle(void)
{
	InittitleUi();
	SetBg(1,false);
	PlaySound(SOUND_LABEL_BGM000);
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
	if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false)
	{
		PlaySound(SOUND_LABEL_YES000);
		SetFade(MODE_CHOICE, true);
	}
}

//�`�揈��
void DrawTitle(void)
{
	DrawtitleUi();
}