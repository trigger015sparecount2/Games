//---------------------------
//Author:�O��q��
//���f��(model.cpp)
//---------------------------
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "gamepad.h"
#include "bullet.h"
#include "particle.h"
#include "enemy.h"

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshModel = NULL; //���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL; //�}�e���A���i�ގ����j�ւ̃|�C���^
DWORD g_nNumMatModel = 1; //�}�e���A���̐�
LPDIRECT3DTEXTURE9 g_aTextureModel[1] = {}; //�e�N�X�`��
D3DXVECTOR3 g_posModel; //�ʒu
D3DXVECTOR3 g_rotModel; //����
D3DXVECTOR3 g_rotModelDesh; //�ړI�̌���
D3DXMATRIX g_mtxWorldModel; //���[���h�}�g���b�N�X
D3DXVECTOR3 g_movePolygon;
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel; //���f���̍ő�l,�ŏ��l
int g_nShadow;
bool g_bArrow;

//����������
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/Model/ball.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatModel,
						NULL,
						&g_nNumMatModel,
						&g_pMeshModel);
	int nCntTex = 0;
	g_bArrow = false;
	D3DXMATERIAL *pMat;
	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_aTextureModel[nCntTex]);
			nCntTex++;
		}
	}
	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	//���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());
	g_vtxMaxModel.x = -10000.0f;
	g_vtxMaxModel.y = -10000.0f;
	g_vtxMaxModel.z = -10000.0f;
	g_vtxMinModel.x = 10000.0f;
	g_vtxMinModel.y = 10000.0f;
	g_vtxMinModel.z = 10000.0f;
	//���_�o�b�t�@�̃��b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W�̑��
		if (g_vtxMinModel.x > vtx.x)
		{
			g_vtxMinModel.x = vtx.x;
		}
		if (g_vtxMinModel.y > vtx.y)
		{
			g_vtxMinModel.y = vtx.y;
		}
		if (g_vtxMinModel.z > vtx.z)
		{
			g_vtxMinModel.z = vtx.z;
		}
		if (g_vtxMaxModel.x < vtx.x)
		{
			g_vtxMaxModel.x = vtx.x;
		}
		if (g_vtxMaxModel.y < vtx.y)
		{
			g_vtxMaxModel.y = vtx.y;
		}
		if (g_vtxMaxModel.z < vtx.z)
		{
			g_vtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();
	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModelDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nShadow = SetShadow(g_posModel, 10.0f);
	g_movePolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//�I������
void UninitModel(void)
{
	//�e�N�X�`���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//�X�V����
void UpdateModel(void)
{
	g_posModel = ECollisionPos();
}

//�`�揈��
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;		 //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			 //�}�e���A���f�[�^�ւ̃|�C���^
	pDevice = GetDevice();		 //�f�o�C�X���擾����
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);
	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	//�}�e���A���f�[�^�ւ̃|�C���^�̔��f
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	int nCntTex = 0;
	int nCntMat;
	for (nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aTextureModel[nCntTex]);
			nCntMat++;
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
		//���f���i�p�[�c�j�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//���f���̏ꏊ
float ModelPos(int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_posModel.x;
		break;
	case 1:
		return g_posModel.y;
		break;
	case 2:
		return g_posModel.z;
		break;
	}
	return 0.0f;
}

//���f���̌���
float ModelRot(void)
{
	return g_rotModel.y;
}

//�ړ����x��
void ModelMoveX(void)
{
	g_movePolygon.x -= (sinf(g_rotModelDesh.y) * 5.0f + g_movePolygon.x) * 0.1f;
}

//�ړ����x�c
void ModelMoveZ(void)
{
	g_movePolygon.z -= (cosf(g_rotModelDesh.y) * 5.0f + g_movePolygon.z) * 0.1f;
}

//���f���̖ړI�̌����擾
float ModelRotDesh(void)
{
	return g_rotModelDesh.y;
}

//���f���̈ړ��ʎ擾
float ModelMove(int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_movePolygon.x;
		break;
	case 1:
		return g_movePolygon.y;
		break;
	case 2:
		return g_movePolygon.z;
		break;
	}
	return 0.0f;
}

//���f���̃T�C�Y�̍ŏ��l
float ModelMinSize(int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_vtxMinModel.x;
		break;
	case 1:
		return g_vtxMinModel.y;
		break;
	case 2:
		return g_vtxMinModel.z;
		break;
	}
	return 0.0f;
}

//���f���̃T�C�Y�̍ő�l
float ModelMaxSize(int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_vtxMaxModel.x;
		break;
	case 1:
		return g_vtxMaxModel.y;
		break;
	case 2:
		return g_vtxMaxModel.z;
		break;
	}
	return 0.0f;
}

//�ړ����x�ቺ��
void ModelMoveXslow(void)
{
	g_movePolygon.x -= g_movePolygon.x * 0.1f;
}

//�ړ����x�ቺ�c
void ModelMoveZslow(void)
{
	g_movePolygon.z -= g_movePolygon.z * 0.1f;
}