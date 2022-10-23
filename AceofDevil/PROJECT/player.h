//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2d.h"

#define MAX_TYPE (5)

class CInputKeyboard;
class CInputGamePad;
class CWater;
class CWind;

class CPlayer : public CScene2D
{
public:
	CPlayer(PRIORITY Priority = PRIORITY_CHARA);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetDamage(void);
	void Damage(int nDamage);

	static HRESULT Load(void);
	static void UnLoad(void);
	static CPlayer *Create(D3DXVECTOR3 pos);
	static void GetPrize(int nType, int nHeal);
	static bool GetGameOver(void);
	static void SetTuto(bool bTuto);

private:
	void Move(float fRot);
	void Stop(void);
	int SetBulletTime(int nType);
	void SetGauge(void);
	void Shot(D3DXVECTOR3 pos);

	CInputKeyboard *m_pInputKeyboard;
	CInputGamePad *m_pInputGamePad;
	CWater *m_pWater;
	CWind *m_pWind;
	D3DXVECTOR3 m_move; //�ړ����x
	D3DXVECTOR3 m_Maxmove;
	CScene2D *m_pShadowScene;
	int m_nBullet; //�e�����Ă���̃J�E���^
	int m_nBulletTime; //���ˊԊu
	int m_nHP; //�̗�
	int m_nDamageTime; //���G����
	int m_nDTime; //�_���[�W��H����Ă���̎���
	int m_nType;
	int m_nMagicTime; //���͂̉񕜂̊Ԋu
	int m_nSlide;
	bool m_bSlide;
	float m_fScale;
	bool m_bUse;
	static bool m_bDeath;
	static int m_aResource[MAX_TYPE];
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static bool m_bTuto;
};

#endif