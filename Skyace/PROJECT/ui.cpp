//-------------------------
//Author:�O��q��
//UI����(ui.cpp)
//-------------------------
#include "ui.h"
#include "aircraft.h"
#include "enemy.h"

//�}�N����`
#define MAX_NUMBER (8)      //����
#define NUMBER_PATTERN (10) //�����̃p�^�[����
#define NUMBER_WIDTH (40)   //�����̍���
#define NUMBER_HEIGHT (60)  //�����̕�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureUi[13] = {};    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aPos[9 + 4 + 1 + 1 + 3 + 4];   //�e�|���S���̈ʒu(�X�R�A,���Đ�,�l�p,HUD�퓬�@,�����x,���ꕺ��)
int g_aUIclear[3];
int g_nATime;
int g_nScore = 0; //�X�R�A
int g_nkill = 0; //���Đ�
int g_nReScore; //��蒼�����̃X�R�A
int g_nReKill;  //��蒼�����̌��Đ�

//����������
void InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi = 0;
	int nCntcol;
	pDevice = GetDevice();
	for (nCntcol = 0; nCntcol < 3; nCntcol++)
	{
		g_aUIclear[nCntcol] = 200;
	}
	g_aPos[nCntUi] = D3DXVECTOR3(155.0f, 55.0f, 0.0f);//�X�R�A�l�p
	for (nCntUi++; nCntUi < 9; nCntUi++)//�X�R�A���l
	{
		g_aPos[nCntUi] = D3DXVECTOR3(45.0f + (nCntUi - 1) * 30.0f, 55.0f, 0.0f);
	}
	g_aPos[nCntUi] = D3DXVECTOR3(1200.0f, 50.0f, 0.0f);//���Đ��l�p
	for (nCntUi++; nCntUi < 13; nCntUi++)//���Đ����l
	{
		g_aPos[nCntUi] = D3DXVECTOR3(1170.0f + (nCntUi - 10) * 30.0f, 50.0f, 0.0f);
	}
	g_aPos[nCntUi] = D3DXVECTOR3(1180.0f, 540.0f, 0.0f);//�퓬�@�֘A�l�p
	nCntUi++;
	g_aPos[nCntUi] = D3DXVECTOR3(1180.0f, 460.0f, 0.0f);//HUD�퓬�@
	for (nCntUi++; nCntUi < 17; nCntUi++)//�@�̂̑����x(���l)
	{
		g_aPos[nCntUi] = D3DXVECTOR3(1140.0f + (nCntUi - 15) * 30.0f, 560.0f, 0.0f);
	}
	g_aPos[nCntUi] = D3DXVECTOR3(1210.0f, 560.0f, 0.0f);//�u%�v�}�[�N
	nCntUi++;
	g_aPos[nCntUi] = D3DXVECTOR3(1130.0f, 650.0f, 0.0f);//HUD���ꕺ��
	nCntUi++;
	g_aPos[nCntUi] = D3DXVECTOR3(1175.0f, 630.0f, 0.0f);//���ꕺ���c�e��
	nCntUi++;
	g_aPos[nCntUi] = D3DXVECTOR3(1203.0f, 650.0f, 0.0f);//�u/�v�}�[�N
	nCntUi++;
	g_aPos[nCntUi] = D3DXVECTOR3(1233.0f, 660.0f, 0.0f);//���ꕺ���ő吔
	g_nScore = 0;
	g_nkill = 0;
	g_nATime = 0;
	g_nReKill = 0;
	g_nReScore = 0;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/number.png",
		&g_pTextureUi[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDeagle.png",
		&g_pTextureUi[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDflanker.png",
		&g_pTextureUi[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDuav.png",
		&g_pTextureUi[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDmissile.png",
		&g_pTextureUi[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDbarrier.png",
		&g_pTextureUi[5]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDrailgun.png",
		&g_pTextureUi[6]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDbombmissile.png",
		&g_pTextureUi[7]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/HUDlaser.png",
		&g_pTextureUi[8]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/%mark.png",
		&g_pTextureUi[9]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/slashmark.png",
		&g_pTextureUi[10]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�c���l�p.png",
		&g_pTextureUi[11]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/�����l�p.png",
		&g_pTextureUi[12]);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 22,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL);
	VERTEX_2D *pVtx;
	nCntUi = 0;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUi->Lock(0, 0, (void **)&pVtx, 0);
	//�X�R�A�l�p
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 150, g_aPos[nCntUi].y - 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 150, g_aPos[nCntUi].y - 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 150, g_aPos[nCntUi].y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 150, g_aPos[nCntUi].y + 50, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;
	for (nCntUi++; nCntUi < MAX_NUMBER + 1; nCntUi++)//�X�R�A���l
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//���Đ��l�p
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 70, g_aPos[nCntUi].y - 45, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 70, g_aPos[nCntUi].y - 45, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 70, g_aPos[nCntUi].y + 45, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 70, g_aPos[nCntUi].y + 45, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;
	for (nCntUi++; nCntUi < 13; nCntUi++)//���Đ����l
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;
	}
	//�퓬�@�֘A�l�p
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 90, g_aPos[nCntUi].y - 170, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 90, g_aPos[nCntUi].y - 170, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 90, g_aPos[nCntUi].y + 170, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 90, g_aPos[nCntUi].y + 170, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;
	nCntUi++;
	//HUD�퓬�@
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - AIRCRAFT_WIDTH / 2, g_aPos[nCntUi].y - AIRCRAFT_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + AIRCRAFT_WIDTH / 2, g_aPos[nCntUi].y - AIRCRAFT_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - AIRCRAFT_WIDTH / 2, g_aPos[nCntUi].y + AIRCRAFT_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + AIRCRAFT_WIDTH / 2, g_aPos[nCntUi].y + AIRCRAFT_HEIGHT / 2, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;
	for (nCntUi++; nCntUi < 17; nCntUi++)//�@�̂̑����x
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//�u%�v�}�[�N
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 25, g_aPos[nCntUi].y - 25, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 25, g_aPos[nCntUi].y - 25, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 25, g_aPos[nCntUi].y + 25, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 25, g_aPos[nCntUi].y + 25, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;
	nCntUi++;
	//���ꕺ��HUD
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 27, g_aPos[nCntUi].y - 24, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 27, g_aPos[nCntUi].y - 24, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 27, g_aPos[nCntUi].y + 24, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 27, g_aPos[nCntUi].y + 24, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx += 4;
	//���ꕺ���c�e��
	nCntUi++;
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - (NUMBER_WIDTH / 2 + 5), g_aPos[nCntUi].y - (NUMBER_HEIGHT / 2 + 5), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + (NUMBER_WIDTH / 2 + 5), g_aPos[nCntUi].y - (NUMBER_HEIGHT / 2 + 5), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - (NUMBER_WIDTH / 2 + 5), g_aPos[nCntUi].y + (NUMBER_HEIGHT / 2 + 5), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + (NUMBER_WIDTH / 2 + 5), g_aPos[nCntUi].y + (NUMBER_HEIGHT / 2 + 5), 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.2f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.3f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.3f, 1.0f);
	pVtx += 4;
	//�u/�v�}�[�N
	nCntUi++;
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 12, g_aPos[nCntUi].y - 24, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 12, g_aPos[nCntUi].y - 24, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - 12, g_aPos[nCntUi].y + 24, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + 12, g_aPos[nCntUi].y + 24, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;
	//���ꕺ���ő吔(6)
	nCntUi++;
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y - NUMBER_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPos[nCntUi].x - NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPos[nCntUi].x + NUMBER_WIDTH / 2, g_aPos[nCntUi].y + NUMBER_HEIGHT / 2, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.6f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.7f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.6f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.7f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUi->Unlock();
}

