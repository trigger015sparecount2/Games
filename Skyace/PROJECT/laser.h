//--------------------------
//Author:�O��q��
//���[�U�[�̏���(laser.h)
//--------------------------
#ifndef _LASER_H_
#define _LASER_H_
#include "main.h"
//�v���g�^�C�v�錾
void InitLaser(void);
void UninitLaser(void);
void UpdateLaser(void);
void DrawLaser(void);
void SetLaser(D3DXVECTOR3 pos, int ntype);
void ResetLaser(void);
#endif _LASER_H_

