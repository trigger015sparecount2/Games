//=============================================================================
//
// �e�ۏ��� [bullet.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2d.h"

class CBullet : public CScene2D
{
public:
	CBullet(PRIORITY Priority);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, bool bEnemy);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_BULLET; }	//���
	bool GetEnemy() { return m_bEnemy; }	//�G�̕����Ԃ�
	int Damage() { return 1; }	//�_���[�W��

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, bool bEnemy);	//�쐬

private:
	bool CollisionBomb(D3DXVECTOR3 pos);	//���e�Ƃ̓����蔻��

	D3DXVECTOR3 m_move;	//�ړ����x
	bool m_bEnemy;		//�G�̂��̂�
	bool m_bSlow;		//�x����
};

#endif