//=============================================================================
//
// �S�[������ [goal.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"
#include "plane.h"

class CGoal : public CPlane
{
public:
	CGoal(int nPriority);
	~CGoal();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	static CGoal *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//�쐬

private:
	
};

#endif