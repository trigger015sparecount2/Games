//=============================================================================
// �t�F�[�h[Fade.h]
// Author : satou syusuke
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_


#include "manager.h"
#include "Scene2D.h"


class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE,	//�������Ȃ�
		FADE_IN,	//�t�F�[�h�C��
		FADE_OUT,	//�t�F�[�h�A�E�g
	} FADE;

	CFade(int nPriority);
	~CFade();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CFade *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType);	//�쐬

	//�t�F�[�h�ݒ�
	static void SetFade(CManager::MODE ModeNext);
	static FADE GetFade() { return m_afade; }

private:
	static FADE m_afade;				//�t�F�[�h
	static CManager::MODE m_modenext;	//���̃��[�h
	static int m_ncolorFade;			//�F

	static bool m_bUninit;				//�I��

};

#endif