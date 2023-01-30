//--------------------------
//Author:�O��q��
//�藠���̏���(cross.cpp)
//--------------------------
#include "cross.h"
#include "sound.h"
#include "block.h"
#include "target.h"

//�}�N����`
#define MAX_CROSS (16)   //�藠���̍ő吔
#define CROSS_SIZE (40)  //�藠���̃T�C�Y

//�i�C�t�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 BlockMove;
	CROSSROT kniferot;
	float fRot[4];
	int nTime;
	bool bLand;
	bool bLand2;
	bool bSound;
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Cross;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureKnife = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKnife = NULL; //���_�o�b�t�@�ւ̃|�C���^
Cross g_aKnife[MAX_CROSS];

//����������
void InitCross(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntKnife;
	int nCntRot;
	pDevice = GetDevice();

	//�藠���̏�����
	for (nCntKnife = 0; nCntKnife < MAX_CROSS; nCntKnife++)
	{
		g_aKnife[nCntKnife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aKnife[nCntKnife].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aKnife[nCntKnife].BlockMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aKnife[nCntKnife].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aKnife[nCntKnife].nTime = 0;
		g_aKnife[nCntKnife].kniferot = CROSS_UP;
		g_aKnife[nCntKnife].bUse = false;
		g_aKnife[nCntKnife].bSound = false;
		for (nCntRot = 0; nCntRot < 4; nCntRot++)
		{
			g_aKnife[nCntKnife].fRot[nCntRot] = 0.0f;
		}
		g_aKnife[nCntKnife].bLand = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/closs.png",
		&g_pTextureKnife);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CROSS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffKnife,
		NULL);
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffKnife->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntKnife = 0; nCntKnife < MAX_CROSS; nCntKnife++)
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
	g_pVtxBuffKnife->Unlock();
}

//�藠���̏I������
void UninitCross(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureKnife != NULL)
	{
		g_pTextureKnife->Release();
		g_pTextureKnife = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffKnife != NULL)
	{
		g_pVtxBuffKnife->Release();
		g_pVtxBuffKnife = NULL;
	}
}

//�藠���̍X�V����
void UpdateCross(void)
{
	int nCntKnife;
	VERTEX_2D *pVtx;
	g_pVtxBuffKnife->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntKnife = 0; nCntKnife < MAX_CROSS; nCntKnife++)
	{
		//�g���Ă�
		if (g_aKnife[nCntKnife].bUse == true)
		{
			g_aKnife[nCntKnife].posOld = g_aKnife[nCntKnife].pos;
			//�ړ�������
			g_aKnife[nCntKnife].pos += g_aKnife[nCntKnife].move;
			int nCntRot;
			if (g_aKnife[nCntKnife].bLand2 == false) //�܂����ł���
			{
				//��]������
				for (nCntRot = 0; nCntRot < 4; nCntRot++)
				{
					g_aKnife[nCntKnife].fRot[nCntRot] -= 0.1f;
					if (g_aKnife[nCntKnife].fRot[nCntRot] <= -1.0f)
					{
						g_aKnife[nCntKnife].fRot[nCntRot] += 2.0f;
					}
				}
			}
			else //�ǂ����Ɏh������
			{
				//���Ԃ����Ǝg�p���ĂȂ���Ԃɂ���
				g_aKnife[nCntKnife].nTime++;
				if (g_aKnife[nCntKnife].nTime >= 20)
				{
					g_aKnife[nCntKnife].bUse = false;
				}
			}

			//�I�ɓ�����ƁA����
			if (BreakTarget(g_aKnife[nCntKnife].pos, CROSS_SIZE / 2, CROSS_SIZE / 2) == true)
			{
				g_aKnife[nCntKnife].bUse = false;
				PlaySound(SOUND_LABEL_TARGETBREAK);
			}

			//�u���b�N�Ƃ̓����蔻��
			g_aKnife[nCntKnife].bLand = CollisionBlock(&g_aKnife[nCntKnife].pos, &g_aKnife[nCntKnife].posOld, &g_aKnife[nCntKnife].move, CROSS_SIZE / 2, CROSS_SIZE / 2, &g_aKnife[nCntKnife].BlockMove, 1);
			
			//���������Ƃ��A����炷
			if (g_aKnife[nCntKnife].bLand == true)
			{
				g_aKnife[nCntKnife].bLand2 = true;
				if (g_aKnife[nCntKnife].bSound == false)
				{
					PlaySound(SOUND_LABEL_CROSSBLOCK);
					g_aKnife[nCntKnife].bSound = true;
				}
			}

			//��ʊO�ɂ����������
			if (g_aKnife[nCntKnife].pos.x <= -CROSS_SIZE / 2) //���s�����ꍇ
			{
				g_aKnife[nCntKnife].bUse = false;
			}
			if (g_aKnife[nCntKnife].pos.y <= -CROSS_SIZE) //��s�����ꍇ
			{
				g_aKnife[nCntKnife].bUse = false;
			}
			if (g_aKnife[nCntKnife].pos.x >= SCREEN_WIDTH + (CROSS_SIZE / 2)) //�E�s�����ꍇ
			{
				g_aKnife[nCntKnife].bUse = false;
			}
			if (g_aKnife[nCntKnife].pos.y >= SCREEN_HEIGHT + CROSS_SIZE) //���s�����ꍇ
			{
				g_aKnife[nCntKnife].bUse = false;
			}


			pVtx[0].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[0]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[0]), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[1]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[1]), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[2]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[2]), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[3]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[3]), 0.0f);
		}
		pVtx += 4;
	}
	g_pVtxBuffKnife->Unlock();
}

