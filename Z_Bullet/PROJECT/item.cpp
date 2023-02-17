//---------------------------
//Author:�O��q��
//�A�C�e��(item.cpp)
//---------------------------
#include "item.h"
#include "sound.h"
#include "player.h"

//�}�N����`
#define MAX_ITEM (4)

typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 rot;
	float fRadius;
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	bool bUse;
} Item;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL; //�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshItem; //���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatItem; //�}�e���A���i�ގ����j�ւ̃|�C���^
DWORD g_nNumMatItem; //�}�e���A���̐�
Item g_Item[MAX_ITEM];
float g_fRadius;

//����������
HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntItem;
	D3DXMATERIAL *pMat;
	D3DXLoadMeshFromX("data/MODEL/Aidkit_00.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatItem,
		NULL,
		&g_nNumMatItem,
		&g_pMeshItem);
	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatItem->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatItem; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureItem);
		}
	}
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntItem].bUse = false;
	}
	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtxMaxItem;
	D3DXVECTOR3 vtxMinItem;
	for (nCntItem = 0; nCntItem < (int)g_nNumMatItem; nCntItem++)
	{
		//���_�����擾
		nNumVtx = g_pMeshItem->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem->GetFVF());
		vtxMaxItem.x = -10000.0f;
		vtxMaxItem.y = -10000.0f;
		vtxMaxItem.z = -10000.0f;
		vtxMinItem.x = 10000.0f;
		vtxMinItem.y = 10000.0f;
		vtxMinItem.z = 10000.0f;
		//���_�o�b�t�@�̃��b�N
		g_pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W�̑��
			if (vtxMinItem.x > vtx.x)
			{
				vtxMinItem.x = vtx.x;
			}
			if (vtxMinItem.y > vtx.y)
			{
				vtxMinItem.y = vtx.y;
			}
			if (vtxMinItem.z > vtx.z)
			{
				vtxMinItem.z = vtx.z;
			}
			if (vtxMaxItem.x < vtx.x)
			{
				vtxMaxItem.x = vtx.x;
			}
			if (vtxMaxItem.y < vtx.y)
			{
				vtxMaxItem.y = vtx.y;
			}
			if (vtxMaxItem.z < vtx.z)
			{
				vtxMaxItem.z = vtx.z;
			}
			pVtxBuff += sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_pMeshItem->UnlockVertexBuffer();
	}

	g_fRadius = (vtxMaxItem.x - vtxMinItem.x) / 2;
	if (g_fRadius < (vtxMaxItem.z - vtxMinItem.z) / 2)
	{
		g_fRadius = (vtxMaxItem.z - vtxMinItem.z) / 2;
	}
	return S_OK;
}

//�I������
void UninitItem(void)
{
	//�e�N�X�`���̔j��
	if (g_pMeshItem != NULL)
	{
		g_pMeshItem->Release();
		g_pMeshItem = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pBuffMatItem != NULL)
	{
		g_pBuffMatItem->Release();
		g_pBuffMatItem = NULL;
	}
}

//�X�V����
void UpdateItem(void)
{
	int nCntItem;
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			g_Item[nCntItem].rot.y += 0.02f;
			if (g_Item[nCntItem].rot.y > D3DX_PI)
			{
				g_Item[nCntItem].rot.y -= D3DX_PI * 2;
			}
		}
	}
}

//�`�揈��
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;		 //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			 //�}�e���A���f�[�^�ւ̃|�C���^
	int nCntItem;
	pDevice = GetDevice();		 //�f�o�C�X���擾����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Item[nCntItem].mtxWorld);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCntItem].rot.y, g_Item[nCntItem].rot.x, g_Item[nCntItem].rot.z);
			D3DXMatrixMultiply(&g_Item[nCntItem].mtxWorld, &g_Item[nCntItem].mtxWorld, &mtxRot);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Item[nCntItem].pos.x, g_Item[nCntItem].pos.y, g_Item[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_Item[nCntItem].mtxWorld, &g_Item[nCntItem].mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntItem].mtxWorld);
			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			//�}�e���A���f�[�^�ւ̃|�C���^�̔��f
			pMat = (D3DXMATERIAL*)g_pBuffMatItem->GetBufferPointer();
			int nCntMat;
			for (nCntMat = 0; nCntMat < (int)g_nNumMatItem; nCntMat++)
			{
				//�v���C���[�̃}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureItem);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}
				//�v���C���[�̃��f���i�p�[�c�j�̕`��
				g_pMeshItem->DrawSubset(nCntMat);
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

void SetItem(D3DXVECTOR3 pos)
{
	int nCntItem;
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == false)
		{
			g_Item[nCntItem].fRadius = g_fRadius;
			g_Item[nCntItem].pos = pos;
			g_Item[nCntItem].bUse = true;
			break;
		}
	}
}

void CollisionItem(D3DXVECTOR3 pos, float fRadius)
{
	int nCntItem;
	float fLengthX; //�A�C�e���ƃv���C���[��X�����̒���
	float fLengthZ; //�A�C�e���ƃv���C���[��Z�����̒���
	float fDistance; //�A�C�e���ƃv���C���[�̋���
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			fLengthX = powf(pos.x - g_Item[nCntItem].pos.x, 2);
			fLengthZ = powf(pos.z - g_Item[nCntItem].pos.z, 2);
			fDistance = sqrtf(fLengthX + fLengthZ);
			if (fDistance <= fRadius + g_Item[nCntItem].fRadius)
			{
				AddItem();
				PlaySound(SOUND_LABEL_ITEM);
				g_Item[nCntItem].bUse = false;
			}
		}
	}
}

void ResetItem(void)
{
	int nCntItem;
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].bUse = false;
	}
}