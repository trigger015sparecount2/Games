//--------------------------
//Author:�O��q��
//�I����ʂ̏���(choice.cpp)
//--------------------------
#include "choice.h"
#include "bg.h"
#include "choiceui.h"

//����������
void InitChoice(void)
{
	InitchoiceUi();
	SetBg(0,false);
}

//�I����ʂ̏I������
void UninitChoice(void)
{
	UninitchoiceUi();
}

//�I����ʂ̍X�V����
void UpdateChoice(void)
{
	UpdatechoiceUi();
}

//�`�揈��
void DrawChoice(void)
{
	DrawchoiceUi();
}