//-------------------------
//Author:�O��q��
//�I�����UI����(choiceui.cpp)
//-------------------------
#include "titleui.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturetitleUi[3] = {};    //�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_atitlePos[3],g_atitleCenter[3];   //�e�|���S���̈ʒu(�^�C�g�����S�AJ�L�[)
RECT g_recttitle[3];
D3DXVECTOR3 g_Scaletitle[3];
D3DXMATRIX g_mtxtitleUi[3];
D3DXCOLOR g_colortitle[3];
bool g_bPressClear;

//����������
void InittitleUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	g_bPressClear = true;
	pDevice = GetDevice();

	g_atitlePos[nCntUi] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�^�C�g��
	g_recttitle[nCntUi].top = 0;
	g_recttitle[nCntUi].left = 0;
	g_recttitle[nCntUi].right = 2048;
	g_recttitle[nCntUi].bottom = 1024;
	g_Scaletitle[nCntUi] = D3DXVECTOR3(0.65f, 0.75f, 0.0f);
	g_atitleCenter[nCntUi] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_colortitle[nCntUi] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	nCntUi++;

	g_atitlePos[nCntUi] = D3DXVECTOR3(0.0f, 70.0f, 0.0f);//�^�C�g��
	g_recttitle[nCntUi].top = 0;
	g_recttitle[nCntUi].left = 0;
	g_recttitle[nCntUi].right = 512;
	g_recttitle[nCntUi].bottom = 256;
	g_Scaletitle[nCntUi] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	g_atitleCenter[nCntUi] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_colortitle[nCntUi] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	nCntUi++;

	g_atitlePos[nCntUi] = D3DXVECTOR3(300.0f, 430.0f, 0.0f);//PushPressJ
	g_recttitle[nCntUi].top = 0;
	g_recttitle[nCntUi].left = 0;
	g_recttitle[nCntUi].right = 1024;
	g_recttitle[nCntUi].bottom = 128;
	g_Scaletitle[nCntUi] = D3DXVECTOR3(0.4f, 0.4f, 0.0f);
	g_atitleCenter[nCntUi] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_colortitle[nCntUi] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/title.JPG",
		&g_pTexturetitleUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/title.png",
		&g_pTexturetitleUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/press.png",
		&g_pTexturetitleUi[2]);
	
}

//UI�̏I������
void UninittitleUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 3; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturetitleUi[nCntUi] != NULL)
		{
			g_pTexturetitleUi[nCntUi]->Release();
			g_pTexturetitleUi[nCntUi] = NULL;
		}
	}
}

//UI�̍X�V����
void UpdatetitleUi(void)
{
	//�_����
	if (g_bPressClear == true)
	{
		//��������
		g_colortitle[2].a -= 0.04f;
		if (g_colortitle[2].a <= 0.0f)
		{
			g_colortitle[2].a = 0.0f;
			g_bPressClear = false;
		}
	}
	//������
	else
	{
		//�Z������
		g_colortitle[2].a += 0.04f;
		if (g_colortitle[2].a >= 1.0f)
		{
			g_colortitle[2].a = 1.0f;
			g_bPressClear = true;
		}
	}
}


//�`�揈��
void DrawtitleUi(void)
{
	LPD3DXSPRITE pSprite; //�f�o�C�X�̃|�C���^
	int nCntUi;
	pSprite = GetSprite();     //�f�o�C�X���擾����
	for (nCntUi = 0; nCntUi < 3; nCntUi++)
	{
		D3DXMATRIX mtxTransUI, mtxScaleUI;
		//UI�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxtitleUi[nCntUi]);

		//�g�嗦�𔽉f
		D3DXMatrixScaling(&mtxScaleUI, g_Scaletitle[nCntUi].x, g_Scaletitle[nCntUi].y, g_Scaletitle[nCntUi].z);
		D3DXMatrixMultiply(&g_mtxtitleUi[nCntUi], &g_mtxtitleUi[nCntUi], &mtxScaleUI);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransUI, g_atitlePos[nCntUi].x, g_atitlePos[nCntUi].y, g_atitlePos[nCntUi].z);
		D3DXMatrixMultiply(&g_mtxtitleUi[nCntUi], &g_mtxtitleUi[nCntUi], &mtxTransUI);

		//���[���h�}�g���b�N�X�̐ݒ�
		pSprite->SetTransform(&g_mtxtitleUi[nCntUi]);

		//�摜�A�摜�̕`��̈�A�摜�̒��S���W�A�摜���\����ꏊ�A�F
		pSprite->Draw(g_pTexturetitleUi[nCntUi], &g_recttitle[nCntUi], &g_atitleCenter[nCntUi], &g_atitlePos[nCntUi], g_colortitle[nCntUi]);
	}
}