//=============================================================================
//
// �󏈗� [sky.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "scene3d.h"

class CSky : public CScene
{
public:
	CSky(int nPriority);
	~CSky();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	void SetTexture(LPDIRECT3DTEXTURE9 *Texture) { m_pTexture = *Texture; }				//�e�N�X�`���ݒ�
	void SetScroll(float fScroll) { m_fScroll = fScroll; }	//�X�N���[�����x�ݒ�

	static CSky *Create(D3DXVECTOR3 pos, float fScroll, LPDIRECT3DTEXTURE9 *Texture);	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;		//�ꏊ
	D3DXVECTOR3 m_rot;		//����

	float m_fScroll;		//�X�N���[�����x
};

#endif