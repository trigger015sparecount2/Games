//--------------------------
//Author:�O��q��
//�~�T�C���̏���(missile.cpp)
//--------------------------
#include "missile.h"
#include "enemy.h"
#include "smoke.h"
#include "explosion.h"
#include "sound.h"
#include "boss.h"
#include "barrier.h"

//�}�N����`
#define MAX_MISSILE (32)   //�~�T�C���̍ő吔
#define MISSILE_WIDTH (20.0f)  //�~�T�C���̕�
#define MISSILE_HEIGHT (60.0f) //�~�T�C���̍���
#define MISSILE_SLIDE_TIME (15) //�~�T�C���̉��ړ��̎���

//�~�T�C���̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 move; //�ړ���
	int nTime;        //�����Ă���̎��Ԍo��
	int nType;        //2��ނ̂����ǂ��炩
	float fPosx;      //���ˎ���x���W�̈ʒu
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Missile;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMissile[2] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMissile = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Missile g_aMissile[MAX_MISSILE];					//�~�T�C��

//����������
void InitMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntMissile;
	pDevice = GetDevice();

	//�e�̏�����
	for (nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		g_aMissile[nCntMissile].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMissile[nCntMissile].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMissile[nCntMissile].nTime = 0;
		g_aMissile[nCntMissile].nType = 0;
		g_aMissile[nCntMissile].fPosx = 0.0f;
		g_aMissile[nCntMissile].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/missile.png",
		&g_pTextureMissile[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/bombmissile.png",
		&g_pTextureMissile[1]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MISSILE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMissile,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMissile->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
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
	g_pVtxBuffMissile->Unlock();
}

//�~�T�C���̏I������
void UninitMissile(void)
{
	int nCntMissile;
	//�e�N�X�`���̔j��
	for (nCntMissile = 0; nCntMissile < 2; nCntMissile++)
	{
		if (g_pTextureMissile[nCntMissile] != NULL)
		{
			g_pTextureMissile[nCntMissile]->Release();
			g_pTextureMissile[nCntMissile] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMissile != NULL)
	{
		g_pVtxBuffMissile->Release();
		g_pVtxBuffMissile = NULL;
	}
}

//�~�T�C���̍X�V����
void UpdateMissile(void)
{
	int nCntMissile;
	VERTEX_2D *pVtx;
	int nNowEnemy = -1;
	int nFirstEnemy = 0;
	Enemy *pFirstEnemy;
	pFirstEnemy = GetEnemy();
	int nNowBoss = -1;
	int nFirstBoss = 0;
	Boss *pFirstBoss;
	pFirstBoss = GetBoss();
	int nCntBarrier;
	Barrier *pBarrier;
	pBarrier = GetBarrier();
	g_pVtxBuffMissile->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		//�g���Ă�
		if (g_aMissile[nCntMissile].bUse == true)
		{
			int nCntEnemy;
			Enemy *pEnemy;
			pEnemy = GetEnemy();
			int nCntBoss;
			Boss *pBoss;
			pBoss = GetBoss();

			//���Ԑi�߂�
			g_aMissile[nCntMissile].nTime++;
			pVtx[0].pos = D3DXVECTOR3(g_aMissile[nCntMissile].pos.x - (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile].pos.y - (MISSILE_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMissile[nCntMissile].pos.x + (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile].pos.y - (MISSILE_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMissile[nCntMissile].pos.x - (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile].pos.y + (MISSILE_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMissile[nCntMissile].pos.x + (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile].pos.y + (MISSILE_HEIGHT / 2.0f), 0.0f);
			
			//���Ԑi��
			if (g_aMissile[nCntMissile].nTime > MISSILE_SLIDE_TIME + 15)
			{
				//�~�T�C���ړ��A���o��
				g_aMissile[nCntMissile].pos += g_aMissile[nCntMissile].move;
				SetSmoke(D3DXVECTOR3(g_aMissile[nCntMissile].pos.x, g_aMissile[nCntMissile].pos.y + (MISSILE_HEIGHT / 2), 0.0f));
			}

			//��ʊO�����������
			if (g_aMissile[nCntMissile].pos.y <= -(MISSILE_HEIGHT / 2))
			{
				g_aMissile[nCntMissile].bUse = false;
			}

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				//�G���g���Ă�܂��͓G�̃J�E���g���Ō�
				if (pEnemy->bUse == true || nCntEnemy == MAX_ENEMY - 1)
				{
					//�G���g���Ă�
					if (pEnemy->bUse == true)
					{
						//�����蔻��
						if (pEnemy->pos.x - (ENEMY_BLOCK / 2.0f) - (MISSILE_WIDTH / 2.0f) <= g_aMissile[nCntMissile].pos.x &&
							g_aMissile[nCntMissile].pos.x <= pEnemy->pos.x + (ENEMY_BLOCK / 2.0f) + (MISSILE_WIDTH / 2.0f) &&
							pEnemy->pos.y - (ENEMY_BLOCK / 2.0f) - (MISSILE_HEIGHT / 2.0f) <= g_aMissile[nCntMissile].pos.y &&
							g_aMissile[nCntMissile].pos.y <= pEnemy->pos.y + (ENEMY_BLOCK / 2.0f) + (MISSILE_HEIGHT / 2.0f))
						{
							PlaySound(SOUND_LABEL_MISSILE000);

							//�ʏ�~�T�C��
							if (g_aMissile[nCntMissile].nType == 0)
							{
								HitEnemy(nCntEnemy, 8, true);
							}
							//�t���A�~�T�C��
							else if(g_aMissile[nCntMissile].nType == 1)
							{
								SetExplosion(g_aMissile[nCntMissile].pos);
								PlaySound(SOUND_LABEL_EXPLOSION000);
							}

							//�~�T�C�������A�G�̃~�T�C���t���O�I�t
							g_aMissile[nCntMissile].bUse = false;
							pEnemy->bMissile = false;
						}
					}

					//���O�̓G�̃J�E���g�����J�E���g���傫�����G���g���Ă�܂��͓G�̃J�E���g���Ōォ�G���g���ĂȂ�
					if (nNowEnemy < nCntEnemy && pEnemy->bUse == true || nCntEnemy == MAX_ENEMY - 1 && pEnemy->bUse == false)
					{
						//���O�̓G�̃J�E���g��-1���G���g���Ă�
						if (nNowEnemy == -1 && pEnemy->bUse == true)
						{
							//�ŏ��̓G�̔ԍ��ƃ|�C���^���L�^
							pFirstEnemy = pEnemy;
							nFirstEnemy = nCntEnemy;
						}

						//���O�̓G�̔ԍ��ƍ��̓G�̔ԍ����قȂ�A�����ɂ���
						if (nNowEnemy != nCntEnemy)
						{
							nNowEnemy = nCntEnemy;
						}

						//���̓G�̔ԍ����Ōォ�G���g���ĂȂ�
						if (nCntEnemy == MAX_ENEMY - 1 && pEnemy->bUse == false)
						{
							//�ŏ��̓G��Ώۂɂ���
							pEnemy = pFirstEnemy;
							nNowEnemy = nFirstEnemy;
						}

						//���ɃX���C�h���鎞�Ԓ����G���g���Ă�
						if (g_aMissile[nCntMissile].nTime <= MISSILE_SLIDE_TIME && pEnemy->bUse == true)
						{
							if (g_aMissile[nCntMissile].pos.x < pEnemy->pos.x) //�G���~�T�C�����E���ɋ���Ƃ�
							{
								g_aMissile[nCntMissile].pos.x += fabsf(g_aMissile[nCntMissile].fPosx - pEnemy->pos.x) / MISSILE_SLIDE_TIME;
							}
							else //�G���~�T�C����荶���ɋ���Ƃ�
							{
								g_aMissile[nCntMissile].pos.x -= fabsf(g_aMissile[nCntMissile].fPosx - pEnemy->pos.x) / MISSILE_SLIDE_TIME;
							}
							g_aMissile[nCntMissile].pos.y += 1.5f;
							pEnemy->bMissile = true;
						}
						break;
					}
				}
			}
			for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++, pBoss++)
			{
				//�{�X���g���Ă�܂��̓{�X�J�E���g���Ō�
				if (pBoss->bUse == true || nCntBoss == MAX_ENEMY - 1)
				{
					//�{�X���g���Ă邩�o���A����Ȃ�������ĂȂ�
					if (pBoss->bUse == true && pBoss->state != BOSSSTATE_BARRIER && pBoss->state != BOSSSTATE_DEATH)
					{
						//����̎��
						if (pBoss->type == BOSS_XU_44 || pBoss->type == BOSS_XU_80)
						{
							//�����蔻��
							if (pBoss->pos.x - 50.0f - (MISSILE_WIDTH / 2.0f) <= g_aMissile[nCntMissile].pos.x &&
								g_aMissile[nCntMissile].pos.x <= pBoss->pos.x + 50.0f + (MISSILE_WIDTH / 2.0f) &&
								pBoss->pos.y - 65.0f - (MISSILE_HEIGHT / 2.0f) <= g_aMissile[nCntMissile].pos.y &&
								g_aMissile[nCntMissile].pos.y <= pBoss->pos.y + 65.0f + (MISSILE_HEIGHT / 2.0f))
							{
								PlaySound(SOUND_LABEL_MISSILE000);

								//�ʏ�~�T�C��
								if (g_aMissile[nCntMissile].nType == 0)
								{
									HitBoss(nCntBoss, 10, true);
								}
								//�t���A�~�T�C��
								else if (g_aMissile[nCntMissile].nType == 1)
								{
									SetExplosion(g_aMissile[nCntMissile].pos);
									PlaySound(SOUND_LABEL_EXPLOSION000);
								}
								//�~�T�C������
								g_aMissile[nCntMissile].bUse = false;
								pBoss->bMissile = false;
							}
						}
						//����̎��
						else if (pBoss->type == BOSS_ENGINE)
						{
							//�����蔻��
							if (pBoss->pos.x - 35.0f - (MISSILE_WIDTH / 2.0f) <= g_aMissile[nCntMissile].pos.x &&
								g_aMissile[nCntMissile].pos.x <= pBoss->pos.x + 35.0f + (MISSILE_WIDTH / 2.0f) &&
								pBoss->pos.y - 35.0f - (MISSILE_HEIGHT / 2.0f) <= g_aMissile[nCntMissile].pos.y &&
								g_aMissile[nCntMissile].pos.y <= pBoss->pos.y + 35.0f + (MISSILE_HEIGHT / 2.0f))
							{
								PlaySound(SOUND_LABEL_MISSILE000);

								//�ʏ�~�T�C��
								if (g_aMissile[nCntMissile].nType == 0)
								{
									HitBoss(nCntBoss, 10, true);
								}
								//�t���A�~�T�C��
								else if (g_aMissile[nCntMissile].nType == 1)
								{
									SetExplosion(g_aMissile[nCntMissile].pos);
									PlaySound(SOUND_LABEL_EXPLOSION000);
								}

								//�~�T�C������
								g_aMissile[nCntMissile].bUse = false;
								pBoss->bMissile = false;
							}
						}
					}

					//���O�̃{�X�̃J�E���g�����J�E���g���傫�����G������ĂȂ�������̎�ނ���Ȃ��A
					//�܂��͓G�̃J�E���g���Ōォ�G������ĂȂ��A�܂��̓{�X�J�E���g���}�b�N�X���g���ĂȂ�
					if (nNowBoss < nCntBoss && pBoss->state != BOSSSTATE_DEATH && pBoss->type != BOSS_SEAGULL || 
						nCntBoss == MAX_BOSS - 1 && pBoss->state != BOSSSTATE_DEATH || nCntBoss == MAX_BOSS && pBoss->bUse == false)
					{
						//���O�̓G�̃J�E���g��-1���G���g���Ă邩�{�X������̎�ނ���Ȃ�
						if (nNowBoss == -1 && pBoss->state != BOSSSTATE_DEATH && pBoss->type != BOSS_SEAGULL)
						{
							pFirstBoss = pBoss;
							nFirstBoss = nCntBoss;
						}

						//���O�̓G�̃J�E���g�ƍ��̃J�E���g���Ⴄ���{�X������̎�ނ���Ȃ�
						if (nNowBoss != nCntBoss && pBoss->type != BOSS_SEAGULL)
						{
							nNowBoss = nCntBoss;
						}

						//�{�X�̃J�E���g���Ōォ�{�X������ĂȂ�
						if (nCntBoss == MAX_BOSS - 1 && pBoss->state != BOSSSTATE_DEATH)
						{
							//�ŏ��̓G��Ώۂɂ���
							pBoss = pFirstBoss;
							nNowBoss = nFirstBoss;
						}

						//���ɃX���C�h���鎞�Ԓ����{�X������ĂȂ�
						if (g_aMissile[nCntMissile].nTime <= MISSILE_SLIDE_TIME && pBoss->state != BOSSSTATE_DEATH)
						{
							if (g_aMissile[nCntMissile].pos.x < pBoss->pos.x) //�G���~�T�C�����E���ɋ���Ƃ�
							{
								g_aMissile[nCntMissile].pos.x += fabsf(g_aMissile[nCntMissile].fPosx - pBoss->pos.x) / MISSILE_SLIDE_TIME;
							}
							else //�G���~�T�C����荶���ɋ���Ƃ�
							{
								g_aMissile[nCntMissile].pos.x -= fabsf(g_aMissile[nCntMissile].fPosx - pBoss->pos.x) / MISSILE_SLIDE_TIME;
							}
							g_aMissile[nCntMissile].pos.y += 1.5f;
							pBoss->bMissile = true;
						}
						break;
					}
				}
			}

			for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++, pBarrier++)
			{
				//�o���A���g���Ă邩�G�̃o���A
				if (pBarrier->bUse == true && pBarrier->ntype == 1)
				{
					//�����蔻��
					if (pBarrier->pos.x - BARRIER_WIDTH - (MISSILE_WIDTH / 2.0f) <= g_aMissile[nCntMissile].pos.x &&
						g_aMissile[nCntMissile].pos.x <= pBarrier->pos.x + BARRIER_WIDTH + (MISSILE_WIDTH / 2.0f) &&
						pBarrier->pos.y - BARRIER_HEIGHT - (MISSILE_HEIGHT / 2.0f) <= g_aMissile[nCntMissile].pos.y &&
						g_aMissile[nCntMissile].pos.y <= pBarrier->pos.y + BARRIER_HEIGHT + (MISSILE_HEIGHT / 2.0f))
					{
						//�_���[�W
						HitBarrier(8, nCntBarrier);
						g_aMissile[nCntMissile].bUse = false;
					}
				}
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffMissile->Unlock();
}

//�~�T�C���̕`�揈��
void DrawMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntMissile;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMissile, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�

	for (nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		//�g�p��
		if (g_aMissile[nCntMissile].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureMissile[g_aMissile[nCntMissile].nType]);    //�e�N�X�`���̐ݒ�
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntMissile * 4,
				2);
		}
	}
}

//�~�T�C���̐ݒ菈��
void SetMissile(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntMissile;
	int nCntMissile2;
	VERTEX_2D *pVtx;
	int nNumber;
	g_pVtxBuffMissile->Lock(0, 0, (void **)&pVtx, 0);

	//�~�T�C���̎�ނɉ����ă��[�v�񐔕ς���
	if (nType == 0)
	{
		nNumber = 6;
	}
	else
	{
		nNumber = 1;
	}

	for (nCntMissile = 0; nCntMissile < nNumber; nCntMissile++)
	{
		for (nCntMissile2 = 0; nCntMissile2 < MAX_MISSILE; nCntMissile2++)
		{
			//�g���ĂȂ�
			if (g_aMissile[nCntMissile2].bUse == false)
			{
				//�F�X�ݒ�
				g_aMissile[nCntMissile2].pos = pos;
				g_aMissile[nCntMissile2].fPosx = pos.x;
				pVtx[0].pos = D3DXVECTOR3(g_aMissile[nCntMissile2].pos.x - (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile2].pos.y - (MISSILE_HEIGHT / 2.0f), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aMissile[nCntMissile2].pos.x + (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile2].pos.y - (MISSILE_HEIGHT / 2.0f), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aMissile[nCntMissile2].pos.x - (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile2].pos.y + (MISSILE_HEIGHT / 2.0f), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aMissile[nCntMissile2].pos.x + (MISSILE_WIDTH / 2.0f), g_aMissile[nCntMissile2].pos.y + (MISSILE_HEIGHT / 2.0f), 0.0f);
				g_aMissile[nCntMissile2].move = move;
				g_aMissile[nCntMissile2].nType = nType;
				g_aMissile[nCntMissile2].nTime = 0;
				g_aMissile[nCntMissile2].bUse = true;
				break;
			}
			pVtx += 4;
		}
	}
	g_pVtxBuffMissile->Unlock();
}

//�~�T�C���擾
Missile *GetMissile(void)
{
	return &g_aMissile[0];
}

//���Z�b�g
void ResetMissile(void)
{
	int nCntMissile;
	for (nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		g_aMissile[nCntMissile].bUse = false;
	}
}