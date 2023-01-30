//=============================================================================
//
// �e���� [shadow.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "scene2d.h"

class CShadow : public CScene2D
{
public:
	CShadow(PRIORITY Priority);
	~CShadow();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CShadow *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nType);	//�쐬

private:
	
};

#endif