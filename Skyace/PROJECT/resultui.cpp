//-------------------------
//Author:�O��q��
//���U���g���UI����(resultui.cpp)
//-------------------------
#include "resultui.h"
#include "rank.h"
#include "ui.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureresultUi[10] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffresultUi = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aresultPos[4 + 11 + (5 * 13)];   //�e�|���S���̈ʒu(�����A���v���C�̃X�R�A���A�e���ʂ̃X�R�A��)

//����������
void InitresultUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	int nCntrank;
	int nRank;
	int nNumber;
	int nCntnumber;
	pDevice = GetDevice();
	g_aresultPos[nCntUi] = D3DXVECTOR3(640.0f, 70.0f, 0.0f);//���U���g
	nCntUi++;
	g_aresultPos[nCntUi] = D3DXVECTOR3(400.0f, 170.0f, 0.0f);//�X�R�A�i�����j
	nCntUi++;
	g_aresultPos[nCntUi] = D3DXVECTOR3(880.0f, 170.0f, 0.0f);//�L���i�����j
	nCntUi++;
	g_aresultPos[nCntUi] = D3DXVECTOR3(240.0f, 230.0f, 0.0f);//you�i�����j
	nCntUi++;
	for (nCntnumber = 0; nCntnumber < 11; nCntnumber++)//���v���C�̃X�R�A�ƌ��Đ�
	{
		if (nCntnumber < 8)
		{
			g_aresultPos[nCntUi] = D3DXVECTOR3(330.0f + nCntnumber * 30.0f, 230.0f, 0.0f);//�X�R�A�i�����j
		}
		else
		{
			g_aresultPos[nCntUi] = D3DXVECTOR3(850.0f + (nCntnumber - 8) * 30.0f, 230.0f, 0.0f);//���Đ��i�����j
		}
		nCntUi++;
	}
	for (nCntrank = 0; nCntrank < 5; nCntrank++)
	{
		g_aresultPos[nCntUi] = D3DXVECTOR3(240.0f, 330.0f + nCntrank * 80.0f, 0.0f);//���ʁi�����j
		nCntUi++;
		for (nCntnumber = 0; nCntnumber < 11; nCntnumber++)//�X�R�A�ƌ��Đ�
		{
			if (nCntnumber < 8)
			{
				g_aresultPos[nCntUi] = D3DXVECTOR3(330.0f + nCntnumber * 30.0f, 330.0f + nCntrank * 80.0f, 0.0f);//�X�R�A�i�����j
			}
			else
			{
				if (nCntnumber == 8)
				{
					g_aresultPos[nCntUi] = D3DXVECTOR3(730.0f, 330.0f + nCntrank * 80.0f, 0.0f);//���ʁi�����j
					nCntUi++;
				}
				g_aresultPos[nCntUi] = D3DXVECTOR3(850.0f + (nCntnumber - 8) * 30.0f, 330.0f + nCntrank * 80.0f, 0.0f);//���Đ��i�����j
			}
			nCntUi++;
		}
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/result.png",
		&g_pTextureresultUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/score.png",
		&g_pTextureresultUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/kill.png",
		&g_pTextureresultUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/you.png",
		&g_pTextureresultUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/number.png",
		&g_pTextureresultUi[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/1st.png",
		&g_pTextureresultUi[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/2nd.png",
		&g_pTextureresultUi[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/3rd.png",
		&g_pTextureresultUi[7]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/4th.png",
		&g_pTextureresultUi[8]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/5th.png",
		&g_pTextureresultUi[9]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 80,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffresultUi,
		NULL);
	VERTEX_2D *pVtx;
	nCntUi = 0;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffresultUi->Lock(0, 0, (void **)&pVtx, 0);
	//���U���g(����)
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 105, g_aresultPos[nCntUi].y - 30, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 105, g_aresultPos[nCntUi].y - 30, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 105, g_aresultPos[nCntUi].y + 30, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 105, g_aresultPos[nCntUi].y + 30, 0.0f);
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
	nCntUi++;
	pVtx += 4;
	//�X�R�A(����)
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 54, g_aresultPos[nCntUi].y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 54, g_aresultPos[nCntUi].y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 54, g_aresultPos[nCntUi].y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 54, g_aresultPos[nCntUi].y + 20, 0.0f);
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
	nCntUi++;
	pVtx += 4;
	//�L��(����)
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 40, g_aresultPos[nCntUi].y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 40, g_aresultPos[nCntUi].y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 40, g_aresultPos[nCntUi].y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 40, g_aresultPos[nCntUi].y + 20, 0.0f);
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
	nCntUi++;
	pVtx += 4;
	//you(����)
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 60, g_aresultPos[nCntUi].y - 30, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 60, g_aresultPos[nCntUi].y - 30, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 60, g_aresultPos[nCntUi].y + 30, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 60, g_aresultPos[nCntUi].y + 30, 0.0f);
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
	for (nCntnumber = 0; nCntnumber < 11; nCntnumber++)
	{
		//�X�R�A�ƌ��Đ�(����)
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 20, g_aresultPos[nCntUi].y - 30, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 20, g_aresultPos[nCntUi].y - 30, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 20, g_aresultPos[nCntUi].y + 30, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 20, g_aresultPos[nCntUi].y + 30, 0.0f);
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
		if (nCntnumber < 8)
		{
			nRank = pow(10, 8 - nCntnumber);
			nNumber = Score() % nRank / (nRank / 10);
		}
		else
		{
			nRank = pow(10, 11 - nCntnumber);
			nNumber = Kill() % nRank / (nRank / 10);
		}
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
		pVtx += 4;
		nCntUi++;
	}
	for (nCntrank = 0; nCntrank < 5; nCntrank++)
	{
		for (nCntnumber = 0; nCntnumber < 11; nCntnumber++)//�X�R�A�ƌ��Đ�
		{
			if (nCntnumber == 0 || nCntnumber == 8)
			{
				//����(����)
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 60, g_aresultPos[nCntUi].y - 30, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 60, g_aresultPos[nCntUi].y - 30, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 60, g_aresultPos[nCntUi].y + 30, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 60, g_aresultPos[nCntUi].y + 30, 0.0f);
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
				nCntUi++;
				pVtx += 4;
			}
			//�X�R�A�ƌ��Đ�(����)
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 20, g_aresultPos[nCntUi].y - 30, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 20, g_aresultPos[nCntUi].y - 30, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x - 20, g_aresultPos[nCntUi].y + 30, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aresultPos[nCntUi].x + 20, g_aresultPos[nCntUi].y + 30, 0.0f);
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
			if (nCntnumber < 8)
			{
				nRank = pow(10, 8 - nCntnumber);
				nNumber = SRankData(nCntrank) % nRank / (nRank / 10);
			}
			else
			{
				nRank = pow(10, 11 - nCntnumber);
				nNumber = KRankData(nCntrank) % nRank / (nRank / 10);
			}
			pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
			nCntUi++;
			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffresultUi->Unlock();
}

