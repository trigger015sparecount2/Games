//-----------------------------------------
//Author:�O��q��
//���b�V���t�B�[���h(meshfield.cpp)
//-----------------------------------------
#include "meshfield.h"

//�}�N����`
#define MAX_WIDTH (20) //x�����̐����`�̐�
#define MAX_DEPTH (20) //z�����̐����`�̐�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL; 
D3DXVECTOR3 g_posMeshfield; //�ʒu
D3DXVECTOR3 g_rotMeshfield; //����
D3DXMATRIX g_mtxWorldMeshfield; //���[���h�}�g���b�N�X

//����������
HRESULT InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nWidth; //x����
	int nDepth; //z����
	int nBlock = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/field000.jpg",
		&g_pTextureMeshfield);

	g_posMeshfield = D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MAX_WIDTH + 1) * (MAX_DEPTH + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void **)&pVtx, 0);
	for (nDepth = 0; nDepth < MAX_DEPTH + 1; nDepth++)
	{
		for (nWidth = 0; nWidth < MAX_WIDTH + 1; nWidth++)
		{
			//���_���W�̐ݒ�
			pVtx[nBlock].pos = D3DXVECTOR3(nWidth * 200.0f, 0.0f,-nDepth * 200.0f); //�������珇�Ԃɔz�u�����
			//�@���x�N�g���̐ݒ�
			pVtx[nBlock].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			//���_�J���[
			pVtx[nBlock].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`�����W
			pVtx[nBlock].tex = D3DXVECTOR2(nWidth * 1.0f,(MAX_DEPTH - nDepth) * 1.0f);
			nBlock++;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (2 * (MAX_WIDTH + 1) * MAX_DEPTH + 2 * (MAX_DEPTH - 1)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);
	nBlock = 0;
	WORD *pIdx; //�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void **)&pIdx, 0);
	for (nDepth = 0; nDepth < MAX_DEPTH; nDepth++)
	{
		for (nWidth = 0; nWidth < MAX_WIDTH + 1; nWidth++)
		{
			//�ԍ��f�[�^�̐ݒ�
			pIdx[nBlock] = nWidth + (nDepth + 1) * (MAX_WIDTH + 1);
			pIdx[nBlock + 1] = nWidth + nDepth * (MAX_WIDTH + 1);
			nBlock += 2;
		}
		if (nDepth < MAX_DEPTH - 1)
		{
			pIdx[nBlock] = MAX_WIDTH + nDepth * (MAX_WIDTH + 1);
			pIdx[nBlock + 1] = (nDepth + 2) * (MAX_WIDTH + 1);
			nBlock += 2;
		}
	}
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshField->Unlock();
	return S_OK;
}

//�I������
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//�X�V����
void UpdateMeshfield(void)
{

}

//�`�揈��
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	pDevice = GetDevice();     //�f�o�C�X���擾����

	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, g_pTextureMeshfield);    //�e�N�X�`���̐ݒ�

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		(MAX_WIDTH + 1) * (MAX_DEPTH + 1), //���_�̐�
		0,
		2 * (MAX_WIDTH + 1) * MAX_DEPTH + 2 * (MAX_DEPTH - 2)); //�`�悷��v���~�e�B�u��
	
																//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//�t�B�[���h�Ƃ̓����蔻��
bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius)
{
	bool bLand = false;
	if (pPos->x - fRadius < g_posMeshfield.x + MAX_WIDTH * 200.0f && g_posMeshfield.x < pPos->x + fRadius &&
		pPos->z + fRadius > g_posMeshfield.z - MAX_DEPTH * 200.0f && g_posMeshfield.z > pPos->z - fRadius)
	{
		//�t�B�[���h�̏㑤�ɂԂ�����(�����)�Ƃ�
		if (pPosOld->y >= g_posMeshfield.y && g_posMeshfield.y >= pPos->y)
		{
			bLand = true;
			pMove->y = 0.0f;
			pPos->y = g_posMeshfield.y;
		}
	}
	return bLand;
}