//--------------------------
//Author:�O��q��
//�e�ۂ⃌�[���K���̏���(bullet.cpp)
//--------------------------
#include "bullet.h"
#include "enemy.h"
#include "boss.h"
#include "aircraft.h"
#include "barrier.h"
#include "sound.h"

//�}�N����`
#define MAX_BULLET (128)   //�e�̍ő吔
#define BULLET_WIDTH (12)  //�e�̕�
#define BULLET_HEIGHT (40) //�e�̍���
//�e�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 move; //�ړ���
	int ntype;        //�e�ۂ̎��
	bool bUav;        //UAV�����������ۂ�
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Bullet;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet[3] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];

//����������
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	pDevice = GetDevice();
	//�e�̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].ntype = 0;
		g_aBullet[nCntBullet].bUav = false;
		g_aBullet[nCntBullet].bUse = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/bluebullet.png",
		&g_pTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/railgunbullet.png",
		&g_pTextureBullet[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/redbullet.png",
		&g_pTextureBullet[2]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();
}

//�e�̏I������
void UninitBullet(void)
{
	int nCntBullet;
	//�e�N�X�`���̔j��
	for (nCntBullet = 0; nCntBullet < 2; nCntBullet++)
	{
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//�e�̍X�V����
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			int nCntEnemy;
			int nCntBoss;
			int nCntBarrier;
			Enemy *pEnemy;
			Boss *pBoss;
			Aircraft *pAircraft;
			Barrier *pBarrier;
			pEnemy = GetEnemy();
			pBoss = GetBoss();
			pAircraft = GetAircraft();
			pBarrier = GetBarrier();
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
			if (g_aBullet[nCntBullet].pos.y <= -(BULLET_HEIGHT / 2) || g_aBullet[nCntBullet].pos.y >= 740.0f)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{
					if (pEnemy->pos.x - (ENEMY_BLOCK / 2) - (BULLET_WIDTH / 2) <= g_aBullet[nCntBullet].pos.x && g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + (ENEMY_BLOCK / 2) + (BULLET_WIDTH / 2) &&
						pEnemy->pos.y - (ENEMY_BLOCK / 2) - (BULLET_HEIGHT / 2) <= g_aBullet[nCntBullet].pos.y && g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + (ENEMY_BLOCK / 2) + (BULLET_HEIGHT / 2))
					{
						if (g_aBullet[nCntBullet].ntype == 0)
						{
							HitEnemy(nCntEnemy, 1, g_aBullet[nCntBullet].bUav);
							g_aBullet[nCntBullet].bUse = false;
						}
						else if(g_aBullet[nCntBullet].ntype == 1)
						{
							HitEnemy(nCntEnemy, 50, true);
						}
					}
				}
			}
			for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++, pBoss++)
			{
				if (pBoss->bUse == true && pBoss->state != BOSSSTATE_DEATH && pBoss->state != BOSSSTATE_BARRIER)
				{
					if (pBoss->type == BOSS_XU_44 || pBoss->type == BOSS_XU_80)
					{
						if (pBoss->pos.x - 50 - (BULLET_WIDTH / 2) <= g_aBullet[nCntBullet].pos.x && g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + 50 + (BULLET_WIDTH / 2) &&
							pBoss->pos.y - 65 - (BULLET_HEIGHT / 2) <= g_aBullet[nCntBullet].pos.y && g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + 65 + (BULLET_HEIGHT / 2))
						{
							if (g_aBullet[nCntBullet].ntype == 0)
							{
								HitBoss(nCntBoss, 1, g_aBullet[nCntBullet].bUav);
								g_aBullet[nCntBullet].bUse = false;
							}
							else if (g_aBullet[nCntBullet].ntype == 1)
							{
								HitBoss(nCntBoss, 35, true);
							}
						}
					}
					else if (pBoss->type == BOSS_ENGINE)
					{
						if (pBoss->pos.x - 35 - (BULLET_WIDTH / 2) <= g_aBullet[nCntBullet].pos.x && g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + 35 + (BULLET_WIDTH / 2) &&
							pBoss->pos.y - 35 - (BULLET_HEIGHT / 2) <= g_aBullet[nCntBullet].pos.y && g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + 35 + (BULLET_HEIGHT / 2))
						{
							if (g_aBullet[nCntBullet].ntype == 0)
							{
								HitBoss(nCntBoss, 1, g_aBullet[nCntBullet].bUav);
								g_aBullet[nCntBullet].bUse = false;
							}
							else if (g_aBullet[nCntBullet].ntype == 1)
							{
								HitBoss(nCntBoss, 35, true);
							}
						}
					}
				}
			}
			for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++, pBarrier++)
			{
				if (pBarrier->bUse == true)
				{
					if (pBarrier->pos.x - (BARRIER_WIDTH / 2) - (BULLET_WIDTH / 2) <= g_aBullet[nCntBullet].pos.x && g_aBullet[nCntBullet].pos.x <= pBarrier->pos.x + (BARRIER_WIDTH / 2) + (BULLET_WIDTH / 2) &&
						pBarrier->pos.y - (BARRIER_HEIGHT / 2) - (BULLET_HEIGHT / 2) <= g_aBullet[nCntBullet].pos.y && g_aBullet[nCntBullet].pos.y <= pBarrier->pos.y + (BARRIER_HEIGHT / 2) + (BULLET_HEIGHT / 2))
					{
						if (g_aBullet[nCntBullet].ntype == 2 && pBarrier->state == BARRIERSTATE_NORMAL && pBarrier->ntype == 0)
						{
							HitBarrier(1, nCntBarrier);
							g_aBullet[nCntBullet].bUse = false;
						}
						else if (pBarrier->ntype == 1)
						{
							if (g_aBullet[nCntBullet].ntype == 0)
							{
								HitBarrier(1, nCntBarrier);
								g_aBullet[nCntBullet].bUse = false;
							}
							else if(g_aBullet[nCntBullet].ntype == 1)
							{
								HitBarrier(10, nCntBarrier);
							}
						}
					}
				}
			}
			if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - (BULLET_WIDTH / 2) <= g_aBullet[nCntBullet].pos.x && g_aBullet[nCntBullet].pos.x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + (BULLET_WIDTH / 2) &&
				pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - (BULLET_HEIGHT / 2) <= g_aBullet[nCntBullet].pos.y && g_aBullet[nCntBullet].pos.y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + (BULLET_HEIGHT / 2))
			{
				if (g_aBullet[nCntBullet].ntype == 2 && pAircraft->state == AIRCRAFTSTATE_NORMAL)
				{
					HitAircraft();
					g_aBullet[nCntBullet].bUse = false;
				}
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}

//�`�揈��
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntBullet;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBullet[g_aBullet[nCntBullet].ntype]);    //�e�N�X�`���̐ݒ�
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,
				2);
		}
	}
}

//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int ntype, bool bUav)
{
	int nCntBullet;
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].bUav = bUav;
			g_aBullet[nCntBullet].ntype = ntype;
			if (ntype != 1)
			{
				PlaySound(SOUND_LABEL_SHOT000);
			}
			else
			{
				PlaySound(SOUND_LABEL_RAILGUN000);
			}
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}

void ResetBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].bUse = false;
	}
}