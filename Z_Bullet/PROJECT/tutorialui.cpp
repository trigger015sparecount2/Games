//-------------------------
//Author:�O��q��
//�`���[�g���A�����UI����(tutorialui.cpp)
//-------------------------
#include "tutorialui.h"
#include "mouse.h"
#include "gamepad.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturetutorialUi[2] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftutoUI = NULL;//���_�o�b�t�@�ւ̃|�C���^

//����������
void InittutorialUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXVECTOR3 pos;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufftutoUI,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/square.png",
		&g_pTexturetutorialUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/tutotext.png",
		&g_pTexturetutorialUi[1]);

	pos = D3DXVECTOR3(1140.0f, 400.0f, 0.0f);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
	g_pVtxBufftutoUI->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̐ݒ�(u,v)float
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(pos.x - 120.0f, pos.y - 180.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 120.0f, pos.y - 180.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 120.0f, pos.y + 180.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 120.0f, pos.y + 180.0f, 0.0f);

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
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.4f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.4f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(pos.x - 115.0f, pos.y - 170.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 115.0f, pos.y - 170.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 115.0f, pos.y + 170.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 115.0f, pos.y + 170.0f, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufftutoUI->Unlock();
}

//UI�̏I������
void UninittutorialUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 2; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturetutorialUi[nCntUi] != NULL)
		{
			g_pTexturetutorialUi[nCntUi]->Release();
			g_pTexturetutorialUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBufftutoUI != NULL)
	{
		g_pVtxBufftutoUI->Release();
		g_pVtxBufftutoUI = NULL;
	}
}

//UI�̍X�V����
void UpdatetutorialUi(void)
{
	if (MouseZ() > 0.0f || PressCrossKey(0) == true && GamePad() == true)
	{

		VERTEX_2D *pVtx;//���_���ւ̃|�C���^
		//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
		g_pVtxBufftutoUI->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4;
		//�e�N�X�`���̐ݒ�(u,v)float
		if (pVtx[0].tex.y > 0.0f)
		{
			pVtx[0].tex.y -= 0.01f;
			pVtx[1].tex.y -= 0.01f;
			pVtx[2].tex.y -= 0.01f;
			pVtx[3].tex.y -= 0.01f;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBufftutoUI->Unlock();
	}
	if (MouseZ() < 0.0f || PressCrossKey(18000) == true)
	{
		VERTEX_2D *pVtx;//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
		g_pVtxBufftutoUI->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4;
		//�e�N�X�`���̐ݒ�(u,v)float
		if (pVtx[2].tex.y < 1.0f)
		{
			pVtx[0].tex.y += 0.01f;
			pVtx[1].tex.y += 0.01f;
			pVtx[2].tex.y += 0.01f;
			pVtx[3].tex.y += 0.01f;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBufftutoUI->Unlock();
	}
}


//�`�揈��
void DrawtutorialUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();//�f�o�C�X�̎擾
	int nCntUI;
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufftutoUI, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�
	for (nCntUI = 0; nCntUI < 2; nCntUI++)
	{
		pDevice->SetTexture(0, g_pTexturetutorialUi[nCntUI]);//�e�N�X�`���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);//�|���S���̕`��
	}
}