//*****************************************************************************
// UI�i��������ω�����j�֘A����(Change_UI.h)
// Author : satou syusuke
//*****************************************************************************
#ifndef _CHANGE_UI_H_
#define _CHANGE_UI_H_

#include "UI.h"
class CChangeUI : public CUI
{
public:
	//�`�F���W�^��UI�̓���
	typedef enum
	{
		CHANGE_NONE,		//�ω��Ȃ�
		CHANGE_COUNTDOWN,	//�J�E���g�_�E��
		CHANGE_TARGETMOVE,	//�ڕW�Ɍ����Ĉړ�
		CHANGE_PAUSE,		//�|�[�Y���ɕ\��
		CHANGE_CONTROL,		//�������
		CHANGE_BOUNCE,		//�o�E���h

		CHANGE_MAX,
	} CHANGE_TYPE;

	CChangeUI(int nPriority);
	~CChangeUI();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nType, D3DCOLORVALUE color, D3DCOLORVALUE MinColor, 
		CChangeUI::CHANGE_TYPE ChangeType, int nLife, D3DXVECTOR2 Nextpos, D3DXVECTOR2 move);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CChangeUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nType, D3DCOLORVALUE color, D3DCOLORVALUE MinColor, 
		CChangeUI::CHANGE_TYPE ChangeType, int nLife, D3DXVECTOR2 Nextpos, D3DXVECTOR2 move);	//�쐬

	static void SetCountDown();	//�J�E���g�_�E���ݒ�


private:

	D3DXVECTOR3 m_pos;			//���݈ʒu

	CHANGE_TYPE m_aChangeType;	//�ǂ̓��������邩
	int m_nLife;				//UI�̕\������

	D3DXVECTOR2 m_nextpos;		//���̈ړ���
	D3DXVECTOR2 m_move;			//�ړ��ʂłǂ̊p�x��
	D3DXVECTOR2 m_moveSpeed;	//�ړ���
	D3DXVECTOR2 m_Distanse;		//�p�x�v�Z�p

	D3DXVECTOR2 m_Size;			//�傫��
	D3DXVECTOR2 m_MinSize;		//�傫������

	D3DCOLORVALUE m_Color;			//�J���[
	D3DCOLORVALUE m_MinColor;		//�J���[����

	bool m_bUninit;					//����

	float m_fAngle;					//�p�x

	static int m_nCountDown;		//�J�E���g

	int m_nCntBounce;				//�o�E���h��
};

#endif
