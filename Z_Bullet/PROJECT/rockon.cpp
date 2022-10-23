//---------------------------
//Author:�O��q��
//���b�N�I��(rockon.cpp)
//---------------------------
#include "rockon.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRockon = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRockon = NULL; //���_�o�b�t�@�ւ̃|�C���^
Rockon g_Rockon;

//����������
HRESULT InitRockon(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
							   //�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/target000.png",
		&g_pTextureRockon);
	g_Rockon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Rockon.nNumber = 0;
	g_Rockon.bUse = false;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRockon,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRockon->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-15.0f, 15.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(15.0f, 15.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-15.0f, -15.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(15.0f, -15.0f, 0.0f);
	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRockon->Unlock();
	return S_OK;
}

//�I������
void UninitRockon(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRockon != NULL)
	{
		g_pTextureRockon->Release();
		g_pTextureRockon = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRockon != NULL)
	{
		g_pVtxBuffRockon->Release();
		g_pVtxBuffRockon = NULL;
	}
}

//�X�V����
void UpdateRockon(void)
{

}

//�`�揈��
void DrawRockon(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	if (g_Rockon.bUse == true)
	{
		pDevice = GetDevice();     //�f�o�C�X���擾����
		//���C���e�B���O�𖳎�����
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//��ɕ\�������悤�ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Rockon.mtxWorld);
		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&g_Rockon.mtxWorld, NULL, &mtxView); //�t�s������߂�
		g_Rockon.mtxWorld._41 = 0.0f;
		g_Rockon.mtxWorld._42 = 0.0f;
		g_Rockon.mtxWorld._43 = 0.0f;
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
		D3DXMatrixTranslation(&mtxTrans, g_Rockon.pos.x, g_Rockon.pos.y, g_Rockon.pos.z);
		D3DXMatrixMultiply(&g_Rockon.mtxWorld, &g_Rockon.mtxWorld, &mtxTrans);
		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Rockon.mtxWorld);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffRockon, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, g_pTextureRockon);    //�e�N�X�`���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,  //�J�n����n�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
		//���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

void SetRockon(D3DXVECTOR3 pos, int nNumber)
{
	if (nNumber != g_Rockon.nNumber)
	{
		g_Rockon.pos = pos;
		g_Rockon.nNumber = nNumber;
		g_Rockon.bUse = true;
	}
}

void MoveRockon(D3DXVECTOR3 pos)
{
	g_Rockon.pos = pos;
}

int RemoveRockon(void)
{
	g_Rockon.nNumber = -1;
	g_Rockon.bUse = false;
	return -1;
}

int RockNumber(void)
{
	return g_Rockon.nNumber;
}