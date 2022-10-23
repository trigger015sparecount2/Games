//--------------------------
//Author:�O��q��
//�o���A�̏���(barrier.cpp)
//--------------------------
#include "barrier.h"
#include "aircraft.h"
#include "boss.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBarrier = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBarrier = NULL; //���_�o�b�t�@�ւ̃|�C���^
Barrier g_aBarrier[MAX_BARRIER];

//����������
void InitBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBarrier;
	//�o���A�̏�����
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		g_aBarrier[nCntBarrier].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBarrier[nCntBarrier].state = BARRIERSTATE_NORMAL;
		g_aBarrier[nCntBarrier].nLife = 0;
		g_aBarrier[nCntBarrier].bBlight = true;
		g_aBarrier[nCntBarrier].nClear = 0;
		g_aBarrier[nCntBarrier].fBig = 0.0f;
		g_aBarrier[nCntBarrier].nDTime = 0;
		g_aBarrier[nCntBarrier].nDClear = 0;
		g_aBarrier[nCntBarrier].ntype = 0;
		g_aBarrier[nCntBarrier].bUse = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/barrier.png",
		&g_pTextureBarrier);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BARRIER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBarrier,
		NULL);
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBarrier->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
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
	g_pVtxBuffBarrier->Unlock();
}

//�o���A�̏I������
void UninitBarrier(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBarrier != NULL)
	{
		g_pTextureBarrier->Release();
		g_pTextureBarrier = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBarrier != NULL)
	{
		g_pVtxBuffBarrier->Release();
		g_pVtxBuffBarrier = NULL;
	}
}

