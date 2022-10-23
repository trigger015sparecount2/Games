//--------------------------
//Author:�O��q��
//���̏���(smoke.cpp)
//--------------------------
#include "smoke.h"
//�}�N����`
#define MAX_SMOKE (256)   //���̍ő吔
#define SMOKE_WIDTH (36)  //���̕�
#define SMOKE_HEIGHT (32) //���̍���
//���̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	int nTime;        //����
	int nRed;         //�Ԃ݋
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Smoke;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureSmoke = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSmoke = NULL; //���_�o�b�t�@�ւ̃|�C���^
Smoke g_aSmoke[MAX_SMOKE];

//����������
void InitSmoke(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntSmoke;
	pDevice = GetDevice();
	//���̏�����
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		g_aSmoke[nCntSmoke].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSmoke[nCntSmoke].nRed = 0;
		g_aSmoke[nCntSmoke].nTime = 0;
		g_aSmoke[nCntSmoke].bUse = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/smoke.png",
		&g_pTextureSmoke);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SMOKE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSmoke,
		NULL);
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSmoke->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 180);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 180);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 180);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 180);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSmoke->Unlock();
}

//���̏I������
void UninitSmoke(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSmoke != NULL)
	{
		g_pTextureSmoke->Release();
		g_pTextureSmoke = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSmoke != NULL)
	{
		g_pVtxBuffSmoke->Release();
		g_pVtxBuffSmoke = NULL;
	}
}

//���̍X�V����
void UpdateSmoke(void)
{
	int nCntSmoke;
	VERTEX_2D *pVtx;
	g_pVtxBuffSmoke->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		if (g_aSmoke[nCntSmoke].bUse == true)
		{
			g_aSmoke[nCntSmoke].nTime++;
			g_aSmoke[nCntSmoke].nRed -= 34;
			if (g_aSmoke[nCntSmoke].nRed <= 0)
			{
				g_aSmoke[nCntSmoke].nRed = 0;
			}
			if (g_aSmoke[nCntSmoke].nTime == 180)
			{
				g_aSmoke[nCntSmoke].bUse = false;
			}
			g_aSmoke[nCntSmoke].pos.y += 0.75f;
			if (g_aSmoke[nCntSmoke].pos.y >= 720.0f + (SMOKE_HEIGHT / 2))
			{
				g_aSmoke[nCntSmoke].bUse = false;
			}
			pVtx[0].col = D3DCOLOR_RGBA(255, 255 - g_aSmoke[nCntSmoke].nRed, 255 - g_aSmoke[nCntSmoke].nRed, 180 - g_aSmoke[nCntSmoke].nTime);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255 - g_aSmoke[nCntSmoke].nRed, 255 - g_aSmoke[nCntSmoke].nRed, 180 - g_aSmoke[nCntSmoke].nTime);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255 - g_aSmoke[nCntSmoke].nRed, 255 - g_aSmoke[nCntSmoke].nRed, 180 - g_aSmoke[nCntSmoke].nTime);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255 - g_aSmoke[nCntSmoke].nRed, 255 - g_aSmoke[nCntSmoke].nRed, 180 - g_aSmoke[nCntSmoke].nTime);
			pVtx[0].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x - (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y - (SMOKE_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x + (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y - (SMOKE_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x - (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y + (SMOKE_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x + (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y + (SMOKE_HEIGHT / 2), 0.0f);
		}
		pVtx += 4;
	}
	g_pVtxBuffSmoke->Unlock();
}

//�`�揈��
void DrawSmoke(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntSmoke;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSmoke, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureSmoke);    //�e�N�X�`���̐ݒ�
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		if (g_aSmoke[nCntSmoke].bUse == true)
		{
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntSmoke * 4,
				2);
		}
	}
}

//���̐ݒ菈��
void SetSmoke(D3DXVECTOR3 pos)
{
	int nCntSmoke;
	VERTEX_2D *pVtx;
	g_pVtxBuffSmoke->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		if (g_aSmoke[nCntSmoke].bUse == false)
		{
			g_aSmoke[nCntSmoke].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x - (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y - (SMOKE_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x + (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y - (SMOKE_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x - (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y + (SMOKE_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSmoke[nCntSmoke].pos.x + (SMOKE_WIDTH / 2), g_aSmoke[nCntSmoke].pos.y + (SMOKE_HEIGHT / 2), 0.0f);
			g_aSmoke[nCntSmoke].nRed = 255;
			g_aSmoke[nCntSmoke].nTime = 0;
			g_aSmoke[nCntSmoke].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffSmoke->Unlock();
}

void ResetSmoke(void)
{
	int nCntSmoke;
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		g_aSmoke[nCntSmoke].bUse = false;
	}
}