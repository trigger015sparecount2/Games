//=============================================================================
//
// �V�[������ [scene3d.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//
struct VERTEX_3D
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
};

class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY Priority);
	~CScene3D();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	//pos�ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos() { return m_pos; }

	//�}�g���b�N�X�ݒ�
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }

	//rot�ݒ�
	D3DXVECTOR3 GetRot() { return m_rot; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	//��--------------�g��Ȃ�----------------��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return m_mtxWorld; }
	//��--------------�g��Ȃ�----------------��

	static CScene3D *Create(const D3DXVECTOR3& pos);	//�쐬
	
private:
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_pos;		//�ꏊ
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
};
#endif