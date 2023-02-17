//=============================================================================
//
// �e���� [shadow.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "plane.h"

class CShadow : public CPlane
{
public:
	CShadow(PRIORITY Priority);
	~CShadow();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	void Move(float fHeight);	//�ړ�
	void MoveY(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�ړ�

	static CShadow *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//�쐬

private:
	float m_fPosY;		//����
	float m_fLength;	//����
	D3DXVECTOR3 m_size;	//�T�C�Y
};

#endif