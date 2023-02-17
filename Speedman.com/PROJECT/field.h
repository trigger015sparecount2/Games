//=============================================================================
//
// �t�B�[���h���� [field.h]
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
	CField(int nPriority);
	~CField();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CField *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nTex, D3DXVECTOR2 Tex);	//�쐬

private:
	
};

#endif