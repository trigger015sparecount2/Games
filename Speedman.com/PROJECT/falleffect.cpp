//*****************************************************************************
// (������)�G�t�F�N�g���� [FallEffect.cpp]
// Author : �����G��
//*****************************************************************************

#include "FallEffect.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CFallEffect::CFallEffect(int nPriority) : CEffect(nPriority)
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);

	m_nLife = 0;
	m_bUninit = false;
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_Addpos = D3DXVECTOR2(0.0f, 0.0f);
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CFallEffect::~CFallEffect()
{

}

//*****************************************************************************
//	������
//*****************************************************************************
HRESULT CFallEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR2 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nLife, int nType, D3DXVECTOR2 AddMovement)
{
	CEffect::Init(pos, color, Mincolor, Size, nLife, nType);
	m_Size = Size;
	m_MinSize = MinSize;

	m_nLife = nLife;
	m_Addpos = AddMovement;
	m_move = move;
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CFallEffect::Uninit()
{
	CEffect::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CFallEffect::Update()
{
	CEffect::Update();

	D3DXVECTOR3 pos = GetPosition();

	m_move += m_Addpos;		//�ړ��l�Ɋ��������Z

	pos += D3DXVECTOR3(m_move.x, m_move.y, 0.0f);

	SetPosition(pos);
	m_Size += m_MinSize;

	//�T�C�Y�ύX�i����ꍇ�j
	SetWidth(m_Size.x);
	SetHeight(m_Size.y);

	m_nLife--;		//���C�t���Z

					//��ʊO����
	if (pos.y < 0)
	{
		m_bUninit = true;
	}
	else if (pos.y > SCREEN_HEIGHT)
	{
		m_bUninit = true;
	}
	if (pos.x < 0)
	{
		m_bUninit = true;
	}
	else if (pos.x > SCREEN_WIDTH)
	{
		m_bUninit = true;
	}


	//����������0�ɂȂ�����
	if (m_Size.x < 0 || m_Size.y < 0)
	{
		m_bUninit = true;
	}
	//������0�ɂȂ�����
	if (m_nLife < 0)
	{
		m_bUninit = true;
	}

	//�j��
	if (m_bUninit == true)
	{
		SetDeath(true);
	}
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CFallEffect::Draw()
{
	CEffect::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CFallEffect *CFallEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nLife, int nType, D3DXVECTOR2 AddMovement)
{
	CFallEffect *pFallEffect = NULL;
	pFallEffect = new CFallEffect(3);		//�������m��
											//NULL�`�F�b�N
	if (pFallEffect != NULL)
	{
		pFallEffect->Init(pos, move, color, Mincolor, Size, MinSize, nLife, nType, AddMovement);
	}

	return pFallEffect;
}
