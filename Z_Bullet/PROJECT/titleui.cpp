//-------------------------
//Author:�O��q��
//�I�����UI����(choiceui.cpp)
//-------------------------
#include "titleui.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturetitleUi[2] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitleUI = NULL;//���_�o�b�t�@�ւ̃|�C���^
int g_nClear;
bool g_bPressClear;

//����������
void InittitleUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	g_bPressClear = true;
	pDevice = GetDevice();

	D3DXVECTOR3 pos;

	pos = D3DXVECTOR3(640.0f, 500.0f, 0.0f);
	g_nClear = 0;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufftitleUI,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/title.png",
		&g_pTexturetitleUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/press.png",
		&g_pTexturetitleUi[1]);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
	g_pVtxBufftitleUI->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̐ݒ�(u,v)float
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx += 4;

	//�e�N�X�`���̐ݒ�(u,v)float
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(pos.x - 240.0f, pos.y - 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 240.0f, pos.y - 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 240.0f, pos.y + 40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 240.0f, pos.y + 40.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufftitleUI->Unlock();
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
	if (g_pVtxBufftitleUI != NULL)
	{
		g_pVtxBufftitleUI->Release();
		g_pVtxBufftitleUI = NULL;
	}
}

//UI�̍X�V����
void UpdatetitleUi(void)
{
	if (g_bPressClear == true)
	{
		g_nClear -= 15;
		if (g_nClear <= 0)
		{
			g_nClear = 0;
			g_bPressClear = false;
		}
	}
	else
	{
		g_nClear += 15;
		if (g_nClear >= 255)
		{
			g_nClear = 255;
			g_bPressClear = true;
		}
	}
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
	g_pVtxBufftitleUI->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nClear);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nClear);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nClear);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nClear);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufftitleUI->Unlock();
}


//�`�揈��
void DrawtitleUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();//�f�o�C�X�̎擾
	int nCntUI;
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufftitleUI, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�
	for (nCntUI = 0; nCntUI < 2; nCntUI++)
	{
		pDevice->SetTexture(0, g_pTexturetitleUi[nCntUI]);//�e�N�X�`���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);//�|���S���̕`��
	}
}