//-------------------------
//Author:�O��q��
//���U���g���UI����(resultui.cpp)
//-------------------------
#include "resultui.h"
#include "player.h"
#include "rank.h"

#define MAX_SCORE (8)
#define MAX_RANK (5)

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	int nTexType;//���
} ResultUI;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureresultUi[8] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreResult = NULL;//���_�o�b�t�@�ւ̃|�C���^
ResultUI g_resultui[MAX_RANK + 1][MAX_SCORE + 1];
int g_nYourRank;
int g_nRankTime;
bool g_bRankClear;

//����������
void InitresultUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi;
	int nCntRank;
	int nScore;
	int nRank;
	int NumRank = 1;
	int nTScore = -1;
	int nRag = 0;
	int nNumber;
	g_bRankClear = true;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/result.png",
		&g_pTextureresultUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/you.png",
		&g_pTextureresultUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Rank1st.png",
		&g_pTextureresultUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Rank2nd.png",
		&g_pTextureresultUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Rank3rd.png",
		&g_pTextureresultUi[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Rank4th.png",
		&g_pTextureresultUi[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/Rank5th.png",
		&g_pTextureresultUi[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/number.png",
		&g_pTextureresultUi[7]);

	g_nYourRank = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (1 + (MAX_SCORE + 1) * (MAX_RANK + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreResult,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̐ݒ�(u,v)float
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx += 4;

	
	//�e�N�X�`���̐ݒ�(u,v)float
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���W�̒��S
	g_resultui[0][0].pos = D3DXVECTOR3(300.0f, 200.0f, 0.0f);

	//���W�̐ݒ�(x,y)float
	pVtx[0].pos = D3DXVECTOR3(g_resultui[0][0].pos.x - 50.0f, g_resultui[0][0].pos.y - 30.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_resultui[0][0].pos.x + 50.0f, g_resultui[0][0].pos.y - 30.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_resultui[0][0].pos.x - 50.0f, g_resultui[0][0].pos.y + 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_resultui[0][0].pos.x + 50.0f, g_resultui[0][0].pos.y + 30.0f, 0.0f);

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

	g_resultui[0][0].nTexType = 1;

	pVtx += 4;

	nScore = PlayerScore();
	
	for (nCntUi = 0; nCntUi < MAX_SCORE; nCntUi++)
	{
		nRank = powf(10, MAX_SCORE - nCntUi);
		nNumber = nScore % nRank / (nRank / 10);

		//�e�N�X�`���̐ݒ�(u,v)float
		pVtx[0].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.1f, 1.0f);

		//���W�̒��S
		g_resultui[0][nCntUi + 1].pos = D3DXVECTOR3(800.0f, 200.0f, 0.0f);

		//���W�̐ݒ�(x,y)float
		pVtx[0].pos = D3DXVECTOR3(g_resultui[0][nCntUi + 1].pos.x - 20.0f + nCntUi * 40.0f, g_resultui[0][nCntUi + 1].pos.y - 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_resultui[0][nCntUi + 1].pos.x + 20.0f + nCntUi * 40.0f, g_resultui[0][nCntUi + 1].pos.y - 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_resultui[0][nCntUi + 1].pos.x - 20.0f + nCntUi * 40.0f, g_resultui[0][nCntUi + 1].pos.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_resultui[0][nCntUi + 1].pos.x + 20.0f + nCntUi * 40.0f, g_resultui[0][nCntUi + 1].pos.y + 30.0f, 0.0f);

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

		g_resultui[0][nCntUi + 1].nTexType = 7;

		pVtx += 4;
	}
	
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		//�e�N�X�`���̐ݒ�(u,v)float
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���W�̒��S
		g_resultui[nCntRank + 1][0].pos = D3DXVECTOR3(300.0f, 220.0f + (nCntRank + 1) * 80.0f, 0.0f);

		//���W�̐ݒ�(x,y)float
		pVtx[0].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][0].pos.x - 50.0f, g_resultui[nCntRank + 1][0].pos.y - 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][0].pos.x + 50.0f, g_resultui[nCntRank + 1][0].pos.y - 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][0].pos.x - 50.0f, g_resultui[nCntRank + 1][0].pos.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][0].pos.x + 50.0f, g_resultui[nCntRank + 1][0].pos.y + 30.0f, 0.0f);

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

		nScore = SRankData(nCntRank);

		if (nScore == PlayerScore() && g_nYourRank == 0 && nScore > 0)
		{
			g_nYourRank = NumRank;
		}

		if (nScore == nTScore)
		{
			nRag++;
		}
		else
		{
			NumRank += nRag + 1;
			nRag = 0;
		}

		g_resultui[nCntRank + 1][0].nTexType = NumRank;

		for (nCntUi = 0; nCntUi < MAX_SCORE; nCntUi++)
		{
			nRank = powf(10, MAX_SCORE - nCntUi);
			nNumber = nScore % nRank / (nRank / 10);

			//�e�N�X�`���̐ݒ�(u,v)float
			pVtx[0].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.1f, 1.0f);

			//���W�̒��S
			g_resultui[nCntRank + 1][nCntUi + 1].pos = D3DXVECTOR3(800.0f, 220.0f + (nCntRank + 1) * 80.0f, 0.0f);

			//���W�̐ݒ�(x,y)float
			pVtx[0].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][nCntUi + 1].pos.x - 20.0f + nCntUi * 40.0f, g_resultui[nCntRank + 1][nCntUi + 1].pos.y - 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][nCntUi + 1].pos.x + 20.0f + nCntUi * 40.0f, g_resultui[nCntRank + 1][nCntUi + 1].pos.y - 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][nCntUi + 1].pos.x - 20.0f + nCntUi * 40.0f, g_resultui[nCntRank + 1][nCntUi + 1].pos.y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_resultui[nCntRank + 1][nCntUi + 1].pos.x + 20.0f + nCntUi * 40.0f, g_resultui[nCntRank + 1][nCntUi + 1].pos.y + 30.0f, 0.0f);

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

			g_resultui[nCntRank + 1][nCntUi + 1].nTexType = 7;

			pVtx += 4;
		}
		nTScore = nScore;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScoreResult->Unlock();

}

