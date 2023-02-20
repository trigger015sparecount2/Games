//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "model.h"
#include "scene3d.h"

class CObject : public CScene3D
{
public:
	CObject(PRIORITY Priority);
	~CObject();
	HRESULT Init(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_BLOCK; }			//���
	D3DXVECTOR3 GetPos() { return m_pos; }						//pos�擾
	//D3DXVECTOR3 GetMove() { return m_move; }
	float GetRadius() { return m_fRadius; }						//���a�擾
	COLLISION GetCollision() { return m_Collision; }			//�R���W�����̎�ގ擾
	D3DXVECTOR3 GetVtxMax() { return m_pModel->GetMaxSize(); }	//�T�C�Y�ő�擾
	D3DXVECTOR3 GetVtxMin() { return m_pModel->GetMinSize(); }	//�T�C�Y�ŏ��擾
	D3DXMATRIX GetMatrix() { return m_pModel->GetMatrix(); }	//�}�g���b�N�X�擾

	static CObject *Create(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot);	//�쐬
	static void Load(int nCnt, const char *aModelName);	//���f���ǂݍ���
	static void UnLoad();	//���f���j��

private:
	CModel *m_pModel;				//���f��
	D3DXVECTOR3 m_pos;				//pos
	CScene::COLLISION m_Collision;	//�����蔻��
	float m_fRadius;				//���a
	bool m_bDraw;					//�`�悷�邩

	static CModel *m_paModel[8];	//���f�����^
};

#endif