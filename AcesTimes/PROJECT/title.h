//=============================================================================
// �^�C�g���Ǘ�[Title.h]
// Author : �����G��
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "manager.h"
#include "Scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;
class CUI;

class CTitle : public CScene
{
public:
	CTitle(PRIORITY Priority);
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR2 GetSize() { return D3DXVECTOR2(0.0f, 0.0f); }
	float GetSizeRot() { return 0.0f; }
	void Damage(int) { ; }
	int Damage() { return 0; }
	int GetHP() { return 0; }
	int GetMaxHP() { return 0; }
	bool GetEnemy() { return false; }
	void AddScore(int) { ; }

	static CTitle *Create();

private:
	void Select(int nAdd);
	void Choice();

	CKeyboard *m_pKeyboard;
	CGamePad *m_pGamePad;
	CUI *m_pUI[4];
	int m_nSelect;
};

#endif // _TITLE_H_
