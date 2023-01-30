//=============================================================================
//
// �{�X�p�[�c���� [bossparts.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BOSSPARTS_H_
#define _BOSSPARTS_H_

#include "main.h"
#include "scene2d.h"

class CBossParts : public CScene2D
{
public:
	CBossParts(PRIORITY Priority = PRIORITY_CHARA);
	~CBossParts();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nFireTex, int nHP, int nMoney, int nScore);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_ENEMY; }	//���
	void Damage(int nDamage);							//�_���[�W����
	void SetDestroy(bool bDeath) { m_bDeath = bDeath; }	//���ꂽ���ݒ�
	bool GetDestroy() { return m_bDeath; }				//���Ă��邩�Ԃ�

	static CBossParts *Create(D3DXVECTOR3 pos, int nTexType, int nFireTex, D3DXVECTOR2 size, int nHP, int nMoney, int nScore);	//�쐬

private:
	void CollisionBullet(D3DXVECTOR3 pos);	//�e�Ƃ̓����蔻��

	CScene2D *m_pFire;	//�o�b�N�t�@�C�A
	int m_nHP;			//�̗�
	int m_nDamageTime;	//�_���[�W��H����Ă���̎���
	int m_nMoney;		//��
	int m_nScore;		//�X�R�A
	int m_nCntFire;		//�o�b�N�t�@�C�A�̑召�J�E���g
	bool m_bFire;		//�o�b�N�t�@�C�A
	bool m_bDeath;		//���ꂽ��
	int m_nCntDeath;	//���ꂽ���Ƃ̃J�E���g
};
#endif