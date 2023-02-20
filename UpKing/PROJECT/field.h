//=============================================================================
//
// �n�ʏ��� [field.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "plane.h"

class CField : public CPlane
{
public:
	CField(PRIORITY Priority);
	~CField();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 Tex, bool bRotX);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_FIELD; }	//���
	D3DXVECTOR3 GetVtxMax() { return m_VtxMax; }		//�T�C�Y�ő�l�擾
	D3DXVECTOR3 GetVtxMin() { return m_VtxMin; }		//�T�C�Y�ŏ��l�擾
	bool GetRotX() { return m_bRotX; }					//�X�������擾

	static CField *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTex, D3DXVECTOR2 Tex, bool bRotX);	//�쐬

private:
	D3DXVECTOR3 m_VtxMax;	//�T�C�Y�ő�l
	D3DXVECTOR3 m_VtxMin;	//�T�C�Y�ŏ��l
	bool m_bRotX;			//�X������
	bool m_bDraw;			//�`�悷�邩
};

#endif