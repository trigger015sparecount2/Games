//-------------------------
//Author:�O��q��
//�|�[�Y���UI����(pauseui.cpp)
//-------------------------
#include "pauseui.h"
#include "camera.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturepauseUi = NULL;    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffpauseUi = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_apauseUiPos;
D3DXMATRIX g_mtxWorldpauseUi;

//����������
void InitpauseUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntUi = 0;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/.png",
		&g_pTexturepauseUi);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffpauseUi,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffpauseUi->Lock(0, 0, (void **)&pVtx, 0);
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
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 200);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 200);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 200);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffpauseUi->Unlock();
}

//UI�̏I������
void UninitpauseUi(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturepauseUi != NULL)
	{
		g_pTexturepauseUi->Release();
		g_pTexturepauseUi = NULL;
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
	
}


//�`�揈��
void DrawpauseUi(void)
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
	D3DXMatrixIdentity(&g_mtxWorldpauseUi);
	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldpauseUi, NULL, &mtxView); //�t�s������߂�
	g_mtxWorldpauseUi._41 = 0.0f;
	g_mtxWorldpauseUi._42 = 0.0f;
	g_mtxWorldpauseUi._43 = 0.0f;
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_apauseUiPos.x, g_apauseUiPos.y, g_apauseUiPos.z);
	D3DXMatrixMultiply(&g_mtxWorldpauseUi, &g_mtxWorldpauseUi, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldpauseUi);
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffpauseUi, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTexturepauseUi);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
			//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void Setpause(void)
{
	g_apauseUiPos = CameraPosR();
}