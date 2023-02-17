//=============================================================================
//
// �J�������� [camera.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class CKeyboard;
class CMouse;
class CScene;

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
		D3DXVECTOR3 posPlus;		//pos����
		D3DXVECTOR3 vecU;			//������x�N�g��
		D3DXVECTOR3 rot;			//�J�����̌���
		D3DXVECTOR3 rotDesh;		//�J�����̖ړI����
		float fLength;				//����
		D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
		bool bRot[2];				//X��Y
		bool bAdd[2];				//X��Y
	} Camera;
	CCamera();
	~CCamera();
	HRESULT Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V

	float GetRotY() { return m_camera.rot.y; }	//����Y�擾
	float GetRotX() { return m_camera.rot.x; }	//����X�擾
	void SetPosV(D3DXVECTOR3 pos);				//���_�ݒ�
	void SetPosR(D3DXVECTOR3 pos);				//�����_�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_camera.rot = rot; }			//�����ݒ�
	void SetLength(float fLength) { m_camera.fLength = fLength; }	//�����ݒ�
	D3DXVECTOR3 GetPosR() { return m_camera.posR; }					//���ݒ����_�擾
	D3DXVECTOR3 GetPosV() { return m_camera.posV; }					//���ݎ��_�擾
	void AddRotY(float fRotY);	//����Y���Z
	void AddRotX(float fRotX);	//����X���Z
	void MoveX(float fMove);	//�ړ�X
	void MoveZ(float fMove);	//�ړ�Z
	void ResetRot() { m_camera.rot = D3DXVECTOR3(0.8f, 0.0f, 0.0f); }	//�������Z�b�g
	void SetPlayer(CScene *pPlayer) { m_pPlayer = pPlayer; }			//�v���C���[�ݒ�
	void SetRotDeshX(float fRotX);	//�ړI�̌���X�ݒ�
	void SetRotDeshY(float fRotY);	//�ړI�̌���Y�ݒ�
	void SetAdd(bool bAdd);			//�����Ă������ݒ�
	void AddLength(float fLength) { m_camera.fLength += fLength; }				//�������Z
	void AddPosReset(void){ m_camera.posPlus = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//�ꏊ���Z�l���Z�b�g
	void AddPosPlus(D3DXVECTOR3 pos, D3DXVECTOR2 aCamera[2]);					//�ꏊ���Z�n�����Z������

	static CCamera *Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//�쐬

private:
	Camera m_camera;	//�J����
	CScene *m_pPlayer;	//�v���C���[
};

#endif