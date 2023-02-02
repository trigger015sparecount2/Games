//--------------------------
//Author:�O��q��
//�t�F�[�h�A�E�g�̏���(fade.cpp)
//--------------------------
#include "fade.h"
#include "game.h"
#include "ui.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^
FADE g_fade;									//�t�F�[�h�̏��
MODE g_modeNext;								//���̉��(���[�h)
D3DXCOLOR g_colorFade;							//�t�F�[�h�̐F
int g_nBlackTime;								//�Â����鎞��
bool g_bSetMode;								//���̃��[�h�Ɉڍs���邩

//����������
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_bSetMode = true;
	g_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_nBlackTime = 0;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�V���[�e�B���O�������.JPG",
		&g_pTextureFade);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void **)&pVtx, 0);
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
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//�I������
void UninitFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//�X�V����
void UpdateFade(void)
{
	//�ʏ킶��Ȃ�
	if (g_fade != FADE_NONE)
	{
		//�t�F�[�h�C��
		if (g_fade == FADE_IN)
		{
			//�F��������
			g_colorFade.a -= 0.02f;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		//�t�F�[�h�A�E�g
		else if (g_fade == FADE_OUT)
		{
			//�F�Z������
			g_colorFade.a += 0.02f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_nBlackTime++;

				//��莞�ԑҋ@
				if (g_nBlackTime >= 180)
				{
					g_nBlackTime = 0;
					g_fade = FADE_IN;
					//���[�h�̐ݒ肷��
					if (g_bSetMode == true)
					{
						SetMode(g_modeNext);
					}
					//���[�h�؂�ւ��Ȃ��ꍇ�A���̃X�e�[�W�Ɉڍs
					else
					{
						NextStage();
						NextGame();
					}
				}
			}
		}

		VERTEX_2D *pVtx; //���_���ւ̃|�C���^
		g_pVtxBuffFade->Lock(0, 0, (void **)&pVtx, 0);
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
		g_pVtxBuffFade->Unlock();
	}
}

//�`�揈��
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

//�t�F�[�h�̐ݒ菈��
void SetFade(MODE modeNext, bool bSetMode)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_bSetMode = bSetMode;
}

//�t�F�[�h�̎擾����
FADE GetFade(void)
{
	return g_fade;
}