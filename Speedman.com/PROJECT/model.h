//=============================================================================
//
// ���f������ [model.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

class CModel
{
public:
	CModel();
	~CModel();
	HRESULT Init(const char *aModelName);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	void DrawObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�I�u�W�F�N�g�`��

	//�e�ݒ�
	void SetParent(CModel *model) { m_pParent = model; }
	CModel *GetParent() { return m_pParent; }

	//�}�g���b�N�X�ݒ�
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }
	void SetMatrix(D3DXMATRIX Matrix) { m_mtxWorld = Matrix; }

	//pos�ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos() { return m_pos; }

	//rot�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot() { return m_rot; }

	//����pos��rot�̐ݒ�
	void SetOriPos(D3DXVECTOR3 pos) { m_posOri = pos; }
	void SetOriRot(D3DXVECTOR3 rot) { m_rotOri = rot; }

	//�ő�ŏ��T�C�Y�擾
	D3DXVECTOR3 GetMinSize();
	D3DXVECTOR3 GetMaxSize();
	
	static CModel *Create(const char *aModelName);	//�쐬

private:
	LPD3DXMESH m_pMesh;			//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD m_nNumMat;			//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 m_aTextureModel[4] = {};	//�e�N�X�`��
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_posOri;		//���X�̈ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_rotOri;		//���X�̌���
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	int m_nIdxModelParent;		//�e���f���̃C���f�b�N�X

	CModel *m_pParent;			//�e���f��
};

#endif