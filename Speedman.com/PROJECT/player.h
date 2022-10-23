//=============================================================================
//
// �V�[������ [player.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene3d.h"

class CKeyboard;
class CGamePad;
class CMouse;
class CModel;
class CCamera;
class CShadow;

class CPlayer : public CScene3D
{
	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_RUN,
		MOTIONTYPE_JUMP,
		MOTIONTYPE_LANDING,
		MOTIONTYPE_ZIPNUETRAL,
		MOTIONTYPE_ZIPMOVE,
		MOTIONTYPE_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MOTIONTYPE_ZIPRETURN,
		MAX_MOTION
	} MOTIONTYPE;

	//�L�[�̍\����
	typedef struct
	{
		float fPosX; //�ʒuX
		float fPosY; //�ʒuY
		float fPosZ; //�ʒuZ
		float fRotX; //����X
		float fRotY; //����Y
		float fRotZ; //����Z
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame; //�t���[��
		KEY aKey[32]; //�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
	} KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop; //���[�v���邩�ǂ���
		int nNumKey; //�L�[�̑���
		int nNonOpe;
		KEY_INFO aKeyInfo[16]; //�L�[��� []���̓L�[�̍ő吔
	} MOTION_INFO;

public:
	CPlayer(int nPriority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);
	void Uninit();
	void Update();
	void Draw();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);
	static int GetControlNum() { return m_nControl; }
	static void SetLife(int Life) { m_nLife = Life; }
	static int GetLife() { return m_nLife; }

private:
	void Load(const char *aFileName);
	void Move(float fRotY);
	void SlackMove(float fRotY);
	void Stop();
	void Goal(D3DXVECTOR3 PlayerPos);
	void UnderSearch(D3DXVECTOR3 pos);
	void Trampoline(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);
	bool Slackline(D3DXVECTOR3 *pPos);
	bool Land(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);
	bool CatchSlackline(D3DXVECTOR3 *pPos);
	D3DXVECTOR3 SearchSlackline(int nNumber);
	void CameraWarp(D3DXVECTOR3 pos);
	void Motion();
	void MotionChange(MOTIONTYPE motionType);

	D3DXVECTOR3 m_PosOld;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rotDesh;
	D3DXVECTOR3 m_RestartPos;
	float m_fRot;
	float m_fMove;
	float m_fGravity;
	float m_fJump;
	float m_fHeight;
	bool m_bJump;
	bool m_bSlack;
	bool m_bSlackMove;
	bool m_bLandObject;
	int m_nNumModel;
	MOTIONTYPE m_motionType;
	int m_nCntMotion;
	MOTION_INFO m_aMotionInfo[MAX_MOTION];
	MOTION_INFO m_MotionInfo;
	int m_nNeutralTime;
	KEY m_aKeyDiff[32];
	int m_nKey;
	CModel *m_pModel[32]; //���f���i�p�[�c�j
	CKeyboard *m_pKeyboard;
	CGamePad *m_pGamePad;
	CMouse *m_pMouse;
	CCamera *m_pCamera;
	CShadow *m_pShadow;

	bool m_bLanding;		//���n
	static int m_nControl;	//��������ύX�p
	static int m_nLife;		//�̗�
};
#endif