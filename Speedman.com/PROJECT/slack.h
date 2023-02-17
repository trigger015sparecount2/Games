//=============================================================================
//
// �X���b�N���C���̎x������ [slack.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SLACK_H_
#define _SLACK_H_

#include "main.h"
#include "object.h"

class CModel;

class CSlack : public CObject
{
public:
	CSlack(int nPriority);
	~CSlack();

	HRESULT Init(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot, int nSlack);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CSlack *Create(D3DXVECTOR3 pos, int nType, COLLISION collision, D3DXVECTOR3 rot, int nSlack);	//�쐬
private:

};

#endif