//=============================================================================
//���U���g�Ǘ�[Result.h]
// Author : satou syusuke
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "manager.h"
#include "Scene.h"
//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;

class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CResult *Create();	//�쐬

private:
	CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	CGamePad *m_pGamePad;	//�Q�[���p�b�h

	static bool m_bFade;	//�t�F�[�h
};
#endif // _RESULT_H_
