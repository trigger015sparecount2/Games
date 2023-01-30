//=============================================================================
//
// ���[�v�揈�� [warp.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _WARP_H_
#define _WARP_H_

#include "main.h"
#include "scene2d.h"

class CWarp : public CScene2D
{
public:
	CWarp(PRIORITY Priority);
	~CWarp();
	HRESULT Init(D3DXVECTOR2 size);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }		//�`�悷�邩�ݒ�
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }	//���

	static CWarp *Create(D3DXVECTOR2 size);	//�쐬

private:
	float m_fClear;	//�����x
	bool m_bClear;	//�_�ŔZ�����邩�������邩
	bool m_bDraw;	//�`�悷�邩
};
#endif