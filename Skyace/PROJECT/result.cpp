//--------------------------
//Author:�O��q��
//���U���g��ʂ̏���(result.cpp)
//--------------------------
#include "input.h"
#include "result.h"
#include "bg.h"
#include "fade.h"
#include "sound.h"
#include "ui.h"
#include "rank.h"
#include "resultui.h"

//�O���[�o���錾
int g_ntime;

//����������
void InitResult(void)
{
	SetBg(0,false);
	Rankmain(Score(),Kill());
	InitresultUi();
	g_ntime = 0;
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
	g_ntime++;
	//J���������ԓ��܂��͎��ԉ߂���
	if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false && 300 <= g_ntime && g_ntime < 1200 || g_ntime == 1200)
	{
		SetFade(MODE_TITLE, true);
		//J���������ԓ��A����炷
		if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false && 300 <= g_ntime && g_ntime < 1200)
		{
			PlaySound(SOUND_LABEL_YES000);
		}
	}
}

//�`�揈��
void DrawResult(void)
{
	DrawresultUi();
}