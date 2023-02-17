//------------------------
//Author:�O��q��
//UI����(ui.h)
//------------------------
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitUi(void);				//������
void UninitUi(void);				//�I��
void UpdateUi(void);				//�X�V
void DrawUi(void);					//�`��
void MaxBulletUI(int nMaxBullet);	//�ő�e��UI
void BulletUI(int nBullet);			//���ݒe��UI
void ScoreUI(int nScore);			//�X�R�AUI
void ItemUI(int nItem);				//�A�C�e����UI
void ChainUI(int nChain);			//�`�F�C��UI
void ChainTimeUI(int nChainTime);	//�`�F�C���̎��Ԍo��
void HPUI(float fRate);				//HP��UI
void SPUI(float fRate);				//SP��UI
void BossHPUI(float fRate);			//�{�X��UI
void BossHPUISet(void);				//�{�X��UI�ݒ�
void ResetUI(void);					//���Z�b�g
#endif _UI_H_