//--------------------------
//Author:�O��q��
//���ꂽ�Ƃ�����(death.cpp)
//--------------------------
#include "death.h"
#include "sound.h"

//�}�N����`
#define DEATH_BLOCK (80.0f)  //�����̑傫��

//�����̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	int nCounterAnim;       //����
	int nPatternAnim;
	bool bUse;       //�g�p���Ă��邩�ǂ���
} Death;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureDeath = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDeath = NULL; //���_�o�b�t�@�ւ̃|�C���^
Death g_aDeath[128];

//����������
void InitDeath(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntDeath;
	//�����̏�����
	for (nCntDeath = 0; nCntDeath < 128; nCntDeath++)
	{
		g_aDeath[nCntDeath].bUse = false;
		g_aDeath[nCntDeath].nCounterAnim = 0;
		g_aDeath[nCntDeath].nPatternAnim = 0;
		g_aDeath[nCntDeath].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/death.png",
		&g_pTextureDeath);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 128,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDeath,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDeath->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntDeath = 0; nCntDeath < 128; nCntDeath++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 220);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 220);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 220);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 220);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDeath->Unlock();
}

//�����̏I������
void UninitDeath(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureDeath != NULL)
	{
		g_pTextureDeath->Release();
		g_pTextureDeath = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffDeath != NULL)
	{
		g_pVtxBuffDeath->Release();
		g_pVtxBuffDeath = NULL;
	}
}

//�����̍X�V����
void UpdateDeath(void)
{
	int nCntDeath;
	for (nCntDeath = 0; nCntDeath < 128; nCntDeath++)
	{
		//�g���Ă�
		if (g_aDeath[nCntDeath].bUse == true)
		{
			//�A�j���[�V�����J�E���g�i�߂�
			g_aDeath[nCntDeath].nCounterAnim++;
			if (g_aDeath[nCntDeath].nCounterAnim == 6)
			{
				//�A�j���[�V�����p�^�[���i�߂�A�J�E���g���Z�b�g
				g_aDeath[nCntDeath].nPatternAnim++;
				g_aDeath[nCntDeath].nCounterAnim = 0;
				//�p�^�[���i��
				if (g_aDeath[nCntDeath].nPatternAnim == 8)
				{
					//����
					g_aDeath[nCntDeath].bUse = false;
				}
			}

			//�p�^�[���ɉ����ăe�N�X�`���̕`�����؂�ւ���
			VERTEX_2D *pVtx;
			g_pVtxBuffDeath->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntDeath * 4;
			pVtx[0].tex = D3DXVECTOR2((float)g_aDeath[nCntDeath].nPatternAnim / 8, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((float)(g_aDeath[nCntDeath].nPatternAnim + 1) / 8, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((float)g_aDeath[nCntDeath].nPatternAnim / 8, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((float)(g_aDeath[nCntDeath].nPatternAnim + 1) / 8, 1.0f);
			g_pVtxBuffDeath->Unlock();
		}
	}
}

//�`�揈��
void DrawDeath(void)
{
	int nCntDeath;
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffDeath, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureDeath);    //�e�N�X�`���̐ݒ�
	for (nCntDeath = 0; nCntDeath < 128; nCntDeath++)
	{
		//�g�p���̂ݕ`��
		if (g_aDeath[nCntDeath].bUse == true)
		{
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntDeath * 4,
				2);
		}
	}
}

//�����̐ݒ菈��
void SetDeath(D3DXVECTOR3 pos, bool bSound)
{
	int nCntDeath;
	VERTEX_2D *pVtx;
	g_pVtxBuffDeath->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntDeath = 0; nCntDeath < 128; nCntDeath++)
	{
		//�g���ĂȂ�
		if (g_aDeath[nCntDeath].bUse == false)
		{
			//�F�X�ݒ�
			g_aDeath[nCntDeath].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aDeath[nCntDeath].pos.x - (DEATH_BLOCK / 2.0f), g_aDeath[nCntDeath].pos.y - (DEATH_BLOCK / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aDeath[nCntDeath].pos.x + (DEATH_BLOCK / 2.0f), g_aDeath[nCntDeath].pos.y - (DEATH_BLOCK / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aDeath[nCntDeath].pos.x - (DEATH_BLOCK / 2.0f), g_aDeath[nCntDeath].pos.y + (DEATH_BLOCK / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aDeath[nCntDeath].pos.x + (DEATH_BLOCK / 2.0f), g_aDeath[nCntDeath].pos.y + (DEATH_BLOCK / 2.0f), 0.0f);
			g_aDeath[nCntDeath].nCounterAnim = 0;
			g_aDeath[nCntDeath].nPatternAnim = 0;
			g_aDeath[nCntDeath].bUse = true;
			if (bSound == true)
			{
				PlaySound(SOUND_LABEL_ENEMYDOWN000);
			}
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffDeath->Unlock();
}

//���Z�b�g
void ResetDeath(void)
{
	int nCntDeath;
	for (nCntDeath = 0; nCntDeath < 128; nCntDeath++)
	{
		g_aDeath[nCntDeath].bUse = false;
	}
}