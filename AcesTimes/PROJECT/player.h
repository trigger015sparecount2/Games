//=============================================================================
//
// �V�[������ [player.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2d.h"

class CKeyboard;
class CGamePad;
class CShadow;
class CUI;
class CPauseUI;
class CWarp;
class CTextUI;

class CPlayer : public CScene2D
{
public:
	//�����߂�����ۂɕK�v�ȏ��
	typedef struct
	{
		int nHP;
		D3DXVECTOR3 pos;
	} Status;

	//�V���b�g�̌�����
	typedef enum
	{
		SHOTTYPE_FRONT = 0,
		SHOTTYPE_FRONTWIDE,
		SHOTTYPE_FRONTSIDE,
		SHOTTYPE_FRONTWIDESIDE,
		SHOTTYPE_FRONTWIDEBACKSIDE,
		SHOTTYPE_ALL,
		SHOTTYPE_MAX
	} SHOTTYPE;

	CPlayer(PRIORITY Priority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nHP, float fSpeed, int nMaxSlow, int nMaxReturn, SHOTTYPE ShotType, int nShadowTex, int nHudTex);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }	//���
	void Damage(int nDamage);							//�_���[�W����
	int Damage() { return 1; }							//�_���[�W��
	int GetHP() { return m_Status.nHP; }				//�̗�
	int GetMaxHP() { return m_nMaxHP; }					//�ő�̗�
	void AddScore(int nScore);							//�X�R�A����
	
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nHP, float fSpeed, int nMaxSlow, int nMaxReturn, int nTexType, SHOTTYPE ShotType, int nShadowTex, int nHudTex);	//�쐬

private:
	void Move(float fRot);					//�ړ�
	void Stop();							//��~
	void CollisionBullet(D3DXVECTOR3 pos);	//�e�Ƃ̓����蔻��
	void CollisionUI(D3DXVECTOR3 pos);		//UI�Ƃ̓����蔻��
	void PauseChange(int nAdd);				//�|�[�Y�I�����ς���
	void PauseSelect();						//�|�[�Y�I��
	void TimeKeep(D3DXVECTOR3 pos);			//���^�[���|�C���g�ݒu
	void TimeReturn(D3DXVECTOR3 pos);		//���Ԃ̊����߂�
	D3DXVECTOR3 Return(D3DXVECTOR3 pos);	//�����߂����̈ړ�
	void Shot(D3DXVECTOR3 pos);				//����

	D3DXVECTOR3 m_PosOld;		//�O��ʒu
	D3DXVECTOR3 m_move;			//�ړ�
	D3DXVECTOR3 m_WarpMove;		//�����߂����̈ړ���
	float m_fMove;				//�ő�ړ���
	CKeyboard *m_pKeyboard;		//�L�[�{�[�h
	CGamePad *m_pGamePad;		//�Q�[���p�b�h
	CShadow *m_pShadow;			//�e
	Status m_Status;			//���݃X�e�[�^�X
	Status m_KeepStatus;		//�L�[�v���̃X�e�[�^�X
	int m_nMaxHP;				//�ő�̗�
	int m_nCntDamage;			//�_���[�W��������J�E���g
	bool m_bPinch;				//�s���`��
	bool m_bUIClear;			//�s���`����UI�̎��@�̃V���G�b�g�_��
	int m_nPauseSelect;			//�|�[�Y�̑I����
	int m_nCntPinch;			//�s���`�̓_�ł̃J�E���g
	int m_nCntShot;				//�V���b�g�J�E���g
	int m_nReturn;				//���݊����߂��l
	int m_nMaxReturn;			//�ő努���߂��l
	int m_nSlow;				//���ݔ��e�l
	int m_nMaxSlow;				//�ő唚�e�l
	int m_nScore;				//�X�R�A
	bool m_bWarp;				//�����߂��n�_�ݒu���Ă邩
	bool m_bDeath;				//������
	int m_nCntDeath;			//���ꂽ�J�E���g
	int m_nCntWarpPoint;		//���^�[���|�C���g�̃J�E���g
	bool m_bWarpNow;			//�������߂��Ă��邩
	int m_nHudTex;				//�����߂��ۂ̎c�������̃e�N�X�`��
	int m_nCntWarp;				//�����߂��J�E���g
	float m_fHUDColor;			//���@�̃V���G�b�g�̐F
	float m_fClear[3];			//�eUI�̓����x
	char m_Str[3][32];			//�e����
	SHOTTYPE m_ShotType;		//������
	CUI *m_pHUD[4];				//�E����UI
	CUI *m_pGauge[7];			//������UI
	CUI *m_pScore[3];			//�����UI
	CPauseUI *m_pPauseUI[3];	//�|�[�YUI
	CWarp *m_pWarp;				//�����߂��n�_
	CTextUI *m_pTextUI[3];		//�eUI�̃e�L�X�g
};
#endif