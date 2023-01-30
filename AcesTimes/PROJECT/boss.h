//=============================================================================
//
// �{�X���� [boss.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "scene2d.h"

class CBossParts;
class CShadow;
class CBoss : public CScene2D
{
public:
	CBoss(PRIORITY Priority = PRIORITY_CHARA);
	~CBoss();
	HRESULT Init(D3DXVECTOR3 pos, float fInterval, D3DXVECTOR2 size, int nShadowTex, int nHP, float fBulletMax, int nMoney, int nScore, bool bParts, int nBGMType);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_ENEMY; }	//���
	void Damage(int nDamage);	//�_���[�W����

	static CBoss *Create(D3DXVECTOR3 pos, int nTexType, int nShadowTex, float fInterval, D3DXVECTOR2 size, int nHP, float fBulletMax, int nMoney, int nScore, bool bParts, int nBGMType);	//�쐬

private:
	D3DXVECTOR3 Move();									//�ړ�
	D3DXVECTOR3 SlowMove();								//�x���ړ�
	void CollisionBullet(D3DXVECTOR3 pos);				//�e�Ƃ̓����蔻��
	bool CollisionBomb(D3DXVECTOR3 pos);				//���e�Ƃ̓����蔻��
	void Shot(D3DXVECTOR3 pos);							//����
	void PartsShot(D3DXVECTOR3 pos, int nCntBullet);	//�p�[�c������

	CShadow *m_pShadow;				//�e
	float m_fBullet[7];				//����
	float m_fBulletMax;				//�����܂ł̃C���^�[�o��
	int m_nHP;						//�̗�
	int m_nDamageTime;				//�_���[�W��H����Ă���̎���
	int m_nType;					//�G�̎��
	bool m_bSlow;					//���e�ɓ������Ă��邩
	int m_nMoney;					//��
	int m_nScore;					//�X�R�A
	bool m_bParts;					//�p�[�c������
	bool m_bMove[2];				//�㉺���E�̈ړ�
	int m_nCntStart;				//�o�����Ă���̎���
	int m_nBullet;					//�A���ŉ��񌂂�
	bool m_bDeath;					//������
	int m_nCntDeath;				//����Ă���̃J�E���g
	CBossParts *m_pBossParts[8];	//�{�X�̃p�[�c
};
#endif