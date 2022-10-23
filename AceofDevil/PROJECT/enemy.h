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

#define ENEMY_SIZE (50.0f)

class CEnemy : public CScene2D
{
public:
	CEnemy(PRIORITY Priority = PRIORITY_CHARA);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, int nType, float fRotY, int ninterval, float fSpeed);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetDamage(void);
	void Damage(int nDamage);

	static HRESULT Load(void);
	static void UnLoad(void);
	static CEnemy *Create(D3DXVECTOR3 pos, int nTexType, float fRotY, int nInterval, float fSpeed);

private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void Shot(D3DXVECTOR3 pos);

	static LPDIRECT3DTEXTURE9 m_pTexture[4];
	CScene2D *m_pShadowScene;
	int m_nBullet;
	int m_nBulletInter;
	int m_nHP; //�̗�
	int m_nDamageTime; //�_���[�W��H����Ă���̎���
	bool m_bUninit;
	bool m_bShot;
	float m_fSpeed;
	float m_fRot;
	int m_nScore;
	int m_nType;

};
#endif