//--------------------------
//Author:�O��q��
//�`���|�g���A����ʂ̏���(tutorial.cpp)
//--------------------------
#include "input.h"
#include "bg.h"
#include "sound.h"
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
}

//�`�揈��
void DrawTutorial(void)
{
	DrawtutorialUi();
}