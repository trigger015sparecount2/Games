//=============================================================================
//
// �J�����]�[������ [camerazone.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _CAMERAZONE_H_
#define _CAMERAZONE_H_

#include "main.h"
#include "plane.h"

class CCameraZone : public CPlane
{
public:
	CCameraZone(PRIORITY Priority);
	~CCameraZone();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_CAMERAPANEL; }	//���
	D3DXVECTOR3 GetVtxMax() { return m_VtxMax; }			//�ő�l
	D3DXVECTOR3 GetVtxMin() { return m_VtxMin; }			//�ŏ��l

	static CCameraZone *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//�쐬

private:
	D3DXVECTOR3 m_VtxMax;	//�ő�l
	D3DXVECTOR3 m_VtxMin;	//�ŏ��l
};

#endif