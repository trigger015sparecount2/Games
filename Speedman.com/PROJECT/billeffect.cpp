//=============================================================================
// 3D�G�t�F�N�g���� [BillEffect.cpp]
// Author : �����G��
// 10/24 ���������������̂ł�����Ə��Ȃ����܂����i�J���[�ɂ͖��Ȃ��ł��j
//=============================================================================
#include "billEffect.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N��
//=============================================================================
#define MAX_COLOR (255)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillEffect::CBillEffect(int nPriority) : CPlane::CPlane(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillEffect::~CBillEffect()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CBillEffect::Init(D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nTex, int nLife)
{
	CPlane::Init(Size, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	SetTexture(nTex);

	m_Size = Size;			//�傫��
	m_MinSize = MinSize;	//�傫���ϓ�

	//�J���[
	m_Color = color;

	//�J���[�ϓ�
	m_MinColor = Mincolor;

	m_nLife = nLife;
	m_bUninit = false;

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CBillEffect::Uninit()
{
	CPlane::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CBillEffect::Update()
{

	m_Size += m_MinSize;		//�T�C�Y�ύX

								//�J���[�ύX
	m_Color.r += m_MinColor.r;
	m_Color.g += m_MinColor.g;
	m_Color.b += m_MinColor.b;
	m_Color.a += m_MinColor.a;


	//�T�C�Y��0������肻��
	if (m_Size.x <= 0 ||
		m_Size.y <= 0)
	{
		m_bUninit = true;
	}

	//�J���[�l��0������肻��
	if (m_Color.r <= 0)
	{
		m_Color.r = 0;
	}
	if (m_Color.g <= 0)
	{
		m_Color.g = 0;
	}
	if (m_Color.b <= 0)
	{
		m_Color.b = 0;
	}
	if (m_Color.a <= 0)
	{
		m_Color.a = 0;
	}

	//�J���[�l��MAX_COLOR�����肻��
	if (m_Color.r >= MAX_COLOR)
	{
		m_Color.r = MAX_COLOR;
	}
	if (m_Color.g >= MAX_COLOR)
	{
		m_Color.g = MAX_COLOR;
	}
	if (m_Color.b >= MAX_COLOR)
	{
		m_Color.b = MAX_COLOR;
	}
	if (m_Color.a >= MAX_COLOR)
	{
		m_Color.a = MAX_COLOR;
	}

	//���ꂼ��K��
	ChangeSize(m_Size);
	CPlane::ColorChange(m_Color);

	//��������
	m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	//����
	if (m_bUninit == true)
	{
		SetDeath(true);
	}

}

//=============================================================================
// �`��
//=============================================================================
void CBillEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans, mtxWorld; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����


	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���Z�����֌W
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView); //�t�s������߂�

	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	/*										���ӂ̂���
	g_mtxWorldBillboard._11 = mtxView._11;
	g_mtxWorldBillboard._12 = mtxView._21;
	g_mtxWorldBillboard._13 = mtxView._31;
	g_mtxWorldBillboard._14 = mtxView._41;
	g_mtxWorldBillboard._21 = mtxView._12;
	g_mtxWorldBillboard._22 = mtxView._22;
	g_mtxWorldBillboard._23 = mtxView._32;
	g_mtxWorldBillboard._24 = mtxView._42;
	g_mtxWorldBillboard._31 = mtxView._13;
	g_mtxWorldBillboard._32 = mtxView._23;
	g_mtxWorldBillboard._33 = mtxView._33;
	g_mtxWorldBillboard._34 = mtxView._43;
	g_mtxWorldBillboard._41 = mtxView._14;	x��Pos
	g_mtxWorldBillboard._42 = mtxView._24;	y��Pos
	g_mtxWorldBillboard._43 = mtxView._34;	z��Pos
	g_mtxWorldBillboard._44 = mtxView._44;

	*/

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMatrix(mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtx(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture[m_nTexType]);    //�e�N�X�`���̐ݒ�

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

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

	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//=============================================================================
// �|���S���e�N�X�`���Z�b�g
//=============================================================================
void CBillEffect::SetTexture(int nTex)
{
	m_nTexType = nTex;
}
