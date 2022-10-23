//--------------------------
//Author:�O��q��
//�������l�@�̏���(uav.cpp)
//--------------------------
#include "input.h"
#include "uav.h"
#include "aircraft.h"
#include "bullet.h"
#include "death.h"

//�}�N����`
#define UAV_WIDTH (60)  //�|���S���̕�
#define UAV_HEIGHT (40) //�|���S���̍���
#define SHADOW_UAV_WIDTH (20)  //�|���S���̕�
#define SHADOW_UAV_HEIGHT (15) //�|���S���̍���
#define MAX_UAV (2)     //UAV�̍ő吔

//�������l�@�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 move; //�ړ���
	int nCounterAnim; //�A�j���[�V�����J�E���^
	int nPatternAnim; //�A�j���[�V�����p�^�[��No
	int nLife;        //����
	bool bUse;        //�g�p�����ۂ�
} Uav;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureUav[2] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUav = NULL; //���_�o�b�t�@�ւ̃|�C���^
Uav g_aUav[MAX_UAV];

//����������
void InitUav(void)
{
	int nCntUav;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	for (nCntUav = 0; nCntUav < MAX_UAV; nCntUav++)
	{
		g_aUav[nCntUav].bUse = false;
		g_aUav[nCntUav].nCounterAnim = 0;
		g_aUav[nCntUav].nPatternAnim = 0;
		g_aUav[nCntUav].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUav[nCntUav].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUav[nCntUav].nLife = 0;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/UAV.png",
		&g_pTextureUav[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/UAVshadow.png",
		&g_pTextureUav[1]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UAV * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUav,
		NULL);
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUav->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntUav = 0; nCntUav < MAX_UAV * 2; nCntUav++)
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
		if (nCntUav % 2 == 0)
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
	g_pVtxBuffUav->Unlock();
}

//�I������
void UninitUav(void)
{
	int nCntUav;
	for (nCntUav = 0; nCntUav < 2; nCntUav++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureUav[nCntUav] != NULL)
		{
			g_pTextureUav[nCntUav]->Release();
			g_pTextureUav[nCntUav] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUav != NULL)
	{
		g_pVtxBuffUav->Release();
		g_pVtxBuffUav = NULL;
	}
}

//�X�V����
void UpdateUav(D3DXVECTOR3 pos, int nLag)
{
	int nCntUav;
	for (nCntUav = 0; nCntUav < MAX_UAV; nCntUav++)
	{
		if (g_aUav[nCntUav].bUse == true)
		{
			VERTEX_2D *pVtx; //���_���ւ̃|�C���^
			if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false) //�e����
			{
				SetBullet(g_aUav[nCntUav].pos, D3DXVECTOR3(0.0f, -12.0f, 0.0f), 0, true);
			}
			if (g_aUav[nCntUav].nLife > 870)
			{
				if (nCntUav == 0)
				{
					g_aUav[nCntUav].pos.x -= g_aUav[nCntUav].move.x;
				}
				else
				{
					g_aUav[nCntUav].pos.x += g_aUav[nCntUav].move.x;
				}
			}
			else if(nLag >= 4 || nLag == 0)
			{
				if (nCntUav == 0)//���ɂ���UAV
				{
					if (pos.x - g_aUav[nCntUav].pos.x < 80.0f)//����UAV�����@�ɋ߂��A���邢�͎��@���E�ɂ���ꍇ(=���ɍs������)
					{
						g_aUav[nCntUav].pos.x -= g_aUav[nCntUav].move.x * 1.5f;
					}
					else if(pos.x - g_aUav[nCntUav].pos.x > 200.0f)//����UAV�����@�����啝�ɍ��ɂ���ꍇ
					{
						g_aUav[nCntUav].pos.x += g_aUav[nCntUav].move.x * 1.5f;
					}
					else if (pos.x - g_aUav[nCntUav].pos.x > 120.0f)//����UAV�����@������������č��ɂ���ꍇ
					{
						g_aUav[nCntUav].pos.x += g_aUav[nCntUav].move.x;
					}
				}
				else//�E�ɂ���UAV
				{
					if (g_aUav[nCntUav].pos.x - pos.x < 80.0f)//�E��UAV�����@�ɋ߂��A���邢�͎��@��荶�ɂ���ꍇ
					{
						g_aUav[nCntUav].pos.x += g_aUav[nCntUav].move.x * 1.5f;
					}
					else if (g_aUav[nCntUav].pos.x - pos.x > 200.0f)//�E��UAV�����@�����啝�ɉE�ɂ���ꍇ
					{
						g_aUav[nCntUav].pos.x -= g_aUav[nCntUav].move.x * 1.5f;
					}
					else if (g_aUav[nCntUav].pos.x - pos.x > 120.0f)//�E��UAV�����@������������ĉE�ɂ���ꍇ
					{
						g_aUav[nCntUav].pos.x -= g_aUav[nCntUav].move.x;
					}
				}
				if (g_aUav[nCntUav].pos.y - pos.y > 10.0f)//���@�����Ȃ��ɂ���ꍇ
				{
					g_aUav[nCntUav].pos.y -= g_aUav[nCntUav].move.y * 1.5f;
				}
				else if (g_aUav[nCntUav].pos.y - pos.y > 5.0f)//���@����ɂ���ꍇ
				{
					g_aUav[nCntUav].pos.y -= g_aUav[nCntUav].move.y;
				}
				else if (pos.y - g_aUav[nCntUav].pos.y > 10.0f)//���@�����Ȃ艺�ɂ���ꍇ
				{
					g_aUav[nCntUav].pos.y += g_aUav[nCntUav].move.y * 1.5f;
				}
				else if (pos.y - g_aUav[nCntUav].pos.y > 5.0f)//���@�����ɂ���ꍇ
				{
					g_aUav[nCntUav].pos.y += g_aUav[nCntUav].move.y;
				}
			}
			g_pVtxBuffUav->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntUav * 8;
			pVtx[0].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x - UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y - UAV_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y - UAV_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x - UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + UAV_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + UAV_HEIGHT / 2), 0.0f);
			pVtx += 4;
			pVtx[0].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f - SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f - SHADOW_UAV_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f + SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f - SHADOW_UAV_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f - SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f + SHADOW_UAV_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f + SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f + SHADOW_UAV_HEIGHT / 2), 0.0f);
			g_pVtxBuffUav->Unlock();
			g_aUav[nCntUav].nLife--;
			if (g_aUav[nCntUav].nLife <= 0)
			{
				g_aUav[nCntUav].bUse = false;
				SetDeath(g_aUav[nCntUav].pos, true);
			}
		}
	}
}

