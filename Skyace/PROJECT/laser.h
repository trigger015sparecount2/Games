//--------------------------
//Author:�O��q��
//���[�U�[�̏���(laser.h)
//--------------------------
#ifndef _LASER_H_
#define _LASER_H_
#include "main.h"

//�v���g�^�C�v�錾
void InitLaser(void);	//������
void UninitLaser(void);	//�I��
void UpdateLaser(void);	//�X�V
void DrawLaser(void);	//�`��
void SetLaser(D3DXVECTOR3 pos, int ntype);	//�ݒ�
void ResetLaser(void);	//���Z�b�g
#endif _LASER_H_