//UI�̏I������
void UninitresultUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 10; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureresultUi[nCntUi] != NULL)
		{
			g_pTextureresultUi[nCntUi]->Release();
			g_pTextureresultUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffresultUi != NULL)
	{
		g_pVtxBuffresultUi->Release();
		g_pVtxBuffresultUi = NULL;
	}
}

//UI�̍X�V����
void UpdateresultUi(void)
{
	
}


//�`�揈��
void DrawresultUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntUi = 0;
	int nCntletter;
	int nCntnumber;
	int nCntRank;
	int SRank = 0;
	int SRankLag = 1;
	int ntScore = 0;
	int KRank = 0;
	int KRankLag = 1;
	int ntKill = 0;
	pDevice = GetDevice();//�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffresultUi, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntletter = 0; nCntletter < 4; nCntletter++)
	{
		pDevice->SetTexture(0, g_pTextureresultUi[nCntletter]);//������
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
		nCntUi++;
	}
	for (nCntnumber = 0; nCntnumber < 11; nCntnumber++)
	{
		pDevice->SetTexture(0, g_pTextureresultUi[4]);//�X�R�A�ƌ��Đ��i�����j
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
		nCntUi++;
	}
	for (nCntRank = 0; nCntRank < 5; nCntRank++)
	{
		for (nCntnumber = 0; nCntnumber < 11; nCntnumber++)
		{
			if (nCntnumber == 0)
			{
				if (ntScore == SRankData(nCntRank))
				{
					SRankLag++;
				}
				else
				{
					SRank += SRankLag;
					SRankLag = 1;
				}
				pDevice->SetTexture(0, g_pTextureresultUi[4 + SRank]);//�X�R�A����(����)
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntUi * 4,
					2);
				nCntUi++;
			}
			if (nCntnumber == 8)
			{
				if (ntKill == KRankData(nCntRank))
				{
					KRankLag++;
				}
				else
				{
					KRank += KRankLag;
					KRankLag = 1;
				}
				pDevice->SetTexture(0, g_pTextureresultUi[4 + KRank]);//���Đ�����(����)
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntUi * 4,
					2);
				nCntUi++;
			}
			pDevice->SetTexture(0, g_pTextureresultUi[4]);//�X�R�A�ƌ��Đ�(����)
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntUi * 4,
				2);
			nCntUi++;
		}
		ntScore = SRankData(nCntRank);
		ntKill = KRankData(nCntRank);
	}
}