//�`�揈��
void DrawUav(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntUav;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUav, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntUav = 0; nCntUav < MAX_UAV; nCntUav++)
	{
		if (g_aUav[nCntUav].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureUav[0]);    //�e�N�X�`���̐ݒ�
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntUav * 8,
				2);
			pDevice->SetTexture(0, g_pTextureUav[1]);    //�e�N�X�`���̐ݒ�
														 //�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntUav * 8 + 4,
				2);
		}
	}
}

//�������l�@�̐ݒ菈��
void SetUav(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	int nCntUav;
	for(nCntUav = 0; nCntUav < MAX_UAV; nCntUav++)
	{
		if (g_aUav[nCntUav].bUse == false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffUav->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntUav * 8;
			g_aUav[nCntUav].pos = pos;
			pVtx[0].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x - (UAV_WIDTH / 2)), (float)(g_aUav[nCntUav].pos.y - (UAV_HEIGHT / 2)), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + (UAV_WIDTH / 2)), (float)(g_aUav[nCntUav].pos.y - (UAV_HEIGHT / 2)), 0.0f);
			pVtx[2].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x - (UAV_WIDTH / 2)), (float)(g_aUav[nCntUav].pos.y + (UAV_HEIGHT / 2)), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + (UAV_WIDTH / 2)), (float)(g_aUav[nCntUav].pos.y + (UAV_HEIGHT / 2)), 0.0f);
			g_aUav[nCntUav].nLife = 900;
			g_aUav[nCntUav].move = move;
			g_aUav[nCntUav].nCounterAnim = 0;
			g_aUav[nCntUav].nPatternAnim = 0;
			g_aUav[nCntUav].bUse = true;
			pVtx += 4;
			pVtx[0].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f - SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f - SHADOW_UAV_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f + SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f - SHADOW_UAV_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f - SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f + SHADOW_UAV_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((float)(g_aUav[nCntUav].pos.x + 80.0f + SHADOW_UAV_WIDTH / 2), (float)(g_aUav[nCntUav].pos.y + 80.0f + SHADOW_UAV_HEIGHT / 2), 0.0f);
			g_pVtxBuffUav->Unlock();
		}
	}
}

void ResetUav(void)
{
	int nCntUav;
	for (nCntUav = 0; nCntUav < MAX_UAV; nCntUav++)
	{
		g_aUav[nCntUav].bUse = false;
	}
}