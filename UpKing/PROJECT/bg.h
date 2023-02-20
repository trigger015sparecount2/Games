//=============================================================================
//
// �w�i���� [bg.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"

class CBg : public CScene
{
public:
	CBg(PRIORITY Priority);
	~CBg();
	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }	//���

	//��--------------�g��Ȃ�----------------��
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return m_mtxWorld; }
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }
	//��--------------�g��Ȃ�----------------��

	void SetTexture(LPDIRECT3DTEXTURE9 *pTexture) { m_pTexture = *pTexture; }			//�e�N�X�`���ݒ�
	void SetScroll(float fScroll) { m_fScroll = fScroll; }								//�X�N���[���ݒ�
	static CBg *Create(D3DXVECTOR3 pos, float fScroll, LPDIRECT3DTEXTURE9 *Texture);	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;		//�ꏊ
	D3DXVECTOR3 m_rot;		//����

	float m_fScroll;
};

#endif