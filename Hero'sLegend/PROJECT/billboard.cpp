//---------------------------
//Author:�O��q��
//�r���{�[�h(billboard.cpp)
//---------------------------
#include "billboard.h"
#include "enemy.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL; //���_�o�b�t�@�ւ̃|�C���^
Billboard g_Billboard[MAX_BILLBOURD];

//����������
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntBoard;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/field000.jpg",
		&g_pTextureBillboard);

	for (nCntBoard = 0; nCntBoard < MAX_BILLBOURD; nCntBoard++)
	{
		g_Billboard[nCntBoard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCntBoard].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-20.0f, 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f, -20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(20.0f, -20.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
	return S_OK;
}

//�I������
void UninitBillboard(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//�X�V����
void UpdateBillboard(void)
{
	

}

//�`�揈��
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	int nCntBoard;
	pDevice = GetDevice();     //�f�o�C�X���擾����

	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//��ɕ\�������悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (nCntBoard = 0; nCntBoard < MAX_BILLBOURD; nCntBoard++)
	{
		if (g_Billboard[nCntBoard].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Billboard[nCntBoard].mtxWorld);
			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_Billboard[nCntBoard].mtxWorld, NULL, &mtxView); //�t�s������߂�
			g_Billboard[nCntBoard].mtxWorld._41 = 0.0f;
			g_Billboard[nCntBoard].mtxWorld._42 = 0.0f;
			g_Billboard[nCntBoard].mtxWorld._43 = 0.0f;
			/*										���ӂ̂���
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
			g_mtxWorldBillboard._41 = mtxView._14;	x��Pos
			g_mtxWorldBillboard._42 = mtxView._24;	y��Pos
			g_mtxWorldBillboard._43 = mtxView._34;	z��Pos
			g_mtxWorldBillboard._44 = mtxView._44;

			*/
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBoard].pos.x, g_Billboard[nCntBoard].pos.y, g_Billboard[nCntBoard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBoard].mtxWorld, &g_Billboard[nCntBoard].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBoard].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureBillboard);    //�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,  //�J�n����n�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//�r���{�[�h�Z�b�g
void SetBillboard(D3DXVECTOR3 pos)
{
	int nCntBoard;
	for (nCntBoard = 0; nCntBoard < MAX_BILLBOURD; nCntBoard++)
	{
		//�g���ĂȂ��g���g��
		if (g_Billboard[nCntBoard].bUse == false)
		{
			g_Billboard[nCntBoard].pos = pos;
			g_Billboard[nCntBoard].bUse = true;
			break;
		}
	}
}

//�r���{�[�h�����g���Ă邩
int CountBoard(void)
{
	int nCntBoard;
	int nCount = 0;
	for (nCntBoard = 0; nCntBoard < MAX_BILLBOURD; nCntBoard++)
	{
		if (g_Billboard[nCntBoard].bUse == true)
		{
			nCount++;
		}
	}
	return nCount;
}