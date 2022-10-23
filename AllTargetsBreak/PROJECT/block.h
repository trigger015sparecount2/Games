//--------------------------
//Author:�O��q��
//���@�̏���(block.h)
//--------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"

//�}�N����`
#define MAX_BLOCK (64)

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

//���@�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 Startpos; //�����ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 Maxmove; //�ړ��ʍő�l
	BLOCKTYPE BlockType; //�u���b�N�̎��
	float fWidth;     //��
	float fHeight;    //����
	int nTime; //�ړ�����
	int nMaxTime; //�ړ����ԍő�l
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Block;

//�v���g�^�C�v�錾
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void ResetBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXVECTOR3 Maxmove, int nMaxTime, BLOCKTYPE BlockType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, D3DXVECTOR3 *pBlockMove, int nType);
D3DXVECTOR3 WarpBlock(int nMaxTime);
#endif _PLAYER_H_
