//---------------------------
//Author:�O��q��
//�ړ��֘A(move.cpp)
//---------------------------
#include "move.h"

//�ړ����x
void Move(D3DXVECTOR3 *pMove, float fMove, float fRot)
{
	pMove->x -= (sinf(fRot) * fMove + pMove->x) * 0.1f;
	pMove->z -= (cosf(fRot) * fMove + pMove->z) * 0.1f;
}

//�ړ����x�ቺ��
void Slow(D3DXVECTOR3 *pMove)
{
	pMove->x -= pMove->x * 0.1f;
	pMove->z -= pMove->z * 0.1f;
}