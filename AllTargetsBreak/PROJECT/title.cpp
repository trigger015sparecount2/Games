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
#include "result.h"
#include "padinput.h"

//�O���[�o���ϐ�
int g_nTtime;

//����������
void InitTitle(void)
{
	InittitleUi();
	g_nTtime = 0;
	SetBg(1, false);
	if (Demo() == false)
	{
		PlaySound(SOUND_LABEL_BGM000);
	}
}

//�^�C�g����ʂ̏I������
void UninitTitle(void)
{
	UninittitleUi();
}

//�^�C�g����ʂ̍X�V����
void UpdateTitle(void)
{
	g_nTtime++;
	UpdatetitleUi();
	
	//�����������t�F�[�h�����ĂȂ�
	if (GetAnyKey() == true && GetFade() == FADE_NONE || GetAnyButton() == true && GetFade() == FADE_NONE)
	{
		//�`���[�g���A���Ɉڍs
		PlaySound(SOUND_LABEL_YES);
		SetFade(MODE_TUTORIAL);
		Demoresult(false);
	}
	//���Ԃ������t�F�[�h�����ĂȂ�
	if (g_nTtime >= 1200 && GetFade() == FADE_NONE)
	{
		//���U���g�Ɉڍs
		SetFade(MODE_RESULT);
		Demoresult(true);
	}
}

//�`�揈��
void DrawTitle(void)
{
	DrawtitleUi();
}