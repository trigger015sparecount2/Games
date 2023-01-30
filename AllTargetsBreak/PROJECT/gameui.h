//------------------------
//Author:�O��q��
//UI����(gameui.h)
//------------------------
#ifndef _GAMEUI_H_
#define _GAMEUI_H_
#include "main.h"

//�}�N����`
#define TIME_LIMIT_SEC (60)	//�������ԁi�b�j
#define TIME_LIMIT_COM (60)	//�������ԁi�R���}�j

//�v���g�^�C�v�錾
void InitGameUi(void);		//������
void UninitGameUi(void);	//�I��
void UpdateGameUi(void);	//�X�V
void DrawGameUi(void);		//�`��
void ResetGameUi(void);		//UI���Z�b�g
int TimeMin(void);			//���Ԏ擾(��)
int TimeSec(void);			//���Ԏ擾(�b)
void StopTime(void);		//���Ԓ�~
bool GameOver(void);		//�Q�[���I�[�o�[�擾
void GameClear(void);		//�Q�[���N���A�\
#endif _GAMEUI_H_
