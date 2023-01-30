//--------------------------
//Author:�O��q��
//�e�ۂ̏���(bullet.cpp)
//--------------------------
#include "bullet.h"
#include "explosion.h"
#include "player.h"
#include "meshfield.h"
#include "sound.h"

//�}�N����`
#define MAX_BULLET (512)   //�e�̍ő吔

//�e�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 posold; //�ߋ��̈ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	int nDamage; //�_���[�W��
	int nDamageTime; //�q�b�g�Ԋu
	float fHClash; //���������̐�����΂���
	float fVClash; //���������̐�����΂���
	int nLife;
	float fRoty;
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Bullet;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];

//����������
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	pDevice = GetDevice();

	//�e�̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nDamage = 0;
		g_aBullet[nCntBullet].nDamageTime = 0;
		g_aBullet[nCntBullet].fRoty = 0.0f;
		g_aBullet[nCntBullet].fHClash = 0.0f;
		g_aBullet[nCntBullet].fVClash = 0.0f;
		g_aBullet[nCntBullet].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/bullet000.png",
		&g_pTextureBullet);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-5.0f, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(5.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBullet->Unlock();
	return S_OK;
}

//�e�̏I������
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//�e�̍X�V����
void UpdateBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�e�g���Ă���
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�ړ������A�������炷
			g_aBullet[nCntBullet].posold = g_aBullet[nCntBullet].pos;
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			g_aBullet[nCntBullet].nLife--;

			//���ɓ������Ă���
			if (CollisionField(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].posold, &g_aBullet[nCntBullet].move, 5.0f) == true)
			{
				//�����G�t�F�N�g�쐬�A����
				SetExplosion(g_aBullet[nCntBullet].pos);
				g_aBullet[nCntBullet].bUse = false;
			}

			//�����؂�
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//����
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}
}

//�`�揈��
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	int nCntBullet;
	pDevice = GetDevice();     //�f�o�C�X���擾����

	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�����ȕ�����`�悵�Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);
			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxWorld, NULL, &mtxView); //�t�s������߂�
			g_aBullet[nCntBullet].mtxWorld._41 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._42 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._43 = 0.0f;
			/*
			g_mtxWorldBillboard._11 = mtxView._11;
			g_mtxWorldBillboard._12 = mtxView._21;
			g_mtxWorldBillboard._13 = mtxView._31;
			g_mtxWorldBillboard._14 = mtxView._41;
			g_mtxWorldBillboard._21 = mtxView._12;
			g_mtxWorldBillboard._22 = mtxView._22;
			g_mtxWorldBillboard._23 = mtxView._32;
			g_mtxWorldBillboard._24 = mtxView._42;
			g_mtxWorldBillboard._31 = mtxView._13;
			g_mtxWorldBillboard._32 = mtxView._23;
			g_mtxWorldBillboard._33 = mtxView._33;
			g_mtxWorldBillboard._34 = mtxView._43;
			g_mtxWorldBillboard._41 = mtxView._14;
			g_mtxWorldBillboard._42 = mtxView._24;
			g_mtxWorldBillboard._43 = mtxView._34;
			g_mtxWorldBillboard._44 = mtxView._44;
			*/
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureBullet);    //�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,  //�J�n����n�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�f�t�H���g�ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nDamage, int nDamageTime, float fVClash, float fHClash, float fRoty)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�g���ĂȂ��g���g��
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].nDamage = nDamage;
			g_aBullet[nCntBullet].nDamageTime = nDamageTime;
			g_aBullet[nCntBullet].fHClash = fHClash;
			g_aBullet[nCntBullet].fVClash = fVClash;
			g_aBullet[nCntBullet].fRoty = fRoty;
			g_aBullet[nCntBullet].bUse = true;
			PlaySound(SOUND_LABEL_GUN);
			break;
		}
	}
}

//�e���g���Ă邩
int CountBullet(void)
{
	int nCntBullet;
	int nBullet = 0;
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			nBullet++;
		}
	}
	return nBullet;
}

//�e�Ƃ̓����蔻��
bool CollisionBullet(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fRadius, int nDamageTime, float *fRotY)
{
	float fLengthX; //�N���ƃI�u�W�F�N�g��X�����̒���
	float fLengthY;
	float fLengthZ; //�N���ƃI�u�W�F�N�g��Z�����̒���
	float fHDistance; //�N���ƃI�u�W�F�N�g�̋���
	float fDistance;

	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�g���Ă�
		if (g_aBullet[nCntBullet].bUse == true)
		{
			fLengthX = powf(pPos->x - g_aBullet[nCntBullet].pos.x, 2);
			fLengthY = powf(pPos->y - g_aBullet[nCntBullet].pos.y, 2);
			fLengthZ = powf(pPos->z - g_aBullet[nCntBullet].pos.z, 2);
			fHDistance = fLengthX + fLengthZ;
			fDistance = sqrtf(fHDistance + fLengthY);
			if (fDistance <= fRadius + 5.0f) //�I�u�W�F�N�g���G�ɓ��������Ƃ�
			{
				//����
				g_aBullet[nCntBullet].bUse = false;

				//���G����Ȃ�
				if (nDamageTime == 0)
				{
					//�m�b�N�o�b�N������
					pMove->x = -g_aBullet[nCntBullet].fHClash * sinf(g_aBullet[nCntBullet].fRoty);
					pMove->y = g_aBullet[nCntBullet].fVClash;
					pMove->z = -g_aBullet[nCntBullet].fHClash * cosf(g_aBullet[nCntBullet].fRoty);
					PlayerDamageTime(g_aBullet[nCntBullet].nDamageTime);
					return true;
				}
			}
		}
	}
	return false;
}

//�_���[�W�ʎ擾
int BulletDamage(void)
{
	return g_aBullet[0].nDamage;
}