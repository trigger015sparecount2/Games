//--------------------------
//Author:�O��q��
//�w�i�̏���(bg.cpp)
//--------------------------
#include "bg.h"

//�w�i�̍\���̒�`
typedef struct
{
	int ntype;   //���
	float fPosTexU;
	bool bscroll; //�X�N���[�����邩
} Bg;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBg[2] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Bg g_aBg;	//�w�i

//����������
void InitBg(void)
{
	int nCntBg;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	g_aBg.bscroll = true;
	g_aBg.fPosTexU = 0.0f;
	g_aBg.ntype = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/sky000.jpg",
		&g_pTextureBg[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/mountain000.png",
		&g_pTextureBg[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBg = 0; nCntBg < 2; nCntBg++)
	{
		//���_���W�̐ݒ�
		if (nCntBg == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 550.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 550.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		if (nCntBg == 0)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}

//�I������
void UninitBg(void)
{
	int nCntBg;
	for (nCntBg = 0; nCntBg < 2; nCntBg++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBg[nCntBg] != NULL)
		{
			g_pTextureBg[nCntBg]->Release();
			g_pTextureBg[nCntBg] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//�X�V����
void UpdateBg(void)
{
	//�w�i�X�N���[��������
	if (g_aBg.bscroll == true)
	{
		VERTEX_2D *pVtx;
		g_pVtxBuffBg->Lock(0, 0, (void **)&pVtx, 0);
		g_aBg.fPosTexU += 0.0001f;
		if (g_aBg.fPosTexU >= 1.0f)
		{
			g_aBg.fPosTexU = 0.0f;
		}

		pVtx[0].tex = D3DXVECTOR2(g_aBg.fPosTexU, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aBg.fPosTexU + 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aBg.fPosTexU, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aBg.fPosTexU + 0.25f, 1.0f);
		g_pVtxBuffBg->Unlock();
	}
}

//�`�揈��
void DrawBg(void)
{
	int nCntBg;
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntBg = 0; nCntBg < 2; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureBg[nCntBg]);    //�e�N�X�`���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntBg * 4,  //�J�n����n�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
	}
}

//�w�i�̐ݒ菈��
void SetBg(int nType, bool bscroll)
{
	g_aBg.ntype = nType;
	g_aBg.bscroll = bscroll;
	g_aBg.fPosTexU = 1.0f;
}

void ScrollBg(bool bscroll)
{
	g_aBg.bscroll = bscroll;
}