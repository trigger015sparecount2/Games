//=============================================================================
//���U���g�Ǘ�[Result.h]
// Author : �O��q��
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "manager.h"
#include "scene.h"
//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;
class CUI;

class CResult : public CScene
{
public:
	CResult(PRIORITY Priority);
	~CResult();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }	//���

	//�g��Ȃ���
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR2 GetSize() { return D3DXVECTOR2(0.0f, 0.0f); }
	void Damage(int, D3DXVECTOR3) { ; }
	void Damage(int) { ; }
	float GetSizeRot() { return 0.0f; }
	int Damage() { return 0; }
	int GetHP() { return 0; }
	int GetMaxHP() { return 0; }
	bool GetEnemy() { return false; }
	void AddScore(int) { ; }
	//�g��Ȃ���

	static CResult *Create();	//�쐬

private:
	//�����L���O�̃��[�h�A�Z�[�u
	void RankLoad();
	void RankSave();

	CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	CGamePad *m_pGamePad;	//�Q�[���p�b�h
	LPD3DXFONT m_pFont[4];	//����
	int m_nScore[3];		//�X�R�A
	CUI *m_pUI;				//�_��UI
	bool m_bClear;			//�_��
	float m_fClear;			//�����x
};

#endif // _RESULT_H_
