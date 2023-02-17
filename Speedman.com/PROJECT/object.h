//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "scene3d.h"

class CModel;

class CObject : public CScene3D
{
public:
	CObject(int nPriority);
	~CObject();
	HRESULT Init(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot, int nMoveTime, D3DXVECTOR3 move, bool bDrop);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CObject *Create(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot, int nMoveTime, D3DXVECTOR3 move, bool bDrop);	//�쐬
	static void Load(int nCnt, const char *aModelName);	//���f���ǂݍ���
	static void UnLoad();	//���f���j��

private:
	bool Land(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);	//���Ƃ̓����蔻��

	CModel *m_pModel;				//���f��
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_MaxMove;			//�ő�ړ���
	D3DXVECTOR3 m_pos;				//pos
	int m_nTime;					//����
	int m_nMoveTime;				//�ړ�����
	bool m_bPlus;					//���Z���邩���Z���邩
	bool m_bDrop[2];				//�����邩

	static CModel *m_paModel[8];	//���f����
};

#endif