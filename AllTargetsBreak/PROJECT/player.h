//--------------------------
//Author:�O��q��
//���@�̏���(player.h)
//--------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
//�}�N����`
#define PLAYER_WIDTH (40)  //�|���S���̕�
#define PLAYER_HEIGHT (60) //�|���S���̍���

//���@�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;    //���݈ʒu
	D3DXVECTOR3 posOld; //�O��ʒu
	D3DXVECTOR3 move;   //�ړ���
	D3DXVECTOR3 Blockmove;
	int nCounterAnim;   //�A�j���[�V�����J�E���^
	int nPatternAnim;   //�A�j���[�V�����p�^�[��
	int nknife;
	int nStep;
	float fIce;
	float fLeft;        //���ɓ����Ă邩
	bool bJump;         //�W�����v���\��
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void ResetPlayer(void);
void IcePlayer(bool bIce);
#endif _PLAYER_H_
