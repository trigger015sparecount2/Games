//--------------------------
//Author:�O��q��
//���ꂽ�Ƃ��̏���(death.h)
//--------------------------
#ifndef _DEATH_H_
#define _DEATH_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitDeath(void);	//������
void UninitDeath(void);	//�I��
void UpdateDeath(void);	//�X�V
void DrawDeath(void);	//�`��
void SetDeath(D3DXVECTOR3 pos, bool bSound);	//�ݒ�
void ResetDeath(void);	//���Z�b�g
#endif _DEATH_H_
