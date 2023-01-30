//---------------------------
//Author:�O��q��
//�J����(camera.h)
//---------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//�J�����̍\����
typedef struct
{
	D3DXVECTOR3 posV;			//���݂̎��_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posR;			//���݂̒����_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXVECTOR3 rot;			//�J�����̌���
	D3DXVECTOR3 rotDesh;		//�ړI�̌���
	float fLength;				//����
	int nTime;					//����
	bool bRot;					//����
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
} Camera;

//�v���g�^�C�v�錾
HRESULT InitCamera(void);		//������
void UninitCamera(void);		//�I��
void UpdateCamera(void);		//�X�V
void SetCamera(void);			//�ݒ�
float CameraRot(void);			//�����擾
D3DXVECTOR3 CameraPosV(void);	//���_�擾
D3DXVECTOR3 CameraPosR(void);	//�����_�擾
float CameraDistance(void);		//�J�����̋����擾
float RockCamera(void);			//�J�����������Ă�������甽�]
D3DXMATRIX CameraMtxPro(void);	//�v���W�F�N�V�����擾
D3DXMATRIX CameraMtxView(void);	//�r���[�}�g���b�N�X�擾
float CameraRotH(void);			//���������擾
float CameraRotV(void);			//���������擾
void ResetCamera(void);			//���Z�b�g
float CameraRotDesh(void);		//�ړI�̌����擾
#endif _CAMERA_H_