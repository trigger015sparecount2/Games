//=============================================================================
//�Q�[���I�[�o�[����[GameOver.h]
// Author : satou syusuke
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "manager.h"
#include "Scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;

class CGameOver : public CScene
{
public:
	CGameOver();
	~CGameOver();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CGameOver *Create();	//�쐬
	
	//�I�����ݒ�
	int GetSerectNum() { return m_SerectNam; }
	void SetSerectNum(int SerectNum) { m_SerectNam = SerectNum; }

private:
	static bool m_bFade;	//�t�F�[�h
	CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	CGamePad *m_pGamePad;	//�Q�[���p�b�h

	static int m_SerectNam;	//�I��������

};

#endif // _GAMEOVER_H_
