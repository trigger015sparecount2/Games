//--------------------------
//Author:�O��q��
//���@�̏���(aircraft.h)
//--------------------------
#ifndef _AIRCRAFT_H_
#define _AIRCRAFT_H_
#include "main.h"

//�}�N����`
#define AIRCRAFT_WIDTH (100.0f)		//�|���S���̕�
#define AIRCRAFT_HEIGHT (130.0f)		//�|���S���̍���
#define SHADOW_AIRCRAFT_WIDTH (30.0f)	//�e�̕�
#define SHADOW_AIRCRAFT_HEIGHT (40.0f)	//�e�̍���

//���@�̏��
typedef enum
{
	AIRCRAFTSTATE_NORMAL = 0,	//�ʏ�
	AIRCRAFTSTATE_DAMAGE,		//�_���[�W�H�����
	AIRCRAFTSTATE_NODAMAGE,		//���G
	AIRCRAFTSTATE_BARRIER,		//�o���A
	AIRCRAFTSTATE_MAX
} AIRCRAFTSTATE;

//���@�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 normalmove;	//�ړ���
	AIRCRAFTSTATE state;	//���@�̏��
	bool bDeath;			//���ꂽ��
	int nAType;				//�@�̂̎��
	int nSType;				//���ꕺ���̎��
	int nLife;				//�ϋv�l
	int nMaxLife;			//�ő�ϋv�l
	int nDTime;				//�_���[�W�H����Ă���̎���
	int nClear;				//�����A���̉��̎���
	int nLag;				//�������l�@�̓����̃��O
	int nReload;			//���ꕺ���̃����[�h����
	int nSpecial;			//���ꕺ���c�e��
	int nReSpecial;			//��蒼�����̓��ꕺ���c�e��
} Aircraft;

//�v���g�^�C�v�錾
void InitAircraft(void);		//������
void UninitAircraft(void);		//�I��
void UpdateAircraft(void);		//�X�V
void DrawAircraft(void);		//�`��
void SetAircraft(void);			//�ݒ�
Aircraft *GetAircraft(void);	//�|�C���^�擾
void SetTypeAircraft(int nAType, int nSType);	//��ގ擾
void HitAircraft(void);			//�_���[�W����
void ResetAircraft(void);		//���Z�b�g
#endif _AIRCRAFT_H_
