//=============================================================================
//
// ���j���� [explosion.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2d.h"

class CExplosion : public CScene2D
{
public:
	CExplosion(PRIORITY Priority);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos, float fRadius, int nMaxCount);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }	//���

	static CExplosion *Create(D3DXVECTOR3 pos, float fRadius, int nMaxCount);	//�쐬

private:
	int m_nCount;	//�e�N�X�`���p�^�[���J�E���g
	int m_nMax;		//�ő�e�N�X�`���p�^�[��
	int m_nTexPat;	//�e�N�X�`���p�^�[��
};

#endif