//-------------------------
//Author:�O��q��
//�I�����UI����(choiceui.cpp)
//-------------------------
#include "titleui.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturetitleUi[2] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitleUi = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_atitlePos[2];   //�e�|���S���̈ʒu(�^�C�g�����S�AJ�L�[)
bool g_bPressClear;
int g_nPressClear;

//����������
void InittitleUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	g_nPressClear = 255;
	g_bPressClear = true;
	pDevice = GetDevice();
	g_atitlePos[nCntUi] = D3DXVECTOR3(640.0f, 100.0f, 0.0f);//�^�C�g��
	nCntUi++;
	g_atitlePos[nCntUi] = D3DXVECTOR3(640.0f, 600.0f, 0.0f);//PushPressJ

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�^�C�g�����S.png",
		&g_pTexturetitleUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/PressJ.png",
		&g_pTexturetitleUi[1]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufftitleUi,
		NULL);
	
	VERTEX_2D *pVtx;
	nCntUi = 0;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBufftitleUi->Lock(0, 0, (void **)&pVtx, 0);
	//�^�C�g�����S
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x - 300.0f, g_atitlePos[nCntUi].y - 80.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x + 300.0f, g_atitlePos[nCntUi].y - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x - 300.0f, g_atitlePos[nCntUi].y + 80.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x + 300.0f, g_atitlePos[nCntUi].y + 80.0f, 0.0f);
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
	nCntUi++;
	//pressJkey
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x - 230.0f, g_atitlePos[nCntUi].y - 30.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x + 230.0f, g_atitlePos[nCntUi].y - 30.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x - 230.0f, g_atitlePos[nCntUi].y + 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_atitlePos[nCntUi].x + 230.0f, g_atitlePos[nCntUi].y + 30.0f, 0.0f);
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
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufftitleUi->Unlock();
}

//UI�̏I������
void UninittitleUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 2; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturetitleUi[nCntUi] != NULL)
		{
			g_pTexturetitleUi[nCntUi]->Release();
			g_pTexturetitleUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBufftitleUi != NULL)
	{
		g_pVtxBufftitleUi->Release();
		g_pVtxBufftitleUi = NULL;
	}
}

//UI�̍X�V����
void UpdatetitleUi(void)
{
	//PRESS�𖾂邭������Â������肷��
	if (g_bPressClear == true)
	{
		g_nPressClear -= 15;
		if (g_nPressClear <= 0)
		{
			g_nPressClear = 0;
			g_bPressClear = false;
		}
	}
	else
	{
		g_nPressClear += 15;
		if (g_nPressClear >= 255)
		{
			g_nPressClear = 255;
			g_bPressClear = true;
		}
	}

	VERTEX_2D *pVtx;
	g_pVtxBufftitleUi->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += 4;
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nPressClear);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nPressClear);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nPressClear);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nPressClear);
	g_pVtxBufftitleUi->Unlock();
}


//�`�揈��
void DrawtitleUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntUi = 0;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufftitleUi, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntUi = 0; nCntUi < 2; nCntUi++)
	{
		pDevice->SetTexture(0, g_pTexturetitleUi[nCntUi]);//�^�C�g���Apress
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
	}
}