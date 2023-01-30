//=============================================================================
//
// UI�̃e�L�X�g�������� [textui.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _TEXTUI_H_
#define _TEXTUI_H_

#include "main.h"
#include "scene2d.h"

class CTextUI : public CScene2D
{
public:
	//�e�L�X�g�̈ʒu
	typedef enum
	{
		TEXT_WORDBREAK = 0,	//���l�߉��s�����
		TEXT_RIGHT,			//�E�l��
		TEXT_MAX
	}TEXTTYPE;

	CTextUI(PRIORITY Priority);
	~CTextUI();
	HRESULT Init(int nSize, int nColor[4], TEXTTYPE texttype, char aText[128], RECT rect);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	void SetText(char aText[128]);	//���͐ݒ�
	void SetColor(int  nColor[4]);	//�F�ւ�

	static CTextUI *Create(int nSize, int nColor[4], TEXTTYPE texttype, char aText[128], RECT rect);	//�쐬
private:
	char m_aText[128];		//����
	int m_nColor[4];		//�F
	TEXTTYPE m_texttype;	//�e�L�X�g�̕`��̎d��
	LPD3DXFONT m_pFont;		//�t�H���g�ւ̃|�C���^
	RECT m_rect;			//�e�L�X�g�̕`��g
};
#endif