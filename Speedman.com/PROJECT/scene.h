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
	CScene *GetNext();

	static CScene *GetScene(int nPriority);
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void SetObjType(OBJTYPE obj);
	OBJTYPE GetObjType();
	D3DXVECTOR3 GetPos();
	void SetPos(D3DXVECTOR3 pos);
	void SetRadius(float fRadius);
	float GetRadius();
	COLLISION GetCollision();
	void SetCollision(COLLISION collision);
	D3DXVECTOR3 GetVtxMax() { return m_vtxMaxModel; }
	void SetVtxMax(D3DXVECTOR3 VtxMax);
	D3DXVECTOR3 GetVtxMin() { return m_vtxMinModel; }
	void SetVtxMin(D3DXVECTOR3 VtxMin);
	int GetSlack() { return m_nSlack; }
	void SetSlack(int nSlack);
	D3DXVECTOR3 GetCameraPosV() { return m_CameraPosV; }
	void SetCameraPosV(D3DXVECTOR3 posV);
	D3DXVECTOR3 GetCameraPosR() { return m_CameraPosR; }
	void SetCameraPosR(D3DXVECTOR3 posR);
	void SetDeath(bool bDeath);

private:
	static CScene *m_pTop[PRIORITY]; //�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[PRIORITY]; //����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev[PRIORITY];       //�O�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pNext[PRIORITY];       //���̃I�u�W�F�N�g�̃|�C���^

	static int m_nNumAll;
	static bool m_bKey;
	D3DXVECTOR3 m_pos;
	bool m_bDeath;
	float m_fRadius;
	COLLISION m_Collision;
	D3DXVECTOR3 m_vtxMinModel; //���f���̍ŏ��l
	D3DXVECTOR3 m_vtxMaxModel; //���f���̍ő�l
	int m_nSlack;
	D3DXVECTOR3 m_CameraPosV;
	D3DXVECTOR3 m_CameraPosR;

	int m_nPriority;//�D�揇��

	OBJTYPE m_objType;							//�I�u�W�F�N�g�^�C�v

protected:
	void Release();
};
#endif