//--------------------------
//Author:�O��q��
//�G�̏���(enemy.cpp)
//--------------------------
#include "enemy.h"
#include "aircraft.h"
#include "barrier.h"
#include "ui.h"
#include "prize.h"
#include "sound.h"
#include "death.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[4 * 2] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL; //���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY]; //�G

//����������
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;
	pDevice = GetDevice();

	//�G�̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		int nRoll;
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].type = ENEMY_XU_5;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].nScore = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].bPrize = false;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].bMissile = false;
		for (nRoll = 0; nRoll < 4; nRoll++)
		{
			g_aEnemy[nCntEnemy].fRoll[nRoll] = 0.0f;
		}
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-5.png",
		&g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-17.png",
		&g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-37.png",
		&g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-57.png",
		&g_apTextureEnemy[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-5shadow.png",
		&g_apTextureEnemy[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-17shadow.png",
		&g_apTextureEnemy[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-37shadow.png",
		&g_apTextureEnemy[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/XU-57shadow.png",
		&g_apTextureEnemy[7]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY * 2; nCntEnemy++)
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
		if (nCntEnemy % 2 == 0)
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
	g_pVtxBuffEnemy->Unlock();
}

//�G�̏I������
void UninitEnemy(void)
{
	int nCntEnemy;
	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < 4 * 2; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//�G�̍X�V����
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�g���Ă�
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			Aircraft *pAircraft;
			pAircraft = GetAircraft();
			Barrier *pBarrier;
			pBarrier = GetBarrier();
			int nCntBarrier;

			//��Ԃɂ���ď����𕪂���
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:	//�ʏ�
				break;
			case ENEMYSTATE_DAMAGE:	//�_���\�W�������
				//�J�E���g�i�߂�
				g_aEnemy[nCntEnemy].nCounterState--;

				//�J�E���g�i�񂾂�A�F���ɖ߂�
				if (g_aEnemy[nCntEnemy].nCounterState < 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}

			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;
			//�G����ʊO�ɍs�����Ƃ�
			if (g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) < 0.0f || g_aEnemy[nCntEnemy].pos.x - (ENEMY_BLOCK / 2.0f) > 1280.0f ||
				g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) < 0.0f || g_aEnemy[nCntEnemy].pos.y - (ENEMY_BLOCK / 2.0f) > 720.0f)
			{
				//����
				g_aEnemy[nCntEnemy].bUse = false;
			}

			//�ʒu�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), 0.0f);
			pVtx += 4;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), 0.0f);
			
			for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
			{
				//�o���A�g���Ă�
				if (pBarrier->bUse == true)
				{
					//�o���A�ɓG���Ԃ������Ƃ�
					if (pBarrier->pos.x - (BARRIER_WIDTH / 2.0f) - (ENEMY_BLOCK / 2.0f) <= g_aEnemy[nCntEnemy].pos.x && 
						g_aEnemy[nCntEnemy].pos.x <= pBarrier->pos.x + (BARRIER_WIDTH / 2.0f) + (ENEMY_BLOCK / 2.0f) &&
						pBarrier->pos.y - (BARRIER_HEIGHT / 2.0f) - (ENEMY_BLOCK / 2.0f) <= g_aEnemy[nCntEnemy].pos.y &&
						g_aEnemy[nCntEnemy].pos.y <= pBarrier->pos.y + (BARRIER_HEIGHT / 2.0f) + (ENEMY_BLOCK / 2.0f))
					{
						//�o���A�̏�ԃm�[�}���A���@�̃o���A
						if (pBarrier->state == BARRIERSTATE_NORMAL && pBarrier->ntype == 0)
						{
							//�o���A�A�G�Ƀ_���[�W
							HitBarrier(1, nCntBarrier);
							HitEnemy(nCntEnemy, 3, true);
						}
					}
				}
			}

			//���@���G�ɂԂ������Ƃ�
			if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2.0f) - (ENEMY_BLOCK / 2.0f) <= g_aEnemy[nCntEnemy].pos.x &&
				g_aEnemy[nCntEnemy].pos.x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2.0f) + (ENEMY_BLOCK / 2.0f) &&
				pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2.0f) - (ENEMY_BLOCK / 2.0f) <= g_aEnemy[nCntEnemy].pos.y && 
				g_aEnemy[nCntEnemy].pos.y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2.0f) + (ENEMY_BLOCK / 2.0f))
			{
				//���@�̏�ԃm�[�}��
				if (pAircraft->state == AIRCRAFTSTATE_NORMAL)
				{
					//���@�A�G�Ƀ_���[�W
					HitAircraft();
					HitEnemy(nCntEnemy, 1, false);
				}
			}
			pVtx += 4;
		}
		else
		{
			pVtx += 8;
		}
	}
	g_pVtxBuffEnemy->Unlock();
}

