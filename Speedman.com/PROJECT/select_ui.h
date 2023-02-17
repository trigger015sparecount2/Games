//*****************************************************************************
// UI�i�I�����j�֘A����(Select_UI.h)
// Author : �����G��
//
//UI�N���X����剻�������ߏ����ɂ��N���X�������s���܂���
//*****************************************************************************
#ifndef _SELECT_UI_H_
#define _SELECT_UI_H_

#include "UI.h"
#include "manager.h"

class CSelectUI : public CUI
{
public:

	//UI�̎��
	typedef enum
	{
		SELECT_UI_NOMAL = 0,
		SELECT_UI_CONTROL,
		SELECT_UI_MAX
	} SELECT_UI_TYPE;

	CSelectUI(int nPriority);
	~CSelectUI();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int SelectNum, SELECT_UI_TYPE UIType);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CSelectUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int SelectNum, SELECT_UI_TYPE UIType);	//�쐬

	static void SetPauseSelect(int nPause) { m_nPauseSelect = nPause; }	//�|�[�Y�ԍ��ύX

private:
	D3DXVECTOR3 m_pos;		//���݈ʒu
	D3DCOLORVALUE m_color;	//�F
	int m_UINum;			//UI�ԍ�

	//�傫�����
	float m_fSizeX;
	float m_fSizeY;

	bool m_bUninit;//�l���t���O

	static CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	static int m_nPauseSelect;		//�|�[�Y���̃Z���N�g�ԍ�

	static bool m_bFade;			//�t�F�[�h����
	
	SELECT_UI_TYPE m_nType;			//UI�̎��
};

#endif //_SELECT_UI_H_