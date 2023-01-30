//-------------------------
//Author:�O��q��
//���U���g���UI����(resultui.cpp)
//-------------------------
#include "resultui.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureresultUi[4] = {};    //�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_aresultPos[2], g_aresultCenter[2];   //�e�|���S���̈ʒu
RECT g_rectresult[2];
D3DXVECTOR3 g_Scaleresult[2];
D3DXMATRIX g_mtxresult[2];

//����������
void InitresultUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/gameclear.JPG",
		&g_pTextureresultUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/gameover.JPG",
		&g_pTextureresultUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/clear.png",
		&g_pTextureresultUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/failed.png",
		&g_pTextureresultUi[3]);

	g_aresultPos[nCntUi] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�w�i
	g_rectresult[nCntUi].top = 0;
	g_rectresult[nCntUi].left = 0;
	g_rectresult[nCntUi].right = 2048;
	g_rectresult[nCntUi].bottom = 1024;
	g_aresultCenter[nCntUi] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Scaleresult[nCntUi] = D3DXVECTOR3(0.7f, 0.7f, 1.0f);

	nCntUi++;
	g_aresultPos[nCntUi] = D3DXVECTOR3(200.0f, 30.0f, 0.0f);//����
	g_rectresult[nCntUi].top = 0;
	g_rectresult[nCntUi].left = 0;
	g_rectresult[nCntUi].right = 512;
	g_rectresult[nCntUi].bottom = 128;
	g_aresultCenter[nCntUi] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Scaleresult[nCntUi] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//UI�̏I������
void UninitresultUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 4; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureresultUi[nCntUi] != NULL)
		{
			g_pTextureresultUi[nCntUi]->Release();
			g_pTextureresultUi[nCntUi] = NULL;
		}
	}
}

//UI�̍X�V����
void UpdateresultUi(void)
{

}


//�`�揈��
void DrawresultUi(void)
{
	LPD3DXSPRITE pSprite; //�f�o�C�X�̃|�C���^
	int ntex = 0;
	int nCntui = 0;
	pSprite = GetSprite();     //�f�o�C�X���擾����
	for (nCntui = 0; nCntui < 2; nCntui++)
	{
		D3DXMATRIX mtxTransUI, mtxScaleUI;
		//UI�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxresult[nCntui]);

		//�g�嗦�𔽉f
		D3DXMatrixScaling(&mtxScaleUI, g_Scaleresult[nCntui].x, g_Scaleresult[nCntui].y, g_Scaleresult[nCntui].z);
		D3DXMatrixMultiply(&g_mtxresult[nCntui], &g_mtxresult[nCntui], &mtxScaleUI);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransUI, g_aresultPos[nCntui].x, g_aresultPos[nCntui].y, g_aresultPos[nCntui].z);
		D3DXMatrixMultiply(&g_mtxresult[nCntui], &g_mtxresult[nCntui], &mtxTransUI);

		//���[���h�}�g���b�N�X�̐ݒ�
		pSprite->SetTransform(&g_mtxresult[nCntui]);

		//�摜�A�摜�̕`��̈�A�摜�̒��S���W�A�摜���\����ꏊ�A�F
		if(nCntui == 0)
		{
			if (PlayerHP() > 0)
			{
				ntex = 0;
			}
			else
			{
				ntex = 1;
			}
		}
		else
		{
			ntex += 2;
		}
		pSprite->Draw(g_pTextureresultUi[ntex], &g_rectresult[nCntui], &g_aresultCenter[nCntui], &g_aresultPos[nCntui], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
