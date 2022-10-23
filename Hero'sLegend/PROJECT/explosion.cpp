//---------------------------
//Author:�O��q��
//��������(explosion.cpp)
//---------------------------
#include "explosion.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL; //���_�o�b�t�@�ւ̃|�C���^
Explosion g_Explosion[MAX_EXPLOSION];

//����������
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntExplosion;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/explosion000.png",
		&g_pTextureExplosion);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_Explosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCntExplosion].nTime = 0;
		g_Explosion[nCntExplosion].fTex = 0.0f;
		g_Explosion[nCntExplosion].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
	return S_OK;
}

//�I������
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//�X�V����
void UpdateExplosion(void)
{
	int nCntExplosion;
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{
			g_Explosion[nCntExplosion].nTime++;
			if (g_Explosion[nCntExplosion].nTime >= 4)
			{
				g_Explosion[nCntExplosion].nTime = 0;
				g_Explosion[nCntExplosion].fTex += 0.125f;
				if (g_Explosion[nCntExplosion].fTex == 1.0f)
				{
					g_Explosion[nCntExplosion].bUse = false;
				}
				VERTEX_3D *pVtx;
				g_pVtxBuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
				pVtx += nCntExplosion * 4;
				pVtx[0].tex = D3DXVECTOR2(g_Explosion[nCntExplosion].fTex         , 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_Explosion[nCntExplosion].fTex + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_Explosion[nCntExplosion].fTex         , 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_Explosion[nCntExplosion].fTex + 0.125f, 1.0f);
				g_pVtxBuffExplosion->Unlock();
			}
		}
	}
}

//�`�揈��
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	int nCntExplosion;
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//��ɕ\�������悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Explosion[nCntExplosion].mtxWorld);
			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_Explosion[nCntExplosion].mtxWorld, NULL, &mtxView); //�t�s������߂�
			g_Explosion[nCntExplosion].mtxWorld._41 = 0.0f;
			g_Explosion[nCntExplosion].mtxWorld._42 = 0.0f;
			g_Explosion[nCntExplosion].mtxWorld._43 = 0.0f;
			/*
			g_mtxWorldBillboard._11 = mtxView._11;
			g_mtxWorldBillboard._12 = mtxView._21;
			g_mtxWorldBillboard._13 = mtxView._31;
			g_mtxWorldBillboard._14 = mtxView._41;
			g_mtxWorldBillboard._21 = mtxView._12;
			g_mtxWorldBillboard._22 = mtxView._22;
			g_mtxWorldBillboard._23 = mtxView._32;
			g_mtxWorldBillboard._24 = mtxView._42;
			g_mtxWorldBillboard._31 = mtxView._13;
			g_mtxWorldBillboard._32 = mtxView._23;
			g_mtxWorldBillboard._33 = mtxView._33;
			g_mtxWorldBillboard._34 = mtxView._43;
			g_mtxWorldBillboard._41 = mtxView._14;
			g_mtxWorldBillboard._42 = mtxView._24;
			g_mtxWorldBillboard._43 = mtxView._34;
			g_mtxWorldBillboard._44 = mtxView._44;
			*/
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCntExplosion].pos.x, g_Explosion[nCntExplosion].pos.y, g_Explosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_Explosion[nCntExplosion].mtxWorld, &g_Explosion[nCntExplosion].mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCntExplosion].mtxWorld);
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureExplosion);    //�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntExplosion * 4,  //�J�n����n�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void SetExplosion(D3DXVECTOR3 pos)
{
	int nCntExplosion;
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == false)
		{
			g_Explosion[nCntExplosion].pos = pos;
			g_Explosion[nCntExplosion].bUse = true;
			g_Explosion[nCntExplosion].nTime = 0;
			g_Explosion[nCntExplosion].fTex = 0.0f;
			VERTEX_3D *pVtx;
			g_pVtxBuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntExplosion * 4;
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
			g_pVtxBuffExplosion->Unlock();
			break;
		}
	}
}