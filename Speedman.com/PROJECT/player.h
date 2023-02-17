//=============================================================================
//
// �v���C���[���� [player.h]
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
		float fPosX;	//�ʒuX
		float fPosY;	//�ʒuY
		float fPosZ;	//�ʒuZ
		float fRotX;	//����X
		float fRotY;	//����Y
		float fRotZ;	//����Z
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame;		//�t���[��
		KEY aKey[32];	//�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
	} KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;		//���[�v���邩�ǂ���
		int nNumKey;	//�L�[�̑���
		int nNonOpe;	//����s�\����
		KEY_INFO aKeyInfo[16]; //�L�[��� []���̓L�[�̍ő吔
	} MOTION_INFO;

public:
	CPlayer(int nPriority);
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//�쐬
	static int GetControlNum() { return m_nControl; }	//��������̎�ގ擾

	//���C�t�ݒ�
	static void SetLife(int Life) { m_nLife = Life; }
	static int GetLife() { return m_nLife; }

private:
	void Load(const char *aFileName);								//���f���ǂݍ���
	void Move(float fRotY);											//�ړ�
	void SlackMove(float fRotY);									//�X���b�N���C���ړ�
	void Stop();													//��~
	void Goal(D3DXVECTOR3 PlayerPos);								//�S�[���Ƃ̓����蔻��
	void UnderSearch(D3DXVECTOR3 pos);								//�^���ɂ��鏰����̂𒲂ׂ�
	void Trampoline(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);			//�g�����|�����Ƃ̓����蔻��
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);	//��Q���Ƃ̓����蔻��
	bool Slackline(D3DXVECTOR3 *pPos);								//���[�v�͂߂邩
	bool Land(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);				//���n����
	bool CatchSlackline(D3DXVECTOR3 *pPos);							//���[�v�͂�
	D3DXVECTOR3 SearchSlackline(int nNumber);						//�Ή�����X���b�N���C������
	void CameraWarp(D3DXVECTOR3 pos);								//�J�����p�l���̓����蔻��
	void Motion();													//���[�V����
	void MotionChange(MOTIONTYPE motionType);						//���[�V�����؂�ւ�

	D3DXVECTOR3 m_PosOld;		//�ߋ��ʒu
	D3DXVECTOR3 m_move;			//�ړ��x�N�g��
	D3DXVECTOR3 m_rotDesh;		//�ړI�̕���
	D3DXVECTOR3 m_RestartPos;	//���X�^�[�g����ʒu
	float m_fRot;				//���[�v�͂񂾍ۂ̕���
	float m_fMove;				//�ړ���
	float m_fGravity;			//�d��
	float m_fJump;				//�W�����v��
	float m_fHeight;			//�g��
	bool m_bJump;				//���n���Ă邩
	bool m_bSlack;				//�����߂��ɃX���b�N���C���̃|�[�������邩
	bool m_bSlackMove;			//���[�v�͂�ł邩
	bool m_bLandObject;			//�I�u�W�F�N�g�ɏ���Ă邩
	int m_nNumModel;			//���f�����g���Ă邩
	MOTIONTYPE m_motionType;	//���[�V�����̎��
	int m_nCntMotion;			//���[�V�����̃t���[��
	MOTION_INFO m_aMotionInfo[MAX_MOTION];	//�S���[�V�����̏��
	MOTION_INFO m_MotionInfo;	//���̃��[�V�����̏��
	int m_nNeutralTime;			//���삵�ĂȂ�����
	KEY m_aKeyDiff[32];			//�p�[�c���Ƃ̃L�[�̉��Z��
	int m_nKey;					//���̃L�[��

	CModel *m_pModel[32];		//���f���i�p�[�c�j
	CKeyboard *m_pKeyboard;		//�L�[�{�[�h�̃|�C���^
	CGamePad *m_pGamePad;		//�Q�[���p�b�h�̃|�C���^
	CMouse *m_pMouse;			//�}�E�X�̃|�C���^
	CCamera *m_pCamera;			//�J�����̃|�C���^
	CShadow *m_pShadow;			//�e

	bool m_bLanding;			//���n
	static int m_nControl;		//��������ύX�p
	static int m_nLife;			//�̗�
};
#endif