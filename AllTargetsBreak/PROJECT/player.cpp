//--------------------------
//Author:�O��q��
//���@�̏���(plyer.cpp)
//--------------------------
#include "player.h"
#include "input.h"
#include "block.h"
#include "knife.h"
#include "padinput.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL; //���_�o�b�t�@�ւ̃|�C���^
Player g_aPlayer;

//����������
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	ResetPlayer();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/player000.png",
		&g_pTexturePlayer);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void **)&pVtx, 0);
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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//�I������
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//�X�V����
void UpdatePlayer(void)
{
	g_aPlayer.posOld.x = g_aPlayer.pos.x;
	g_aPlayer.posOld.y = g_aPlayer.pos.y;
	g_aPlayer.nknife--;
	if (g_aPlayer.nknife < 0)
	{
		g_aPlayer.nknife = 0;
	}
	if (GetKeyboardPress(DIK_A) == true || LeftStickX() < 0.0f) //A�L�[���������A���X�e�B�b�N��|�����Ƃ�
	{
		if (g_aPlayer.nStep == 0 && g_aPlayer.bJump == true)
		{
			PlaySound(SOUND_LABEL_FOOTSTEP);
		}
		g_aPlayer.nStep++;
		if (g_aPlayer.nStep >= 15)
		{
			g_aPlayer.nStep = 0;
		}
		g_aPlayer.fLeft = 0.5f;
		g_aPlayer.nCounterAnim++;
		if (g_aPlayer.nCounterAnim == 6)
		{
			g_aPlayer.nPatternAnim++;
			g_aPlayer.nCounterAnim = 0;
			if (g_aPlayer.nPatternAnim == 4)
			{
				g_aPlayer.nPatternAnim = 0;
			}
		}
		if (g_aPlayer.move.x > 0.0f) //�����]������Ƃ�
		{
			if (LeftStickX() < -0.6f || GetKeyboardPress(DIK_A) == true) //�[�����X�e�B�b�N�����ɓ|�����Ƃ���A�L�[���������Ƃ�
			{
				if (g_aPlayer.bJump == true)
				{
					g_aPlayer.move.x -= 1.6f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x -= 1.0f * g_aPlayer.fIce; //��
				}
			}
			else //�󂭍��X�e�B�b�N�����ɓ|�����Ƃ�
			{
				if (g_aPlayer.bJump == true)
				{
					g_aPlayer.move.x -= 0.5f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x -= 0.3f * g_aPlayer.fIce; //��
				}
			}
		}
		else
		{
			if (LeftStickX() < -0.6f || GetKeyboardPress(DIK_A) == true) //�[�����X�e�B�b�N�����ɓ|�����Ƃ�
			{
				if (g_aPlayer.bJump == true)
				{
					g_aPlayer.move.x -= 0.8f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x -= 0.5f * g_aPlayer.fIce; //��
				}
			}
			else
			{
				if (g_aPlayer.bJump == true) //�󂭍��X�e�B�b�N�����ɓ|�����Ƃ�
				{
					g_aPlayer.move.x -= 0.25f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x -= 0.16f * g_aPlayer.fIce; //��
				}
				if (g_aPlayer.move.x <= -4.0f)
				{
					g_aPlayer.move.x += 1.0f; //��������������ꍇ�A���X�ɒx���Ȃ�
				}
				else if (g_aPlayer.move.x <= -3.0f)
				{
					g_aPlayer.move.x = -3.0f; //�����Ă���Ƃ��̍ō����x
				}
			}
		}
		if (g_aPlayer.move.x <= -8.0f)
		{
			g_aPlayer.move.x = -8.0f; //�ʏ펞�̍ō����x
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || LeftStickX() > 0.0f)
	{
		if (g_aPlayer.nStep == 0 && g_aPlayer.bJump == true)
		{
			PlaySound(SOUND_LABEL_FOOTSTEP);
		}
		g_aPlayer.nStep++;
		if (g_aPlayer.nStep >= 15)
		{
			g_aPlayer.nStep = 0;
		}
		g_aPlayer.fLeft = 0.0f;
		g_aPlayer.nCounterAnim++;
		if (g_aPlayer.nCounterAnim == 6)
		{
			g_aPlayer.nPatternAnim++;
			g_aPlayer.nCounterAnim = 0;
			if (g_aPlayer.nPatternAnim == 4)
			{
				g_aPlayer.nPatternAnim = 0;
			}
		}
		if (g_aPlayer.move.x < 0.0f) //�����]������Ƃ�
		{
			if (LeftStickX() > 0.6f || GetKeyboardPress(DIK_D) == true) //�[�����X�e�B�b�N���E�ɓ|�����Ƃ�
			{
				if (g_aPlayer.bJump == true)
				{
					g_aPlayer.move.x += 1.6f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x += 1.0f * g_aPlayer.fIce; //��
				}
			}
			else
			{
				if (g_aPlayer.bJump == true) //�󂭍��X�e�B�b�N��|�����Ƃ�
				{
					g_aPlayer.move.x += 0.5f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x += 0.3f * g_aPlayer.fIce; //��
				}
			}
		}
		else
		{
			if (LeftStickX() > 0.6f || GetKeyboardPress(DIK_D) == true) //�[�����X�e�B�b�N���E�ɓ|�����Ƃ���D�L�[���������Ƃ�
			{
				if (g_aPlayer.bJump == true)
				{
					g_aPlayer.move.x += 0.8f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x += 0.5f * g_aPlayer.fIce; //��
				}
			}
			else
			{
				if (g_aPlayer.bJump == true) //�󂭍��X�e�B�b�N���E�ɓ|�����Ƃ�
				{
					g_aPlayer.move.x += 0.25f * g_aPlayer.fIce; //�n��
				}
				else
				{
					g_aPlayer.move.x += 0.16f * g_aPlayer.fIce; //��
				}
				if (g_aPlayer.move.x >= 4.0f)
				{
					g_aPlayer.move.x -= 1.0f; //��������������Ƃ��A���X�ɒx���Ȃ�
				}
				else if (g_aPlayer.move.x >= 3.0f)
				{
					g_aPlayer.move.x = 3.0f; //�����̍ō����x
				}
			}
		}
		if (g_aPlayer.move.x >= 8.0f)
		{
			g_aPlayer.move.x = 8.0f; //����̍ō����x
		}
	}
	else
	{
		g_aPlayer.nCounterAnim = 0;
		g_aPlayer.nPatternAnim = 0;
		g_aPlayer.nStep = 0;
		if (g_aPlayer.move.x > 0.0f)
		{
			g_aPlayer.move.x -= 1.2f * g_aPlayer.fIce;
			if (g_aPlayer.move.x < 0.0f)
			{
				g_aPlayer.move.x = 0.0f;
			}
		}
		else if (g_aPlayer.move.x < 0.0f)
		{
			g_aPlayer.move.x += 1.2f * g_aPlayer.fIce;
			if (g_aPlayer.move.x > 0.0f)
			{
				g_aPlayer.move.x = 0.0f;
			}
		}
	}
	if (GetKeyboardKey(DIK_I) == true && g_aPlayer.nknife == 0 || GetGamePadButton(5) == true && g_aPlayer.nknife == 0)
	{
		if (GetKeyboardPress(DIK_W) == true || RightStickY() < -0.9f && GamePad() == true) //��
		{
			SetKnife(g_aPlayer.pos, KNIFE_UP);
		}
		else if (GetKeyboardPress(DIK_S) == true || RightStickY() > 0.9f && GamePad() == true) //��
		{
			SetKnife(g_aPlayer.pos, KNIFE_DOWN);
		}
		else if (GetKeyboardPress(DIK_A) == true || RightStickX() < 0.0f && GamePad() == true) //��
		{
			g_aPlayer.fLeft = 0.5f;
			SetKnife(g_aPlayer.pos, KNIFE_LEFT);
		}
		else if (GetKeyboardPress(DIK_D) == true || RightStickX() > 0.0f && GamePad() == true) //�E
		{
			g_aPlayer.fLeft = 0.0f;
			SetKnife(g_aPlayer.pos, KNIFE_RIGHT);
		}
		else
		{
			if (g_aPlayer.fLeft == 0.0f) //�E�������Ă���
			{
				SetKnife(g_aPlayer.pos, KNIFE_RIGHT);
			}
			else //���������Ă���
			{
				SetKnife(g_aPlayer.pos, KNIFE_LEFT);
			}
		}
		g_aPlayer.nknife = 15;
	}
	if (GetKeyboardKey(DIK_J) == true && g_aPlayer.bJump == true || GetGamePadButton(2) == true && g_aPlayer.bJump == true) //�W�����v
	{
		PlaySound(SOUND_LABEL_JUMP);
		g_aPlayer.move.y = -20.0f;
	}
	g_aPlayer.move.y += 1.3f;
	if (g_aPlayer.bJump == false)
	{
		g_aPlayer.nPatternAnim = 1;
		g_aPlayer.nStep = 13;
	}
	g_aPlayer.pos.x += g_aPlayer.move.x + g_aPlayer.Blockmove.x;
	g_aPlayer.pos.y += g_aPlayer.move.y + g_aPlayer.Blockmove.y;
	if (g_aPlayer.pos.x <= -PLAYER_WIDTH / 2) //���s�����ꍇ
	{
		ResetPlayer();
	}
	if (g_aPlayer.pos.y <= -PLAYER_HEIGHT) //��s�����ꍇ
	{
		ResetPlayer();
	}
	if (g_aPlayer.pos.x >= SCREEN_WIDTH + (PLAYER_WIDTH / 2)) //�E�s�����ꍇ
	{
		ResetPlayer();
	}
	if (g_aPlayer.pos.y >= SCREEN_HEIGHT + PLAYER_HEIGHT) //���s�����ꍇ
	{
		ResetPlayer();
	}
	g_aPlayer.bJump = CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, PLAYER_WIDTH / 2, PLAYER_HEIGHT, &g_aPlayer.Blockmove, 0);
	VERTEX_2D *pVtx; //���_���ւ̃|�C���g
	g_pVtxBuffPlayer->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3((float)(g_aPlayer.pos.x - PLAYER_WIDTH / 2), (float)(g_aPlayer.pos.y - PLAYER_HEIGHT), g_aPlayer.pos.z);
	pVtx[1].pos = D3DXVECTOR3((float)(g_aPlayer.pos.x + PLAYER_WIDTH / 2), (float)(g_aPlayer.pos.y - PLAYER_HEIGHT), g_aPlayer.pos.z);
	pVtx[2].pos = D3DXVECTOR3((float)(g_aPlayer.pos.x - PLAYER_WIDTH / 2), (float)(g_aPlayer.pos.y),				 g_aPlayer.pos.z);
	pVtx[3].pos = D3DXVECTOR3((float)(g_aPlayer.pos.x + PLAYER_WIDTH / 2), (float)(g_aPlayer.pos.y),				 g_aPlayer.pos.z);
	pVtx[0].tex = D3DXVECTOR2((float)g_aPlayer.nPatternAnim / 4        , g_aPlayer.fLeft);
	pVtx[1].tex = D3DXVECTOR2((float)g_aPlayer.nPatternAnim / 4 + 0.25f, g_aPlayer.fLeft);
	pVtx[2].tex = D3DXVECTOR2((float)g_aPlayer.nPatternAnim / 4        , g_aPlayer.fLeft + 0.5f);
	pVtx[3].tex = D3DXVECTOR2((float)g_aPlayer.nPatternAnim / 4 + 0.25f, g_aPlayer.fLeft + 0.5f);
	g_pVtxBuffPlayer->Unlock();
}

//�`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
												  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);    //�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

Player *GetPlayer(void)
{
	return &g_aPlayer;
}

void ResetPlayer(void)
{
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.pos = D3DXVECTOR3(640.0f, 460.0f, 0.0f);
	g_aPlayer.posOld = D3DXVECTOR3(640.0f, 460.0f, 0.0f);
	g_aPlayer.Blockmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.nCounterAnim = 0;
	g_aPlayer.nPatternAnim = 0;
	g_aPlayer.nknife = 0;
	g_aPlayer.fLeft = 0.0f;
	g_aPlayer.nStep = 0;
	g_aPlayer.fIce = 1.0f;
	g_aPlayer.bJump = true;
}

void IcePlayer(bool bIce)
{
	if (bIce == true)
	{
		g_aPlayer.fIce = 0.06f;
	}
	else
	{
		g_aPlayer.fIce = 1.0f;
	}
}