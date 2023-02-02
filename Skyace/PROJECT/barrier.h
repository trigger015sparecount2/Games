//--------------------------
//Author:�O��q��
//�o���A�̏���(barrier.h)
//--------------------------
#ifndef _BARRIER_H_
#define _BARRIER_H_
#include "main.h"

//�}�N����`
#define BARRIER_WIDTH (180.0f)  //�|���S���̕�
#define BARRIER_HEIGHT (210.0f) //�|���S���̍���
#define MAX_BARRIER (2)

//�o���A�̏��
typedef enum
{
	BARRIERSTATE_NORMAL = 0,	//�ʏ�
	BARRIERSTATE_DAMAGE,		//�_���[�W�H�����
	BARRIERSTATE_NODAMAGE,		//���G
	BARRIERSTATE_MAX
} BARRIERSTATE;

//�o���A�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	BARRIERSTATE state;	//���
	int ntype;			//�v���C���[�̂��̂��A�G��
	int nLife;			//�ϋv�l
	bool bBlight;		//�����x�𑝂₷�����炷��
	int nClear;			//�o���A�̓����x
	int nDClear;		//�_���[�W�H��������̓�������
	float fBig;			//�g��������̖c���
	int nDTime;			//�_���[�W��H����Ă���̎���
	bool bUse;			//�g�p�����ۂ�
} Barrier;

//�v���g�^�C�v�錾
void InitBarrier(void);		//������
void UninitBarrier(void);	//�I��
void UpdateBarrier(void);	//�X�V
void DrawBarrier(void);		//�`��
void SetBarrier(D3DXVECTOR3 pos, int nLife, int ntype);	//�ݒ�
void HitBarrier(int nDamage, int nCntBarrier);			//��������
Barrier *GetBarrier(void);	//�|�C���^�擾
void ResetBarrier(void);	//���Z�b�g
#endif _BARRIER_H_