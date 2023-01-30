//-------------------------
//Author:�O��q��
//�Q�[������UI����(gameui.cpp)
//-------------------------
#include "gameui.h"
#include "player.h"
#include "fade.h"
#include "target.h"
#include "sound.h"

//�}�N����`
#define MAX_NUMBER (2)		//����
#define NUMBER_PATTERN (10)	//�����̃p�^�[����
#define NUMBER_WIDTH (40)	//�����̍���
#define NUMBER_HEIGHT (60)	//�����̕�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGameUi[6] = {};	 //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameUi = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aPos[5 + 5];   //�e�|���S���̈ʒu(�I�A����)
int g_aGameUIclear[2]; //UI�̓����
int g_nTimeSec; //�c�莞�ԁi�b�j
int g_nTimeCom; //�c�莞�ԁi�R���}�j
bool g_bStopTime; //���Ԃ��~�܂��Ă��邩�ǂ���
bool g_bGameOver; //�Q�[���̏I����������𖞂��������ǂ���
float g_fRot[4];  //���Ԃ̐j�̌���

//����������
void InitGameUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi;
	pDevice = GetDevice();
	g_aPos[0] = D3DXVECTOR3(115.0f, 50.0f, 0.0f); //�I�̎l�p
	g_aPos[1] = D3DXVECTOR3(60.0f, 50.0f, 0.0f); //�I�}�[�N
	g_aPos[2] = D3DXVECTOR3(110.0f, 50.0f, 0.0f); //�~�}�[�N
	for (nCntUi = 0; nCntUi < 2; nCntUi++) //�I�̎c�薇�����l
	{
		g_aPos[nCntUi + 3] = D3DXVECTOR3(150.0f + nCntUi * 30.0f, 50.0f, 0.0f);
	}
	g_aPos[5] = D3DXVECTOR3(1190.0f, 50.0f, 0.0f);//���v�̎l�p
	for (nCntUi = 0; nCntUi < 2; nCntUi++) //���v�}�[�N
	{
		g_aPos[nCntUi + 6] = D3DXVECTOR3(1150.0f, 50.0f, 0.0f);
	}
	for (nCntUi = 0; nCntUi < 2; nCntUi++) //�c�莞��
	{
		g_aPos[nCntUi + 8] = D3DXVECTOR3(1210.0f + nCntUi * 30.0f, 50.0f, 0.0f);
	}
	ResetGameUi();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/number.png",
		&g_pTextureGameUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/target.png",
		&g_pTextureGameUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�~mark.png",
		&g_pTextureGameUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/clock.png",
		&g_pTextureGameUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/clockneedle.png",
		&g_pTextureGameUi[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/slongsquare.png",
		&g_pTextureGameUi[5]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 10,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameUi,
		NULL);
	VERTEX_2D *pVtx;
	nCntUi = 0;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGameUi->Lock(0, 0, (void **)&pVtx, 0);
	//�I�l�p
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[0].x - 110, g_aPos[0].y - 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[0].x + 110, g_aPos[0].y - 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[0].x - 110, g_aPos[0].y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[0].x + 110, g_aPos[0].y + 50, 0.0f);
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
	//�I�}�[�N
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[1].x - 30, g_aPos[1].y - 30, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[1].x + 30, g_aPos[1].y - 30, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[1].x - 30, g_aPos[1].y + 30, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[1].x + 30, g_aPos[1].y + 30, 0.0f);
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
	//�~�}�[�N
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[2].x - 20, g_aPos[2].y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[2].x + 20, g_aPos[2].y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[2].x - 20, g_aPos[2].y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[2].x + 20, g_aPos[2].y + 20, 0.0f);
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
	for (nCntUi = 0; nCntUi < MAX_NUMBER; nCntUi++) //�I�̎c�薇�����l
	{
		pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi + 3].x - NUMBER_WIDTH / 2, g_aPos[nCntUi + 3].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi + 3].x + NUMBER_WIDTH / 2, g_aPos[nCntUi + 3].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi + 3].x - NUMBER_WIDTH / 2, g_aPos[nCntUi + 3].y + NUMBER_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi + 3].x + NUMBER_WIDTH / 2, g_aPos[nCntUi + 3].y + NUMBER_HEIGHT / 2, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//�c�莞�Ԏl�p
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[5].x - 90, g_aPos[5].y - 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[5].x + 90, g_aPos[5].y - 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[5].x - 90, g_aPos[5].y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[5].x + 90, g_aPos[5].y + 50, 0.0f);
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
	for (nCntUi = 0; nCntUi < 2; nCntUi++)//���v
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi + 6].x - 30, g_aPos[nCntUi + 6].y - 30, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi + 6].x + 30, g_aPos[nCntUi + 6].y - 30, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi + 6].x - 30, g_aPos[nCntUi + 6].y + 30, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi + 6].x + 30, g_aPos[nCntUi + 6].y + 30, 0.0f);
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
	for (nCntUi = 0; nCntUi < 2; nCntUi++)//�c�莞�Ԏ��Ԑ��l
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi + 8].x - (NUMBER_WIDTH / 2), g_aPos[nCntUi + 8].y - (NUMBER_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi + 8].x + (NUMBER_WIDTH / 2), g_aPos[nCntUi + 8].y - (NUMBER_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi + 8].x - (NUMBER_WIDTH / 2), g_aPos[nCntUi + 8].y + (NUMBER_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi + 8].x + (NUMBER_WIDTH / 2), g_aPos[nCntUi + 8].y + (NUMBER_HEIGHT / 2), 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGameUi->Unlock();
}

