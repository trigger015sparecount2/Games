//-------------------------
//Author:�O��q��
//UI����(ui.cpp)
//-------------------------
#include "ui.h"
#include "player.h"

//�}�N����`
#define MAX_UI (2)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureUi[MAX_UI] = {};	 //�e�N�X�`���ւ̃|�C���^
RECT g_rectUI[MAX_UI]; //�摜�̕`��̈�
D3DXVECTOR3 g_center[MAX_UI], g_pos[MAX_UI]; //�摜�̒��S�A�\����ꏊ
D3DXVECTOR3 g_Scale[MAX_UI];
D3DXMATRIX g_mtxUi[MAX_UI];

//����������
HRESULT InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HPgaugeGw.png",
		&g_pTextureUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HPgauge.png",
		&g_pTextureUi[1]);

	g_rectUI[0].top = 0;
	g_rectUI[0].left = 0;
	g_rectUI[0].bottom = 64;
	g_rectUI[0].right = 512;
	g_center[0].x = 0.0f;
	g_center[0].y = 0.0f;
	g_pos[0].x = 530.0f;
	g_pos[0].y = 390.0f;
	g_Scale[0] = D3DXVECTOR3(0.7f, 0.7f, 1.0f);

	g_rectUI[1].top = 0;
	g_rectUI[1].left = 0;
	g_rectUI[1].bottom = 64;
	g_rectUI[1].right = 512;
	g_center[1].x = 1230.0f;
	g_center[1].y = 0.0f;
	g_pos[1].x = 1230.0f;
	g_pos[1].y = 402.9f;
	g_Scale[1] = D3DXVECTOR3(-0.64f, 0.65f, 1.0f);
	return S_OK;
}

//UI�̏I������
void UninitUi(void)
{
	int nCntTex;
	for (nCntTex = 0; nCntTex < MAX_UI; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureUi[nCntTex] != NULL)
		{
			g_pTextureUi[nCntTex]->Release();
			g_pTextureUi[nCntTex] = NULL;
		}
	}
}

//UI�̍X�V����
void UpdateUi(void)
{
	
}


//�`�揈��
void DrawUi(void)
{
	LPD3DXSPRITE pSprite; //�f�o�C�X�̃|�C���^
	int nCntUi;
	pSprite = GetSprite();     //�f�o�C�X���擾����
	for (nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		D3DXMATRIX mtxTransUI, mtxScaleUI;
		//UI�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxUi[nCntUi]);

		if (nCntUi == 1)
		{
			//�g�嗦�𔽉f
			D3DXMatrixScaling(&mtxScaleUI, g_Scale[nCntUi].x * PlayerHPRate(), g_Scale[nCntUi].y, g_Scale[nCntUi].z);
		}
		else
		{
			//�g�嗦�𔽉f
			D3DXMatrixScaling(&mtxScaleUI, g_Scale[nCntUi].x, g_Scale[nCntUi].y, g_Scale[nCntUi].z);
		}
		D3DXMatrixMultiply(&g_mtxUi[nCntUi], &g_mtxUi[nCntUi], &mtxScaleUI);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransUI, g_pos[nCntUi].x, g_pos[nCntUi].y, g_pos[nCntUi].z);
		D3DXMatrixMultiply(&g_mtxUi[nCntUi], &g_mtxUi[nCntUi], &mtxTransUI);

		//���[���h�}�g���b�N�X�̐ݒ�
		pSprite->SetTransform(&g_mtxUi[nCntUi]);

		//�摜�A�摜�̕`��̈�A�摜�̒��S���W�A�摜���\����ꏊ�A�F
		pSprite->Draw(g_pTextureUi[nCntUi], &g_rectUI[nCntUi], &g_center[nCntUi], &g_pos[nCntUi], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}