//--------------------------
//Author:�O��q��
//�{�X�̏���(boss.cpp)
//--------------------------
#include "boss.h"
#include "aircraft.h"
#include "barrier.h"
#include "ui.h"
#include "prize.h"
#include "sound.h"
#include "death.h"
#include "bullet.h"
#include "laser.h"
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBoss[4 * 2] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL; //���_�o�b�t�@�ւ̃|�C���^
Boss g_aBoss[MAX_BOSS]; //�G
bool g_bseagulldeath;

//����������
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBoss;
	pDevice = GetDevice();
	//�G�̏�����
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].type = BOSS_XU_44;
		g_aBoss[nCntBoss].nLife = 0;
		g_aBoss[nCntBoss].nfire = 0;
		g_aBoss[nCntBoss].nScore = 0;
		g_aBoss[nCntBoss].nTime = 0;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].nBulletTime = 0;
		g_aBoss[nCntBoss].nLaserTime = 0;
		g_aBoss[nCntBoss].fSmall = 0.0f;
		g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
		g_aBoss[nCntBoss].bUse = false;
		g_aBoss[nCntBoss].bMissile = false;
		g_aBoss[nCntBoss].bLeft = true;
		g_aBoss[nCntBoss].bUp = true;
		g_aBoss[nCntBoss].bBarrier = false;
	}
	g_bseagulldeath = false;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-44.png",
		&g_apTextureBoss[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/seagull.png",
		&g_apTextureBoss[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-80.png",
		&g_apTextureBoss[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/seagullengine.png",
		&g_apTextureBoss[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-44shadow.png",
		&g_apTextureBoss[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/seagullshadow.png",
		&g_apTextureBoss[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-80shadow.png",
		&g_apTextureBoss[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/seagullfire.png",
		&g_apTextureBoss[7]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOSS * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBoss = 0; nCntBoss < MAX_BOSS * 2; nCntBoss++)
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
		if (nCntBoss % 2 == 0)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		}
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
}

//�G�̏I������
void UninitBoss(void)
{
	int nCntBoss;
	//�e�N�X�`���̔j��
	for (nCntBoss = 0; nCntBoss < 4 * 2; nCntBoss++)
	{
		if (g_apTextureBoss[nCntBoss] != NULL)
		{
			g_apTextureBoss[nCntBoss]->Release();
			g_apTextureBoss[nCntBoss] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//�G�̍X�V����
void UpdateBoss(void)
{
	int nCntBoss;
	VERTEX_2D *pVtx;
	g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			Aircraft *pAircraft;
			pAircraft = GetAircraft();
			Barrier *pBarrier;
			pBarrier = GetBarrier();
			int nCntBarrier;
			D3DXVECTOR3 pos;
			switch (g_aBoss[nCntBoss].state)
			{
			case BOSSSTATE_NORMAL:
				break;
			case BOSSSTATE_DAMAGE:
				g_aBoss[nCntBoss].nCounterState--;
				if (g_aBoss[nCntBoss].nCounterState < 0)
				{
					g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			case BOSSSTATE_DEATH:
				g_aBoss[nCntBoss].nCounterState--;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{
					if (g_aBoss[nCntBoss].type == BOSS_XU_44 || g_aBoss[nCntBoss].type == BOSS_XU_80)
					{
						pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 45 + rand() % 90, g_aBoss[nCntBoss].pos.y - 60 + rand() % 120, 0.0f);
						SetDeath(pos, true);
					}
					else if (g_aBoss[nCntBoss].type == BOSS_SEAGULL)
					{
						pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 495 + rand() % 990, g_aBoss[nCntBoss].pos.y - 95 + rand() % 190, 0.0f);
						SetDeath(pos, true);
					}
					else if (g_aBoss[nCntBoss].type == BOSS_ENGINE)
					{
						if (nCntBoss < 3)
						{
							pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 35 + rand() % 70, g_aBoss[nCntBoss].pos.y - 35 + rand() % 70, 0.0f);
						}
						else
						{
							pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 20 + rand() % 40, g_aBoss[nCntBoss].pos.y - 20 + rand() % 40, 0.0f);
						}
						SetDeath(pos, false);
					}
					g_aBoss[nCntBoss].nCounterState = 10;
				}
				if (g_aBoss[nCntBoss].type == BOSS_XU_44 || g_aBoss[nCntBoss].type == BOSS_XU_80 || g_bseagulldeath == true)
				{
					g_aBoss[nCntBoss].fSmall -= 0.05f;
					g_aBoss[nCntBoss].nTime++;
					if (g_aBoss[nCntBoss].nTime % 2 == 0)
					{
						g_aBoss[nCntBoss].pos.x += 3.0f;
					}
					else
					{
						g_aBoss[nCntBoss].pos.x -= 3.0f;
					}
					if (g_aBoss[nCntBoss].nTime >= 600)
					{
						g_aBoss[nCntBoss].pos.y += 3.0f;
					}
					if (g_aBoss[nCntBoss].type == BOSS_XU_44 || g_aBoss[nCntBoss].type == BOSS_XU_80)
					{
						if (g_aBoss[nCntBoss].pos.y >= 785.0f)
						{
							g_aBoss[nCntBoss].bUse = false;
							if (g_aBoss[nCntBoss].type == BOSS_XU_80)
							{
								SetFade(MODE_RESULT, true);
							}
							else
							{
								SetFade(MODE_RESULT, false);
							}
							StopSound();
						}
					}
					else
					{
						if (g_aBoss[nCntBoss].pos.y >= 920.0f)
						{
							g_aBoss[nCntBoss].bUse = false;
							SetFade(MODE_GAME, false);
							StopSound();
						}
					}
				}
				break;
			case BOSSSTATE_BARRIER:
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;
			}
			if (g_aBoss[nCntBoss].nTime <= 500)
			{
				g_aBoss[nCntBoss].pos.y += 0.5f;
				g_aBoss[nCntBoss].nTime++;
			}
			else if (g_aBoss[nCntBoss].type == BOSS_XU_44 || g_aBoss[nCntBoss].type == BOSS_XU_80)
			{
				if (g_aBoss[nCntBoss].state != BOSSSTATE_DEATH)
				{
					g_aBoss[nCntBoss].nBulletTime++;
					g_aBoss[nCntBoss].nLaserTime++;
					if (g_aBoss[nCntBoss].bLeft == true)
					{
						g_aBoss[nCntBoss].pos.x -= 1.5f;
						if (g_aBoss[nCntBoss].pos.x <= 50.0f)
						{
							g_aBoss[nCntBoss].bLeft = false;
						}
					}
					else
					{
						g_aBoss[nCntBoss].pos.x += 1.5f;
						if (g_aBoss[nCntBoss].pos.x >= 1230.0f)
						{
							g_aBoss[nCntBoss].bLeft = true;
						}
					}
					if (g_aBoss[nCntBoss].bUp == true)
					{
						g_aBoss[nCntBoss].pos.y -= 0.5f;
						if (g_aBoss[nCntBoss].pos.y <= 65.0f)
						{
							g_aBoss[nCntBoss].bUp = false;
						}
					}
					else
					{
						g_aBoss[nCntBoss].pos.y += 0.5f;
						if (g_aBoss[nCntBoss].pos.y >= 150.0f)
						{
							g_aBoss[nCntBoss].bUp = true;
						}
					}
					if (g_aBoss[nCntBoss].nBulletTime >= 120 && g_aBoss[nCntBoss].nBulletTime % 12 == 0)
					{
						if (g_aBoss[nCntBoss].bLeft == true)
						{
							SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(-2.0f, 9.0f, 0.0f), 2, false);
						}
						else
						{
							SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(2.0f, 9.0f, 0.0f), 2, false);
						}
						if (g_aBoss[nCntBoss].nBulletTime >= 140)
						{
							g_aBoss[nCntBoss].nBulletTime = -120 - (rand() % 30);
						}
					}
					if (g_aBoss[nCntBoss].nLaserTime >= 900)
					{
						if(g_aBoss[nCntBoss].type == BOSS_XU_80)
						SetLaser(g_aBoss[nCntBoss].pos, 1);
						g_aBoss[nCntBoss].nLaserTime = 0;
					}
				}
			}
			else if (g_aBoss[nCntBoss].type == BOSS_SEAGULL)
			{
				if (g_aBoss[nCntBoss].state != BOSSSTATE_DEATH)
				{
					g_aBoss[nCntBoss].nBulletTime++;
					g_aBoss[nCntBoss].nLaserTime++;
					if (g_aBoss[nCntBoss].nBulletTime >= 40)
					{
						pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (rand() % 7 - 3) * 130, g_aBoss[nCntBoss].pos.y + 80, 0.0f);
						SetBullet(pos, D3DXVECTOR3(0.0f, 7.0f, 0.0f), 2, false);
						g_aBoss[nCntBoss].nBulletTime = 0;
					}
					if (g_aBoss[nCntBoss].nLaserTime >= 900)
					{
						SetLaser(g_aBoss[nCntBoss].pos, 1);
						g_aBoss[nCntBoss].nLaserTime = 0;
					}
				}
			}
			if (g_aBoss[nCntBoss].type == BOSS_XU_44 || g_aBoss[nCntBoss].type == BOSS_XU_80)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (50 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (65 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (50 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (65 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (50 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (65 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (50 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (65 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx += 4;
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (80 + g_aBoss[nCntBoss].fSmall) - 15, g_aBoss[nCntBoss].pos.y + (80 + g_aBoss[nCntBoss].fSmall) - 20, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (80 + g_aBoss[nCntBoss].fSmall) + 15, g_aBoss[nCntBoss].pos.y + (80 + g_aBoss[nCntBoss].fSmall) - 20, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (80 + g_aBoss[nCntBoss].fSmall) - 15, g_aBoss[nCntBoss].pos.y + (80 + g_aBoss[nCntBoss].fSmall) + 20, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (80 + g_aBoss[nCntBoss].fSmall) + 15, g_aBoss[nCntBoss].pos.y + (80 + g_aBoss[nCntBoss].fSmall) + 20, 0.0f);
			}
			else if (g_aBoss[nCntBoss].type == BOSS_SEAGULL)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (500 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (110 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (500 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (110 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (500 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (110 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (500 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (110 + g_aBoss[nCntBoss].fSmall), 0.0f);
				pVtx += 4;
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (300 + g_aBoss[nCntBoss].fSmall) - 200, g_aBoss[nCntBoss].pos.y + (300 + g_aBoss[nCntBoss].fSmall) - 22, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (300 + g_aBoss[nCntBoss].fSmall) + 200, g_aBoss[nCntBoss].pos.y + (300 + g_aBoss[nCntBoss].fSmall) - 22, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (300 + g_aBoss[nCntBoss].fSmall) - 200, g_aBoss[nCntBoss].pos.y + (300 + g_aBoss[nCntBoss].fSmall) + 22, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (300 + g_aBoss[nCntBoss].fSmall) + 200, g_aBoss[nCntBoss].pos.y + (300 + g_aBoss[nCntBoss].fSmall) + 22, 0.0f);
			}
			else if (g_aBoss[nCntBoss].type == BOSS_ENGINE)
			{
				g_aBoss[nCntBoss].nfire++;
				if (nCntBoss < 3)
				{
					pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (40 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (40 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (40 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (40 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (40 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (40 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (40 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (40 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx += 4;
					if (g_aBoss[nCntBoss].state != BOSSSTATE_DEATH)
					{
						if (g_aBoss[nCntBoss].nfire < 5)
						{
							pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 40, g_aBoss[nCntBoss].pos.y + 90 - 50, 0.0f);
							pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 40, g_aBoss[nCntBoss].pos.y + 90 - 50, 0.0f);
							pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 40, g_aBoss[nCntBoss].pos.y + 90 + 50, 0.0f);
							pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 40, g_aBoss[nCntBoss].pos.y + 90 + 50, 0.0f);
						}
						else
						{
							pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 50, g_aBoss[nCntBoss].pos.y + 90 - 50, 0.0f);
							pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50, g_aBoss[nCntBoss].pos.y + 90 - 50, 0.0f);
							pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 50, g_aBoss[nCntBoss].pos.y + 90 + 65, 0.0f);
							pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50, g_aBoss[nCntBoss].pos.y + 90 + 65, 0.0f);
						}
					}
				}
				else
				{
					pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (25 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (25 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (25 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y - (25 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - (25 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (25 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + (25 + g_aBoss[nCntBoss].fSmall), g_aBoss[nCntBoss].pos.y + (25 + g_aBoss[nCntBoss].fSmall), 0.0f);
					pVtx += 4;
					if (g_aBoss[nCntBoss].state != BOSSSTATE_DEATH)
					{
						if (g_aBoss[nCntBoss].nfire < 5)
						{
							pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 25, g_aBoss[nCntBoss].pos.y + 65 - 40, 0.0f);
							pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 25, g_aBoss[nCntBoss].pos.y + 65 - 40, 0.0f);
							pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 25, g_aBoss[nCntBoss].pos.y + 65 + 40, 0.0f);
							pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 25, g_aBoss[nCntBoss].pos.y + 65 + 40, 0.0f);
						}
						else
						{
							pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 30, g_aBoss[nCntBoss].pos.y + 65 - 40, 0.0f);
							pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 30, g_aBoss[nCntBoss].pos.y + 65 - 40, 0.0f);
							pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 30, g_aBoss[nCntBoss].pos.y + 65 + 50, 0.0f);
							pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 30, g_aBoss[nCntBoss].pos.y + 65 + 50, 0.0f);
						}
					}
				}
				if (g_aBoss[nCntBoss].nfire == 10)
				{
					g_aBoss[nCntBoss].nfire = 0;
				}
			}
			for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++, pBarrier++)
			{
				if (pBarrier->bUse == true)
				{
					//�o���A�ɓG���Ԃ������Ƃ�
					if (g_aBoss[nCntBoss].type == BOSS_XU_44 || g_aBoss[nCntBoss].type == BOSS_XU_80)
					{
						if (pBarrier->pos.x - (BARRIER_WIDTH / 2) - 50 <= g_aBoss[nCntBoss].pos.x && g_aBoss[nCntBoss].pos.x <= pBarrier->pos.x + (BARRIER_WIDTH / 2) + 50 &&
							pBarrier->pos.y - (BARRIER_HEIGHT / 2) - 65 <= g_aBoss[nCntBoss].pos.y && g_aBoss[nCntBoss].pos.y <= pBarrier->pos.y + (BARRIER_HEIGHT / 2) + 65)
						{
							if (pBarrier->state == BARRIERSTATE_NORMAL && g_aBoss[nCntBoss].state != BOSSSTATE_DEATH && pBarrier->ntype == 0)
							{
								HitBarrier(1, nCntBarrier);
								HitBoss(nCntBoss, 3, true);
							}
						}
					}
					else if (g_aBoss[nCntBoss].type == BOSS_ENGINE && g_aBoss[nCntBoss].state != BOSSSTATE_DEATH && pBarrier->ntype == 0)
					{
						if (nCntBoss < 3)
						{
							if (pBarrier->pos.x - (BARRIER_WIDTH / 2) - 40 <= g_aBoss[nCntBoss].pos.x && g_aBoss[nCntBoss].pos.x <= pBarrier->pos.x + (BARRIER_WIDTH / 2) + 40 &&
								pBarrier->pos.y - (BARRIER_HEIGHT / 2) - 40 <= g_aBoss[nCntBoss].pos.y && g_aBoss[nCntBoss].pos.y <= pBarrier->pos.y + (BARRIER_HEIGHT / 2) + 40)
							{
								if (pBarrier->state == BARRIERSTATE_NORMAL && g_aBoss[nCntBoss].state != BOSSSTATE_DEATH && pBarrier->ntype == 0)
								{
									HitBarrier(1, nCntBarrier);
									HitBoss(nCntBoss, 3, true);
								}
							}
						}
						else if (pBarrier->pos.x - (BARRIER_WIDTH / 2) - 25 <= g_aBoss[nCntBoss].pos.x && g_aBoss[nCntBoss].pos.x <= pBarrier->pos.x + (BARRIER_WIDTH / 2) + 25 &&
							     pBarrier->pos.y - (BARRIER_HEIGHT / 2) - 25 <= g_aBoss[nCntBoss].pos.y && g_aBoss[nCntBoss].pos.y <= pBarrier->pos.y + (BARRIER_HEIGHT / 2) + 25)
						{
							if (pBarrier->state == BARRIERSTATE_NORMAL && g_aBoss[nCntBoss].state != BOSSSTATE_DEATH && pBarrier->ntype == 0)
							{
								HitBarrier(1, nCntBarrier);
								HitBoss(nCntBoss, 3, true);
							}
						}
					}
				}
			}
			//���@�ɓG���Ԃ������Ƃ�
			if (g_aBoss[nCntBoss].type == BOSS_XU_44 || g_aBoss[nCntBoss].type == BOSS_XU_80)
			{
				if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - 50 <= g_aBoss[nCntBoss].pos.x && g_aBoss[nCntBoss].pos.x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + 50 &&
					pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - 65 <= g_aBoss[nCntBoss].pos.y && g_aBoss[nCntBoss].pos.y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + 65)
				{
					if (pAircraft->state == AIRCRAFTSTATE_NORMAL && g_aBoss[nCntBoss].state != BOSSSTATE_DEATH)
					{
						HitAircraft();
						HitBoss(nCntBoss, 1, false);
					}
				}
			}
			else if (g_aBoss[nCntBoss].type == BOSS_ENGINE && g_aBoss[nCntBoss].state != BOSSSTATE_DEATH)
			{
				if (nCntBoss < 3)
				{
					if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - 40 <= g_aBoss[nCntBoss].pos.x && g_aBoss[nCntBoss].pos.x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + 40 &&
						pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - 40 <= g_aBoss[nCntBoss].pos.y && g_aBoss[nCntBoss].pos.y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + 40)
					{
						if (pAircraft->state == AIRCRAFTSTATE_NORMAL)
						{
							HitAircraft();
							HitBoss(nCntBoss, 1, false);
						}
					}
				}
				else if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - 25 <= g_aBoss[nCntBoss].pos.x && g_aBoss[nCntBoss].pos.x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + 25 &&
						 pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - 25 <= g_aBoss[nCntBoss].pos.y && g_aBoss[nCntBoss].pos.y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + 25)
				{
					if (pAircraft->state == AIRCRAFTSTATE_NORMAL)
					{
						HitAircraft();
						HitBoss(nCntBoss, 1, false);
					}
				}
			}
			pVtx += 4;
		}
		else
		{
			pVtx += 8;
		}
	}
	g_pVtxBuffBoss->Unlock();
}

//�`�揈��
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntBoss;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].type]); //�e�N�X�`���̐ݒ�
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBoss * 8,
				2);
			if (g_aBoss[nCntBoss].type == BOSS_ENGINE && g_aBoss[nCntBoss].state != BOSSSTATE_DEATH || g_aBoss[nCntBoss].type != BOSS_ENGINE)
			{
				pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].type + MAX_BOSS_TYPE]); //�e�N�X�`���̐ݒ�
				//�|���S���`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntBoss * 8 + 4,
					2);
			}
		}
	}
}

