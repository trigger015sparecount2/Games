//=============================================================================
// (���������ɉ����ď���)3D�G�t�F�N�g���� [VecEffect3D.h]
// Author : �����G��
//=============================================================================
#ifndef _VECEFFECT3D_H_
#define _VECEFFECT3D_H_

#include "main.h"
#include "billEffect.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CCamera;

class CVecEffect3D : public CBillEffect
{
public:
	CVecEffect3D(int nPriority);
	~CVecEffect3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife);
	void Uninit();
	void Update();
	void Draw();

	static CVecEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife);
private:

	D3DXVECTOR3 m_FastPos;	//�o���n�_
	D3DXVECTOR3 m_move;		//�ړ��l
	D3DXVECTOR3 m_rot;		//�p�x

	float m_Vec;			//�o���n�_����̒�������

};

#endif