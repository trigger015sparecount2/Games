//--------------------------
//Author:�O��q��
//���@�̏���(aircraft.h)
//--------------------------
#ifndef _AIRCRAFT_H_
#define _AIRCRAFT_H_
#include "main.h"
//�}�N����`
#define AIRCRAFT_WIDTH (100)  //�|���S���̕�
#define AIRCRAFT_HEIGHT (130) //�|���S���̍���
#define SHADOW_AIRCRAFT_HEIGHT (40) //�e�̍���
#define SHADOW_AIRCRAFT_WIDTH (30) //�e�̉���

typedef enum
{
	AIRCRAFTSTATE_NORMAL = 0,
	AIRCRAFTSTATE_DAMAGE,
	AIRCRAFTSTATE_NODAMAGE,
	AIRCRAFTSTATE_BARRIER,
	AIRCRAFTSTATE_MAX
} AIRCRAFTSTATE;

//���@�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;        //�ʒu
	D3DXVECTOR3 move;       //�ړ���
	D3DXVECTOR3 normalmove; //�ړ���
	AIRCRAFTSTATE state;    //���@�̏��
	bool bDeath;            //���ꂽ��
	int nAType;             //�@�̂̎��
	int nSType;             //���ꕺ���̎��
	int nLife;              //�ϋv�l
	int nMaxLife;           //�ő�ϋv�l
	int nDTime;             //�_���[�W�H����Ă���̎���
	int nClear;             //�����A���̉��̎���
	int nLag;               //�������l�@�̓����̃��O
	int nReload;            //���ꕺ���̃����[�h����
	int nSpecial;           //���ꕺ���c�e��
	int nReSpecial;         //��蒼�����̓��ꕺ���c�e��
} Aircraft;

//�v���g�^�C�v�錾
void InitAircraft(void);
void UninitAircraft(void);
void UpdateAircraft(void);
void DrawAircraft(void);
void SetAircraft(void);
Aircraft *GetAircraft(void);
void SetTypeAircraft(int nAType, int nSType);
void HitAircraft(void);
void ResetAircraft(void);
#endif _AIRCRAFT_H_
