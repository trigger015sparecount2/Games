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
	CShadow(int nPriority);
	~CShadow();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);				//������
	void Uninit();													//�I��
	void Update();													//�X�V
	void Draw();													//�`��
	void Move(float fHeight);										//�����̈ړ�
	void MoveY(D3DXVECTOR3 pos, float fRotX);						//�ړ�
	
	static CShadow *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);		//�쐬

private:
	float m_fLength;		//�v���C���[�Ƃ̍����̍�
	float m_fPosY;			//�e�̍���
	D3DXVECTOR3 m_size;		//�T�C�Y
};

#endif