//---------------------------
//Author:�O��q��
//��(wall.h)
//---------------------------
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"
//�v���g�^�C�v�錾
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlock[2], int nSize[2], int nWall);
void CollisionWall(D3DXVECTOR3 *pPos, float fRadius);
void ResetWall(void);
#endif _WALL_H_