//UI�̏I������
void UninitresultUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 8; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureresultUi[nCntUi] != NULL)
		{
			g_pTextureresultUi[nCntUi]->Release();
			g_pTextureresultUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScoreResult != NULL)
	{
		g_pVtxBuffScoreResult->Release();
		g_pVtxBuffScoreResult = NULL;
	}
}

//UI�̍X�V����
void UpdateresultUi(void)
{
	if (g_nYourRank > 0)
	{
		g_nRankTime++;
		if (g_nRankTime >= 5)
		{
			if (g_bRankClear == true)
			{
				VERTEX_2D *pVtx;//���_���ւ̃|�C���^

				//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
				g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (g_nYourRank * 9 + 1) * 4;
				//�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffScoreResult->Unlock();
				g_bRankClear = false;
			}
			else
			{
				VERTEX_2D *pVtx;//���_���ւ̃|�C���^

								//���_�o�b�t�@�����b�N���A���_�f�[�^�G�̃|�C���^���擾
				g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (g_nYourRank * 9 + 1) * 4;
				//�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffScoreResult->Unlock();
				g_bRankClear = true;
			}
			g_nRankTime = 0;
		}
	}
}


//�`�揈��
void DrawresultUi(void)
{
	int nCntScore;//for���p
	int nCntRank;
	int nCntUI = 0;

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScoreResult, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, g_pTextureresultUi[0]);//�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);//�|���S���̕`��
	nCntUI++;
	for (nCntRank = 0; nCntRank < MAX_RANK + 1; nCntRank++)
	{
		for (nCntScore = 0; nCntScore < MAX_SCORE + 1; nCntScore++)
		{
			pDevice->SetTexture(0, g_pTextureresultUi[g_resultui[nCntRank][nCntScore].nTexType]);//�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);//�|���S���̕`��
			nCntUI++;
		}
	}
}
