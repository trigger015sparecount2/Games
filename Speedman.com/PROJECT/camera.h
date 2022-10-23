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
		D3DXVECTOR3 posV;     //���݂̎��_
		D3DXVECTOR3 posVDest; //�ړI�̎��_
		D3DXVECTOR3 posR;     //���݂̒����_
		D3DXVECTOR3 posRDest; //�ړI�̒����_
		D3DXVECTOR3 vecU;     //������x�N�g��
		D3DXVECTOR3 rot;     //�J�����̌���
		float fLength;
		D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView; //�r���[�}�g���b�N�X
	} Camera;
	CCamera();
	~CCamera();
	HRESULT Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);
	void Uninit();
	void Update();

	float GetRotY();
	float GetRotX();
	void SetPosV(D3DXVECTOR3 pos);
	void SetPosR(D3DXVECTOR3 pos);
	void SetRot();
	D3DXVECTOR3 GetPosR() { return m_camera.posR; }
	D3DXVECTOR3 GetPosV() { return m_camera.posV; }
	void AddRotY(float fRotY);
	void AddRotX(float fRotX);
	void ResetRot();

	static CCamera *Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);

private:
	Camera m_camera;
	/*CKeyboard *m_pKeyboard;
	CMouse *m_pMouse;*/
};

#endif