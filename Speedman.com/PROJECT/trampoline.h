//=============================================================================
//
// �g�����|�������� [trampoline.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _TRAMPOLINE_H_
#define _TRAMPOLINE_H_

#include "main.h"
#include "plane.h"

class CTrampoline : public CPlane
{
public:
	CTrampoline(int nPriority);
	~CTrampoline();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CTrampoline *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//�쐬

private:

};

#endif