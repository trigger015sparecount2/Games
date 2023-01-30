//--------------------------------
//Author:�O��q��
//�v���C���[�̏���(player.h)
//--------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//�}�N����`
#define PLAYER_WIDTH (40)  //�|���S���̕�
#define PLAYER_HEIGHT (60) //�|���S���̍���

//���@�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݈ʒu
	D3DXVECTOR3 posOld;		//�O��ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 Blockmove;	//�u���b�N�̈ړ���
	int nCounterAnim;		//�A�j���[�V�����J�E���^
	int nPatternAnim;		//�A�j���[�V�����p�^�[��
	int nCross;				//�藠���C���^�[�o��
	int nStep;				//�����J�E���g
	float fIce;				//�X�ɏ���Ă邩
	float fLeft;			//���ɓ����Ă邩
	bool bJump;				//�W�����v���\��
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);		//������
void UninitPlayer(void);	//�I��
void UpdatePlayer(void);	//�X�V
void DrawPlayer(void);		//�`��
Player *GetPlayer(void);	//�v���C���[�̃|�C���^�擾
void ResetPlayer(void);		//�v���C���[���Z�b�g
void IcePlayer(bool bIce);	//�X�ɏ��������
#endif _PLAYER_H_
