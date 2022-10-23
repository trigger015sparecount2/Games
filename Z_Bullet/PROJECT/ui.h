//------------------------
//Author:�O��q��
//UI����(ui.h)
//------------------------
#ifndef _UI_H_
#define _UI_H_
#include "main.h"
//�v���g�^�C�v�錾
HRESULT InitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
void MaxBulletUI(int nMaxBullet);
void BulletUI(int nBullet);
void ScoreUI(int nScore);
void ItemUI(int nItem);
void ChainUI(int nChain);
void ChainTimeUI(int nChainTime);
void HPUI(float fRate);
void SPUI(float fRate);
void BossHPUI(float fRate);
void BossHPUISet(void);
void ResetUI(void);
#endif _UI_H_