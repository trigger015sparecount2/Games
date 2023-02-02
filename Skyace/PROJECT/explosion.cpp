//--------------------------
//Author:�O��q��
//�����̏���(explosion.cpp)
//--------------------------
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "barrier.h"

//�}�N����`
#define EXPLOSION_BLOCK (400.0f)  //�����̑傫��
#define EXPLOSION_LIFE (270)   //�����̒���

//�����̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	int nTime;       //����
	float fBig;      //�傫��
	int nClear;      //�����x
	bool bUse;       //�g�p���Ă��邩�ǂ���
} Explosion;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL; //���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion;

//����������
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�����̏�����
	g_aExplosion.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aExplosion.nTime = 0;
	g_aExplosion.fBig = 0.0f;
	g_aExplosion.nClear = 0;
	g_aExplosion.bUse = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/explosion.png",
		&g_pTextureExplosion);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
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
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//�����̏I������
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//�����̍X�V����
void UpdateExplosion(void)
{
	VERTEX_2D *pVtx;
	//�g�p��
	if (g_aExplosion.bUse == true)
	{
		//���Ԑi�߂�
		g_aExplosion.nTime++;
		g_aExplosion.pos.y += 0.75f;

		//���Ԑi��
		if (g_aExplosion.nTime == EXPLOSION_LIFE)
		{
			//����
			g_aExplosion.bUse = false;
		}

		//���Ԑi��łȂ�
		if (g_aExplosion.nTime <= 20)
		{
			//�ǂ�ǂ�傫������
			g_aExplosion.fBig += 0.05f;
		}
		else if (g_aExplosion.nTime > EXPLOSION_LIFE - 160)
		{
			//�ǂ�ǂ񔖂�����
			g_aExplosion.nClear++;
		}

		//10�t���[����1�t���[�������蔻��
		if ((g_aExplosion.nTime + 1) % 10 == 0)
		{
			int nCntEnemy;
			int nCntBoss;
			int nCntBarrier;
			Enemy *pEnemy;
			pEnemy = GetEnemy();
			Boss *pBoss;
			pBoss = GetBoss();
			Barrier *pBarrier;
			pBarrier = GetBarrier();

			//�G���G
			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				//�g���Ă�
				if (pEnemy->bUse == true)
				{
					//�����蔻��
					if (pEnemy->pos.x - (ENEMY_BLOCK / 2.0f) - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.x &&
						g_aExplosion.pos.x <= pEnemy->pos.x + (ENEMY_BLOCK / 2.0f) + (EXPLOSION_BLOCK / 2.0f) &&
						pEnemy->pos.y - (ENEMY_BLOCK / 2.0f) - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.y &&
						g_aExplosion.pos.y <= pEnemy->pos.y + (ENEMY_BLOCK / 2.0f) + (EXPLOSION_BLOCK / 2.0f))
					{
						HitEnemy(nCntEnemy, 1, true);
					}
				}
			}

			//�{�X�G
			for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++, pBoss++)
			{
				//�g���Ă�A��ԃm�[�}���A����ĂȂ�
				if (pBoss->bUse == true && pBoss->state != BOSSSTATE_BARRIER && pBoss->state != BOSSSTATE_DEATH)
				{
					//����̓G
					if (pBoss->type == BOSS_XU_44 || pBoss->type == BOSS_XU_80)
					{
						//�����蔻��
						if (pBoss->pos.x - 50.0f - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.x &&
							g_aExplosion.pos.x <= pBoss->pos.x + 50.0f + (EXPLOSION_BLOCK / 2.0f) &&
							pBoss->pos.y - 65.0f - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.y &&
							g_aExplosion.pos.y <= pBoss->pos.y + 65.0f + (EXPLOSION_BLOCK / 2.0f))
						{
							HitBoss(nCntBoss, 1, true);
						}
					}
					//����̓G
					else if (pBoss->type == BOSS_ENGINE)
					{
						//�����蔻��
						if (pBoss->pos.x - 35.0f - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.x &&
							g_aExplosion.pos.x <= pBoss->pos.x + 35.0f + (EXPLOSION_BLOCK / 2.0f) &&
							pBoss->pos.y - 35.0f - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.y &&
							g_aExplosion.pos.y <= pBoss->pos.y + 35.0f + (EXPLOSION_BLOCK / 2.0f))
						{
							HitBoss(nCntBoss, 1, true);
						}
					}
				}
			}

			//�o���A
			for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++, pBarrier++)
			{
				//�g���Ă�A�G�̃o���A
				if (pBarrier->bUse == true && pBarrier->ntype == 1)
				{
					//�����蔻��
					if (pBarrier->pos.x - BARRIER_WIDTH - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.x &&
						g_aExplosion.pos.x <= pBarrier->pos.x + BARRIER_WIDTH + (EXPLOSION_BLOCK / 2.0f) &&
						pBarrier->pos.y - BARRIER_HEIGHT - (EXPLOSION_BLOCK / 2.0f) <= g_aExplosion.pos.y &&
						g_aExplosion.pos.y <= pBarrier->pos.y + BARRIER_HEIGHT + (EXPLOSION_BLOCK / 2.0f))
					{
						HitBarrier(1, nCntBarrier);
					}
				}
			}
		}

		//�ʒu��F�ύX
		g_pVtxBuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion.pos.x - (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, g_aExplosion.pos.y - (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion.pos.x + (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, g_aExplosion.pos.y - (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion.pos.x - (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, g_aExplosion.pos.y + (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion.pos.x + (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, g_aExplosion.pos.y + (EXPLOSION_BLOCK / 2.0f) * g_aExplosion.fBig, 0.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aExplosion.nClear);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aExplosion.nClear);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aExplosion.nClear);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aExplosion.nClear);
		g_pVtxBuffExplosion->Unlock();
	}
}

//�`�揈��
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);    //�e�N�X�`���̐ݒ�
	
	//�g�p��
	if (g_aExplosion.bUse == true)
	{
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}

//�����̐ݒ菈��
void SetExplosion(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
	g_aExplosion.pos = pos;
	pVtx[0].pos = D3DXVECTOR3(g_aExplosion.pos.x - (EXPLOSION_BLOCK / 2.0f), g_aExplosion.pos.y - (EXPLOSION_BLOCK / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aExplosion.pos.x + (EXPLOSION_BLOCK / 2.0f), g_aExplosion.pos.y - (EXPLOSION_BLOCK / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aExplosion.pos.x - (EXPLOSION_BLOCK / 2.0f), g_aExplosion.pos.y + (EXPLOSION_BLOCK / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aExplosion.pos.x + (EXPLOSION_BLOCK / 2.0f), g_aExplosion.pos.y + (EXPLOSION_BLOCK / 2.0f), 0.0f);
	g_aExplosion.fBig = 0.0f;
	g_aExplosion.nTime = 0;
	g_aExplosion.nClear = 0;
	g_aExplosion.bUse = true;
	g_pVtxBuffExplosion->Unlock();
}

//���Z�b�g
void ResetExplosion(void)
{
	g_aExplosion.bUse = false;
}