//--------------------------
//Author:�O��q��
//���@�̏���(aircraft.cpp)
//--------------------------
#include "aircraft.h"
#include "input.h"
#include "bullet.h"
#include "uav.h"
#include "missile.h"
#include "barrier.h"
#include "laser.h"
#include "sound.h"
#include "death.h"
#include "fade.h"

//�}�N����`
#define MAX_AIRCRAFT (2)      //�@�̂̎��
#define MAX_SPECIAL (6)       //���ꕺ���ő�e��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureAircraft[MAX_AIRCRAFT * 2] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAircraft = NULL; //���_�o�b�t�@�ւ̃|�C���^
Aircraft g_aAircraft;

//����������
void InitAircraft(void)
{
	int nCntAircraft;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	g_aAircraft.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aAircraft.normalmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aAircraft.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aAircraft.nLife = 0;
	g_aAircraft.nMaxLife = 0;
	g_aAircraft.nLag = 0;
	g_aAircraft.nReload = 0;
	g_aAircraft.nSpecial = 0;
	g_aAircraft.nDTime = 0;
	g_aAircraft.state = AIRCRAFTSTATE_NORMAL;
	g_aAircraft.nClear = 0;
	g_aAircraft.bDeath = false;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/eagle.png",
		&g_pTextureAircraft[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/flanker.png",
		&g_pTextureAircraft[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/eagleshadow.png",
		&g_pTextureAircraft[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/flankershadow.png",
		&g_pTextureAircraft[3]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAircraft,
		NULL);
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffAircraft->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntAircraft = 0; nCntAircraft < 2; nCntAircraft++)
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
		if (nCntAircraft == 1)
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
	g_pVtxBuffAircraft->Unlock();
}

//�I������
void UninitAircraft(void)
{
	int nCntAircraft;
	//�e�N�X�`���̔j��
	for (nCntAircraft = 0; nCntAircraft < MAX_AIRCRAFT * 2; nCntAircraft++)
	{
		if (g_pTextureAircraft[nCntAircraft] != NULL)
		{
			g_pTextureAircraft[nCntAircraft]->Release();
			g_pTextureAircraft[nCntAircraft] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffAircraft != NULL)
	{
		g_pVtxBuffAircraft->Release();
		g_pVtxBuffAircraft = NULL;
	}
}

//�X�V����
void UpdateAircraft(void)
{
	if (g_aAircraft.bDeath == false)
	{
		VERTEX_2D *pVtx; //���_���ւ̃|�C���g
		g_pVtxBuffAircraft->Lock(0, 0, (void **)&pVtx, 0);
		switch (g_aAircraft.state)
		{
		case AIRCRAFTSTATE_NORMAL:
			break;
		case AIRCRAFTSTATE_DAMAGE:
			g_aAircraft.nDTime--;
			g_aAircraft.nClear--;
			if (g_aAircraft.nDTime <= 475)
			{
				g_aAircraft.state = AIRCRAFTSTATE_NODAMAGE;
			}
			break;
		case AIRCRAFTSTATE_NODAMAGE:
			g_aAircraft.nDTime--;
			g_aAircraft.nClear--;
			if (g_aAircraft.nDTime > 140)
			{
				if (g_aAircraft.nClear > 10)
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					if (g_aAircraft.nClear < 0)
					{
						g_aAircraft.nClear = 20;
					}
				}
			}
			else
			{
				if (g_aAircraft.nClear > 5)
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					if (g_aAircraft.nClear < 0)
					{
						g_aAircraft.nClear = 10;
					}
				}
			}
			if (g_aAircraft.nDTime <= 0)
			{
				g_aAircraft.state = AIRCRAFTSTATE_NORMAL;
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			break;
		case AIRCRAFTSTATE_BARRIER:
			break;
		}
		//shift�Ń_�b�V��
		if (GetKeyboardPress(DIK_O) == true)
		{
			g_aAircraft.move = g_aAircraft.normalmove * 2;
		}
		else
		{
			g_aAircraft.move = g_aAircraft.normalmove;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_aAircraft.nLag++;
			if (GetKeyboardPress(DIK_W) == true) //����
			{
				g_aAircraft.pos.x += sinf(-D3DX_PI * 0.75f) * g_aAircraft.move.x;
				g_aAircraft.pos.y += cosf(-D3DX_PI * 0.75f) * g_aAircraft.move.y;
			}
			else if (GetKeyboardPress(DIK_S) == true) //����
			{
				g_aAircraft.pos.x += sinf(-D3DX_PI * 0.25f) * g_aAircraft.move.x;
				g_aAircraft.pos.y += cosf(-D3DX_PI * 0.25f) * g_aAircraft.move.y;
			}
			else //��
			{
				g_aAircraft.pos.x += sinf(-D3DX_PI * 0.5f) * g_aAircraft.move.x;
				g_aAircraft.pos.y += cosf(-D3DX_PI * 0.5f) * g_aAircraft.move.y;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_aAircraft.nLag++;
			if (GetKeyboardPress(DIK_W) == true) //�E��
			{
				g_aAircraft.pos.x += sinf(D3DX_PI * 0.75f) * g_aAircraft.move.x;
				g_aAircraft.pos.y += cosf(D3DX_PI * 0.75f) * g_aAircraft.move.y;
			}
			else if (GetKeyboardPress(DIK_S) == true) //�E��
			{
				g_aAircraft.pos.x += sinf(D3DX_PI * 0.25f) * g_aAircraft.move.x;
				g_aAircraft.pos.y += cosf(D3DX_PI * 0.25f) * g_aAircraft.move.y;
			}
			else //�E
			{
				g_aAircraft.pos.x += sinf(D3DX_PI * 0.5f) * g_aAircraft.move.x;
				g_aAircraft.pos.y += cosf(D3DX_PI * 0.5f) * g_aAircraft.move.y;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true) //��
		{
			g_aAircraft.nLag++;
			g_aAircraft.pos.x += sinf(D3DX_PI) * g_aAircraft.move.x;
			g_aAircraft.pos.y += cosf(D3DX_PI) * g_aAircraft.move.y;
		}
		else if (GetKeyboardPress(DIK_S) == true) //��
		{
			g_aAircraft.nLag++;
			g_aAircraft.pos.x += sinf(0.0f) * g_aAircraft.move.x;
			g_aAircraft.pos.y += cosf(0.0f) * g_aAircraft.move.y;
		}
		else
		{
			g_aAircraft.nLag = 0;
		}
		if (g_aAircraft.pos.x <= AIRCRAFT_WIDTH / 2) //���s�����ꍇ
		{
			g_aAircraft.pos.x = AIRCRAFT_WIDTH / 2;
		}
		if (g_aAircraft.pos.y <= AIRCRAFT_HEIGHT / 2) //��s�����ꍇ
		{
			g_aAircraft.pos.y = AIRCRAFT_HEIGHT / 2;
		}
		if (g_aAircraft.pos.x >= SCREEN_WIDTH - (AIRCRAFT_WIDTH / 2)) //�E�s�����ꍇ
		{
			g_aAircraft.pos.x = SCREEN_WIDTH - (AIRCRAFT_WIDTH / 2);
		}
		if (g_aAircraft.pos.y >= SCREEN_HEIGHT - (AIRCRAFT_HEIGHT / 2)) //���s�����ꍇ
		{
			g_aAircraft.pos.y = SCREEN_HEIGHT - (AIRCRAFT_HEIGHT / 2);
		}
		if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false) //�e����
		{
			SetBullet(g_aAircraft.pos, D3DXVECTOR3(0.0f, -12.0f, 0.0f), 0, false);
		}
		if (g_aAircraft.nReload > 0)
		{
			g_aAircraft.nReload--;
		}
		if (GetKeyboardTrigger(DIK_I) == true && g_aAircraft.nReload <= 0 && g_aAircraft.nSpecial > 0) //���ꕺ��
		{
			g_aAircraft.nReload = 1800;
			g_aAircraft.nSpecial--;
			switch (g_aAircraft.nAType)
			{
			case 0: //�C�[�O��
				switch (g_aAircraft.nSType)
				{
				case 0:
					SetUav(g_aAircraft.pos, g_aAircraft.move); //UAV
					break;
				case 1:
					SetMissile(g_aAircraft.pos, D3DXVECTOR3(0.0f, -30.0f, 0.0f), 0); //�}���`���b�N�~�T�C��
					break;
				case 2:
					if (g_aAircraft.state != AIRCRAFTSTATE_BARRIER)
					{
						Barrier *pBarrier;
						pBarrier = GetBarrier();
						int nCntBarrier;
						for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++, pBarrier++)
						{
							if (pBarrier->bUse == false)
							{
								SetBarrier(g_aAircraft.pos, 3, 0); //�o���A
								g_aAircraft.state = AIRCRAFTSTATE_BARRIER;
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								break;
							}
						}
					}
					else
					{
						g_aAircraft.nReload = 0;
						g_aAircraft.nSpecial++;
					}
				}
				break;
			case 1: //�t�����J�[
				switch (g_aAircraft.nSType)
				{
				case 0:
					SetBullet(g_aAircraft.pos, D3DXVECTOR3(0.0f, -60.0f, 0.0f), 1, false); //���[���K��
					break;
				case 1:
					SetMissile(g_aAircraft.pos, D3DXVECTOR3(0.0f, -30.0f, 0.0f), 1); //�{���~�T�C��
					break;
				case 2:
					SetLaser(g_aAircraft.pos, 0); //���[�U�[
					break;
				}
				break;
			}
		}
		pVtx[0].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x - AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y - AIRCRAFT_HEIGHT / 2), g_aAircraft.pos.z);
		pVtx[1].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y - AIRCRAFT_HEIGHT / 2), g_aAircraft.pos.z);
		pVtx[2].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x - AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + AIRCRAFT_HEIGHT / 2), g_aAircraft.pos.z);
		pVtx[3].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + AIRCRAFT_HEIGHT / 2), g_aAircraft.pos.z);
		pVtx += 4;
		pVtx[0].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f - SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f - SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f + SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f - SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f - SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f + SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f + SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f + SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
		g_pVtxBuffAircraft->Unlock();
	}
	else
	{
		g_aAircraft.nDTime--;
		if (g_aAircraft.nDTime % 2 == 0)
		{
			g_aAircraft.pos.x += 3.0f;
		}
		else
		{
			g_aAircraft.pos.x -= 3.0f;
		}
		if (g_aAircraft.nDTime % 10 == 0)
		{
			D3DXVECTOR3 pos;
			pos = D3DXVECTOR3(g_aAircraft.pos.x - 45 + rand() % 90, g_aAircraft.pos.y - 60 + rand() % 120, 0.0f);
			SetDeath(pos, true);
		}
	}
}

