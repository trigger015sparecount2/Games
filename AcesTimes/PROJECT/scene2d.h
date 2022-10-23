//*****************************************************************************
// �V�[��2D���� [Scene2D.h]
// Author : �O��q��
//*****************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "Scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAX_TEXTURE (64)		//�ő�Ŏg����2D�p�̉摜��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_����
	float rhw;			// 1.0�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
} VERTEX_2D;

//*****************************************************************************
//�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(PRIORITY Priority);
	~CScene2D();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();				//�I��
	void Update();				//�X�V
	void Draw();				//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR2 GetSize() { return m_Size; }
	void Damage(int) { ; }
	int Damage() { return 0; }
	int GetHP() { return 0; }
	int GetMaxHP() { return 0; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	float GetSizeRot() { return m_fRot[0]; }
	void SetSizeRot(float);
	void AddRot(float);
	void Set();
	bool GetEnemy() { return false; }
	void AddScore(int) { ; }

	static void UninitTexture();

	static void CreateTexture();	//�e�N�X�`���ǂݍ���

	void SetSize(D3DXVECTOR2 Size) { m_Size = Size; }		//�傫���X�V

	void SetTexture(int nTex) { m_nType = nTex; }		//�e�N�X�`���^�C�v

	void ColorChange(D3DXCOLOR color);	//�J���[�ύX

	void SetTex(int Texpos, float TexSize);						//�e�N�X�`���p�^�[���ԍ��A�p�^�[���P�̃T�C�Y
	void TexMove(float TexMoveU, float TexMoveV);				//�e�N�X�`�����W�̍X�V
	void SetTex(D3DXVECTOR2 Scroll, D3DXVECTOR2 TipScroll);

	void SetHGauge(D3DXVECTOR2 size);				//�����Q�[�W�^�C�v�̃X�P�[���ύX

private:

	static LPDIRECT3DTEXTURE9 m_Texture[MAX_TEXTURE];				//�e�N�X�`���[�|�C���^
	static int m_nMaxTex;											//�g�p����ő�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;				//�ʒu

	D3DXVECTOR2 m_Size;

	int m_nType;					//���

	int m_Texpos;					//�e�N�X�`�����W
	float m_TexSize;				//�e�N�X�`���T�C�Y

	float m_TexMoveU;				//�e�N�X�`���ړ��l
	float m_TexMoveV;				//�e�N�X�`���ړ��l

	float m_PosTexU;				//�e�N�X�`��U���W
	float m_PosTexV;				//�e�N�X�`��V���W

	float m_fRot[4];

	//�J���[�l
	D3DCOLORVALUE m_color;
};
#endif
