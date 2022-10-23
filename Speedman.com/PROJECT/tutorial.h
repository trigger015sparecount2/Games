//=============================================================================
//�`���[�g���A���Ǘ�[Tutorial.h]
// Author : satou syusuke
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "manager.h"
#include "Scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;

class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	static CTutorial *Create();

	//�I��ԍ������Ƃ��ł�����
	static void SetSelectNum(int m_SelectNum);
	static int GetSelectNum() { return m_SelectNum; };

private:
	static bool m_bFade;
	CKeyboard *m_pKeyboard;
	CGamePad *m_pGamePad;

	static int m_SelectNum;			//�I��ԍ�

};

#endif // _TUTORIAL_H_