//�`�揈��
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntEnemy;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�g�p���̂ݕ`��
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].type]); //�e�N�X�`���̐ݒ�
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 8,
				2);
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].type + MAX_ENEMY_TYPE]); //�e�N�X�`���̐ݒ�
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 8 + 4,
				2);
		}
	}
}

//�G�̐ݒ菈��
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE enemytype, D3DXVECTOR3 move, bool bPrize, WAY way)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�g���ĂȂ�
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�X�e�[�^�X�ݒ�
			VERTEX_2D *pVtx;
			g_pVtxBuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntEnemy * 8;
			g_aEnemy[nCntEnemy].pos = pos;
			switch (way)
			{
			case WAY_UP:
				g_aEnemy[nCntEnemy].fRoll[0] = -0.75f;
				g_aEnemy[nCntEnemy].fRoll[1] = 0.75f;
				g_aEnemy[nCntEnemy].fRoll[2] = -0.25f;
				g_aEnemy[nCntEnemy].fRoll[3] = 0.25f;
				break;
			case WAY_RIGHT:
				g_aEnemy[nCntEnemy].fRoll[0] = 0.75f;
				g_aEnemy[nCntEnemy].fRoll[1] = 0.25f;
				g_aEnemy[nCntEnemy].fRoll[2] = -0.75f;
				g_aEnemy[nCntEnemy].fRoll[3] = -0.25f;
				break;
			case WAY_DOWN:
				g_aEnemy[nCntEnemy].fRoll[0] = 0.25f;
				g_aEnemy[nCntEnemy].fRoll[1] = -0.25f;
				g_aEnemy[nCntEnemy].fRoll[2] = 0.75f;
				g_aEnemy[nCntEnemy].fRoll[3] = -0.75f;
				break;
			case WAY_LEFT:
				g_aEnemy[nCntEnemy].fRoll[0] = -0.25f;
				g_aEnemy[nCntEnemy].fRoll[1] = -0.75f;
				g_aEnemy[nCntEnemy].fRoll[2] = 0.25f;
				g_aEnemy[nCntEnemy].fRoll[3] = 0.75f;
				break;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), g_aEnemy[nCntEnemy].pos.y + (ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), 0.0f);
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_aEnemy[nCntEnemy].type = enemytype;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].bPrize = bPrize;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].bMissile = false;
			switch (enemytype)
			{
			case ENEMY_XU_5:
				g_aEnemy[nCntEnemy].nScore = 200;
				g_aEnemy[nCntEnemy].nLife = 15;
				break;
			case ENEMY_XU_17:
				g_aEnemy[nCntEnemy].nScore = 150;
				g_aEnemy[nCntEnemy].nLife = 11;
				break;
			case ENEMY_XU_37:
				g_aEnemy[nCntEnemy].nScore = 250;
				g_aEnemy[nCntEnemy].nLife = 10;
				break;
			case ENEMY_XU_57:
				g_aEnemy[nCntEnemy].nScore = 300;
				g_aEnemy[nCntEnemy].nLife = 13;
				break;
			}
			pVtx += 4;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[0]), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[1]), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[2]), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * sinf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), g_aEnemy[nCntEnemy].pos.y + 80.0f + (SHADOW_ENEMY_BLOCK / 2.0f) * cosf(D3DX_PI * g_aEnemy[nCntEnemy].fRoll[3]), 0.0f);
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			g_pVtxBuffEnemy->Unlock();
			break;
		}
	}
}

//�G�̎擾
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//�G�̃_���[�W����
void HitEnemy(int nCntEnemy, int nDamage, bool bSpecial)
{
	//�̗͌��炷
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	//�|�ꂽ
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//���o���A�����A�v���C�Y�o���A�X�R�A���Z�A���Đ����Z
		SetDeath(g_aEnemy[nCntEnemy].pos, true);
		g_aEnemy[nCntEnemy].bUse = false;
		if (g_aEnemy[nCntEnemy].bPrize == true)
		{
			SetPrize(g_aEnemy[nCntEnemy].pos);
		}
		if (bSpecial == true)
		{
			AddScore(g_aEnemy[nCntEnemy].nScore * 2);
		}
		else
		{
			AddScore(g_aEnemy[nCntEnemy].nScore);
		}
		AddKill();
	}
	//�܂�����ĂȂ�
	else
	{
		//�_���[�W�H������A�J�E���g�ݒ�
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;

		//�X�R�A���Z
		if (bSpecial == true)
		{
			AddScore(g_aEnemy[nCntEnemy].nScore / 10);
		}
		else
		{
			AddScore(g_aEnemy[nCntEnemy].nScore / 20);
		}
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
		pVtx += nCntEnemy * 8;
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffEnemy->Unlock();
	}
}

//�G���Z�b�g
void ResetEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].bUse = false;
	}
}