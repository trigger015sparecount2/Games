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

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	static CTitle *Create();

	int GetSerectNum();
	void SetSerectNum(int SerectNum);

private:
	static int m_SerectNam;
	static bool m_bFade;
	CKeyboard *m_pKeyboard;
	CGamePad *m_pGamePad;

};

#endif // _TITLE_H_
