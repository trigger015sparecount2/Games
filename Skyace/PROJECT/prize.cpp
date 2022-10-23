//--------------------------
//Author:�O��q��
//�v���C�Y�̏���(prize.cpp)
//--------------------------
#include "prize.h"
#include "aircraft.h"
#include "sound.h"

//�}�N����`
#define MAX_PRIZE (16) //�v���C�Y�̍ő吔
#define PRIZE_SIZE (20) //�v���C�Y�̃T�C�Y
//�v���C�Y�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	int nTime;        //�_�ŗp����
	D3DXCOLOR col;    //�F
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Prize;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePrize = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPrize = NULL; //���_�o�b�t�@�ւ̃|�C���^
Prize g_aPrize[MAX_PRIZE];

//����������
void InitPrize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPrize;
	pDevice = GetDevice();
	//�e�̏�����
	for (nCntPrize = 0; nCntPrize < MAX_PRIZE; nCntPrize++)
	{
		g_aPrize[nCntPrize].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPrize[nCntPrize].nTime = 0;
		g_aPrize[nCntPrize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPrize[nCntPrize].bUse = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Smark.png",
		&g_pTexturePrize);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PRIZE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPrize,
		NULL);
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPrize->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntPrize = 0; nCntPrize < MAX_PRIZE; nCntPrize++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPrize->Unlock();
}

//�e�̏I������
void UninitPrize(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePrize != NULL)
	{
		g_pTexturePrize->Release();
		g_pTexturePrize = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPrize != NULL)
	{
		g_pVtxBuffPrize->Release();
		g_pVtxBuffPrize = NULL;
	}
}

//�v���C�Y�̍X�V����
void UpdatePrize(void)
{
	int nCntPrize;
	VERTEX_2D *pVtx;
	g_pVtxBuffPrize->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntPrize = 0; nCntPrize < MAX_PRIZE; nCntPrize++)
	{
		if (g_aPrize[nCntPrize].bUse == true)
		{
			Aircraft *pAircraft;
			pAircraft = GetAircraft();
			g_aPrize[nCntPrize].nTime++;
			if (g_aPrize[nCntPrize].nTime % 10 == 0)
			{
				g_aPrize[nCntPrize].nTime = 0;
				if (g_aPrize[nCntPrize].col.b == 1.0f)
				{
					g_aPrize[nCntPrize].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
				}
				else
				{
					g_aPrize[nCntPrize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
			if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - PRIZE_SIZE <= g_aPrize[nCntPrize].pos.x && g_aPrize[nCntPrize].pos.x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + PRIZE_SIZE &&
				pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - PRIZE_SIZE <= g_aPrize[nCntPrize].pos.y && g_aPrize[nCntPrize].pos.y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + PRIZE_SIZE)
			{
				if (pAircraft->nSpecial < 6)
				{
					pAircraft->nSpecial++;
				}
				g_aPrize[nCntPrize].bUse = false;
				PlaySound(SOUND_LABEL_ITEM000);
				break;
			}
			g_aPrize[nCntPrize].pos.y += 1.0f;
			pVtx[0].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x - PRIZE_SIZE, g_aPrize[nCntPrize].pos.y - PRIZE_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x + PRIZE_SIZE, g_aPrize[nCntPrize].pos.y - PRIZE_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x - PRIZE_SIZE, g_aPrize[nCntPrize].pos.y + PRIZE_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x + PRIZE_SIZE, g_aPrize[nCntPrize].pos.y + PRIZE_SIZE, 0.0f);
			pVtx[0].col = g_aPrize[nCntPrize].col;
			pVtx[1].col = g_aPrize[nCntPrize].col;
			pVtx[2].col = g_aPrize[nCntPrize].col;
			pVtx[3].col = g_aPrize[nCntPrize].col;
			if (g_aPrize[nCntPrize].pos.y > 720 - PRIZE_SIZE)
			{
				g_aPrize[nCntPrize].bUse = false;
			}
			
		}
		pVtx += 4;
	}
	g_pVtxBuffPrize->Unlock();
}

//�`�揈��
void DrawPrize(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntPrize;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPrize, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntPrize = 0; nCntPrize < MAX_PRIZE; nCntPrize++)
	{
		if (g_aPrize[nCntPrize].bUse == true)
		{
			pDevice->SetTexture(0, g_pTexturePrize);    //�e�N�X�`���̐ݒ�
																					  //�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntPrize * 4,
				2);
		}
	}
}

//�v���C�Y�̐ݒ菈��
void SetPrize(D3DXVECTOR3 pos)
{
	int nCntPrize;
	VERTEX_2D *pVtx;
	g_pVtxBuffPrize->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntPrize = 0; nCntPrize < MAX_PRIZE; nCntPrize++)
	{
		if (g_aPrize[nCntPrize].bUse == false)
		{
			g_aPrize[nCntPrize].pos = pos;
			g_aPrize[nCntPrize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x - PRIZE_SIZE, g_aPrize[nCntPrize].pos.y - PRIZE_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x + PRIZE_SIZE, g_aPrize[nCntPrize].pos.y - PRIZE_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x - PRIZE_SIZE, g_aPrize[nCntPrize].pos.y + PRIZE_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPrize[nCntPrize].pos.x + PRIZE_SIZE, g_aPrize[nCntPrize].pos.y + PRIZE_SIZE, 0.0f);
			g_aPrize[nCntPrize].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffPrize->Unlock();
}

void ResetPrize(void)
{
	int nCntPrize;
	for (nCntPrize = 0; nCntPrize < MAX_PRIZE; nCntPrize++)
	{
		g_aPrize[nCntPrize].bUse = false;
	}
}