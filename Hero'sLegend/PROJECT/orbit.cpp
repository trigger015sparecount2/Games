//---------------------------
//Author:�O��q��
//�c������(orbit.cpp)
//---------------------------
#include "orbit.h"

typedef struct
{
	int nTime; //������܂ł̎���
	int nCountTime; //�o�ߎ���
	D3DXVECTOR3 pos;
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	bool bUse;
} Orbit;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureOrbit = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOrbit = NULL; //���_�o�b�t�@�ւ̃|�C���^
Orbit g_Orbit[MAX_ORBIT];

//����������
HRESULT InitOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	int nCntOrbit;
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		g_Orbit[nCntOrbit].nTime = 0;
		g_Orbit[nCntOrbit].nCountTime = 0;
		g_Orbit[nCntOrbit].bUse = false;
		g_Orbit[nCntOrbit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ORBIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOrbit,
		NULL);
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffOrbit->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(100, 0, 100, 160);
		pVtx[1].col = D3DCOLOR_RGBA(100, 0, 100, 160);
		pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 160);
		pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 160);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOrbit->Unlock();
	return S_OK;
}

//�I������
void UninitOrbit(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureOrbit != NULL)
	{
		g_pTextureOrbit->Release();
		g_pTextureOrbit = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffOrbit != NULL)
	{
		g_pVtxBuffOrbit->Release();
		g_pVtxBuffOrbit = NULL;
	}
}

//�X�V����
void UpdateOrbit(void)
{
	int nCntOrbit;
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		if (g_Orbit[nCntOrbit].bUse == true)
		{
			g_Orbit[nCntOrbit].nCountTime++;
			VERTEX_3D *pVtx;
			g_pVtxBuffOrbit->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntOrbit * 4;
			pVtx[0].col = D3DCOLOR_RGBA(100, 0, 100, 160 - g_Orbit[nCntOrbit].nCountTime * 10);
			pVtx[1].col = D3DCOLOR_RGBA(100, 0, 100, 160 - g_Orbit[nCntOrbit].nCountTime * 10);
			pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 160 - g_Orbit[nCntOrbit].nCountTime * 10);
			pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 160 - g_Orbit[nCntOrbit].nCountTime * 10);
			g_pVtxBuffOrbit->Unlock();
			if (g_Orbit[nCntOrbit].nCountTime >= g_Orbit[nCntOrbit].nTime)
			{
				g_Orbit[nCntOrbit].bUse = false;
			}
		}
	}
}

//�`�揈��
void DrawOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	int nCntOrbit;
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	pDevice = GetDevice();     //�f�o�C�X���擾����
	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�J�����O�I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		if (g_Orbit[nCntOrbit].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Orbit[nCntOrbit].mtxWorld);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Orbit[nCntOrbit].pos.x, g_Orbit[nCntOrbit].pos.y, g_Orbit[nCntOrbit].pos.z);
			D3DXMatrixMultiply(&g_Orbit[nCntOrbit].mtxWorld, &g_Orbit[nCntOrbit].mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Orbit[nCntOrbit].mtxWorld);
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffOrbit, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, NULL);    //�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntOrbit * 4,  //�J�n����n�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�J�����O�I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void SetOrbit(D3DXVECTOR3 pos, D3DXVECTOR3 Tippos, D3DXVECTOR3 posOld, D3DXVECTOR3 TipposOld, int nTime)
{
	int nCntOrbit;
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		if (g_Orbit[nCntOrbit].bUse == false)
		{
			g_Orbit[nCntOrbit].bUse = true;
			g_Orbit[nCntOrbit].nTime = nTime;
			g_Orbit[nCntOrbit].nCountTime = 0;
			g_Orbit[nCntOrbit].pos = TipposOld;
			VERTEX_3D *pVtx;
			g_pVtxBuffOrbit->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntOrbit * 4;
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�؂���Â�
			pVtx[1].pos = Tippos - TipposOld; //�؂���V����
			pVtx[2].pos = posOld - TipposOld; //�����葤�Â�
			pVtx[3].pos = pos - TipposOld; //�����葤�V����
			g_pVtxBuffOrbit->Unlock();
			break;
		}
	}
}