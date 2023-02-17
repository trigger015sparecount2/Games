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
//class CGamePad;
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
		//MOTIONTYPE_AIRNUETRAL,
		MOTIONTYPE_RUN,
		MOTIONTYPE_CHARGE,
		MOTIONTYPE_FRONTJUMP,
		MOTIONTYPE_BACKJUMP,
		MOTIONTYPE_LANDING,
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
		int nFrame;		//�t���[��
		int nSound;		//���̉����邩
		float fMove;	//���̃L�[�̐����ړ���
		float fHeight;	//���̃L�[�̐����ړ���
		KEY aKey[32];	//�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
	} KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;		//���[�v���邩�ǂ���
		bool bGravity;	//�d�͂�������
		int nNumKey;	//�L�[�̑���
		int nNonOpe;	//����s�\����
		KEY_INFO aKeyInfo[16];	//�L�[��� []���̓L�[�̍ő吔
	} MOTION_INFO;

public:
	CPlayer(PRIORITY Priority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }									//���
	float GetRadius() { return m_fRadius; }												//���a
	float GetHeight() { return m_fHeight; }												//�g��
	D3DXMATRIX GetMatrix(int nPart) { return m_pModel[nPart]->GetMatrix(); }			//�p�[�c�̃}�g���b�N�X
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//�쐬

private:
	void Load(const char *aFileName);	//���f���ȂǓǂݍ���
	bool Move(float fRotY);				//�ړ�
	bool Stop();						//��~
	void Jump();						//�W�����v
	void GaugeFadeIn();					//�Q�[�W���t�F�[�h�C��������
	void GaugeFadeOut();				//�Q�[�W���t�F�[�h�A�E�g������
	void MouseSelect();					//�}�E�X�ɂ��I��
	void JumpCharge();					//�W�����v�̃`���[�W�֘A
	void JumpFirst();					//�`���[�W�J�n
	void JumpCharging();				//�`���[�W��
	void MouseMoveX();					//�}�E�X���ړ�
	void Gravity();						//�d��
	void RunFirst();					//����n��
	void RunStop();						//����̎~�߂�
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);					//�I�u�W�F�N�g�Ƃ̓����蔻��
	void CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);						//���ʂƂ̓����蔻��
	bool CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);		//���Ƃ̓����蔻��
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);		//�ǂƂ̓����蔻��
	bool Collision(D3DXVECTOR3 aPoint[4], D3DXVECTOR3 Point, D3DXVECTOR3 PointOld);	//�_�Ǝl�p�`�Ƃ̓����蔻��
	bool CollisionBlock(D3DXVECTOR3 aPoint[4], D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, bool *bLand, D3DXVECTOR3 *Nextpos);	//�u���b�N�̓����蔻��
	bool CollisionCamera(D3DXVECTOR3 *pPos, CScene *pScene);		//�J�����]�[���Ƃ̓����蔻��
	void ShadowObject(D3DXVECTOR3 aPoint[4], D3DXVECTOR3 *pPos);	//��Q���̑΂���e�̕`��
	void Motion();								//���[�V����
	void MotionChange(MOTIONTYPE motionType);	//���[�V�����؂�ւ�
	void PauseChange(int nAdd);					//�|�[�Y�I�����؂�ւ�
	void PauseSelect();							//�|�[�Y����
	void EndChange(int nAdd);					//�I���I�����؂�ւ�
	void EndSelect();							//�I������

	D3DXVECTOR3 m_PosOld;			//�ߋ��ʒu
	D3DXVECTOR3 m_move;				//�ړ�
	D3DXVECTOR3 m_rotDesh;			//�ړI����
	D3DXVECTOR3 m_RestartPos;		//���X�^�[�g�ꏊ
	float m_fMove;					//�ړ�
	float m_fChargeJump;			//�`���[�W�̃W�����v��
	float m_fGravity;				//�d��
	float m_fJump;					//�W�����v��
	float m_fHeight;				//�g��
	float m_fRadius;				//���a
	float m_fJumpMoveX;				//�`���[�W�̃W�����v��
	float m_fGaugeFade;				//�Q�[�W�̓����x
	bool m_bCharge;					//�`���[�W����
	bool m_bLanding;				//���n���Ă邩
	bool m_bLandObject;				//�I�u�W�F�N�g�ɒ��n
	bool m_bLandField;				//�n�ʂɒ��n
	bool m_bChargePlus;				//�`���[�W���v���X���}�C�i�X��
	bool m_bGaugeFade;				//�Q�[�W���邢��������
	int m_nFastMotion;				//���t���[�����[�V������������
	int m_nNumModel;				//���f����
	int m_nTotalTime;				//���[�V�����̍��v�t���[��
	MOTIONTYPE m_motionType;		//���[�V�����̎��
	MOTIONTYPE m_motionTypeOld;		//�ߋ��̃��[�V�����̎��
	int m_nCntMotion;				//���݂̃��[�V������
	MOTION_INFO m_aMotionInfo[32];	//���[�V�����̏��
	MOTION_INFO m_MotionInfo;		//���݃��[�V�����̏��
	int m_nNeutralTime;				//�j���[�g�����̎���
	KEY m_aKeyDiff[32];				//�p�[�c�̈Ⴂ
	int m_nKey;						//���݃L�[
	CModel *m_pModel[32];			//���f���i�p�[�c�j
	CKeyboard *m_pKeyboard;			//�L�[�{�[�h
	//CGamePad *m_pGamePad;
	CMouse *m_pMouse;				//�}�E�X
	CCamera *m_pCamera;				//�J����
	CShadow *m_pShadow;				//�e
	int m_nRunStop;					//����̎~�߂��t���[��
	D3DXVECTOR3 m_MotionMove;		//���[�V�����̓���
	bool m_bGameClear;				//�Q�[���N���A������
	bool m_bEndSelect;				//�I���̑I����
	int m_nPauseSelect;				//�|�[�Y�̑I��ԍ�
	float m_fShadowPosY;			//�e�̍���
	int m_nCntJump;					//�؋󎞊�
	D3DXVECTOR3 m_ShadowRot;		//�e�̌���
	CPauseUI *m_pPauseUI[3];		//�|�[�YUI
	CUI *m_pBlackGauge[3];			//�Q�[�W�ޔw�i
	CUI *m_pGauge;					//�Q�[�W
	CUI *m_pBlockGauge[20];			//���E�̈ړ��ʂ̃Q�[�W
	D3DXVECTOR2 m_aCamera[2];		//�J�����ړ���
};
#endif