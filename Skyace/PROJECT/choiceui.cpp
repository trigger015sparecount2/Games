//-------------------------
//Author:�O��q��
//�I�����UI����(choiceui.cpp)
//-------------------------
#include "choiceui.h"
#include "input.h"
#include "aircraft.h"
#include "fade.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturechoiceUi[18] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffchoiceUi = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_achoicePos[2 + 6 + 2 + 6 + 1];   //�e�|���S���̈ʒu(HUD�퓬�@�A���ꕺ���A*2�A������)
int g_nAtype;	//�퓬�@�̎��
int g_nStype;	//���ꕺ���̎��
int g_nStage;	//�g���Ԗڂ�
int g_nlight;	//�ǂꂾ���������邩
bool g_blight;	//���邭���邩�Â����邩

//����������
void InitchoiceUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	int nCntspecial;
	int nCntsquare;
	g_nAtype = 0;
	g_nStype = 0;
	g_nStage = 0;
	g_nlight = 0;
	g_blight = true;
	pDevice = GetDevice();
	g_achoicePos[nCntUi] = D3DXVECTOR3(400.0f, 270.0f, 0.0f);//�C�[�O���l�p
	nCntUi++;
	g_achoicePos[nCntUi] = D3DXVECTOR3(400.0f, 200.0f, 0.0f);//�C�[�O��
	nCntUi++;
	for (nCntspecial = 0; nCntspecial < 3; nCntspecial++)
	{
		for (nCntsquare = 0; nCntsquare < 2; nCntsquare++)
		{
			g_achoicePos[nCntUi] = D3DXVECTOR3(300.0f + nCntspecial * 100.0f, 400.0f, 0.0f);//�C�[�O�����ꕺ��
			nCntUi++;
		}
	}
	g_achoicePos[nCntUi] = D3DXVECTOR3(800.0f, 270.0f, 0.0f);//�t�����J�[�l�p
	nCntUi++;
	g_achoicePos[nCntUi] = D3DXVECTOR3(800.0f, 200.0f, 0.0f);//�t�����J�[
	nCntUi++;
	for (nCntspecial = 0; nCntspecial < 3; nCntspecial++)
	{
		for (nCntsquare = 0; nCntsquare < 2; nCntsquare++)
		{
			g_achoicePos[nCntUi] = D3DXVECTOR3(700.0f + nCntspecial * 100.0f, 400.0f, 0.0f);//�t�����J�[���ꕺ��
			nCntUi++;
		}
	}
	g_achoicePos[nCntUi] = D3DXVECTOR3(640.0f, 630.0f, 0.0f);//�������l�p
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDeagle.png",
		&g_pTexturechoiceUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDflanker.png",
		&g_pTexturechoiceUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDuav.png",
		&g_pTexturechoiceUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDmissile.png",
		&g_pTexturechoiceUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDbarrier.png",
		&g_pTexturechoiceUi[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDrailgun.png",
		&g_pTexturechoiceUi[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDbombmissile.png",
		&g_pTexturechoiceUi[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDlaser.png",
		&g_pTexturechoiceUi[7]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�c���l�p.png",
		&g_pTexturechoiceUi[8]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/square.png",
		&g_pTexturechoiceUi[9]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�C�[�O��������.png",
		&g_pTexturechoiceUi[10]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�t�����J�[������.png",
		&g_pTexturechoiceUi[11]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/UAV������.png",
		&g_pTexturechoiceUi[12]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�}���`���b�N�~�T�C��������.png",
		&g_pTexturechoiceUi[13]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�o���A������.png",
		&g_pTexturechoiceUi[14]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/���[���K��������.png",
		&g_pTexturechoiceUi[15]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�{���~�T�C��������.png",
		&g_pTexturechoiceUi[16]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/���[�U�[������.png",
		&g_pTexturechoiceUi[17]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 17,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffchoiceUi,
		NULL);

	VERTEX_2D *pVtx;
	nCntUi = 0;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffchoiceUi->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntsquare = 0; nCntsquare < 2; nCntsquare++)
	{
		//�퓬�@��g�l�p
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 160.0f, g_achoicePos[nCntUi].y - 260.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 160.0f, g_achoicePos[nCntUi].y - 260.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 160.0f, g_achoicePos[nCntUi].y + 260.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 160.0f, g_achoicePos[nCntUi].y + 260.0f, 0.0f);
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
		//�퓬�@
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 100.0f, g_achoicePos[nCntUi].y - 130.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 100.0f, g_achoicePos[nCntUi].y - 130.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 100.0f, g_achoicePos[nCntUi].y + 130.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 100.0f, g_achoicePos[nCntUi].y + 130.0f, 0.0f);
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
		if (nCntsquare == 0)//�C�[�O��
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);
		}
		else//�t�����J�[
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
		}
		pVtx += 4;
		nCntUi++;
		for (nCntspecial = 0; nCntspecial < 3; nCntspecial++)//���ꕺ��
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 40.0f, g_achoicePos[nCntUi].y - 40.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 40.0f, g_achoicePos[nCntUi].y - 40.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 40.0f, g_achoicePos[nCntUi].y + 40.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 40.0f, g_achoicePos[nCntUi].y + 40.0f, 0.0f);
			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx += 4;
			nCntUi++;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 30.0f, g_achoicePos[nCntUi].y - 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 30.0f, g_achoicePos[nCntUi].y - 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 30.0f, g_achoicePos[nCntUi].y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 30.0f, g_achoicePos[nCntUi].y + 30.0f, 0.0f);
			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx += 4;
			nCntUi++;
		}
	}
	//�������l�p
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 630.0f, g_achoicePos[nCntUi].y - 80.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 630.0f, g_achoicePos[nCntUi].y - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x - 630.0f, g_achoicePos[nCntUi].y + 80.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_achoicePos[nCntUi].x + 630.0f, g_achoicePos[nCntUi].y + 80.0f, 0.0f);
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
	g_pVtxBuffchoiceUi->Unlock();
}

//UI�̏I������
void UninitchoiceUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 18; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturechoiceUi[nCntUi] != NULL)
		{
			g_pTexturechoiceUi[nCntUi]->Release();
			g_pTexturechoiceUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffchoiceUi != NULL)
	{
		g_pVtxBuffchoiceUi->Release();
		g_pVtxBuffchoiceUi = NULL;
	}
}

//UI�̍X�V����
void UpdatechoiceUi(void)
{
	int nCntchoiceUi;
	int nCntSquare;

	//���邭����
	if (g_blight == true)
	{
		g_nlight++;
		if (g_nlight >= 30)
		{
			g_nlight = 30;
			g_blight = false;
		}
	}
	//�Â�����
	else
	{
		g_nlight--;
		if (g_nlight <= 0)
		{
			g_nlight = 0;
			g_blight = true;
		}
	}

	//�@�̑I��
	if (g_nStage == 0)
	{
		g_nStype = 0;
		
		//���E�ɑI��
		if (GetKeyboardTrigger(DIK_D) == true && GetKeyboardRelease(DIK_D) == false)
		{
			PlaySound(SOUND_LABEL_CHOICE000);
			g_nAtype = (g_nAtype + 1) % 2;
		}
		else if (GetKeyboardTrigger(DIK_A) == true && GetKeyboardRelease(DIK_A) == false)
		{
			PlaySound(SOUND_LABEL_CHOICE000);
			g_nAtype--;
			if (g_nAtype == -1)
			{
				g_nAtype = 1;
			}
		}

		//����
		if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false)
		{
			g_nStage++;
			PlaySound(SOUND_LABEL_YES000);
		}

		//�S�����Â��`��
		for (nCntchoiceUi = 0; nCntchoiceUi < 16; nCntchoiceUi++)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffchoiceUi->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntchoiceUi * 4;
			pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 255);
			g_pVtxBuffchoiceUi->Unlock();
		}

		//�I�������ق��𖾂邭�`��
		VERTEX_2D *pVtx;
		g_pVtxBuffchoiceUi->Lock(0, 0, (void **)&pVtx, 0);
		pVtx += g_nAtype * 4 * 8;
		for (nCntchoiceUi = 0; nCntchoiceUi < 2; nCntchoiceUi++)
		{
			pVtx[0].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx[1].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx[2].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx[3].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx += 4;
		}
		g_pVtxBuffchoiceUi->Unlock();
	}
	//���ꕺ���I��
	else
	{
		//���ꕺ����S���Â�����
		for (nCntSquare = 0; nCntSquare < 2; nCntSquare++)
		{
			for (nCntchoiceUi = 0; nCntchoiceUi < 6; nCntchoiceUi++)
			{
				VERTEX_2D *pVtx;
				g_pVtxBuffchoiceUi->Lock(0, 0, (void **)&pVtx, 0);
				pVtx += nCntchoiceUi * 4 + nCntSquare * 32 + 8;
				pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 255);
				pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 255);
				pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 255);
				pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 255);
				g_pVtxBuffchoiceUi->Unlock();
			}
		}

		//�I��������S�����邭����
		VERTEX_2D *pVtx;
		g_pVtxBuffchoiceUi->Lock(0, 0, (void **)&pVtx, 0);
		pVtx += g_nAtype * 32 + g_nStype * 8 + 8;
		for (nCntchoiceUi = 0; nCntchoiceUi < 2; nCntchoiceUi++)
		{
			pVtx[0].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx[1].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx[2].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx[3].col = D3DCOLOR_RGBA(225 + g_nlight, 225 + g_nlight, 225 + g_nlight, 255);
			pVtx += 4;
		}
		g_pVtxBuffchoiceUi->Unlock();

		//���E�ɑI��
		if (GetKeyboardTrigger(DIK_D) == true && GetKeyboardRelease(DIK_D) == false)
		{
			PlaySound(SOUND_LABEL_CHOICE000);
			g_nStype = (g_nStype + 1) % 3;
		}
		else if (GetKeyboardTrigger(DIK_A) == true && GetKeyboardRelease(DIK_A) == false)
		{
			PlaySound(SOUND_LABEL_CHOICE000);
			g_nStype--;
			if (g_nStype == -1)
			{
				g_nStype = 2;
			}
		}

		//����
		if (GetKeyboardTrigger(DIK_J) == true && GetKeyboardRelease(DIK_J) == false)
		{
			PlaySound(SOUND_LABEL_YES000);
			SetFade(MODE_GAME, true);
			SetTypeAircraft(g_nAtype, g_nStype);
		}
		//�L�����Z��
		else if (GetKeyboardTrigger(DIK_I) == true && GetKeyboardRelease(DIK_I) == false)
		{
			PlaySound(SOUND_LABEL_CANCEL000);
			g_nStage--;
		}
	}
}


