//=============================================================================
//
// �V�[������ [scene.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//�}�N����`
#define POLYGON_SIZE (70.0f)
#define PRIORITY (7)
#define CIRCLE (float(rand() % 324) / 100.0f - float(rand() % 324) / 100.0f) //�~

class CCameraPanel;

class CScene
{
public:

	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJECTTYPE_NONE = 0,
		OBJECTTYPE_UI,
		OBJECTTYPE_EFFECT,
		OBJECTTYPE_ZIPLINE,
		OBJECTTYPE_FIELD,
		OBJECTTYPE_BLOCK,
		OBJCTTYPE_GOAL,
		OBJCTTYPE_TRAMPOLINE,
		OBJCTTYPE_SLACKLINE,
		OBJCTTYPE_CAMERAPANEL,
		OBJCTTYPE_CHECKPOINT,
		OBJECTTYPE_SERECTUI,
		OBJECTTYPE_MAX
	} OBJTYPE;

	//�����蔻��̎��
	typedef enum
	{
		COLLISION_SPHERE = 0,
		COLLISION_PALL,
		COLLISION_SQUARE,
		COLLISION_MAX
	} COLLISION;

	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	CScene *GetNext() { return *m_pNext; }

	static CScene *GetScene(int nPriority) { return m_pTop[nPriority]; }
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	void SetObjType(OBJTYPE obj) { m_objType = obj; }
	OBJTYPE GetObjType() { return m_objType; }

	//pos�̐ݒ�
	D3DXVECTOR3 GetPos() { return m_pos; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	//���a�̐ݒ�
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	float GetRadius() { return m_fRadius; }

	//�����蔻��ݒ�
	COLLISION GetCollision() { return m_Collision; }
	void SetCollision(COLLISION collision) { m_Collision = collision; }

	//���f���̍ő�T�C�Y�ݒ�
	D3DXVECTOR3 GetVtxMax() { return m_vtxMaxModel; }
	void SetVtxMax(D3DXVECTOR3 VtxMax) { m_vtxMaxModel = VtxMax; }

	//���f���̍ŏ��T�C�Y�ݒ�
	D3DXVECTOR3 GetVtxMin() { return m_vtxMinModel; }
	void SetVtxMin(D3DXVECTOR3 VtxMin) { m_vtxMinModel = VtxMin; }

	//�X���b�N���C���̔ԍ��ݒ�
	int GetSlack() { return m_nSlack; }
	void SetSlack(int nSlack) { m_nSlack = nSlack; }

	//�J�����̎��_�ݒ�
	D3DXVECTOR3 GetCameraPosV() { return m_CameraPosV; }
	void SetCameraPosV(D3DXVECTOR3 posV) { m_CameraPosV = posV; }

	//�J�����̒����_�ݒ�
	D3DXVECTOR3 GetCameraPosR() { return m_CameraPosR; }
	void SetCameraPosR(D3DXVECTOR3 posR) { m_CameraPosR = posR; }

	//���̃t���[���ŏ����ݒ�
	void SetDeath(bool bDeath) { m_bDeath = bDeath; }

private:
	static CScene *m_pTop[PRIORITY];	//�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[PRIORITY];	//����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev[PRIORITY];			//�O�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pNext[PRIORITY];			//���̃I�u�W�F�N�g�̃|�C���^

	static int m_nNumAll;		//���V�[�����邩
	//static bool m_bKey;
	D3DXVECTOR3 m_pos;			//�ꏊ
	bool m_bDeath;				//������
	float m_fRadius;			//���a
	COLLISION m_Collision;		//�����蔻��
	D3DXVECTOR3 m_vtxMinModel;	//���f���̍ŏ��l
	D3DXVECTOR3 m_vtxMaxModel;	//���f���̍ő�l
	int m_nSlack;				//�X���b�N���C���̔ԍ�
	D3DXVECTOR3 m_CameraPosV;	//�J�������_
	D3DXVECTOR3 m_CameraPosR;	//�J���������_

	int m_nPriority;			//�D�揇��

	OBJTYPE m_objType;			//�I�u�W�F�N�g�^�C�v

protected:
	void Release();				//�폜
};
#endif