//--------------------------
//Author:�O��q��
//���U���g��ʂ̏���(result.cpp)
//--------------------------
#include "input.h"
#include "result.h"
#include "bg.h"
#include "fade.h"
#include "sound.h"
#include "gameui.h"
#include "rank.h"
#include "padinput.h"
#include "resultui.h"

//�O���[�o���錾
int g_nRtime;
bool g_bDemo;

//����������
void InitResult(void)
{
	//�w�i�ݒ�
	SetBg(0, false);

	//�����L���O�ݒ�
	Rankmain(TimeMin(), TimeSec(), g_bDemo);

	//������
	InitresultUi();
	g_nRtime = 0;
	if (g_bDemo == false)
	{
		if (TimeMin() == TIME_LIMIT_SEC)
		{
			PlaySound(SOUND_LABEL_BGM003);
		}
		else
		{
			PlaySound(SOUND_LABEL_BGM002);
		}
	}
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
	g_nRtime++;

	//�����{�^��������邩���Ԃ��o��
	if (GetAnyKey() == true || GetAnyButton() == true || g_nRtime == 1200)
	{
		//�f�����t�F�[�h�����ĂȂ��A�܂��̓f������Ȃ����Ԃ�������x�o���Ă��ăt�F�[�h�����ĂȂ�
		if (GetFade() == FADE_NONE && g_bDemo == true || g_bDemo == false && g_nRtime > 300 && GetFade() == FADE_NONE)
		{
			//�^�C�g���ɖ߂�
			SetFade(MODE_TITLE);
			if (GetAnyKey() == true || GetAnyButton() == true)
			{
				PlaySound(SOUND_LABEL_YES);
			}
		}
	}
}

//�`�揈��
void DrawResult(void)
{
	DrawresultUi();
}

//�f�����ݒ肷��
void Demoresult(bool bDemo)
{
	g_bDemo = bDemo;
}

//�f�����擾
bool Demo(void)
{
	return g_bDemo;
}

//���Ԏ擾
int ResultTime(void)
{
	return g_nRtime;
}