//UI�̏I������
void UninitGameUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 6; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureGameUi[nCntUi] != NULL)
		{
			g_pTextureGameUi[nCntUi]->Release();
			g_pTextureGameUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameUi != NULL)
	{
		g_pVtxBuffGameUi->Release();
		g_pVtxBuffGameUi = NULL;
	}
}

//UI�̍X�V����
void UpdateGameUi(void)
{
	int nCntUi;
	int nNumber;
	int nRank;
	if (g_bStopTime == false)
	{
		g_nTimeCom--;
		if (g_nTimeCom <= 0)
		{
			g_nTimeSec--;
			g_nTimeCom = TIME_LIMIT_COM;
			if (g_nTimeSec <= 10)
			{
				PlaySound(SOUNT_LABEL_COUNTDOWN);
			}
		}
		for (nCntUi = 0; nCntUi < 4; nCntUi++)
		{
			g_fRot[nCntUi] += 2.0f / (float)(TIME_LIMIT_COM * TIME_LIMIT_SEC);
			if (g_fRot[nCntUi] <= -1.0f)
			{
				g_fRot[nCntUi] += 2.0f;
			}
		}
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffGameUi->Lock(0, 0, (void **)&pVtx, 0);
	Player *pPlayer;
	pPlayer = GetPlayer();
	if (pPlayer->pos.x - (PLAYER_WIDTH / 2) <= g_aPos[0].x + 110 && g_aPos[0].x - 110 <= pPlayer->pos.x + (PLAYER_WIDTH / 2) &&
		pPlayer->pos.y - PLAYER_HEIGHT <= g_aPos[0].y + 50 && g_aPos[0].y - 50 <= pPlayer->pos.y) //���ߏ���
	{
		g_aGameUIclear[0] -= 7;
		if (g_aGameUIclear[0] <= 60)
		{
			g_aGameUIclear[0] = 60;
		}
	}
	else
	{
		g_aGameUIclear[0] += 7;
		if (g_aGameUIclear[0] >= 255)
		{
			g_aGameUIclear[0] = 255;
		}
	}

	//�I�l�p�ƃ}�[�N
	for(nCntUi = 0; nCntUi < 3; nCntUi++)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx += 4;
	}

	for (nCntUi = 0; nCntUi < MAX_NUMBER; nCntUi++) //�I�̎c�薇�����l
	{
		nRank = pow(10, MAX_NUMBER - nCntUi);
		nNumber = CountTarget() % nRank / (nRank / 10);
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[0]);
		pVtx += 4;
	}

	//���Ԃɓ������Ă��邩
	if (pPlayer->pos.x - (PLAYER_WIDTH / 2) <= g_aPos[5].x + 90 && g_aPos[5].x - 90 <= pPlayer->pos.x + (PLAYER_WIDTH / 2) &&
	    pPlayer->pos.y - PLAYER_HEIGHT <= g_aPos[5].y + 50 && g_aPos[5].y - 50 <= pPlayer->pos.y) //���ߏ���
	{
		g_aGameUIclear[1] -= 7;
		if (g_aGameUIclear[1] <= 60)
		{
			g_aGameUIclear[1] = 60;
		}
	}
	else
	{
		g_aGameUIclear[1] += 7;
		if (g_aGameUIclear[1] >= 255)
		{
			g_aGameUIclear[1] = 255;
		}

	}
	//�c�莞�Ԏl�p�Ǝ��v
	for(nCntUi = 0; nCntUi < 2; nCntUi++)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
		pVtx += 4;
	}
	//���v�̐j
	pVtx[0].pos = D3DXVECTOR3(g_aPos[7].x + 30 * sinf(D3DX_PI * g_fRot[0]), g_aPos[7].y + 30 * cosf(D3DX_PI * g_fRot[0]), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[7].x + 30 * sinf(D3DX_PI * g_fRot[1]), g_aPos[7].y + 30 * cosf(D3DX_PI * g_fRot[1]), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[7].x + 30 * sinf(D3DX_PI * g_fRot[2]), g_aPos[7].y + 30 * cosf(D3DX_PI * g_fRot[2]), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[7].x + 30 * sinf(D3DX_PI * g_fRot[3]), g_aPos[7].y + 30 * cosf(D3DX_PI * g_fRot[3]), 0.0f);
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
	pVtx += 4;
	for (nCntUi = 0; nCntUi < 2; nCntUi++) //�c�莞�Ԑ��l
	{
		nRank = pow(10, 2 - nCntUi);
		nNumber = g_nTimeSec % nRank / (nRank / 10);
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
		if (g_nTimeSec > 10)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aGameUIclear[1]);
		}
		else
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, g_aGameUIclear[1]);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, g_aGameUIclear[1]);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, g_aGameUIclear[1]);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, g_aGameUIclear[1]);
		}
		pVtx += 4;
	}
	g_pVtxBuffGameUi->Unlock();
	if (g_nTimeSec <= 0 && GetFade() == FADE_NONE)
	{
		g_nTimeSec = 0;
		g_bGameOver = true;
		StopTime();
		SetFade(MODE_RESULT);
	}
}


