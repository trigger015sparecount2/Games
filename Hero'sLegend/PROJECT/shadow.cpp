//---------------------------
//Author:�O��q��
//�e(shadow.cpp)
//---------------------------
#include "shadow.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //���_�o�b�t�@�ւ̃|�C���^
Shadow g_Shadow[MAX_SHADOW];

//����������
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntShadow;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/shadow000.jpg",
		&g_pTextureShadow);
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].fRadius = 0.0f;
		g_Shadow[nCntShadow].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
	return S_OK;
}

//�I������
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//�X�V����
void UpdateShadow(void)
{

}

//�`�揈��
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntShadow;
	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureShadow);    //�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntShadow * 4,  //�J�n����n�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
			
		}
	}
	//�ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//�e�̐ݒ�
int SetShadow(D3DXVECTOR3 pos, float fRadius)
{
	int nIdx = -1;
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos.x = pos.x;
			g_Shadow[nCntShadow].pos.y = 0.0f;
			g_Shadow[nCntShadow].pos.z = pos.z;
			g_Shadow[nCntShadow].fRadius = fRadius;
			g_Shadow[nCntShadow].bUse = true;
			g_Shadow[nCntShadow].nLength = 0;
			VERTEX_3D *pVtx;
			g_pVtxBuffShadow->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntShadow * 4;
			pVtx[0].pos = D3DXVECTOR3(-fRadius, 0.0f, fRadius);
			pVtx[1].pos = D3DXVECTOR3(fRadius, 0.0f, fRadius);
			pVtx[2].pos = D3DXVECTOR3(-fRadius, 0.0f, -fRadius);
			pVtx[3].pos = D3DXVECTOR3(fRadius, 0.0f,  -fRadius);
			g_pVtxBuffShadow->Unlock();
			nIdx = nCntShadow;
			break;
		}
	}
	return nIdx;
}

//�e���������Ƃ�
void MoveShadow(int nShadow, D3DXVECTOR3 pos)
{
	int nLength;
	nLength = ceilf(pos.y);
	g_Shadow[nShadow].pos.x = pos.x;
	g_Shadow[nShadow].pos.z = pos.z;
	if (nLength >= 120)
	{
		nLength = 120;
	}
	VERTEX_3D *pVtx;
	g_pVtxBuffShadow->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += nShadow * 4;
	pVtx[0].pos = D3DXVECTOR3(- g_Shadow[nShadow].fRadius - (float)nLength / 10, 0.0f, g_Shadow[nShadow].fRadius + (float)nLength / 10);
	pVtx[1].pos = D3DXVECTOR3(g_Shadow[nShadow].fRadius + (float)nLength / 10,   0.0f, g_Shadow[nShadow].fRadius + (float)nLength / 10);
	pVtx[2].pos = D3DXVECTOR3(- g_Shadow[nShadow].fRadius - (float)nLength / 10, 0.0f, -g_Shadow[nShadow].fRadius - (float)nLength / 10);
	pVtx[3].pos = D3DXVECTOR3(g_Shadow[nShadow].fRadius + (float)nLength / 10,   0.0f, -g_Shadow[nShadow].fRadius - (float)nLength / 10);
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120 - nLength);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120 - nLength);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120 - nLength);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120 - nLength);
	g_pVtxBuffShadow->Unlock();
}

void ResetShadow(void)
{
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			g_Shadow[nCntShadow].bUse = false;
		}
	}
}

void RemoveShadow(int nShadow)
{
	g_Shadow[nShadow].bUse = false;
}