//�G�̐ݒ菈��
void SetBoss(D3DXVECTOR3 pos, BOSSTYPE bosstype)
{
	int nCntBoss = 0;
	VERTEX_2D *pVtx;
	g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);
	g_aBoss[nCntBoss].pos = pos;
	if (bosstype == BOSS_XU_44 || bosstype == BOSS_XU_80)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 50, g_aBoss[nCntBoss].pos.y - 65, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50, g_aBoss[nCntBoss].pos.y - 65, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 50, g_aBoss[nCntBoss].pos.y + 65, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50, g_aBoss[nCntBoss].pos.y + 65, 0.0f);
	}
	else if (bosstype == BOSS_SEAGULL)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 500, g_aBoss[nCntBoss].pos.y - 100, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 500, g_aBoss[nCntBoss].pos.y - 100, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 500, g_aBoss[nCntBoss].pos.y + 100, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 500, g_aBoss[nCntBoss].pos.y + 100, 0.0f);
	}
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_aBoss[nCntBoss].type = bosstype;
	g_aBoss[nCntBoss].nfire = 0;
	g_aBoss[nCntBoss].nTime = 0;
	g_aBoss[nCntBoss].nCounterState = 0;
	g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
	g_aBoss[nCntBoss].fSmall = 0.0f;
	g_aBoss[nCntBoss].bUse = true;
	g_aBoss[nCntBoss].bMissile = false;
	g_aBoss[nCntBoss].bLeft = true;
	g_aBoss[nCntBoss].bUp = true;
	switch (bosstype)
	{
	case BOSS_XU_44:
		g_aBoss[nCntBoss].nScore = 3000;
		g_aBoss[nCntBoss].nLife = 450;
		break;
	case BOSS_SEAGULL:
		g_aBoss[nCntBoss].nScore = 0;
		g_aBoss[nCntBoss].nLife = 8;
		break;
	case BOSS_XU_80:
		g_aBoss[nCntBoss].nScore = 10000;
		g_aBoss[nCntBoss].nLife = 500;
		break;
	}
	pVtx += 4;
	if (bosstype == BOSS_XU_44 || bosstype == BOSS_XU_80)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 80 - 50, g_aBoss[nCntBoss].pos.y + 80 - 65, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 80 + 50, g_aBoss[nCntBoss].pos.y + 80 - 65, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 80 - 50, g_aBoss[nCntBoss].pos.y + 80 + 65, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 80 + 50, g_aBoss[nCntBoss].pos.y + 80 + 65, 0.0f);
	}
	else if (bosstype == BOSS_SEAGULL)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 300 - 200, g_aBoss[nCntBoss].pos.y + 300 - 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 300 + 200, g_aBoss[nCntBoss].pos.y + 300 - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 300 - 200, g_aBoss[nCntBoss].pos.y + 300 + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 300 + 200, g_aBoss[nCntBoss].pos.y + 300 + 50, 0.0f);
	}
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	if (bosstype == BOSS_SEAGULL)
	{
		for (nCntBoss = 1; nCntBoss < 9; nCntBoss++)
		{
			pVtx += 4;
			switch (nCntBoss)
			{
			case 1:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x - 60, pos.y + 90, pos.z);
				break;
			case 2:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x + 60, pos.y + 90, pos.z);
				break;
			case 3:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x - 200, pos.y + 90, pos.z);
				break;
			case 4:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x + 200, pos.y + 90, pos.z);
				break;
			case 5:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x - 340, pos.y + 90, pos.z);
				break;
			case 6:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x + 340, pos.y + 90, pos.z);
				break;
			case 7:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x - 460, pos.y + 90, pos.z);
				break;
			case 8:
				g_aBoss[nCntBoss].pos = D3DXVECTOR3(pos.x + 460, pos.y + 90, pos.z);
				break;
			}
			if(nCntBoss < 3)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 40, g_aBoss[nCntBoss].pos.y - 40, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 40, g_aBoss[nCntBoss].pos.y - 40, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 40, g_aBoss[nCntBoss].pos.y + 40, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 40, g_aBoss[nCntBoss].pos.y + 40, 0.0f);
			}
			else
			{
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 25, g_aBoss[nCntBoss].pos.y - 25, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 25, g_aBoss[nCntBoss].pos.y - 25, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 25, g_aBoss[nCntBoss].pos.y + 25, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 25, g_aBoss[nCntBoss].pos.y + 25, 0.0f);
			}
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_aBoss[nCntBoss].type = BOSS_ENGINE;
			g_aBoss[nCntBoss].nfire = 0;
			g_aBoss[nCntBoss].nCounterState = 0;
			g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
			g_aBoss[nCntBoss].bUse = true;
			g_aBoss[nCntBoss].bMissile = false;
			g_aBoss[nCntBoss].bLeft = true;
			g_aBoss[nCntBoss].bUp = true;
			g_aBoss[nCntBoss].nBulletTime = 0;
			g_aBoss[nCntBoss].nLaserTime = 0;
			g_aBoss[nCntBoss].nScore = 900;
			g_aBoss[nCntBoss].nLife = 80;
			g_aBoss[nCntBoss].fSmall = 0.0f;
			g_aBoss[nCntBoss].nTime = 0;
			g_aBoss[nCntBoss].bBarrier = false;
			pVtx += 4;
			if (nCntBoss < 3)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 40, g_aBoss[nCntBoss].pos.y + 90 - 50, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 40, g_aBoss[nCntBoss].pos.y + 90 - 50, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 40, g_aBoss[nCntBoss].pos.y + 90 + 50, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 40, g_aBoss[nCntBoss].pos.y + 90 + 50, 0.0f);
			}
			else
			{
				pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 25, g_aBoss[nCntBoss].pos.y + 65 - 40, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 25, g_aBoss[nCntBoss].pos.y + 65 - 40, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - 25, g_aBoss[nCntBoss].pos.y + 65 + 40, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 25, g_aBoss[nCntBoss].pos.y + 65 + 40, 0.0f);
			}
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		}
	}
	g_pVtxBuffBoss->Unlock();
}

