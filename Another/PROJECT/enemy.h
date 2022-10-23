//=============================================================================
//
// �G���� [enemy.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene3d.h"
#include "model.h"

class CShadow;

class CEnemy : public CScene3D
{
	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_RUN,
		MOTIONTYPE_ACTION,
		MOTIONTYPE_DAMAGEBACK,
		MOTIONTYPE_DAMAGEFRONT,
		MOTIONTYPE_REFLECT,
		MOTIONTYPE_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MAX_MOTION
	} MOTIONTYPE;

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

	//�����蔻��̍\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
		int nIdxModelParent; //�e���f���̃C���f�b�N�X
		float fRadius; //�����蔻��̑傫���̔��a
	} Collision;

	//�_���[�W�֘A�̍\����
	typedef struct
	{
		int nDamageTime; //�q�b�g�Ԋu
		int nStartTime; //�����蔻�肪�������鎞��
		int nFinishTime; //�����蔻�肪�����鎞��
		int nDamage; //�_���[�W��
		float fHClash; //���������̐�����΂���
		float fVClash; //���������̐�����΂���
	} Damage;

	//�O�Ղ̍\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�O�Ղ̐�[�̈ʒu
		D3DXVECTOR3 TipposOld; //�O�Ղ̐�[�̑O��ʒu
		D3DXVECTOR3 posOld; //�O�Ղ̍����̑O��ʒu
		D3DXMATRIX TipmtxWorld;
		int nTime; //������܂ł̎���
		int nStartTime; //�������鎞��
		int nFinishTime; //�I���̎���
		int nIdxParent;
		float fDis; //�����鑬��
		D3DXCOLOR col1;	//�F��[
		D3DXCOLOR col2; //�F���{
	} Orbit;

	//�X�e�[�^�X�̍\����
	typedef struct
	{
		int nNumModel;
		int nHP;
		int nMaxHP;
		float fMove;
		float fGravity;
		float fJump;
		float fHeight;
		float fRadius;
	} Status;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;	//���[�v���邩�ǂ���
		bool bGravity;
		int nNumKey;	//�L�[�̑���
		Collision Collision[8];
		int nNumCol;	//�����蔻��̋��̐�
		Damage Damage[8];
		int nNumDmg;
		Orbit Orbit[4];	//�O��
		int nNumOrbit;
		int nNonOpe; //����s�\����
		KEY_INFO aKeyInfo[16];	//�L�[��� []���̓L�[�̍ő吔
	} MOTION_INFO;

	//�R�s�[�������
	typedef struct
	{
		MOTION_INFO amotionInfo[MAX_MOTION];
		Status status;
		CModel *apModel[32];
	} Copies;

public:
	CEnemy(PRIORITY Priority);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_ENEMY; }
	float GetRadius() { return m_Status.fRadius; }
	float GetHeight() { return m_Status.fHeight; }
	/*COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return m_VtxMax; }
	D3DXVECTOR3 GetVtxMin() { return m_VtxMin; }*/
	void Damage(int nDamage, D3DXVECTOR3 clash);
	bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, float fHeight);
	int Damage() { return m_MotionInfo.Damage[m_nDmgNumNow].nDamage; }
	float HClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fHClash; }
	float VClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fVClash; }
	void SetParticle();
	bool GetAttack() { return m_bAttackMove; }
	void Reflect();
	int GetHP() { return m_Status.nHP; }
	int GetMaxHP() { return m_Status.nMaxHP; }
	D3DXMATRIX GetMatrix(int nPart) { return m_pModel[nPart]->GetMatrix(); }

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static void Load(const char *aFileName);
	static void UnLoad();
	static int GetEnemies() { return m_nEnemies; }

private:
	void Move(float fRotY);
	void MotionMove(float fMove, float fHeight);
	void Stop();
	void UnderSearch(D3DXVECTOR3 pos);
	void CollisionPos(int nCntCol);
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);
	void CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);
	bool CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);
	void CollisionEnemy(D3DXVECTOR3 *pPos);
	void Motion();
	void MotionChange(MOTIONTYPE motionType);
	void EnemyDamage(D3DXVECTOR3 pos, float fRadius, float fHeight);
	void EnemyAI();
	bool EnemyAttack();
	void AttackAI(D3DXVECTOR3 pos);
	D3DXVECTOR3 SearchPlayer(void);
	void DataCopy();

	D3DXVECTOR3 m_PosOld;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_motionMove;
	D3DXVECTOR3 m_rotDesh;
	Status m_Status;
	bool m_bJump;
	bool m_bLandObject;
	MOTIONTYPE m_motionType;
	int m_nCntMotion;
	MOTION_INFO m_aMotionInfo[MAX_MOTION];
	MOTION_INFO m_MotionInfo;
	int m_nNeutralTime;
	KEY m_aKeyDiff[32];
	int m_nKey;
	int m_nCntThinkTime;
	int m_nCntMoveTime;
	CModel *m_pModel[32];	//���f���i�p�[�c�j
	CShadow *m_pShadow;
	bool m_bLanding;	//���n
	bool m_bAttackMove;
	bool m_bAttack;
	bool m_bHit;
	int m_nDmgNumNow;
	int m_nTotalTime;
	int m_nCntCol;
	int m_nCntDamage;

	static Copies m_Copies;
	static int m_nEnemies;
};
#endif