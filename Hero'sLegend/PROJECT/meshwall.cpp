//-----------------------------------------
//Author:�O��q��
//���b�V���E�H�[��(meshwall.cpp)
//-----------------------------------------
#include "meshwall.h"

//�}�N����`
#define MAX_WIDTH (8) //x�����̐����`�̐�
#define MAX_HEIGHT (1) //y�����̐����`�̐�
#define MAX_DEPTH (8) //z�����̐����`�̐�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMeshwall = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshwall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshwall = NULL;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posMeshwall;		//�ʒu
D3DXVECTOR3 g_rotMeshwall;		//����
D3DXMATRIX g_mtxWorldMeshwall;	//���[���h�}�g���b�N�X

//����������
HRESULT InitMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nWidth; //x����
	int nHeight; //y����
	int nDepth; //z����
	int nBlock = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/field000.jpg",
		&g_pTextureMeshwall);

	g_posMeshwall = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	g_rotMeshwall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MAX_WIDTH + MAX_DEPTH) * 2 * (MAX_HEIGHT + 1) + MAX_HEIGHT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshwall,
		NULL);

	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshwall->Lock(0, 0, (void **)&pVtx, 0);
	for (nHeight = 0; nHeight < MAX_HEIGHT + 1; nHeight++)
	{
		for (nWidth = 0; nWidth < MAX_WIDTH; nWidth++)
		{
			//���_���W�̐ݒ�
			pVtx[nBlock].pos = D3DXVECTOR3(nWidth * 50.0f, (MAX_HEIGHT - nHeight) * 50.0f, 0.0f); //����
			//�@���x�N�g���̐ݒ�
			pVtx[nBlock].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[
			pVtx[nBlock].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`�����W
			pVtx[nBlock].tex = D3DXVECTOR2(nWidth * 1.0f, (MAX_HEIGHT - nHeight) * 1.0f);
			nBlock++;
		}
		for (nDepth = 0; nDepth < MAX_DEPTH; nDepth++)
		{
			//���_���W�̐ݒ�
			pVtx[nBlock].pos = D3DXVECTOR3(MAX_WIDTH * 50.0f, (MAX_HEIGHT - nHeight) * 50.0f, -nDepth * 50.0f); //�E��
			//�@���x�N�g���̐ݒ�
			pVtx[nBlock].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[
			pVtx[nBlock].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`�����W
			pVtx[nBlock].tex = D3DXVECTOR2(MAX_WIDTH * 1.0f + nDepth * 1.0f, (MAX_HEIGHT - nHeight) * 1.0f);
			nBlock++;
		}
		for (nWidth = 0; nWidth < MAX_WIDTH; nWidth++)
		{
			//���_���W�̐ݒ�
			pVtx[nBlock].pos = D3DXVECTOR3((MAX_WIDTH - nWidth) * 50.0f, (MAX_HEIGHT - nHeight) * 50.0f, -MAX_DEPTH * 50.0f); //���
			//�@���x�N�g���̐ݒ�
			pVtx[nBlock].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[
			pVtx[nBlock].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`�����W
			pVtx[nBlock].tex = D3DXVECTOR2(MAX_WIDTH * 1.0f + MAX_DEPTH * 1.0f + nWidth * 1.0f, (MAX_HEIGHT - nHeight) * 1.0f);
			nBlock++;
		}
		for (nDepth = 0; nDepth < MAX_DEPTH; nDepth++)
		{
			//���_���W�̐ݒ�
			pVtx[nBlock].pos = D3DXVECTOR3(0.0f, (MAX_HEIGHT - nDepth) * 50.0f, -(MAX_DEPTH - nDepth) * 50.0f); //����
			//�@���x�N�g���̐ݒ�
			pVtx[nBlock].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[
			pVtx[nBlock].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`�����W
			pVtx[nBlock].tex = D3DXVECTOR2(MAX_WIDTH * 2.0f + MAX_DEPTH * 1.0f + nDepth * 1.0f, (MAX_HEIGHT - nHeight) * 1.0f);
			nBlock++;
		}
		//���_���W�̐ݒ�
		pVtx[nBlock].pos = D3DXVECTOR3(0.0f, (MAX_HEIGHT - nHeight) * 50.0f, 0.0f); //���΂ߑO�̊p
		//�@���x�N�g���̐ݒ�
		pVtx[nBlock].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�J���[
		pVtx[nBlock].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W
		pVtx[nBlock].tex = D3DXVECTOR2(MAX_WIDTH * 2.0f + MAX_DEPTH * 2.0f + 1.0f, (MAX_HEIGHT - nHeight) * 1.0f);
		nBlock++;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshwall->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (2 * (MAX_WIDTH * 2 + MAX_DEPTH * 2 + 1) * MAX_HEIGHT + 2 * (MAX_HEIGHT - 1)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshwall,
		NULL);
	nBlock = 0;
	WORD *pIdx; //�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshwall->Lock(0, 0, (void **)&pIdx, 0);
	for (nHeight = 0; nHeight < MAX_HEIGHT; nHeight++)
	{
		for (nWidth = 0; nWidth < MAX_WIDTH * 2 + MAX_DEPTH * 2 + 1; nWidth++)
		{
			//�ԍ��f�[�^�̐ݒ�
			pIdx[nBlock] = nWidth + (nHeight + 1) * (MAX_WIDTH * 2 + MAX_DEPTH * 2);
			pIdx[nBlock + 1] = nWidth + nHeight * (MAX_WIDTH * 2 + MAX_DEPTH * 2);
			nBlock += 2;
		}
		if (nHeight < MAX_HEIGHT - 1)
		{
			pIdx[nBlock] = (nHeight + 1) * (MAX_WIDTH * 2 + MAX_DEPTH * 2) + nHeight;
			pIdx[nBlock + 1] = (nHeight + 2) * (MAX_WIDTH * 2 + MAX_DEPTH * 2) + nHeight + 2;
			nBlock += 2;
		}
	}
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshwall->Unlock();
	return S_OK;
}

//�I������
void UninitMeshwall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshwall != NULL)
	{
		g_pTextureMeshwall->Release();
		g_pTextureMeshwall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshwall != NULL)
	{
		g_pVtxBuffMeshwall->Release();
		g_pVtxBuffMeshwall = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshwall != NULL)
	{
		g_pIdxBuffMeshwall->Release();
		g_pIdxBuffMeshwall = NULL;
	}
}

//�X�V����
void UpdateMeshwall(void)
{

}

//�`�揈��
void DrawMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshwall);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshwall.y, g_rotMeshwall.x, g_rotMeshwall.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshwall, &g_mtxWorldMeshwall, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshwall.x, g_posMeshwall.y, g_posMeshwall.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshwall, &g_mtxWorldMeshwall, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshwall);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshwall);
	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, g_pTextureMeshwall);    //�e�N�X�`���̐ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		(MAX_WIDTH + MAX_DEPTH) * 2 * (MAX_HEIGHT + 1) + 2 * MAX_HEIGHT, //���_�̐�
		0,
		2 * (MAX_WIDTH * 2 + MAX_DEPTH * 2 + 1) * MAX_HEIGHT + 2 * (MAX_HEIGHT - 2)); //�`�悷��v���~�e�B�u��
}