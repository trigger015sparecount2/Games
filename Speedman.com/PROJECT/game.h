//=============================================================================
//�Q�[���Ǘ�[Game.h]
// Author : satou syusuke
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"
#include "Scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;

class CGame : public CScene
{
public:
	CGame(int nPriority);
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CGame *Create();	//�쐬

	//�J�E���g�_�E���t���O�ݒ�
	static void SetCountFlag(bool bFlag) { m_bCountFlag = bFlag; }
	static bool GetCountFlag() { return m_bCountFlag; };

	//�I��ԍ������Ƃ��ł�����
	static void SetSelectNum(int nSelectNum) { m_SelectNum = nSelectNum; }
	static int GetSelectNum() { return m_SelectNum; };

private:
	static bool m_bFade;	//�t�F�[�h���Ă邩
	CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	CGamePad *m_pGamePad;	//�Q�[���p�b�h

	static bool m_bCountFlag;	//�J�E���g�_�E�������ǂ���
	static int m_SelectNum;		//�I��ԍ�
};

#endif // _GAME_H_
