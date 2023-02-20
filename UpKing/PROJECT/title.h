//=============================================================================
// �^�C�g���Ǘ�[Title.h]
// Author : �O��q��
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "manager.h"
#include "scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
//class CGamePad;
class CKeyboard;
//class CMouse;
class CUI;

class CTitle : public CScene
{
public:
	CTitle(PRIORITY Priority);
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	//��--------------�g��Ȃ�----------------��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXMATRIX GetMatrix() { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	//��--------------�g��Ȃ�----------------��

	static CTitle *Create();	//�쐬

	//int GetSerectNum();
	//void SetSerectNum(int SerectNum);

private:
	void FadeIn();	//�t�F�[�h�C��

	//static int m_SerectNam;
	CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	//CGamePad *m_pGamePad;
	//CMouse *m_pMouse;
	CUI *m_pUI;			//UI
	float m_fClear;		//�����x
	bool m_bClear;		//���߂����邩�ۂ�
	bool m_bButton;		//��������
	D3DXVECTOR2 m_size;	//UI�̃T�C�Y
};

#endif // _TITLE_H_
