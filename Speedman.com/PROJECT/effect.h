//*****************************************************************************
// �G�t�F�N�g���� [Effect.h]
// Author : �����G��
//*****************************************************************************

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Scene2D.h"

class CEffect : public CScene2D
{
public:
	CEffect(int nPriority = 3);
	virtual ~CEffect();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, int nLife, int nType);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


protected:

private:


	//�J���[�l
	D3DCOLORVALUE m_Color;

	//int m_color_r;
	//int m_color_g;
	//int m_color_b;
	//int m_color_a;

	//���炷�J���[�l
	D3DCOLORVALUE m_MinColor;

	//int m_Mincolor_r;
	//int m_Mincolor_g;
	//int m_Mincolor_b;
	//int m_Mincolor_a;

};
#endif
