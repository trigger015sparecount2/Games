//---------------------------
//Author:�O��q��
//�p�[�e�B�N������(particle.cpp)
//---------------------------
#include "particle.h"
#include "camera.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL; //���_�o�b�t�@�ւ̃|�C���^
Particle g_Particle[MAX_PARTICLE];

//����������
HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntParticle;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/bullet000.png",
		&g_pTextureParticle);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_Particle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Particle[nCntParticle].nTime = 0;
		g_Particle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Particle[nCntParticle].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, -5.0f, 0.0f);
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
	return S_OK;
}

//�I������
void UninitParticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//�X�V����
void UpdateParticle(void)
{
	int nCntParticle;
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{
			g_Particle[nCntParticle].nTime++;
			g_Particle[nCntParticle].pos += g_Particle[nCntParticle].move;
			
			if (g_Particle[nCntParticle].nTime >= 30)
			{
				g_Particle[nCntParticle].bUse = false;
			}
		}
	}
}

//�`�揈��
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	int nCntParticle;
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Particle[nCntParticle].mtxWorld);
			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_Particle[nCntParticle].mtxWorld, NULL, &mtxView); //�t�s������߂�
			g_Particle[nCntParticle].mtxWorld._41 = 0.0f;
			g_Particle[nCntParticle].mtxWorld._42 = 0.0f;
			g_Particle[nCntParticle].mtxWorld._43 = 0.0f;
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
			D3DXMatrixTranslation(&mtxTrans, g_Particle[nCntParticle].pos.x, g_Particle[nCntParticle].pos.y, g_Particle[nCntParticle].pos.z);
			D3DXMatrixMultiply(&g_Particle[nCntParticle].mtxWorld, &g_Particle[nCntParticle].mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Particle[nCntParticle].mtxWorld);
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureParticle);    //�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntParticle * 4,  //�J�n����n�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//�p�[�e�B�N���̐ݒ�(�����Ƃ����������肻��)
void SetParticle(D3DXVECTOR3 pos)
{
	int nCntParticle;
	int nCntPoint = 0;
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == false)
		{
			g_Particle[nCntParticle].pos = pos;
			g_Particle[nCntParticle].nTime = 0;
			g_Particle[nCntParticle].bUse = true;
			switch (nCntPoint)
			{
			case 0:
				g_Particle[nCntParticle].move = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
				break;
			case 1:
				g_Particle[nCntParticle].move = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + CameraRot()) * 2.0f, cosf(D3DX_PI * 0.25f) * 2.0f, sinf(-CameraRot()) * 2.0f);
				break;
			case 2:
				g_Particle[nCntParticle].move = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + CameraRot()) * 2.5f, cosf(D3DX_PI * 0.5f) * 2.0f, sinf(-CameraRot()) * 2.5f);
				break;
			case 3:
				g_Particle[nCntParticle].move = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + CameraRot()) * 2.0f, cosf(D3DX_PI * 0.75f) * 2.0f, sinf(-CameraRot()) * 2.0f);
				break;
			case 4:
				g_Particle[nCntParticle].move = D3DXVECTOR3(0.0f, -2.5f, 0.0f);
				break;
			case 5:
				g_Particle[nCntParticle].move = D3DXVECTOR3(sinf(D3DX_PI * -0.5f + CameraRot()) * 2.0f, cosf(D3DX_PI * -0.75f) * 2.0f, sinf(CameraRot()) * 2.0f);
				break;
			case 6:
				g_Particle[nCntParticle].move = D3DXVECTOR3(sinf(D3DX_PI * -0.5f + CameraRot()) * 2.5f, cosf(D3DX_PI * -0.5f) * 2.0f, sinf(CameraRot()) * 2.5f);
				break;
			case 7:
				g_Particle[nCntParticle].move = D3DXVECTOR3(sinf(D3DX_PI * -0.5f + CameraRot()) * 2.0f, cosf(D3DX_PI * -0.25f) * 2.0f, sinf(CameraRot()) * 2.0f);
				break;
			}
			nCntPoint++;
		}
		if (nCntPoint == 8)
		{
			break;
		}
	}
}