//--------------------------
//Author:�O��q��
//�o���A�̏���(barrier.h)
//--------------------------
#ifndef _BARRIER_H_
#define _BARRIER_H_
#include "main.h"

//�}�N����`
#define BARRIER_WIDTH (180)  //�|���S���̕�
#define BARRIER_HEIGHT (210) //�|���S���̍���
#define MAX_BARRIER (2)

typedef enum
{
	BARRIERSTATE_NORMAL = 0,
	BARRIERSTATE_DAMAGE,
	BARRIERSTATE_NODAMAGE,
	BARRIERSTATE_MAX
} BARRIERSTATE;

//�o���A�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	BARRIERSTATE state;
	int ntype;
	int nLife;       //�ϋv�l
	bool bBlight;    //�����x�𑝂₷�����炷��
	int nClear;      //�o���A�̓����x
	int nDClear;     //�_���[�W�H��������̓�������
	float fBig;      //�g��������̖c���
	int nDTime;     //�_���[�W��H����Ă���̎���
	bool bUse;       //�g�p�����ۂ�
} Barrier;
//�v���g�^�C�v�錾
void InitBarrier(void);
void UninitBarrier(void);
void UpdateBarrier(void);
void DrawBarrier(void);
void SetBarrier(D3DXVECTOR3 pos,int nLife, int ntype);
void HitBarrier(int nDamage, int nCntBarrier);
Barrier *GetBarrier(void);
void ResetBarrier(void);
#endif _BARRIER_H_