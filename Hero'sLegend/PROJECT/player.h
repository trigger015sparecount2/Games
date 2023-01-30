//---------------------------
//Author:�O��q��
//���f���i�K�w�\������j(player.h)
//---------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_WALK,
	MOTIONTYPE_NORMAL,
	MOTIONTYPE_RUSH,
	MOTIONTYPE_ROUND,
	MOTIONTYPE_ARIAIL,
	MOTIONTYPE_GROUND,
	MOTIONTYPE_FINISH,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_DAMAGE,
	MOTIONTYPE_DIE,
	MOTIONTYPE_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
	MAX_MOTION
} MOTIONTYPE;

//�v���g�^�C�v�錾
HRESULT InitPlayer(void);	//������
void UninitPlayer(void);	//�I��
void UpdatePlayer(void);	//�X�V
void DrawPlayer(void);		//�`��

D3DXVECTOR3 PlayerPos(void);	//pos�擾
float PlayerRot(void);			//�����擾
float PlayerMove(int nRot);		//�ړ��擾
float PlayerRotDesh(void);		//�ړI�̕����擾
D3DXMATRIX Playermtx(void);		//�}�g���b�N�X�擾
bool TargetRockon(void);		//���b�N�I�����Ă邩
void RemovePlayerRock(void);	//���b�N�I���O��
int NumParts(void);				//�p�[�c����
bool CollisionDamage(D3DXVECTOR3 pos, float fRadius);	//�����蔻�蓖��������
float CollisionPos(int nNumber, int nRot);	//�����蔻��̏ꏊ
float PlayerLookEnemy(void);				//�G�̕�������
D3DXVECTOR3 EnemyClash(D3DXVECTOR3 pos);	//�G�𐁂���΂�
float ClashRot(D3DXVECTOR3 pos);			//������΂�����
float PlayerClashRot(D3DXVECTOR3 pos);		//�v���C���[��������Ԕ���
int DamageTime(void);			//�����蔻��̎���
int Damage(void);				//�_���[�W��
int PlayerRockEnemy(void);		//���b�N�I�����Ă�G
float PlayerPartsRot(void);		//�p�[�c�̕���
int PlayerKey(void);			//�L�[���Ԗڂ�
float PlayerDistance(D3DXVECTOR3 pos);		//�v���C���[�Ƃ̋���
float PlayerHeight(void);		//�v���C���[�̐g��
void PlayerDamageTime(int nDamageTime);		//���G���Ԑݒ�
bool PlayerDamage(D3DXVECTOR3 pos, float fRadius);	//�v���C���[�̃_���[�W����
void PlayerDamage(int nDamage, int nDamageTime, float fRoty, D3DXVECTOR3 Clash);	//�_���[�W����
int PlayerHP(void);				//�v���C���[��HP
float PlayerHPRate(void);		//�v���C���[��HP�̊���
void PlayerKillAdd(void);		//�|���������Z
int PlayerKill(void);			//�|�������擾
#endif _PLAYER_H_