//�`�揈��
void DrawchoiceUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntUi = 0;
	int nCntSpecial;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffchoiceUi, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTexturechoiceUi[8]);//�C�[�O���l�p
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	pDevice->SetTexture(0, g_pTexturechoiceUi[0]);//�C�[�O��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	for (nCntSpecial = 0; nCntSpecial < 3; nCntSpecial++)
	{
		pDevice->SetTexture(0, g_pTexturechoiceUi[9]);//���ꕺ���l�p
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
		nCntUi++;
		pDevice->SetTexture(0, g_pTexturechoiceUi[nCntSpecial + 2]);//���ꕺ��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
		nCntUi++;
	}
	pDevice->SetTexture(0, g_pTexturechoiceUi[8]);//�t�����J�[�l�p
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	pDevice->SetTexture(0, g_pTexturechoiceUi[1]);//�t�����J�[
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	for (nCntSpecial = 0; nCntSpecial < 3; nCntSpecial++)
	{
		pDevice->SetTexture(0, g_pTexturechoiceUi[9]);//���ꕺ���l�p
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
		nCntUi++;
		pDevice->SetTexture(0, g_pTexturechoiceUi[nCntSpecial + 5]);//���ꕺ��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
		nCntUi++;
	}
	if (g_nStage == 0)
	{
		pDevice->SetTexture(0, g_pTexturechoiceUi[10 + g_nAtype]);//�@�̐�����
	}
	else
	{
		pDevice->SetTexture(0, g_pTexturechoiceUi[12 + (g_nAtype * 3) + g_nStype]);//����������
	}
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
}
