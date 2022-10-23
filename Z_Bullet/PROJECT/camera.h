//---------------------------
//Author:�O��q��
//�J����(camera.h)
//---------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"
//�v���g�^�C�v�錾
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(D3DXVECTOR3 ref, float fDistance);
float CameraRot(void);
float CameraPosV(int nRot);
D3DXVECTOR3 CameraPosR(void);
float CameraDistance(void);
D3DXVECTOR3 CameraVector(void);
void CameraRotReset(float fRoty);
void CameraRot(float fRot);
void PlayerDieCamera(float fRot);
#endif _CAMERA_H_