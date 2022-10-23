//=============================================================================
// (����)3D�G�t�F�N�g���� [Straight3D.cpp]
// Author : �����G��
// 10/24 ����������(����
//=============================================================================
#include "Straight3D.h"

#include "renderer.h"
#include "Camera.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStraight3D::CStraight3D(int nPriority) : CBillEffect(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStraight3D::~CStraight3D()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CStraight3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife)
{
	m_move = move;

	CBillEffect::Init(Size, MinSize, color, Mincolor, nType, nLife);

	m_pCamera = CManager::GetRenderer()->GetCamera();

	//m_rot.x = m_pCamera->GetRotX();
	//m_rot.y = m_pCamera->GetRotY();

	SetPos(pos);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CStraight3D::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CStraight3D::Update()
{
	bool Pause = CManager::GetPause();

	if (Pause == false)
	{
		D3DXVECTOR3 pos = GetPos();

		pos += m_move;

		SetPos(pos);

		CBillEffect::Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CStraight3D::Draw()
{
	CBillEffect::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CStraight3D *CStraight3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife)
{
	CStraight3D *pStraight3D = new CStraight3D(3);

	if (pStraight3D != NULL)
	{
		pStraight3D->Init(pos, Size, MinSize, move, color, Mincolor, nType, nLife);
	}

	return pStraight3D;
}
