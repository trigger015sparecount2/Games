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
#include "model.h"

class CKeyboard;
class CGamePad;
class CMouse;
class CCamera;
class CShadow;
class COrbit;
class CRockon;
class CUI;
class CPauseUI;

class CPlayer : public CScene3D
{
	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_AIRNEUTRAL,
		MOTIONTYPE_RUN,
		MOTIONTYPE_JUMP,
		MOTIONTYPE_SLAP,
		MOTIONTYPE_RUSH,
		MOTIONTYPE_ROUND,
		MOTIONTYPE_ARIAL,
		MOTIONTYPE_DIVE,
		MOTIONTYPE_FINISH,
		MOTIONTYPE_LANDING,
		MOTIONTYPE_GROUNDDODGE,
		MOTIONTYPE_AIRDODGE,
		MOTIONTYPE_GUARD,
		MOTIONTYPE_COUNTER,
		MOTIONTYPE_DAMAGEFRONT,
		MOTIONTYPE_DAMAGEBACK,
		MOTIONTYPE_DEATH,
		MOTIONTYPE_CLEAR,
		MOTIONTYPE_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MOTIONTYPE_AIRRETURN, //�󒆃j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MAX_MOTION
	} MOTIONTYPE;

	//���[�V�����̏㉺������
	typedef enum
	{
		MOTIONUPDN_NONE = 0,
		MOTIONUPDN_UNDER,
		MOTIONUPDN_UPPER,
		MOTIONUPDN_UPDN,
		MAX_MOTIONUPDN
	} MOTIONUPDN;

	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame; //�t���[��
		float fMove; //���̃L�[�̐����ړ���
		float fHeight; //���̃L�[�̐����ړ���
		KEY aKey[32]; //�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
	} KEY_INFO;

	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
		int nIdxModelParent; //�e���f���̃C���f�b�N�X
		float fRadius; //�����蔻��̑傫���̔��a
	} Collision;

	typedef struct
	{
		int nDamageTime; //�q�b�g�Ԋu
		int nStartTime; //�����蔻�肪�������鎞��
		int nFinishTime; //�����蔻�肪�����鎞��
		int nDamage; //�_���[�W��
		float fHClash; //���������̐�����΂���
		float fVClash; //���������̐�����΂���
	} Damage;

	typedef struct
	{
		D3DXVECTOR3 pos; //�O�Ղ̐�[�̈ʒu
		D3DXMATRIX TipmtxWorld;
		float fDis; //�����鑬��
		D3DXCOLOR col1;	//�F��[
		D3DXCOLOR col2; //�F���{
		int nStartTime; //�������鎞��
		int nFinishTime; //�I���̎���
		int nIdxParent;
	} Orbit;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;	//���[�v���邩�ǂ���
		bool bHoming; //�ːi�͂Ȃǂɒǔ��������邩(�r���Ŏ~�܂邩)
		bool bGravity; //�d�͂�������
		int nNumKey;	//�L�[�̑���
		Collision Collision[8];
		int nNumCol;	//�����蔻��̋��̐�
		int nComboTime;	//�R���{�P�\����
		Damage Damage[8];
		int nNumDmg;
		Orbit Orbit[4];	//�O��
		int nNumOrbit;
		int nNonOpe; //����s�\����
		KEY_INFO aKeyInfo[16];	//�L�[��� []���̓L�[�̍ő吔
		int nNoDmg;
		MOTIONUPDN MotionUpdn;
	} MOTION_INFO;

public:
	CPlayer(PRIORITY Priority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }
	float GetRadius() { return m_fRadius; }
	float GetHeight() { return m_fHeight; }
	//COLLISION GetCollision() { return COLLISION_SPHERE; }
	//D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	//D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void Damage(int nDamage, D3DXVECTOR3 clash);
	bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, float fHeight);
	bool SetEnemy(CScene *pEnemy);
	int Damage() { return m_MotionInfo.Damage[m_nDmgNumNow].nDamage; }
	float HClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fHClash; }
	float VClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fVClash; }
	D3DXMATRIX GetMatrix(int nPart) { return m_pModel[nPart]->GetMatrix(); }
	void SetParticle();
	int GetHP() { return m_nHP; }
	int GetMaxHP() { return m_nMaxHP; }
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);

private:
	void Load(const char *aFileName);
	bool Move(float fRotY);
	void MotionMove(float fRotY, float fMove);
	void MotionStopMove();
	void MotionHeight(float fHeight);
	void MotionStopHeight();
	bool Stop();
	void Jump();
	void UnderSearch(D3DXVECTOR3 pos);
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);
	void CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);
	bool CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);
	void Motion();
	void HasteMotion();
	void MotionChange(MOTIONTYPE motionType);
	void CollisionPos(int nCntCol);
	void CollisionEnemy(D3DXVECTOR3 *pPos);
	void Orbit();
	void Rockon();
	void UnRockon();
	void ResetEnemy();
	void RockCameraMove(D3DXVECTOR3 pos);
	MOTIONTYPE RockAttack(D3DXVECTOR3 pos);
	bool AroundEnemy(D3DXVECTOR3 pos);
	void SearchRock(D3DXVECTOR3 pos);
	MOTIONTYPE NoRockAttack();
	void PlayerDamage(D3DXVECTOR3 pos, float fHeight, float fRadius);
	void PauseChange(int nAdd);
	void PauseSelect();
	void EndChange(int nAdd);
	void EndSelect();
	void GameClear();

	D3DXVECTOR3 m_PosOld;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rotDesh;
	D3DXVECTOR3 m_RestartPos;
	float m_fMove;
	float m_fGravity;
	float m_fJump;
	float m_fHeight;
	float m_fRadius;
	bool m_bJump;
	bool m_bLandObject;
	int m_nNumModel;
	int m_nTotalTime;
	MOTIONTYPE m_motionType;
	MOTIONTYPE m_motionTypeOld;
	int m_nCntMotion;
	MOTION_INFO m_aMotionInfo[32];
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
	CRockon *m_pRockon;
	CScene *m_pEnemy[16];
	COrbit *m_pOrbit[4];
	int m_nHP;
	int m_nMaxHP;
	int m_nRunStop;
	int m_nCntDamage;
	int m_nDmgNumNow;
	int m_nCombo;
	int m_nNonOpe;
	int m_nComboTime;
	int m_nCntRun;
	D3DXVECTOR3 m_MotionMove;
	bool m_bRockon;
	bool m_bLanding; //���n
	bool m_bHit;
	bool m_bAttack;
	bool m_bCounter;
	bool m_bGameClear;
	bool m_bEndSelect;
	bool m_bPinch;
	int m_nCntCol;
	int m_nCntNoDmg;
	int m_nPauseSelect;
	int m_nCntRoundChange;
	int m_nCntDeath;
	int m_nCntPinch;
	CUI *m_pCounterUI;
	CUI *m_pHPUI;
	CUI *m_pEnemyHPUI[3];
	CPauseUI *m_pPauseUI[3];
	CUI *m_pRoundUI[4];
	CUI *m_pEndUI[2];
};
#endif