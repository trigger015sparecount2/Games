//--------------------------
//Author:�O��q��
//�u���b�N�̏���(block.h)
//--------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"

//�}�N����`
#define MAX_BLOCK (64)

//�u���b�N�̎��
typedef enum
{
	BLOCK_NORMAL = 0,
	BLOCK_DOWN,
	BLOCK_UP,
	BLOCK_ICE,
	BLOCK_CARRY,
	BLOCK_WARP,
	BLOCK_MAX
} BLOCKTYPE;

//�u���b�N�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 Startpos; //�����ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 Maxmove; //�ǂ��܂ňړ����邩
	BLOCKTYPE BlockType; //�u���b�N�̎��
	float fWidth;     //��
	float fHeight;    //����
	int nTime; //�ړ�����
	int nMaxTime; //�ړ����ԍő�l
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Block;

//�v���g�^�C�v�錾
HRESULT InitBlock(void);	//������
void UninitBlock(void);		//�I��
void UpdateBlock(void);		//�X�V
void DrawBlock(void);		//�`��
void ResetBlock(void);		//�S������
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXVECTOR3 Maxmove, int nMaxTime, BLOCKTYPE BlockType);	//�u���b�N�ݒ�
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, D3DXVECTOR3 *pBlockMove, int nType);	//�u���b�N�Ƃ̓����蔻��
D3DXVECTOR3 WarpBlock(int nMaxTime);	//���[�v���������
#endif _PLAYER_H_
