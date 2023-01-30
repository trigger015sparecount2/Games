//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2d.h"

class CShadow;

class CEnemy : public CScene2D
{
public:
	CEnemy(PRIORITY Priority = PRIORITY_CHARA);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, float fRotY, float fInterval, float fSpeed, D3DXVECTOR2 size, int nShadowTex, int nHP, float fBulletMax, int nMoney, int nScore, float fBulletSpeed, int nBulletType);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_ENEMY; }	//���
	void Damage(int nDamage);	//�_���[�W����

	static CEnemy *Create(D3DXVECTOR3 pos, int nTexType, int nShadowTex, float fRotY, float fInterval, float fSpeed, D3DXVECTOR2 size, int nHP, float fBulletMax, int nMoney, int nScore, float fBulletSpeed, int nBulletType);	//�쐬
private:
	D3DXVECTOR3 Move();						//�ړ�
	D3DXVECTOR3 SlowMove();					//�x���ړ�
	void CollisionBullet(D3DXVECTOR3 pos);	//�e�Ƃ̓����蔻��
	bool CollisionBomb(D3DXVECTOR3 pos);	//���e�Ƃ̓����蔻��
	void Shot(D3DXVECTOR3 pos);				//����

	CShadow *m_pShadow;		//�e
	float m_fBullet;		//�e���܂ł̃J�E���g
	float m_fBulletMax;		//�����܂ł̃J�E���g
	int m_nHP;				//�̗�
	int m_nDamageTime;		//�_���[�W��H����Ă���̎���
	float m_fSpeed;			//�ړ����x
	float m_fRot;			//�����Ă����
	int m_nType;			//�G�̎��
	bool m_bSlow;			//�x����
	int m_nMoney;			//��
	int m_nScore;			//�X�R�A
	float m_fBulletSpeed;	//�e��
	int m_nBulletType;		//������
};
#endif