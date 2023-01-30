//=============================================================================
//
// �{������ [bomb.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_

#include "main.h"
#include "scene2d.h"

class CBomb : public CScene2D
{
public:
	CBomb(PRIORITY Priority);
	~CBomb();
	HRESULT Init(D3DXVECTOR3 pos, float fRadius, int nCount);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }	//���

	static CBomb *Create(D3DXVECTOR3 pos, float fRadius, int nCount);	//�쐬

private:
	int m_nCount;	//����
	float m_fClear;	//�����x
	bool m_bClear;	//�_��
};

#endif