//�`�揈��
void DrawCross(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntKnife;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffKnife, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntKnife = 0; nCntKnife < CROSS_SIZE; nCntKnife++)
	{
		if (g_aKnife[nCntKnife].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureKnife);    //�e�N�X�`���̐ݒ�
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntKnife * 4,
				2);
		}
	}
}

//�藠���̐ݒ菈��
void SetCross(D3DXVECTOR3 pos, CROSSROT Crossrot)
{
	int nCntKnife;
	VERTEX_2D *pVtx;
	g_pVtxBuffKnife->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntKnife = 0; nCntKnife < CROSS_SIZE; nCntKnife++)
	{
		if (g_aKnife[nCntKnife].bUse == false)
		{
			g_aKnife[nCntKnife].pos = D3DXVECTOR3(pos.x, pos.y - 40.0f, pos.z);
			g_aKnife[nCntKnife].bUse = true;
			g_aKnife[nCntKnife].kniferot = Crossrot;
			g_aKnife[nCntKnife].nTime = 0;
			g_aKnife[nCntKnife].bLand = false;
			g_aKnife[nCntKnife].bLand2 = false;
			g_aKnife[nCntKnife].bSound = false;
			g_aKnife[nCntKnife].BlockMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aKnife[nCntKnife].posOld = pos;
			g_aKnife[nCntKnife].fRot[0] = -0.75f;
			g_aKnife[nCntKnife].fRot[1] = 0.75f;
			g_aKnife[nCntKnife].fRot[2] = -0.25f;
			g_aKnife[nCntKnife].fRot[3] = 0.25f;
			switch (Crossrot)
			{
			case CROSS_UP:
				g_aKnife[nCntKnife].move = D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * 15.0f, cosf(D3DX_PI * 1.0f) * 15.0f, 0.0f);
				break;
			case CROSS_RIGHT:
				g_aKnife[nCntKnife].move = D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 15.0f, cosf(D3DX_PI * 0.5f) * 15.0f, 0.0f);
				break;
			case CROSS_DOWN:
				g_aKnife[nCntKnife].move = D3DXVECTOR3(sinf(D3DX_PI * 0.0f) * 15.0f, cosf(D3DX_PI * 0.0f) * 15.0f, 0.0f);
				break;
			case CROSS_LEFT:
				g_aKnife[nCntKnife].move = D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 15.0f, cosf(D3DX_PI * -0.5f) * 15.0f, 0.0f);
				break;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[0]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[0]), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[1]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[1]), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[2]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[2]), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aKnife[nCntKnife].pos.x + (CROSS_SIZE / 2) * sinf(D3DX_PI * g_aKnife[nCntKnife].fRot[3]), g_aKnife[nCntKnife].pos.y + (CROSS_SIZE / 2) * cosf(D3DX_PI * g_aKnife[nCntKnife].fRot[3]), 0.0f);
			PlaySound(SOUND_LABEL_THROW);
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffKnife->Unlock();
}

//�S������
void ResetCross(void)
{
	int nCntKnife;
	for (nCntKnife = 0; nCntKnife < CROSS_SIZE; nCntKnife++)
	{
		g_aKnife[nCntKnife].bUse = false;
	}
}