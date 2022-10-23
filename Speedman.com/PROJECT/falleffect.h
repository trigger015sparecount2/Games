//*****************************************************************************
// (������)�G�t�F�N�g���� [FallEffect.h]
// Author : �����G��
//*****************************************************************************
#ifndef _FALLEFFECT_H_
#define _FALLEFFECT_H_

#include "Effect.h"

class CFallEffect : public CEffect
{
public:
	CFallEffect(int nPriority);
	~CFallEffect();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nLife, int nType, D3DXVECTOR2 AddMovement);
	void Uninit();
	void Update();
	void Draw();

	static CFallEffect*Create(D3DXVECTOR3 pos, D3DXVECTOR2 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nLife, int nType, D3DXVECTOR2 AddMovement);
private:
	D3DXVECTOR2 m_Size;			//�傫��
	D3DXVECTOR2 m_MinSize;		//�傫���ϓ�

	int m_nLife;				//����
	D3DXVECTOR2 m_move;			//�ړ�
	D3DXVECTOR2 m_Addpos;		//����

	bool m_bUninit;		//�������ǂ���
};

#endif // !_FALLEFFECT_H_
