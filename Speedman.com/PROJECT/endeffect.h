//*****************************************************************************
// (�I�����ɉ�������)�G�t�F�N�g���� [EndEffect.h]
// Author : �����G��
//*****************************************************************************
#ifndef _ENDEFFECT_H_
#define _ENDEFFECT_H_

#include "Effect.h"

class CEndEffect : public CEffect
{
public:

	typedef enum
	{
		TYPE_FIREWORK,

		TYPE_MAX,
	} TYPE_ENDEFFECT;

	CEndEffect(int nPriority);
	~CEndEffect();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, int nLife, int nType, CEndEffect::TYPE_ENDEFFECT atype);
	void Uninit();
	void Update();
	void Draw();

	static CEndEffect*Create(D3DXVECTOR3 pos, D3DXVECTOR2 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, int nLife, int nType, CEndEffect::TYPE_ENDEFFECT atype);
private:

	TYPE_ENDEFFECT m_nType;		//�o���z
	D3DXVECTOR2 m_Size;			//�傫��

	int m_nLife;				//����
	D3DXVECTOR2 m_move;			//�ړ�

	bool m_bUninit;		//�������ǂ���
};

#endif // !_FALLEFFECT_H_
