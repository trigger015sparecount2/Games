//--------------------------
//Author:�O��q��
//���b�N�I���V�[�J�[�̏���(lockon.cpp)
//--------------------------
#include "lockon.h"
#include "enemy.h"
#include "boss.h"
//�}�N����`
#define MAX_LOCKON (128)   //���b�N�I���V�[�J�[�̍ő吔
#define LOCKON_BLOCK (30.0f)  //���b�N�I���V�[�J�[�̑傫��

//���b�N�I���V�[�J�[�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Lockon;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureLockon = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLockon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Lockon g_aLockon[MAX_LOCKON];						//���b�N�I��

//����������
void InitLockon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLockon;
	pDevice = GetDevice();

	//���b�N�I���̏�����
	for (nCntLockon = 0; nCntLockon < MAX_LOCKON; nCntLockon++)
	{
		g_aLockon[nCntLockon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLockon[nCntLockon].bUse = false;
	}
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/lockon.png",
		&g_pTextureLockon);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LOCKON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLockon,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLockon->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntLockon = 0; nCntLockon < MAX_LOCKON; nCntLockon++)
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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLockon->Unlock();
}

//���b�N�I���V�[�J�[�̏I������
void UninitLockon(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLockon != NULL)
	{
		g_pTextureLockon->Release();
		g_pTextureLockon = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLockon != NULL)
	{
		g_pVtxBuffLockon->Release();
		g_pVtxBuffLockon = NULL;
	}
}

//���b�N�I���V�[�J�[�̍X�V����
void UpdateLockon(void)
{
	int nCntLockon;
	VERTEX_2D *pVtx;
	int nNowEnemy = -1;
	float fRed;
	int nCntEnemy;
	Enemy *pEnemy;
	int nNowBoss = -1;
	int nCntBoss;
	Boss *pBoss;
	for (nCntLockon = 0; nCntLockon < MAX_LOCKON; nCntLockon++)
	{
		//�g���ĂȂ�
		g_aLockon[nCntLockon].bUse = false;
		pEnemy = GetEnemy();
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			//���b�N�I�����g���Ă�A�I��
			if (g_aLockon[nCntLockon].bUse == true)
			{
				break;
			}

			//�G���g���Ă�A
			if (pEnemy->bUse == true && nNowEnemy < nCntEnemy)
			{
				//���b�N�I������
				nNowEnemy = nCntEnemy;
				g_aLockon[nCntLockon].bUse = true;
			}
		}

		pBoss = GetBoss();
		for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++, pBoss++)
		{
			//���b�N�I�����g���Ă�A�I��
			if (g_aLockon[nCntLockon].bUse == true)
			{
				break;
			}

			//�{�X���g���Ă�A����̃{�X�ȊO�A����ĂȂ�
			if (pBoss->bUse == true && nNowBoss < nCntBoss && pBoss->type != BOSS_SEAGULL && pBoss->state != BOSSSTATE_DEATH)
			{
				//���b�N�I������
				nNowBoss = nCntBoss;
				g_aLockon[nCntLockon].bUse = true;
			}
		}
	}
	nNowEnemy = -1;
	nNowBoss = -1;
	g_pVtxBuffLockon->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntLockon = 0; nCntLockon < MAX_LOCKON; nCntLockon++)
	{
		fRed = 0.0f;
		pEnemy = GetEnemy();
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			//�G�g���Ă�
			if (pEnemy->bUse == true)
			{
				//���b�N�I���g�p��
				if (g_aLockon[nCntLockon].bUse == true && nNowEnemy < nCntEnemy)
				{
					//�G�̃~�T�C���t���O�I���̏ꍇ�A�Ԃ�����
					if (pEnemy->bMissile == true)
					{
						fRed = 0.5f;
					}
					pVtx[0].tex = D3DXVECTOR2(fRed, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(fRed + 0.5f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(fRed, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(fRed + 0.5f, 1.0f);
					g_aLockon[nCntLockon].pos = pEnemy->pos;
					pVtx[0].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x - (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y - (LOCKON_BLOCK / 2.0f), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x + (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y - (LOCKON_BLOCK / 2.0f), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x - (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y + (LOCKON_BLOCK / 2.0f), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x + (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y + (LOCKON_BLOCK / 2.0f), 0.0f);
					nNowEnemy = nCntEnemy;
					break;
				}
			}
		}
		pBoss = GetBoss();
		for (nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++, pBoss++)
		{
			//�{�X�g���Ă�
			if (pBoss->bUse == true)
			{
				//���b�N�I���g�p���A����̃{�X�ȊO�A����ĂȂ�
				if (g_aLockon[nCntLockon].bUse == true && nNowBoss < nCntBoss && pBoss->type != BOSS_SEAGULL && pBoss->state != BOSSSTATE_DEATH)
				{
					//�{�X�̃~�T�C���t���O�I���A�Ԃ�����
					if (pBoss->bMissile == true)
					{
						fRed = 0.5f;
					}
					pVtx[0].tex = D3DXVECTOR2(fRed, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(fRed + 0.5f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(fRed, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(fRed + 0.5f, 1.0f);
					g_aLockon[nCntLockon].pos = pBoss->pos;
					pVtx[0].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x - (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y - (LOCKON_BLOCK / 2.0f), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x + (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y - (LOCKON_BLOCK / 2.0f), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x - (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y + (LOCKON_BLOCK / 2.0f), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aLockon[nCntLockon].pos.x + (LOCKON_BLOCK / 2.0f), g_aLockon[nCntLockon].pos.y + (LOCKON_BLOCK / 2.0f), 0.0f);
					nNowBoss = nCntBoss;
					break;
				}
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffLockon->Unlock();
}

//���b�N�I���V�[�J�[�̕`�揈��
void DrawLockon(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntLockon;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLockon, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureLockon);    //�e�N�X�`���̐ݒ�
	//�|���S���`��
	for (nCntLockon = 0; nCntLockon < MAX_LOCKON; nCntLockon++)
	{
		//�g�p��
		if (g_aLockon[nCntLockon].bUse == true)
		{
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntLockon * 4,
				2);
		}
	}
}

//���Z�b�g
void ResetLockon(void)
{
	int nCntLockon;
	for (nCntLockon = 0; nCntLockon < MAX_LOCKON; nCntLockon++)
	{
		g_aLockon[nCntLockon].bUse = false;
	}
}