//�`�揈��
void DrawGameUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntUi = 0;
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGameUi, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureGameUi[5]); //�����l�p
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi = 1;
	pDevice->SetTexture(0, g_pTextureGameUi[1]); //�I�}�[�N
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi = 2;
	pDevice->SetTexture(0, g_pTextureGameUi[2]); //�~�}�[�N
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	for (nCntUi = 3; nCntUi < 5; nCntUi++) //�I�̎c�薇��
	{
		pDevice->SetTexture(0, g_pTextureGameUi[0]);//�I�̎c�薇��(���l)
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
	}
	nCntUi = 5;
	pDevice->SetTexture(0, g_pTextureGameUi[5]);//�c�莞�Ԏl�p
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi = 6;
	pDevice->SetTexture(0, g_pTextureGameUi[3]);//���v
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi = 7;
	pDevice->SetTexture(0, g_pTextureGameUi[4]);//���v�̐j
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	for (nCntUi = 8; nCntUi < 10; nCntUi++)//�c�莞�Ԑ��l
	{
		pDevice->SetTexture(0, g_pTextureGameUi[0]);//�c�莞�Ԑ��l
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
	}
}

//UI���Z�b�g
void ResetGameUi(void)
{
	g_nTimeCom = TIME_LIMIT_COM;
	g_nTimeSec = TIME_LIMIT_SEC;
	int nCntUi;
	for (nCntUi = 0; nCntUi < 2; nCntUi++)
	{
		g_aGameUIclear[nCntUi] = 255;
	}
	g_fRot[0] = -0.75;
	g_fRot[1] = 0.75;
	g_fRot[2] = -0.25;
	g_fRot[3] = 0.25;
	g_bStopTime = false;
	g_bGameOver = false;
}

//�c��̕b�擾
int TimeMin(void)
{
	return TIME_LIMIT_COM - g_nTimeCom;
}

//�c��R���}�擾
int TimeSec(void)
{
	return TIME_LIMIT_SEC - g_nTimeSec;
}

//���Ԏ~�߂�
void StopTime(void)
{
	g_bStopTime = true;
}

//�Q�[���I�[�o�[�擾
bool GameOver(void)
{
	return g_bGameOver;
}

//�Q�[���N���A�\
void GameClear(void)
{
	g_bGameOver = true;
}