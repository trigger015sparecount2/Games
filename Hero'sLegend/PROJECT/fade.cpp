//--------------------------
//Author:�O��q��
//�t�F�[�h�A�E�g�̏���(fade.cpp)
//--------------------------
#include "fade.h"
#include "camera.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXMATRIX g_mtxWorldFade;
D3DXVECTOR3 g_posFade;
FADE g_fade;                                   //�t�F�[�h�̏��
MODE g_modeNext;                               //���̉��(���[�h)
D3DXCOLOR g_colorFade;                         //�t�F�[�h�̐F

//����������
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�V���[�e�B���O�������.JPG",
		&g_pTextureFade);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-10000.0f, 10000.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(10000.0f, 10000.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-10000.0f, -10000.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(10000.0f, -10000.0f, 0.0f);
	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
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
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= 0.02f;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += 0.02f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;
				//���[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}
		VERTEX_3D *pVtx; //���_���ւ̃|�C���^
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
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//��ɕ\�������悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldFade);
	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldFade, NULL, &mtxView); //�t�s������߂�
	g_mtxWorldFade._41 = 0.0f;
	g_mtxWorldFade._42 = 0.0f;
	g_mtxWorldFade._43 = 0.0f;
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posFade.x, g_posFade.y, g_posFade.z);
	D3DXMatrixMultiply(&g_mtxWorldFade, &g_mtxWorldFade, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldFade);
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//�t�F�[�h�̐ݒ菈��
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_posFade = CameraPosR();
}

//�t�F�[�h�̎擾����
FADE GetFade(void)
{
	return g_fade;
}