//�`�揈��
void DrawAircraft(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffAircraft, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureAircraft[g_aAircraft.nAType]);    //�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		    0,  //�J�n����n�_�̃C���f�b�N�X
		    2); //�`�悷��v���~�e�B�u��
	pDevice->SetTexture(0, g_pTextureAircraft[g_aAircraft.nAType + 2]);    //�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4,  //�J�n����n�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
}

//���@�̐ݒ菈��
void SetAircraft(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffAircraft->Lock(0, 0, (void **)&pVtx, 0);
	g_aAircraft.pos = D3DXVECTOR3(640.0f, 700.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x - (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y - (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y - (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x - (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y + (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y + (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	switch (g_aAircraft.nAType)
	{
	case 0:
		g_aAircraft.nLife = 5;
		g_aAircraft.move = D3DXVECTOR3(7.0f, 7.0f, 0.0f);
		break;
	case 1:
		g_aAircraft.nLife = 4;
		g_aAircraft.move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		break;
	}
	g_aAircraft.normalmove = g_aAircraft.move;
	g_aAircraft.nMaxLife = g_aAircraft.nLife;
	pVtx += 4;
	pVtx[0].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f - SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f - SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f + SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f - SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f - SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f + SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f + SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f + SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	g_aAircraft.nDTime = 0;
	g_aAircraft.nLag = 0;
	g_aAircraft.nReload = 0;
	g_aAircraft.nClear = 0;
	g_aAircraft.bDeath = false;
	g_aAircraft.state = AIRCRAFTSTATE_NORMAL;
	if (g_aAircraft.nSpecial < 2)
	{
		g_aAircraft.nSpecial = 2;
	}
	g_aAircraft.nReSpecial = g_aAircraft.nSpecial;
	g_pVtxBuffAircraft->Unlock();
}

//���@�̎擾
Aircraft *GetAircraft(void)
{
	return &g_aAircraft;
}

//���@�̎�ސݒ�
void SetTypeAircraft(int nAType, int nSType)
{
	g_aAircraft.nAType = nAType;
	g_aAircraft.nSType = nSType;
}

void HitAircraft(void)
{
	g_aAircraft.nLife--;
	g_aAircraft.nDTime = 480;
	g_aAircraft.nClear = 20;
	PlaySound(SOUND_LABEL_DAMAGE000);
	if (g_aAircraft.nLife <= 0)
	{
		g_aAircraft.bDeath = true;
		SetDeath(g_aAircraft.pos, true);
		SetFade(MODE_RESULT, true);
	}
	if (g_aAircraft.nLife == 1)
	{
		PlaySound(SOUND_LABEL_PINCH000);
	}
	g_aAircraft.state = AIRCRAFTSTATE_DAMAGE;
	VERTEX_2D *pVtx;
	g_pVtxBuffAircraft->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	g_pVtxBuffAircraft->Unlock();
}

void ResetAircraft(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffAircraft->Lock(0, 0, (void **)&pVtx, 0);
	g_aAircraft.pos = D3DXVECTOR3(640.0f, 700.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x - (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y - (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y - (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x - (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y + (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + (AIRCRAFT_WIDTH / 2)), (float)(g_aAircraft.pos.y + (AIRCRAFT_HEIGHT / 2)), 0.0f);
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	switch (g_aAircraft.nAType)
	{
	case 0:
		g_aAircraft.nLife = 5;
		g_aAircraft.move = D3DXVECTOR3(7.0f, 7.0f, 0.0f);
		break;
	case 1:
		g_aAircraft.nLife = 4;
		g_aAircraft.move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		break;
	}
	g_aAircraft.normalmove = g_aAircraft.move;
	g_aAircraft.nMaxLife = g_aAircraft.nLife;
	pVtx += 4;
	pVtx[0].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f - SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f - SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f + SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f - SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f - SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f + SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)(g_aAircraft.pos.x + 80.0f + SHADOW_AIRCRAFT_WIDTH / 2), (float)(g_aAircraft.pos.y + 80.0f + SHADOW_AIRCRAFT_HEIGHT / 2), 0.0f);
	g_aAircraft.nDTime = 0;
	g_aAircraft.state = AIRCRAFTSTATE_NORMAL;
	g_aAircraft.nClear = 0;
	g_aAircraft.nLag = 0;
	g_aAircraft.nReload = 0;
	g_aAircraft.bDeath = false;
	g_aAircraft.nSpecial = g_aAircraft.nReSpecial;
	g_aAircraft.state = AIRCRAFTSTATE_NORMAL;
	g_pVtxBuffAircraft->Unlock();
}