//�G�̎擾
Boss *GetBoss(void)
{
	return &g_aBoss[0];
}

//�G�̃_���[�W����
void HitBoss(int nCntBoss, int nDamage, bool bSpecial)
{
	g_aBoss[nCntBoss].nLife -= nDamage;
	if (g_aBoss[nCntBoss].nLife <= 0)
	{
		SetDeath(g_aBoss[nCntBoss].pos, true);
		if (g_aBoss[nCntBoss].type == BOSS_XU_44)
		{
			SetPrize(g_aBoss[nCntBoss].pos);
		}
		else
		{
			if (g_aBoss[nCntBoss].type == BOSS_ENGINE)
			{
				int nCntBoss2;
				for (nCntBoss2 = 0; nCntBoss2 < MAX_BOSS; nCntBoss2++)
				{
					if (g_aBoss[nCntBoss2].type == BOSS_SEAGULL)
					{
						g_aBoss[nCntBoss2].nLife--;
						break;
					}
				}
				if (g_aBoss[nCntBoss2].nLife <= 0)
				{
					SetDeath(g_aBoss[nCntBoss2].pos, true);
					g_aBoss[nCntBoss2].state = BOSSSTATE_DEATH;
					SetPrize(g_aBoss[nCntBoss2].pos);
					g_bseagulldeath = true;
				}
			 }
		}
		g_aBoss[nCntBoss].state = BOSSSTATE_DEATH;
		g_aBoss[nCntBoss].nCounterState = 10;
		if (bSpecial == true)
		{
			AddScore(g_aBoss[nCntBoss].nScore * 2);
		}
		else
		{
			AddScore(g_aBoss[nCntBoss].nScore);
		}
		AddKill();
	}
	else
	{
		g_aBoss[nCntBoss].state = BOSSSTATE_DAMAGE;
		g_aBoss[nCntBoss].nCounterState = 5;
		if (bSpecial == true)
		{
			AddScore(g_aBoss[nCntBoss].nScore / 50);
		}
		else
		{
			AddScore(g_aBoss[nCntBoss].nScore / 100);
		}
		if (g_aBoss[nCntBoss].type == BOSS_XU_80 && g_aBoss[nCntBoss].bBarrier == false && g_aBoss[nCntBoss].nLife <= 250)
		{
			SetBarrier(g_aBoss[nCntBoss].pos, 90, 1);
			g_aBoss[nCntBoss].bBarrier = true;
			g_aBoss[nCntBoss].state = BOSSSTATE_BARRIER;
		}
		VERTEX_2D *pVtx;
		g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);
		pVtx += nCntBoss * 8;
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffBoss->Unlock();
	}
}

void ResetBoss(void)
{
	int nCntBoss;
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].bUse = false;
	}
}