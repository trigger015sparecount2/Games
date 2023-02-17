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
class CKeyboard;

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CTitle *Create();	//�쐬

	//�I�񂾔ԍ��ݒ�
	int GetSerectNum() { return m_nSelectNum; }
	void SetSerectNum(int SelectNum) { m_nSelectNum = SelectNum; }

private:
	static int m_nSelectNum;	//�I�񂾔ԍ�
	static bool m_bFade;		//�t�F�[�h
	CKeyboard *m_pKeyboard;		//�L�[�{�[�h
	CGamePad *m_pGamePad;		//�Q�[���p�b�h

};

#endif // _TITLE_H_
