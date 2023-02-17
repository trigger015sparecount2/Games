//=============================================================================
// (���������ɉ����ď���)3D�G�t�F�N�g���� [VecEffect3D.cpp]
// Author : �����G��
//=============================================================================
#include "VecEffect3d.h"

#include "renderer.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CVecEffect3D::CVecEffect3D(int nPriority) : CBillEffect(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CVecEffect3D::~CVecEffect3D()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CVecEffect3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife)
{
	m_move = move;

	CBillEffect::Init(Size, MinSize, color, Mincolor, nType, nLife);

	m_FastPos = pos;

	SetPos(pos);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CVecEffect3D::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CVecEffect3D::Update()
{
	bool Pause = CManager::GetPause();

	if (Pause == false)
	{
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		D3DXVECTOR3 Endpos = pos - m_FastPos;

		//���������v�Z
		m_Vec = sqrtf(Endpos.x * Endpos.x + Endpos.y * Endpos.y + Endpos.z * Endpos.z);

		if (m_Vec >= 50.0f)
		{
			m_bUninit = true;
		}
		SetPos(pos);
		CBillEffect::Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CVecEffect3D::Draw()
{
	CBillEffect::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CVecEffect3D *CVecEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife)
{
	CVecEffect3D *pVecEffect3D = new CVecEffect3D(4);

	if (pVecEffect3D != NULL)
	{
		pVecEffect3D->Init(pos, Size, MinSize, move, color, Mincolor, nType, nLife);
	}

	return pVecEffect3D;
}
