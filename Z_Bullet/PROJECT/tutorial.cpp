//--------------------------
//Author:�O��q��
//�`���|�g���A����ʂ̏���(tutorial.cpp)
//--------------------------
#include "input.h"
#include "gamepad.h"
#include "mouse.h"
#include "fade.h"
#include "tutorialui.h"

//����������
void InitTutorial(void)
{
	InittutorialUi();
}

//�`���[�g���A����ʂ̏I������
void UninitTutorial(void)
{
	UninittutorialUi();
}

//�`���[�g���A����ʂ̍X�V����
void UpdateTutorial(void)
{
	UpdatetutorialUi();
	if (GetAnyKey() == true || GetMouseButton(DIM_L) == true || GetAnyButton() == true)
	{
		if (GetFade() == FADE_NONE)
		{
			SetFade(MODE_GAME);
		}
	}
}

//�`�揈��
void DrawTutorial(void)
{

}