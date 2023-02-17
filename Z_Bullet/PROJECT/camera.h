//---------------------------
//Author:�O��q��
//�J����(camera.h)
//---------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitCamera(void);			//������
void UninitCamera(void);			//�I��
void UpdateCamera(void);			//�X�V
void SetCamera(D3DXVECTOR3 ref, float fDistance);	//�ݒ�
float CameraRot(void);				//����
float CameraPosV(int nRot);			//���_�̏ꏊ
D3DXVECTOR3 CameraPosR(void);		//�����_�̏ꏊ
float CameraDistance(void);			//�J�����̋���
D3DXVECTOR3 CameraVector(void);		//�J�����̕���
void CameraRotReset(float fRoty);	//�������Z�b�g
void CameraRot(float fRot);			//����
void PlayerDieCamera(float fRot);	//���ꂽ���̃J��������
#endif _CAMERA_H_