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

	CSelectUI(int nPriority);
	~CSelectUI();

	typedef enum
	{
		SELECT_UI_NOMAL,
		SELECT_UI_CONTROL,

		SELECT_UI_MAX,
	} SELECT_UI_TYPE;

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int SelectNum, SELECT_UI_TYPE UIType);
	void Uninit();
	void Update();
	void Draw();

	static CSelectUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, int SelectNum, SELECT_UI_TYPE UIType);

	static void SetPauseSelect(int nPause);

private:
	D3DXVECTOR3 m_pos;			//���݈ʒu
	D3DCOLORVALUE m_color;
	int m_UINum;

	//�傫�����
	float m_fSizeX;
	float m_fSizeY;

	bool m_bUninit;//�l���t���O

	static CKeyboard *m_pKeyboard;
	static int m_PauseSelect;		//�|�[�Y���̃Z���N�g�ԍ�

	static bool m_bFade;

	SELECT_UI_TYPE m_nType;
};

#endif //_SELECT_UI_H_