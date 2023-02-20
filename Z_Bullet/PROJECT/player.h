//---------------------------
//Author:�O��q��
//�v���C���[(player.h)
//---------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitPlayer(void);	//������
void UninitPlayer(void);	//�I��
void UpdatePlayer(void);	//�X�V
void DrawPlayer(void);		//�`��

D3DXVECTOR3 PlayerPos(void);		//�v���C���[�̏ꏊ
float PlayerRot(void);				//�v���C���[�̌���
float ClashRot(D3DXVECTOR3 pos);	//������ԕ���
D3DXVECTOR3 PlayerGetMove(void);	//�v���C���[�̈ړ���
float GetPlayerHeight(void);		//�v���C���[�̐g��
float GetPlayerRadius(void);		//�v���C���[�̔��a
float PlayerRotDesh(void);			//�v���C���[�̖ړI�̌���
bool TargetRockon(void);			//���b�N�I�����Ă邩
int NumParts(void);					//�p�[�c��
D3DXMATRIX CollisionPlayerPos(int nCntParts);	//�v���C���[�̓����蔻��
float PlayerLookEnemy(void);			//�v���C���[���猩���G�̕���
void ScoreAdd(int nScore);				//�X�R�A���Z
float PlayerDistance(D3DXVECTOR3 pos);	//�v���C���[�̋���
void PlayerDamage(int nDamage, int nDamageTime, D3DXVECTOR3 Clash, float fRot);	//�v���C���[���_���[�W�H�����
bool PlayerDamage(D3DXVECTOR3 pos, float fRadius);	//�v���C���[���_���[�W�H�炤��
float PlayerClashRot(D3DXVECTOR3 pos);	//�v���C���[��������ԕ���
void ResetPlayer(void);		//���Z�b�g
void AddItem(void);			//�A�C�e�����Z
int PlayerScore(void);		//�X�R�A�擾
bool GetPlayerDie(void);	//�v���C���[�����ꂽ��
#endif _PLAYER_H_