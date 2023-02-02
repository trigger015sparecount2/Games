//--------------------------
//Author:�O��q��
//���[�U�[�̏���(laser.cpp)
//--------------------------
#include "laser.h"
#include "enemy.h"
#include "aircraft.h"
#include "boss.h"
#include "barrier.h"
#include "sound.h"

//�}�N����`
#define MAX_LASER (2)   //���[�U�[�̍ő吔
#define LASER_WIDTH (24.0f)  //���[�U�[�̕�
#define LASER_HEIGHT (900.0f) //���[�U�[�̒���

//���[�U�[�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int ntype;			//�G��������
	int nLife;			//����
	float fLength;		//����
	int nClear;			//�����x
	float fWidth;		//����
	int nGather;		//�ŏ��̏k��
	bool bDamage;		//�����蔻��
	bool bUse;			//�g�p���Ă��邩�ǂ���
} Laser;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureLaser[3] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLaser = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Laser g_aLaser[MAX_LASER];						//�ő僌�[�U�[

//����������
void InitLaser(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLaser;
	pDevice = GetDevice();

	//���[�U�[�̏�����
	for (nCntLaser = 0; nCntLaser < MAX_LASER; nCntLaser++)
	{
		g_aLaser[nCntLaser].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLaser[nCntLaser].nLife = 0;
		g_aLaser[nCntLaser].ntype = 0;
		g_aLaser[nCntLaser].fLength = 0.0f;
		g_aLaser[nCntLaser].fWidth = 0.0f;
		g_aLaser[nCntLaser].nGather = 180;
		g_aLaser[nCntLaser].bUse = false;
		g_aLaser[nCntLaser].bDamage = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/bluelaser.png",
		&g_pTextureLaser[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/redlaser.png",
		&g_pTextureLaser[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/���[�U�[����.png",
		&g_pTextureLaser[2]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LASER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLaser,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLaser->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntLaser = 0; nCntLaser < MAX_LASER; nCntLaser++)
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
	g_pVtxBuffLaser->Unlock();
}

//���[�U�[�̏I������
void UninitLaser(void)
{
	int nCntLaser;
	//�e�N�X�`���̔j��
	for (nCntLaser = 0; nCntLaser < MAX_LASER; nCntLaser++)
	{
		if (g_pTextureLaser[nCntLaser] != NULL)
		{
			g_pTextureLaser[nCntLaser]->Release();
			g_pTextureLaser[nCntLaser] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLaser != NULL)
	{
		g_pVtxBuffLaser->Release();
		g_pVtxBuffLaser = NULL;
	}
}

//���[�U�[�̍X�V����
void UpdateLaser(void)
{
	int nCntLaser;
	VERTEX_2D *pVtx;
	g_pVtxBuffLaser->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntLaser = 0; nCntLaser < MAX_LASER; nCntLaser++)
	{
		//�g�p��
		if (g_aLaser[nCntLaser].bUse == true)
		{
			int nCntEnemy;
			Enemy *pEnemy;
			pEnemy = GetEnemy();
			Aircraft *pAircraft;
			pAircraft = GetAircraft();
			int nCntBoss;
			Boss *pBoss;
			pBoss = GetBoss();
			Barrier *pBarrier;
			pBarrier = GetBarrier();
			int nCntBarrier;

			//�������炷
			g_aLaser[nCntLaser].nLife--;

			//�����̃��[�U�[
			if (g_aLaser[nCntLaser].ntype == 0)
			{
				//�ꏊ�ݒ�
				g_aLaser[nCntLaser].pos = pAircraft->pos;
			}
			else
			{
				for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++,pBoss++)
				{
					//�{�X�̏ꏊ�ɐݒ�
					if (pBoss->type == BOSS_SEAGULL || pBoss->type == BOSS_XU_80)
					{
						g_aLaser[nCntLaser].pos = pBoss->pos;
						break;
					}
				}
			}

			//�G�̃��[�U�[�A�������ȏ゠��
			if (g_aLaser[nCntLaser].ntype == 1 && g_aLaser[nCntLaser].nLife >= 240)
			{
				//�ŏ��̎���������
				g_aLaser[nCntLaser].nGather -= 3;

				//���������ɂȂ�ƁA���炷
				if (g_aLaser[nCntLaser].nLife == 240)
				{
					PlaySound(SOUND_LABEL_LASER000);
				}
			}

			//���˂��Ă����A���@�̕�
			if (g_aLaser[nCntLaser].nLife >= 465 && g_aLaser[nCntLaser].ntype == 0)
			{
				g_aLaser[nCntLaser].fLength += LASER_HEIGHT / 30.0f;
			}
			//���˂��Ă����A�G�̂��́A�ŏ��̎����I����Ă�
			else if (g_aLaser[nCntLaser].nLife >= 225 && g_aLaser[nCntLaser].ntype == 1 && g_aLaser[nCntLaser].nGather <= 0)
			{
				g_aLaser[nCntLaser].fLength += LASER_HEIGHT / 30.0f;
			}
			if ((g_aLaser[nCntLaser].nLife + 1) % 15 == 0) //15�t���[�����ƂɃ_���[�W
			{
				g_aLaser[nCntLaser].bDamage = true;
			}
			//�_���[�W�^���Ȃ�
			else
			{
				g_aLaser[nCntLaser].bDamage = false;
			}

			if (g_aLaser[nCntLaser].nLife == 0) //8�b����3�b�ŏƎˏI��
			{
				//����
				g_aLaser[nCntLaser].bUse = false;
			}

			if (g_aLaser[nCntLaser].nLife < 60) //�I��肩���ɐF�������Ȃ�
			{
				g_aLaser[nCntLaser].nClear += 2;
			}

			if (g_aLaser[nCntLaser].nLife < 30 && g_aLaser[nCntLaser].nLife % 3 == 0) //�I��肩���ɍׂ��Ȃ�
			{
				g_aLaser[nCntLaser].fWidth -= 1.0f;
				//�G�̃��[�U�[�͂���ɍׂ�����
				if (g_aLaser[nCntLaser].ntype == 1)
				{
					g_aLaser[nCntLaser].fWidth -= 9.0f;
				}
			}

			//���@�̂���
			if (g_aLaser[nCntLaser].ntype == 0)
			{
				//�����̕�pos���ړ�������
				g_aLaser[nCntLaser].pos.y -= g_aLaser[nCntLaser].fLength;
			}
			//�G�̂���
			else
			{
				//�����̕�pos���ړ�������
				g_aLaser[nCntLaser].pos.y += g_aLaser[nCntLaser].fLength;
			}

			//�G�̂��̂�������
			if (g_aLaser[nCntLaser].ntype == 1 && g_aLaser[nCntLaser].nGather > 0)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x - g_aLaser[nCntLaser].nGather, g_aLaser[nCntLaser].pos.y - g_aLaser[nCntLaser].nGather, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x + g_aLaser[nCntLaser].nGather, g_aLaser[nCntLaser].pos.y - g_aLaser[nCntLaser].nGather, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x - g_aLaser[nCntLaser].nGather, g_aLaser[nCntLaser].pos.y + g_aLaser[nCntLaser].nGather, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x + g_aLaser[nCntLaser].nGather, g_aLaser[nCntLaser].pos.y + g_aLaser[nCntLaser].nGather, 0.0f);
			}
			//�����̂��́A�܂��͓G�̃��[�U�[���˒�
			else
			{
				pVtx[0].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x - (g_aLaser[nCntLaser].fWidth / 2.0f), g_aLaser[nCntLaser].pos.y - g_aLaser[nCntLaser].fLength, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x + (g_aLaser[nCntLaser].fWidth / 2.0f), g_aLaser[nCntLaser].pos.y - g_aLaser[nCntLaser].fLength, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x - (g_aLaser[nCntLaser].fWidth / 2.0f), g_aLaser[nCntLaser].pos.y + g_aLaser[nCntLaser].fLength, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x + (g_aLaser[nCntLaser].fWidth / 2.0f), g_aLaser[nCntLaser].pos.y + g_aLaser[nCntLaser].fLength, 0.0f);
			}

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aLaser[nCntLaser].nClear);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aLaser[nCntLaser].nClear);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aLaser[nCntLaser].nClear);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 180 - g_aLaser[nCntLaser].nClear);

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				//�g���Ă�
				if (pEnemy->bUse == true)
				{
					//�G�ւ̓����蔻��
					if (pEnemy->pos.x - (ENEMY_BLOCK / 2.0f) - (g_aLaser[nCntLaser].fWidth / 2.0f) <= g_aLaser[nCntLaser].pos.x &&
						g_aLaser[nCntLaser].pos.x <= pEnemy->pos.x + (ENEMY_BLOCK / 2.0f) + (g_aLaser[nCntLaser].fWidth / 2.0f) &&
						pEnemy->pos.y - (ENEMY_BLOCK / 2.0f) - g_aLaser[nCntLaser].fLength <= g_aLaser[nCntLaser].pos.y &&
						g_aLaser[nCntLaser].pos.y <= pEnemy->pos.y + (ENEMY_BLOCK / 2.0f) + g_aLaser[nCntLaser].fLength)
					{
						//���@�̂��́A���[�U�[�Ƀ_���[�W���蒆
						if (g_aLaser[nCntLaser].ntype == 0 && g_aLaser[nCntLaser].bDamage == true)
						{
							//�_���[�W�^����
							HitEnemy(nCntEnemy, 2, true);
						}
					}
				}
			}

			for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++, pBoss++)
			{
				//�g���Ă�A����ĂȂ��A�o���A����Ȃ�
				if (pBoss->bUse == true && pBoss->state != BOSSSTATE_DEATH && pBoss->state != BOSSSTATE_BARRIER)
				{
					//����̓G
					if (pBoss->type == BOSS_XU_44 || pBoss->type == BOSS_XU_80)
					{
						//�����蔻��
						if (pBoss->pos.x - 50.0f - (g_aLaser[nCntLaser].fWidth / 2.0f) <= g_aLaser[nCntLaser].pos.x &&
							g_aLaser[nCntLaser].pos.x <= pBoss->pos.x + 50.0f + (g_aLaser[nCntLaser].fWidth / 2.0f) &&
							pBoss->pos.y - 65.0f - g_aLaser[nCntLaser].fLength <= g_aLaser[nCntLaser].pos.y &&
							g_aLaser[nCntLaser].pos.y <= pBoss->pos.y + 65.0f + g_aLaser[nCntLaser].fLength)
						{
							//���@�̂��́A���[�U�[�Ƀ_���[�W���蒆
							if (g_aLaser[nCntLaser].ntype == 0 && g_aLaser[nCntLaser].bDamage == true)
							{
								//�_���[�W�^����
								HitBoss(nCntBoss, 2, true);
							}
						}
					}
					//����̓G
					else if (pBoss->type == BOSS_ENGINE)
					{
						//�����蔻��
						if (pBoss->pos.x - 35.0f - (g_aLaser[nCntLaser].fWidth / 2.0f) <= g_aLaser[nCntLaser].pos.x &&
							g_aLaser[nCntLaser].pos.x <= pBoss->pos.x + 35.0f + (g_aLaser[nCntLaser].fWidth / 2.0f) &&
							pBoss->pos.y - 35.0f - g_aLaser[nCntLaser].fLength <= g_aLaser[nCntLaser].pos.y &&
							g_aLaser[nCntLaser].pos.y <= pBoss->pos.y + 35.0f + g_aLaser[nCntLaser].fLength)
						{
							//���@�̂��́A���[�U�[�_���[�W���蒆
							if (g_aLaser[nCntLaser].ntype == 0 && g_aLaser[nCntLaser].bDamage == true)
							{
								//�_���[�W�^����
								HitBoss(nCntBoss, 2, true);
							}
						}
					}
				}
			}

			for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++, pBarrier++)
			{
				//�o���A�ւ̓����蔻��
				if (pBarrier->bUse == true)
				{
					//�����蔻��
					if (pBarrier->pos.x - (BARRIER_WIDTH / 2.0f) - (g_aLaser[nCntLaser].fWidth / 2.0f) <= g_aLaser[nCntLaser].pos.x &&
						g_aLaser[nCntLaser].pos.x <= pBarrier->pos.x + (BARRIER_WIDTH / 2.0f) + (g_aLaser[nCntLaser].fWidth / 2.0f) &&
						pBarrier->pos.y - (BARRIER_HEIGHT / 2.0f) - g_aLaser[nCntLaser].fLength <= g_aLaser[nCntLaser].pos.y &&
						g_aLaser[nCntLaser].pos.y <= pBarrier->pos.y + (BARRIER_HEIGHT / 2.0f) + g_aLaser[nCntLaser].fLength)
					{
						//�G�̃��[�U�[�A�o���A�̏�ԃm�[�}���A���@�̃o���A
						if (g_aLaser[nCntLaser].ntype == 1 && pBarrier->state == BARRIERSTATE_NORMAL && pBarrier->ntype == 0)
						{
							HitBarrier(1,nCntBarrier);
						}
						//���@�̃��[�U�[�A�G�̃o���A�A���[�U�[�����蔻�蒆
						else if (g_aLaser[nCntLaser].ntype == 0 && pBarrier->ntype == 1 && g_aLaser[nCntLaser].bDamage == true)
						{
							HitBarrier(2, nCntBarrier);
						}
					}
				}
			}

			//���@�Ƃ̓����蔻��
			if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2.0f) - (g_aLaser[nCntLaser].fWidth / 2.0f) <= g_aLaser[nCntLaser].pos.x &&
				g_aLaser[nCntLaser].pos.x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2.0f) + (g_aLaser[nCntLaser].fWidth / 2.0f) &&
				pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2.0f) - g_aLaser[nCntLaser].fLength <= g_aLaser[nCntLaser].pos.y &&
				g_aLaser[nCntLaser].pos.y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2.0f) + g_aLaser[nCntLaser].fLength)
			{
				//�G�̃��[�U�[�A���@�̏�ԃm�[�}��
				if (g_aLaser[nCntLaser].ntype == 1 && pAircraft->state == AIRCRAFTSTATE_NORMAL)
				{
					HitAircraft();
				}
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffLaser->Unlock();
}

