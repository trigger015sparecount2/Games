//---------------------------
//Author:�O��q��
//��(wall.cpp)
//---------------------------
#include "wall.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall = NULL;
D3DXVECTOR3 g_posWall[4]; //�ʒu
D3DXVECTOR3 g_rotWall[4]; //����
D3DXMATRIX g_mtxWorldWall[4]; //���[���h�}�g���b�N�X

//����������
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/field000.jpg",
		&g_pTextureWall);
	g_posWall[0] = D3DXVECTOR3(0.0f, 0.0f, 2000.0f);
	g_rotWall[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posWall[1] = D3DXVECTOR3(2000.0f, 0.0f, 0.0f);
	g_rotWall[1] = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
	g_posWall[2] = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
	g_rotWall[2] = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
	g_posWall[3] = D3DXVECTOR3(0.0f, 0.0f, -2000.0f);
	g_rotWall[3] = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-2000.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f   , 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(2000.0f , 400.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(-2000.0f, 200.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f   , 200.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(2000.0f , 200.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f   , 0.0f, 0.0f);
	pVtx[8].pos = D3DXVECTOR3(2000.0f , 0.0f, 0.0f);
	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffWall,
		NULL);
	WORD *pIdx; //�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffWall->Lock(0, 0, (void **)&pIdx, 0);
	//�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffWall->Unlock();
	return S_OK;
}

//�I������
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
	if (g_pIdxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
	}
}

//�X�V����
void UpdateWall(void)
{

}

//�`�揈��
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntWall;
	for (nCntWall = 0; nCntWall < 4; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldWall[nCntWall]);
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotWall[nCntWall].y, g_rotWall[nCntWall].x, g_rotWall[nCntWall].z);
		D3DXMatrixMultiply(&g_mtxWorldWall[nCntWall], &g_mtxWorldWall[nCntWall], &mtxRot);
		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_posWall[nCntWall].x, g_posWall[nCntWall].y, g_posWall[nCntWall].z);
		D3DXMatrixMultiply(&g_mtxWorldWall[nCntWall], &g_mtxWorldWall[nCntWall], &mtxTrans);
		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall[nCntWall]);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));
		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffWall);
		//���_�t�H�[�}�b�g
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, g_pTextureWall);    //�e�N�X�`���̐ݒ�
		
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			9, //���_�̐�
			0,
			12); //�`�悷��v���~�e�B�u��
	}
}

void CollisionWall(D3DXVECTOR3 *pPos, float fRadius)
{
	if (pPos->x - fRadius < -2000.0f)
	{
		pPos->x = -2000.0f + fRadius;
	}
	else if (pPos->x + fRadius > 2000.0f)
	{
		pPos->x = 2000.0f - fRadius;
	}
	if (pPos->z - fRadius < -2000.0f)
	{
		pPos->z = -2000.0f + fRadius;
	}
	else if (pPos->z + fRadius > 2000.0f)
	{
		pPos->z = 2000.0f - fRadius;
	}
}