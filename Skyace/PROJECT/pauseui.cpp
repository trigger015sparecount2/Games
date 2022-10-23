//-------------------------
//Author:�O��q��
//�|�[�Y���UI����(pauseui.cpp)
//-------------------------
#include "pauseui.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturepauseUi[5] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffpauseUi = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_apauseUiPos[4];   //�e�|���S���̈ʒu(�l�p�A��*3)
int g_ncommand;

//����������
void InitpauseUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	g_ncommand = 0;
	pDevice = GetDevice();
	g_apauseUiPos[nCntUi] = D3DXVECTOR3(640.0f, 360.0f, 0.0f);//�l�p
	for (nCntUi++; nCntUi < 4; nCntUi++)
	{
		g_apauseUiPos[nCntUi] = D3DXVECTOR3(640.0f, 230.0f + (nCntUi - 1) * 100.0f, 0.0f);//������A���̃X�e�[�W�����蒼���A�^�C�g���ɖ߂�
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/.png",
		&g_pTexturepauseUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�c���l�p.png",
		&g_pTexturepauseUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/gamestart.png",
		&g_pTexturepauseUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/restartgame.png",
		&g_pTexturepauseUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/QUIT.png",
		&g_pTexturepauseUi[4]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 5,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffpauseUi,
		NULL);
	VERTEX_2D *pVtx;
	nCntUi = 0;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffpauseUi->Lock(0, 0, (void **)&pVtx, 0);
	//���Â�
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 150);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;
	//�l�p
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x - 150, g_apauseUiPos[nCntUi].y - 250, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x + 150, g_apauseUiPos[nCntUi].y - 250, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x - 150, g_apauseUiPos[nCntUi].y + 250, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x + 150, g_apauseUiPos[nCntUi].y + 250, 0.0f);
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
	for (nCntUi++; nCntUi < 4; nCntUi++)
	{
		//����
		//���_���W�̐ݒ�
		if (nCntUi < 3)
		{
			pVtx[0].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x - 130, g_apauseUiPos[nCntUi].y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x + 130, g_apauseUiPos[nCntUi].y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x - 130, g_apauseUiPos[nCntUi].y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x + 130, g_apauseUiPos[nCntUi].y + 25, 0.0f);
		}
		else
		{
			pVtx[0].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x - 60, g_apauseUiPos[nCntUi].y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x + 60, g_apauseUiPos[nCntUi].y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x - 60, g_apauseUiPos[nCntUi].y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_apauseUiPos[nCntUi].x + 60, g_apauseUiPos[nCntUi].y + 25, 0.0f);
		}
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
	g_pVtxBuffpauseUi->Unlock();
}

//UI�̏I������
void UninitpauseUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 5; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturepauseUi[nCntUi] != NULL)
		{
			g_pTexturepauseUi[nCntUi]->Release();
			g_pTexturepauseUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffpauseUi != NULL)
	{
		g_pVtxBuffpauseUi->Release();
		g_pVtxBuffpauseUi = NULL;
	}
}

//UI�̍X�V����
void UpdatepauseUi(void)
{
	int nCntpauseUi;
	if (GetKeyboardTrigger(DIK_W) == true && GetKeyboardRelease(DIK_W) == false)
	{
		PlaySound(SOUND_LABEL_CHOICE000);
		g_ncommand--;
		if (g_ncommand < 0)
		{
			g_ncommand = 2;
		}
	}
	if (GetKeyboardTrigger(DIK_S) == true && GetKeyboardRelease(DIK_S) == false)
	{
		PlaySound(SOUND_LABEL_CHOICE000);
		g_ncommand = (g_ncommand + 1) % 3;
	}
	if (GetKeyboardTrigger(DIK_P) == true && GetKeyboardRelease(DIK_P) == false)
	{
		g_ncommand = 0;
	}
	if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false)
	{
		PlaySound(SOUND_LABEL_YES000);
		switch (g_ncommand)
		{
		case 0:
			StartGame();
			break;
		case 1:
			RestartGame();
			StartGame();
			g_ncommand = 0;
			break;
		case 2:
			SetFade(MODE_TITLE, true);
			break;
		}
	}
	for (nCntpauseUi = 0; nCntpauseUi < 3; nCntpauseUi++)
	{
		VERTEX_2D *pVtx;
		g_pVtxBuffpauseUi->Lock(0, 0, (void **)&pVtx, 0);
		pVtx += nCntpauseUi * 4 + 8;
		pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		g_pVtxBuffpauseUi->Unlock();
	}
	VERTEX_2D *pVtx;
	g_pVtxBuffpauseUi->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += g_ncommand * 4 + 8;
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxBuffpauseUi->Unlock();
}


//�`�揈��
void DrawpauseUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntUi;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffpauseUi, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntUi = 0; nCntUi < 5; nCntUi++)
	{
		pDevice->SetTexture(0, g_pTexturepauseUi[nCntUi]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
	}
}
