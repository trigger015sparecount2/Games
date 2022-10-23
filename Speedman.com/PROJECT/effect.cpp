//*****************************************************************************
// �G�t�F�N�g���� [Effect.cpp]
// Author : �����G��
//*****************************************************************************

#include "Effect.h"
#include "manager.h"
#include "Renderer.h"


//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_MinColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CEffect::~CEffect()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, int /*nLife*/, int nType)
{
	CScene2D::Init(pos);

	m_Color = color;
	m_MinColor = Mincolor;

	CScene2D::SetTexture(nType);	//�I�������ԍ��̃e�N�X�`����\��
	CScene2D::SetWhidth(Size.x);
	CScene2D::SetHight(Size.y);

	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CEffect::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CEffect::Update()
{


	//�J���[�ύX
	m_Color.r += m_MinColor.r;
	m_Color.g += m_MinColor.g;
	m_Color.b += m_MinColor.b;
	m_Color.a += m_MinColor.a;

	//�J���[��0�ȉ��̎�
	if (m_Color.r < 0)
	{
		m_Color.r = 0;
	}
	if (m_Color.g < 0)
	{
		m_Color.g = 0;
	}
	if (m_Color.b < 0)
	{
		m_Color.b = 0;
	}
	if (m_Color.a < 0)
	{
		m_Color.a = 0;
	}

	ColorChange(m_Color);


}

//*****************************************************************************
// �`��
//*****************************************************************************
void CEffect::Draw()
{
	// ���_����ݒ�
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̎擾

																	 //Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//���Z�����֌W
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	CScene2D::Draw();


	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//�ʏ퍇���ɖ߂�(���Z����)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}