//UI�̏I������
void UninitUi(void)
{
	int nCntUi;
	for (nCntUi = 0; nCntUi < 13; nCntUi++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureUi[nCntUi] != NULL)
		{
			g_pTextureUi[nCntUi]->Release();
			g_pTextureUi[nCntUi] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//UI�̍X�V����
void UpdateUi(void)
{
	int nCntUi;
	int nNumber;
	int nRank;
	VERTEX_2D *pVtx;
	g_pVtxBuffUi->Lock(0, 0, (void **)&pVtx, 0);
	Aircraft *pAircraft;
	pAircraft = GetAircraft();
	if (pAircraft->nLife == 1)
	{
		g_nATime++;
	}
	//�X�R�A�l�p
	if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - 150 <= g_aPos[0].x && g_aPos[0].x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + 150 &&
		pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - 50 <= g_aPos[0].y && g_aPos[0].y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + 50) //���@���߂Â����瓧����
	{
		g_aUIclear[0] -= 7;
		if (g_aUIclear[0] <= 60)
		{
			g_aUIclear[0] = 60;
		}
	}
	else
	{
		g_aUIclear[0] += 7;
		if (g_aUIclear[0] >= 200)
		{
			g_aUIclear[0] = 200;
		}
	}
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
	pVtx += 4;
	for (nCntUi = 1; nCntUi < MAX_NUMBER + 1; nCntUi++)//�X�R�A���l
	{
		nRank = pow(10, MAX_NUMBER + 1 - nCntUi);
		nNumber = g_nScore % nRank / (nRank / 10);
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[0]);
		pVtx += 4;
	}
	//���Đ��l�p
	if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - 70 <= g_aPos[9].x && g_aPos[9].x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + 70 &&
		pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - 45 <= g_aPos[9].y && g_aPos[9].y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + 45) //���@���߂Â����瓧����
	{
		g_aUIclear[1] -= 7;
		if (g_aUIclear[1] <= 60)
		{
			g_aUIclear[1] = 60;
		}
	}
	else
	{
		g_aUIclear[1] += 7;
		if (g_aUIclear[1] >= 200)
		{
			g_aUIclear[1] = 200;
		}
	}
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
	pVtx += 4;
	for (nCntUi = 10; nCntUi < 13; nCntUi++)//���Đ����l
	{
		nRank = pow(10, 13 - nCntUi);
		nNumber = g_nkill % nRank / (nRank / 10);
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[1]);
		pVtx += 4;
	}
	//�퓬�@�֘A�l�p
	if (pAircraft->pos.x - (AIRCRAFT_WIDTH / 2) - 90 <= g_aPos[13].x && g_aPos[13].x <= pAircraft->pos.x + (AIRCRAFT_WIDTH / 2) + 90 &&
		pAircraft->pos.y - (AIRCRAFT_HEIGHT / 2) - 170 <= g_aPos[13].y && g_aPos[13].y <= pAircraft->pos.y + (AIRCRAFT_HEIGHT / 2) + 170) //���@���߂Â����瓧����
	{
		g_aUIclear[2] -= 7;
		if (g_aUIclear[2] <= 60)
		{
			g_aUIclear[2] = 60;
		}
	}
	else
	{
		g_aUIclear[2] += 7;
		if (g_aUIclear[2] >= 200)
		{
			g_aUIclear[2] = 200;
		}
	}
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx += 4;
	//HUD�퓬�@
	if (pAircraft->nLife > 0)
	{
		pVtx[0].tex = D3DXVECTOR2((pAircraft->nMaxLife - pAircraft->nLife) * (1.0f / pAircraft->nMaxLife), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((pAircraft->nMaxLife - pAircraft->nLife + 1.0f) * (1.0f / pAircraft->nMaxLife), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((pAircraft->nMaxLife - pAircraft->nLife) * (1.0f / pAircraft->nMaxLife), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((pAircraft->nMaxLife - pAircraft->nLife + 1.0f) * (1.0f / pAircraft->nMaxLife), 1.0f);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2((pAircraft->nMaxLife - (pAircraft->nLife + 1)) * (1.0f / pAircraft->nMaxLife), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((pAircraft->nMaxLife - (pAircraft->nLife + 1) + 1.0f) * (1.0f / pAircraft->nMaxLife), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((pAircraft->nMaxLife - (pAircraft->nLife + 1)) * (1.0f / pAircraft->nMaxLife), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((pAircraft->nMaxLife - (pAircraft->nLife + 1) + 1.0f) * (1.0f / pAircraft->nMaxLife), 1.0f);
	}
	if (g_nATime < 6)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	}
	else
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		if (g_nATime >= 10)
		{
			g_nATime = 0;
		}
	}
	pVtx += 4;
	for (nCntUi = 15; nCntUi < 17; nCntUi++)//�@�̑����x���l
	{
		nRank = pow(10, 17 - nCntUi);
		nNumber = (100 / pAircraft->nMaxLife) * (pAircraft->nMaxLife - pAircraft->nLife) % nRank / (nRank / 10);
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
		pVtx += 4;
	}
	nCntUi++;
	//�u%�v�}�[�N
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx += 4;
	//HUD���ꕺ��
	if (pAircraft->nReload == 0 && pAircraft->nSpecial > 0)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx += 4;
	//���ꕺ���c�e��
	nNumber = pAircraft->nSpecial;
	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx += 4;
	//�u/�v�}�[�N
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx += 4;
	//���ꕺ���ő吔
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aUIclear[2]);
	g_pVtxBuffUi->Unlock();
}


//�`�揈��
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	int nCntUi = 0;
	Aircraft *pAircraft;
	pAircraft = GetAircraft();
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureUi[12]);//�X�R�A�l�p
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	pDevice->SetTexture(0, g_pTextureUi[0]);//�e�N�X�`���̐ݒ�
	for (nCntUi++; nCntUi < 9; nCntUi++)//�X�R�A
	{
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
	}
	pDevice->SetTexture(0, g_pTextureUi[12]);//���Đ��l�p
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	pDevice->SetTexture(0, g_pTextureUi[0]);//�e�N�X�`���̐ݒ�
	for (nCntUi++; nCntUi < 13; nCntUi++)//���Đ�
	{
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
	}
	pDevice->SetTexture(0, g_pTextureUi[11]);//�퓬�@�֘A�l�p
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	pDevice->SetTexture(0, g_pTextureUi[pAircraft->nAType + 1]);//HUD�퓬�@
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	pDevice->SetTexture(0, g_pTextureUi[0]);
	for (nCntUi++; nCntUi < 17; nCntUi++)//�@�̂̑����x
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntUi * 4,
			2);
	}
	pDevice->SetTexture(0, g_pTextureUi[9]);//�u%�v�}�[�N
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	pDevice->SetTexture(0, g_pTextureUi[pAircraft->nAType * 3 + pAircraft->nSType + 3]);//HUD���ꕺ��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	pDevice->SetTexture(0, g_pTextureUi[0]);//���ꕺ���c�e��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	pDevice->SetTexture(0, g_pTextureUi[10]);//�u/�v�}�[�N
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
	nCntUi++;
	pDevice->SetTexture(0, g_pTextureUi[0]);//���ꕺ���ő吔
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		nCntUi * 4,
		2);
}

//�X�R�A���Z
void AddScore(int nValue)
{
	g_nScore += nValue;
}

void AddKill(void)
{
	g_nkill++;
}

void ResetUi(void)
{
	int nCntClear;
	g_nScore = g_nReScore;
	g_nkill = g_nReKill;
	for (nCntClear = 0; nCntClear < 3; nCntClear++)
	{
		g_aUIclear[nCntClear] = 200;
	}
	g_nATime = 0;
}

int Score(void)
{
	return g_nScore;
}

int Kill(void)
{
	return g_nkill;
}

void NextStage(void)
{
	int nCntClear;
	g_nReScore = g_nScore;
	g_nReKill = g_nkill;
	for (nCntClear = 0; nCntClear < 3; nCntClear++)
	{
		g_aUIclear[nCntClear] = 200;
	}
	g_nATime = 0;
}