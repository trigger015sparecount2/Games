//---------------------------
//Author:�O��q��
//��(wall.h)
//---------------------------
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitWall(void);	//������
void UninitWall(void);	//�I��
void UpdateWall(void);	//�X�V
void DrawWall(void);	//�`��
void CollisionWall(D3DXVECTOR3 *pPos, float fRadius);	//�ǂƂ̓����蔻��
#endif _WALL_H_