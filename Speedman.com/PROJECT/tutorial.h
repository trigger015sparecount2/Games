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

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CTutorial *Create();	//�쐬

	//�I��ԍ������Ƃ��ł�����
	static void SetSelectNum(int nSelectNum) { m_nSelectNum = nSelectNum; }
	static int GetSelectNum() { return m_nSelectNum; };

private:
	static bool m_bFade;		//�t�F�[�h
	CKeyboard *m_pKeyboard;		//�L�[�{�[�h
	CGamePad *m_pGamePad;		//�Q�[���p�b�h

	static int m_nSelectNum;	//�I��ԍ�
};

#endif // _TUTORIAL_H_
