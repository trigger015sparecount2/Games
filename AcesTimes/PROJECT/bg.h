//=============================================================================
//
// �w�i���� [bg.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "scene2d.h"

class CBg : public CScene2D
{
public:
	CBg(PRIORITY Priority);
	~CBg();
	HRESULT Init(D3DXVECTOR2 size, D3DXVECTOR3 pos, D3DXVECTOR2 TexSize);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	static CBg *Create(D3DXVECTOR2 size, D3DXVECTOR3 pos, D3DXVECTOR2 TexSize, int nTex);	//�쐬

private:
	D3DXVECTOR2 m_TexSize[2];	//�e�N�X�`�����W
	float m_fMaxTex;			//�e�N�X�`���X�N���[��
};

#endif