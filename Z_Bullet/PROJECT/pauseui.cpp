//-------------------------
//Author:�O��q��
//���U���g���UI����(resultui.cpp)
//-------------------------
#include "pauseui.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturepauseUi[5] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffpauseUI = NULL;//���_�o�b�t�@�ւ̃|�C���^
int g_nSelect;

//����������
HRESULT InitpauseUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	D3DXVECTOR3 pos[4];
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/BgBlack.png",
		&g_pTexturepauseUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/square.png",
		&g_pTexturepauseUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/continue.png",
		&g_pTexturepauseUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/retry.png",
		&g_pTexturepauseUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/quit.png",
		&g_pTexturepauseUi[4]);
	g_nSelect = 0;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 5,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffpauseUI,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
	g_pVtxBuffpauseUI->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̐ݒ�(u,v)float �w�i
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 160);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 160);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 160);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 160);
	pVtx += 4;

	pos[nCntUi] = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	//�e�N�X�`���̐ݒ�(u,v)float �l�p
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(pos[nCntUi].x - 200.0f, pos[nCntUi].y - 240.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos[nCntUi].x + 200.0f, pos[nCntUi].y - 240.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos[nCntUi].x - 200.0f, pos[nCntUi].y + 240.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos[nCntUi].x + 200.0f, pos[nCntUi].y + 240.0f, 0.0f);

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
	nCntUi++;

	pos[nCntUi] = D3DXVECTOR3(640.0f, 210.0f, 0.0f);
	//�e�N�X�`���̐ݒ�(u,v)float ������
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(pos[nCntUi].x - 160.0f, pos[nCntUi].y - 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos[nCntUi].x + 160.0f, pos[nCntUi].y - 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos[nCntUi].x - 160.0f, pos[nCntUi].y + 40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos[nCntUi].x + 160.0f, pos[nCntUi].y + 40.0f, 0.0f);

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
	nCntUi++;

	pos[nCntUi] = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	//�e�N�X�`���̐ݒ�(u,v)float ��蒼��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(pos[nCntUi].x - 160.0f, pos[nCntUi].y - 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos[nCntUi].x + 160.0f, pos[nCntUi].y - 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos[nCntUi].x - 160.0f, pos[nCntUi].y + 40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos[nCntUi].x + 160.0f, pos[nCntUi].y + 40.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx += 4;
	nCntUi++;

	pos[nCntUi] = D3DXVECTOR3(640.0f, 510.0f, 0.0f);
	//�e�N�X�`���̐ݒ�(u,v)float �^�C�g��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(pos[nCntUi].x - 160.0f, pos[nCntUi].y - 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos[nCntUi].x + 160.0f, pos[nCntUi].y - 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos[nCntUi].x - 160.0f, pos[nCntUi].y + 40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos[nCntUi].x + 160.0f, pos[nCntUi].y + 40.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffpauseUI->Unlock();

	return S_OK;
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
}

//UI�̍X�V����
void UpdatepauseUi(void)
{
	if (GetKeyboardKey(DIK_UP) == true || CrossKey(0) == true)
	{
		PlaySound(SOUND_LABEL_SELECT);
		int nSelect;
		nSelect = g_nSelect;
		VERTEX_2D *pVtx;//���_���ւ̃|�C���^
		//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
		g_pVtxBuffpauseUI->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (g_nSelect + 2) * 4;
		//�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_nSelect--;
		if (g_nSelect < 0)
		{
			g_nSelect = 2;
		}

		pVtx += (g_nSelect - nSelect) * 4;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffpauseUI->Unlock();
	}
	if (GetKeyboardKey(DIK_DOWN) == true || CrossKey(18000) == true)
	{
		PlaySound(SOUND_LABEL_SELECT);
		int nSelect;
		nSelect = g_nSelect;
		VERTEX_2D *pVtx;//���_���ւ̃|�C���^
						//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
		g_pVtxBuffpauseUI->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (g_nSelect + 2) * 4;
		//�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_nSelect++;
		if (g_nSelect > 2)
		{
			g_nSelect = 0;
		}

		pVtx += (g_nSelect - nSelect) * 4;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffpauseUI->Unlock();
	}
}


//�`�揈��
void DrawpauseUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();//�f�o�C�X�̎擾
	int nCntUI;
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffpauseUI, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�
	for (nCntUI = 0; nCntUI < 5; nCntUI++)
	{
		pDevice->SetTexture(0, g_pTexturepauseUi[nCntUI]);//�e�N�X�`���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);//�|���S���̕`��
	}
}

int GetSelect(void)
{
	return g_nSelect;
}

void ResetpauseUi(void)
{
	g_nSelect = 0;
	int nCntUI;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
	g_pVtxBuffpauseUI->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * 2;
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	for (nCntUI = 0; nCntUI < 2; nCntUI++)
	{
		pVtx += 4;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffpauseUI->Unlock();
}