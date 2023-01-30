//--------------------------
//Author:�O��q��
//�I�̏���(target.cpp)
//--------------------------
#include "target.h"
#include "player.h"
#include "sound.h"
#include "gameui.h"
#include "fade.h"

//�}�N����`
#define MAX_TARGET (8) //�I�̍ő吔
#define TARGET_SIZE (50) //�I�̃T�C�Y

//�I�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXVECTOR3 move; //����
	D3DXVECTOR3 Maxmove;
	int nTime;
	int nMaxTime;
	bool bUse;        //�g�p���Ă��邩�ǂ���
} Target;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTarget = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTarget = NULL; //���_�o�b�t�@�ւ̃|�C���^
Target g_aTarget[MAX_TARGET];

//����������
void InitTarget(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTarget;
	pDevice = GetDevice();
	//�I�̏�����
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		g_aTarget[nCntTarget].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTarget[nCntTarget].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTarget[nCntTarget].Maxmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTarget[nCntTarget].nTime = 0;
		g_aTarget[nCntTarget].nMaxTime = 0;
		g_aTarget[nCntTarget].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/target.png",
		&g_pTextureTarget);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TARGET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTarget,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTarget->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffTarget->Unlock();
}

//�I�̏I������
void UninitTarget(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTarget != NULL)
	{
		g_pTextureTarget->Release();
		g_pTextureTarget = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTarget != NULL)
	{
		g_pVtxBuffTarget->Release();
		g_pVtxBuffTarget = NULL;
	}
}

//�I�̍X�V����
void UpdateTarget(void)
{
	int nCntTarget;
	VERTEX_2D *pVtx;
	g_pVtxBuffTarget->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		//�I�g���Ă���
		if (g_aTarget[nCntTarget].bUse == true)
		{
			//���Ԃ�i�߁A�ʒu���ς���Ă����ꍇ�͕ς���
			g_aTarget[nCntTarget].nTime++;
			pVtx[0].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x               , g_aTarget[nCntTarget].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x + TARGET_SIZE, g_aTarget[nCntTarget].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x               , g_aTarget[nCntTarget].pos.y + TARGET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x + TARGET_SIZE, g_aTarget[nCntTarget].pos.y + TARGET_SIZE, 0.0f);
		}
		pVtx += 4;
	}
	g_pVtxBuffTarget->Unlock();
}

//�`�揈��
void DrawTarget(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntTarget;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTarget, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		if (g_aTarget[nCntTarget].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTarget);    //�e�N�X�`���̐ݒ�
														//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntTarget * 4,
				2);
		}
	}
}

//�I�̐ݒ菈��
void SetTarget(D3DXVECTOR3 pos)
{
	int nCntTarget;
	VERTEX_2D *pVtx;
	g_pVtxBuffTarget->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		if (g_aTarget[nCntTarget].bUse == false)
		{
			//�ʒu�ݒ�
			g_aTarget[nCntTarget].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x               , g_aTarget[nCntTarget].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x + TARGET_SIZE, g_aTarget[nCntTarget].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x               , g_aTarget[nCntTarget].pos.y + TARGET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTarget[nCntTarget].pos.x + TARGET_SIZE, g_aTarget[nCntTarget].pos.y + TARGET_SIZE, 0.0f);
			g_aTarget[nCntTarget].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffTarget->Unlock();
}

//�I��ꂽ��
bool BreakTarget(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	int nCntTarget;
	bool bBreak = false;
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		if (g_aTarget[nCntTarget].bUse == true)
		{
			//�I�ɓ���������
			if (pos.x <= g_aTarget[nCntTarget].pos.x + TARGET_SIZE && g_aTarget[nCntTarget].pos.x <= pos.x &&
				pos.y <= g_aTarget[nCntTarget].pos.y + TARGET_SIZE && g_aTarget[nCntTarget].pos.y <= pos.y)
			{
				//�I������
				g_aTarget[nCntTarget].bUse = false;
				bBreak = true;
			}
		}
	}
	return bBreak;
}

//�S������
void ResetTarget(void)
{
	int nCntTarget;
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		g_aTarget[nCntTarget].bUse = false;
	}
}

//�����I�����邩
int CountTarget(void)
{
	int nCntTarget;
	int nTarget = 0;
	//�I���������邩���ׂ�
	for (nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
	{
		if (g_aTarget[nCntTarget].bUse == true)
		{
			nTarget++;
		}
	}

	//0�̏ꍇ���t�F�[�h�����ĂȂ�
	if (nTarget == 0 && GetFade() == FADE_NONE)
	{
		//���U���g�Ɉڍs�A���Ԏ~�߂�A�Q�[���N���A����������
		SetFade(MODE_RESULT);
		StopTime();
		GameClear();
	}
	return nTarget;
}