//---------------------------
//Author:三上航世
//移動関連(move.h)
//---------------------------
#ifndef _MOVE_H_
#define _MOVE_H_
#include "main.h"

void Move(D3DXVECTOR3 *pMove, float fMove, float fRot);	//移動
void Slow(D3DXVECTOR3 *pMove);	//遅くする
#endif _MOVE_H_