//�o���A�̍X�V����
void UpdateBarrier(void)
{
	int nCntBarrier;
	VERTEX_2D *pVtx;
	g_pVtxBuffBarrier->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		if (g_aBarrier[nCntBarrier].bUse == true)
		{
			switch (g_aBarrier[nCntBarrier].state)
			{
			case BARRIERSTATE_NORMAL:
				if (g_aBarrier[nCntBarrier].ntype == 0)
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 2 + g_aBarrier[nCntBarrier].nClear);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 2 + g_aBarrier[nCntBarrier].nClear);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 2 + g_aBarrier[nCntBarrier].nClear);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 2 + g_aBarrier[nCntBarrier].nClear);
				}
				break;
			case BARRIERSTATE_DAMAGE:
				g_aBarrier[nCntBarrier].nDTime--;
				g_aBarrier[nCntBarrier].nDClear--;
				if (g_aBarrier[nCntBarrier].nDTime <= 475)
				{
					if (g_aBarrier[nCntBarrier].ntype == 0)
					{
						g_aBarrier[nCntBarrier].state = BARRIERSTATE_NODAMAGE;
					}
					else
					{
						g_aBarrier[nCntBarrier].state = BARRIERSTATE_NORMAL;
					}
				}
				break;
			case BARRIERSTATE_NODAMAGE:
				g_aBarrier[nCntBarrier].nDTime--;
				g_aBarrier[nCntBarrier].nDClear--;
				if (g_aBarrier[nCntBarrier].nDTime > 140)
				{
					if (g_aBarrier[nCntBarrier].nDClear > 10)
					{
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					}
					else
					{
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						if (g_aBarrier[nCntBarrier].nDClear < 0)
						{
							g_aBarrier[nCntBarrier].nDClear = 20;
						}
					}
				}
				else
				{
					if (g_aBarrier[nCntBarrier].nDClear > 5)
					{
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					}
					else
					{
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
						if (g_aBarrier[nCntBarrier].nDClear < 0)
						{
							g_aBarrier[nCntBarrier].nDClear = 10;
						}
					}
				}
				if (g_aBarrier[nCntBarrier].nDTime <= 0)
				{
					g_aBarrier[nCntBarrier].state = BARRIERSTATE_NORMAL;
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aBarrier[nCntBarrier].nLife * 60 + g_aBarrier[nCntBarrier].nClear);
				}
				break;
			}
			if (g_aBarrier[nCntBarrier].ntype == 0)
			{
				Aircraft *pAircraft;
				pAircraft = GetAircraft();
				g_aBarrier[nCntBarrier].pos = pAircraft->pos;
			}
			else
			{
				Boss *pBoss;
				pBoss = GetBoss();
				int nCntBoss;
				for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++,pBoss++)
				{
					g_aBarrier[nCntBarrier].pos = pBoss->pos;
					break;
				}
			}
			if (g_aBarrier[nCntBarrier].bBlight == true)
			{
				g_aBarrier[nCntBarrier].nClear += 2;
				if (g_aBarrier[nCntBarrier].nClear >= 40)
				{
					g_aBarrier[nCntBarrier].bBlight = false;
				}
			}
			else
			{
				g_aBarrier[nCntBarrier].nClear -= 2;
				if (g_aBarrier[nCntBarrier].nClear <= 0)
				{
					g_aBarrier[nCntBarrier].bBlight = true;
				}
			}
			g_aBarrier[nCntBarrier].fBig += 0.05f;
			if (g_aBarrier[nCntBarrier].fBig >= 1.0f)
			{
				g_aBarrier[nCntBarrier].fBig = 1.0f;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x - (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y - (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x + (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y - (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x - (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y + (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x + (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y + (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
		}
		pVtx += 4;
	}
	g_pVtxBuffBarrier->Unlock();
}

//�`�揈��
void DrawBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	int nCntBarrier;
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBarrier, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureBarrier);    //�e�N�X�`���̐ݒ�
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		if (g_aBarrier[nCntBarrier].bUse == true)
		{
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBarrier * 4,
				2);
		}
	}
}

//�o���A�̐ݒ菈��
void SetBarrier(D3DXVECTOR3 pos, int nLife, int ntype)
{
	int nCntBarrier;
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		if (g_aBarrier[nCntBarrier].bUse == false)
		{
			g_aBarrier[nCntBarrier].pos = pos;
			g_aBarrier[nCntBarrier].fBig = 0.0f;
			g_aBarrier[nCntBarrier].bUse = true;
			g_aBarrier[nCntBarrier].bBlight = true;
			g_aBarrier[nCntBarrier].nLife = nLife;
			g_aBarrier[nCntBarrier].nClear = 0;
			g_aBarrier[nCntBarrier].nDTime = 0;
			g_aBarrier[nCntBarrier].nDClear = 0;
			g_aBarrier[nCntBarrier].ntype = ntype;
			g_aBarrier[nCntBarrier].state = BARRIERSTATE_NORMAL;
			VERTEX_2D *pVtx;
			g_pVtxBuffBarrier->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntBarrier * 4;
			pVtx[0].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x - (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y - (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x + (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y - (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x - (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y + (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBarrier[nCntBarrier].pos.x + (BARRIER_WIDTH / 2) * g_aBarrier[nCntBarrier].fBig, g_aBarrier[nCntBarrier].pos.y + (BARRIER_HEIGHT / 2) * g_aBarrier[nCntBarrier].fBig, 0.0f);
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			PlaySound(SOUND_LABEL_BARRIER000);
			g_pVtxBuffBarrier->Unlock();
			break;
		}
	}
}

Barrier *GetBarrier(void)
{
	return &g_aBarrier[0];
}

void HitBarrier(int nDamage, int nCntBarrier)
{
	if (g_aBarrier[nCntBarrier].bUse == true)
	{
		g_aBarrier[nCntBarrier].nLife -= nDamage;
		if (g_aBarrier[nCntBarrier].nLife <= 0)
		{
			if (g_aBarrier[nCntBarrier].ntype == 0)
			{
				Aircraft *pAircraft;
				pAircraft = GetAircraft();
				pAircraft->state = AIRCRAFTSTATE_NORMAL;
			}
			else
			{
				Boss * pBoss;
				pBoss = GetBoss();
				int nCntBoss;
				for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++,pBoss++)
				{
					if (pBoss->type == BOSS_XU_80)
					{
						pBoss->state = BOSSSTATE_NORMAL;
					}
				}
			}
			g_aBarrier[nCntBarrier].bUse = false;
		}
		g_aBarrier[nCntBarrier].nDTime = 480;
		g_aBarrier[nCntBarrier].nDClear = 20;
		g_aBarrier[nCntBarrier].state = BARRIERSTATE_DAMAGE;
		VERTEX_2D *pVtx;
		g_pVtxBuffBarrier->Lock(0, 0, (void **)&pVtx, 0);
		pVtx += nCntBarrier * 4;
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffBarrier->Unlock();
	}
}

void ResetBarrier(void)
{
	int nCntBarrier;
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		g_aBarrier[nCntBarrier].bUse = false;
	}
}