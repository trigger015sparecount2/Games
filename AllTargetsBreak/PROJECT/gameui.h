//------------------------
//Author:�O��q��
//UI����(gameui.h)
//------------------------
#ifndef _GAMEUI_H_
#define _GAMEUI_H_
#include "main.h"
//�}�N����`
#define TIME_LIMIT_MIN (60)   //�������ԁi���j
#define TIME_LIMIT_SEC (60)   //�������ԁi�b�j
//�v���g�^�C�v�錾
void InitGameUi(void);
void UninitGameUi(void);
void UpdateGameUi(void);
void DrawGameUi(void);
void ResetGameUi(void);
int TimeMin(void);
int TimeSec(void);
void StopTime(void);
bool GameOver(void);
void GameClear(void);
#endif _GAMEUI_H_
