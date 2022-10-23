//=============================================================================
//
// �V�[������ [scene2d.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "main.h"
#include "scene.h"
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���_�t�H�[�}�b�g

typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw;       //1.0f�ŌŒ�
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

class CScene2D : public CScene
{
public:
	CScene2D(PRIORITY Priority = PRIORITY_CHARA);
	~CScene2D();
	HRESULT Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(float fWidth, float fHeight, D3DXVECTOR3 pos);
	void SetRot(float fRot);
	void SetSize(float fSize);
	static CScene2D *Create(float fWidth, float fHeight, D3DXVECTOR3 pos, PRIORITY Priority);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture(int nCntTex, int nNumTex);
	void ScrollTexture(float fTex);
	void ChangeColor(D3DCOLOR col);
	bool GetDamage(void);
	void Damage(int nDamage);
	float GetRot(int nRot);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL; //���_�o�b�t�@�ւ̃|�C���^
	float m_fRot[4]; //�|���S���̌���(�オ1.0f)
	float m_fScale;    //�|���S���̑傫��
	bool m_bScale;     //�|���S�����傫���Ȃ邩�������Ȃ邩
	LPDIRECT3DTEXTURE9 m_pTexture = NULL; //�e�N�X�`���ւ̃|�C���^
};

#endif