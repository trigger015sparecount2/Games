//=============================================================================
// (����)3D�G�t�F�N�g���� [Straight3D.h]
// Author : �����G��
// 10/24 ����������(����
//=============================================================================
#ifndef _STRAIGHT3D_H_
#define _STRAIGHT3D_H_

#include "main.h"
#include "billEffect.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CCamera;

class CStraight3D : public CBillEffect
{
public:
	CStraight3D(int nPriority);
	~CStraight3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CStraight3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, D3DXVECTOR3 move, 
		D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, int nType, int nLife);	//�쐬
private:

	D3DXVECTOR3 m_move;	//�ړ��l
	D3DXVECTOR3 m_rot;	//����

	CCamera *m_pCamera;	//�J����

};

#endif