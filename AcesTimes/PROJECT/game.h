//=============================================================================
//�Q�[���Ǘ�[Game.h]
// Author : �O��q��
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"
#include "scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************

class CGame : public CScene
{
	//�e�G���G�̎�ނ��Ƃ̃X�y�b�N
	typedef struct
	{
		int nTex;			//�e�N�X�`���̔ԍ�
		int nShadowTex;		//�e�e�N�X�`���̔ԍ�
		D3DXVECTOR2 size;	//�傫��
		int nHP;			//�̗�
		int nScore;			//�X�R�A
		int nMoney;			//��
	} TypeSpec;

	//�e�G���G�̃X�y�b�N
	typedef struct
	{
		int nType;
		D3DXVECTOR3 pos;	//�o���ʒu
		float fRotY;		//�����Ă����
		float fInterval;	//�ŏ����܂ł̎���
		float fSpeed;		//����
		float fBulletMax;	//2���ڈȍ~���܂ł̎���
		int nTime;			//�o�Ă��鎞��
		int nBulletType;	//�e�̌�����
		float fBulletSpeed;	//�e��
	} EnemySpec;

	//�{�X�̃X�y�b�N
	typedef struct
	{
		int nTex;			//�e�N�X�`���̔ԍ�
		int nShadowTex;		//�e�e�N�X�`���̔ԍ�
		D3DXVECTOR3 pos;	//�o���ʒu
		D3DXVECTOR2 size;	//�傫��
		int nHP;			//�̗�
		float fInterval;	//�ŏ����܂ł̎���
		float fBulletMax;	//2���ڈȍ~���܂ł̎���
		int nScore;			//�X�R�A
		int nMoney;			//��
		int nTime;			//�o�Ă��鎞��
		bool bParts;		//�p�[�c������
		int nBGMType;
	} BossSpec;

public:
	CGame(PRIORITY Priority);
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();					//�I��
	void Update();					//�X�V
	void Draw();					//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }	//���

	//�g��Ȃ���
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR2 GetSize() { return D3DXVECTOR2(0.0f, 0.0f); }
	void Damage(int, D3DXVECTOR3) { ; }
	void Damage(int) { ; }
	float GetSizeRot() { return 0.0f; }
	int Damage() { return 0; }
	int GetHP() { return 0; }
	int GetMaxHP() { return 0; }
	bool GetEnemy() { return false; }
	void AddScore(int) { ; }
	//�g��Ȃ���

	static CGame *Create();	//�쐬

private:
	void Load();			//�t�@�C���ǂݍ���
	
	TypeSpec m_Type[6];		//�G���̎��
	EnemySpec m_Enemy[64];	//�G
	BossSpec m_Boss;		//�{�X
	int m_nBgTex;			//�w�i�e�N�X�`���̎��
	int m_nTime;			//����
	int m_nCntEnemy;		//���Ԗڂ̓G���Q�Ƃ��邩
	bool m_bBoss;			//�{�X���o��������
};

#endif // _GAME_H_
