//=============================================================================
//
// �V�[������ [camera.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class CKeyboard;
class CMouse;

class CCamera
{
public:
	//�J�����̍\����
	typedef struct
	{
		D3DXVECTOR3 posV;			//���݂̎��_
		D3DXVECTOR3 posVDest;		//�ړI�̎��_
		D3DXVECTOR3 posR;			//���݂̒����_
		D3DXVECTOR3 posRDest;		//�ړI�̒����_
		D3DXVECTOR3 vecU;			//������x�N�g��
		D3DXVECTOR3 rot;			//�J�����̌���
		float fLength;				//�J�����̋���
		D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	} Camera;

	CCamera();
	~CCamera();
	HRESULT Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V

	float GetRotY() { return m_camera.rot.y; }	//Y�����擾
	float GetRotX() { return m_camera.rot.x; }	//X�����擾
	void SetPosV(D3DXVECTOR3 pos);		//���_�ݒ�
	void SetPosR(D3DXVECTOR3 pos);		//�����_�ݒ�
	void SetRot(){ m_camera.rot.y = atan2f(m_camera.posR.x - m_camera.posV.x, m_camera.posR.z - m_camera.posV.z); }	//�����ݒ�
	D3DXVECTOR3 GetPosR() { return m_camera.posR; }	//�����_�擾
	D3DXVECTOR3 GetPosV() { return m_camera.posV; }	//���_�擾
	void AddRotY(float fRotY);						//Y�������Z
	void AddRotX(float fRotX);						//X�������Z
	void ResetRot() { m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//�������Z�b�g

	static CCamera *Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//�쐬

private:
	Camera m_camera;	//�J����
};

#endif