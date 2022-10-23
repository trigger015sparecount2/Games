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
	D3DXVECTOR3 posV;     //���݂̎��_
	D3DXVECTOR3 posVDest; //�ړI�̎��_
	D3DXVECTOR3 posR;     //���݂̒����_
	D3DXVECTOR3 posRDest; //�ړI�̒����_
	D3DXVECTOR3 vecU;     //������x�N�g��
	D3DXVECTOR3 rot;     //�J�����̌���
	D3DXVECTOR3 rotDesh;
	float fLength;
	int nTime;
	bool bRot;
	D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X
} Camera;
//�v���g�^�C�v�錾
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
float CameraRot(void);
D3DXVECTOR3 CameraPosV(void);
D3DXVECTOR3 CameraPosR(void);
float CameraDistance(void);
float RockCamera(void);
D3DXMATRIX CameraMtxPro(void);
D3DXMATRIX CameraMtxView(void);
float CameraRotH(void);
float CameraRotV(void);
void ResetCamera(void);
float CameraRotDesh(void);
float CameraDistance(D3DXVECTOR3 pos);
#endif _CAMERA_H_