//*****************************************************************************
// UI�i�G�t�F�N�g�j�֘A����(Effect_UI.h)
// Author : �����G��
// 10/24 �]����ui.cpp���c��オ�����̂ōו������܂���
//*****************************************************************************
#ifndef _EFFECT_UI_H_
#define _EFFECT_UI_H_

#include "UI.h"

class CEffectUI : public CUI
{
public:

	//�Ȃ�̃G�t�F�N�g���o����
	typedef enum
	{
		EFFECT_NONE,		//�G�t�F�N�g�o���Ȃ�
		EFFECT_FIRE,		//���p�[�e�B�N��
		EFFECT_CYCLE,		//�ւ����G�t�F�N�g
		EFFECT_RANKCYCLE,	//�����L���O�p�ւ����G�t�F�N�g
		EFFECT_PETAL,		//����

		EFFECT_MAX,
	} EFFECT_TYPE;

	CEffectUI(int nPriority);
	~CEffectUI();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, CEffectUI::EFFECT_TYPE EffectType);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CEffectUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, CEffectUI::EFFECT_TYPE EffectType);	//�쐬

private:
	EFFECT_TYPE m_aEffectType;	//�o���G�t�F�N�g
	D3DXVECTOR3 m_pos;			//���݈ʒu

	int m_cooltime;				//�N�[���^�C��
};

#endif //_EFFECT_UI_H_