//�`�揈��
void DrawLaser(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntLaser;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLaser, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntLaser = 0; nCntLaser < MAX_LASER; nCntLaser++)
	{
		//�g�p��
		if (g_aLaser[nCntLaser].bUse == true)
		{
			//�G�̃��[�U�[�A�������ȏ�
			if (g_aLaser[nCntLaser].ntype == 1 && g_aLaser[nCntLaser].nLife >= 240)
			{
				pDevice->SetTexture(0, g_pTextureLaser[2]);    //�e�N�X�`���̐ݒ�
			}
			//����ȊO
			else
			{
				pDevice->SetTexture(0, g_pTextureLaser[g_aLaser[nCntLaser].ntype]);    //�e�N�X�`���̐ݒ�
			}
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntLaser * 4,
				2);
		}
	}
}

//���[�U�[�̐ݒ菈��
void SetLaser(D3DXVECTOR3 pos, int ntype)
{
	int nCntLaser;
	VERTEX_2D *pVtx;
	g_pVtxBuffLaser->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntLaser = 0; nCntLaser < MAX_LASER; nCntLaser++)
	{
		//�g���ĂȂ�
		if (g_aLaser[nCntLaser].bUse == false)
		{
			//�F�X�ݒ�
			g_aLaser[nCntLaser].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x - 240.0f, g_aLaser[nCntLaser].pos.y - 240.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x + 240.0f, g_aLaser[nCntLaser].pos.y - 240.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x - 240.0f, g_aLaser[nCntLaser].pos.y + 240.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLaser[nCntLaser].pos.x + 240.0f, g_aLaser[nCntLaser].pos.y + 240.0f, 0.0f);
			g_aLaser[nCntLaser].bDamage = false;
			g_aLaser[nCntLaser].fLength = 0.0f;
			g_aLaser[nCntLaser].bUse = true;
			g_aLaser[nCntLaser].ntype = ntype;
			g_aLaser[nCntLaser].nGather = 360;
			g_aLaser[nCntLaser].nClear = 0;
			if (ntype == 0)
			{
				g_aLaser[nCntLaser].nLife = 480;
				g_aLaser[nCntLaser].fWidth = LASER_WIDTH;
				PlaySound(SOUND_LABEL_LASER000);
			}
			else
			{
				g_aLaser[nCntLaser].nLife = 360;
				g_aLaser[nCntLaser].fWidth = 120.0f;
			}
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffLaser->Unlock();
}

//���Z�b�g
void ResetLaser(void)
{
	int nCntLaser;
	for (nCntLaser = 0; nCntLaser < MAX_LASER; nCntLaser++)
	{
		g_aLaser[nCntLaser].bUse = false;
	}
}