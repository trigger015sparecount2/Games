//--------------------------
//Author:�O��q��
//�Q�[����ʂ̏���(game.cpp)
//--------------------------
#include "input.h"
#include "game.h"
#include "bg.h"
#include "player.h"
#include "gameui.h"
#include "sound.h"
#include "fade.h"
#include "target.h"
#include "block.h"
#include "pauseui.h"
#include "cross.h"
#include "padinput.h"

//�O���[�o���ϐ�
bool g_bStop; //�Q�[�����ꎞ��~���Ă邩�ǂ���

//����������
void InitGame(void)
{
	InitPlayer();
	InitBlock();
	InitCross();
	InitTarget();
	InitGameUi();
	InitPauseUi();
	SetObject();
	g_bStop = false;
	SetBg(1, true);
	PlaySound(SOUND_LABEL_BGM001);
}

//�Q�[����ʂ̏I������
void UninitGame(void)
{
	UninitBlock();
	UninitTarget();
	UninitPlayer();
	UninitCross();
	UninitGameUi();
	UninitPauseUi();
}

//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
	if (GetKeyboardKey(DIK_P) == true && GameOver() == false || GetGamePadButton(11) == true && GameOver() == false)
	{
		if (g_bStop == false)
		{
			PlaySound(SOUND_LABEL_PAUSE);
			g_bStop = true;
		}
		else
		{
			PlaySound(SOUND_LABEL_CANCEL);
			g_bStop = false;
		}
	}
	if (g_bStop == false)
	{
		ScrollBg(true);
		UpdateBlock();
		UpdatePlayer();
		UpdateTarget();
		UpdateCross();
		UpdateGameUi();
	}
	else
	{
		UpdatePauseUi();
		ScrollBg(false);
	}
}

//�`�揈��
void DrawGame(void)
{
	DrawBlock();
	DrawTarget();
	DrawCross();
	DrawPlayer();
	DrawGameUi();
	if (g_bStop == true)
	{
		DrawPauseUi();
	}
}

//�Q�[���X�^�[�g
void StartGame(void)
{
	g_bStop = false; 
}

//���X�^�[�g����
void RestartGame(void)
{
	ResetBlock();
	ResetPlayer();
	ResetCross();
	ResetTarget();
	ResetGameUi();
	SetObject();
	SetBg(1, true);
	StopSound();
	PlaySound(SOUND_LABEL_BGM001);
}

//�I�u�W�F�N�g�Z�b�g������
void SetObject(void)
{
	SetTarget(D3DXVECTOR3(260.0f, 620.0f, 0.0f));  //�^�񒆉������~�肽��
	SetTarget(D3DXVECTOR3(820.0f, 550.0f, 0.0f));  //�^�񒆉��E��
	SetTarget(D3DXVECTOR3(1210.0f, 280.0f, 0.0f)); //�E���ԑ_��
	SetTarget(D3DXVECTOR3(25.0f, 100.0f, 0.0f));   //���^�C�~���O
	SetTarget(D3DXVECTOR3(1200.0f, 620.0f, 0.0f)); //�E�����[�v�z�[���Ɏ藠��
	SetTarget(D3DXVECTOR3(500.0f, 160.0f, 0.0f));  //�^�񒆏�
	SetBlock(D3DXVECTOR3(0.0f, 700.0f, 0.0f), 1280.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //��ʉ�
	SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 720.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);       //��ʍ�
	SetBlock(D3DXVECTOR3(20.0f, 0.0f, 0.0f), 1260.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);     //��ʏ�
	SetBlock(D3DXVECTOR3(1260.0f, 20.0f, 0.0f), 20.0f, 680.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //��ʉE
	SetBlock(D3DXVECTOR3(580.0f, 460.0f, 0.0f), 100.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�X�^�[�g�n�_
	SetBlock(D3DXVECTOR3(1200.0f, 20.0f, 0.0f), 20.0f, 270.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�E�̂킸���Ȍ��Ԃ�����Ǐ㑤
	SetBlock(D3DXVECTOR3(1200.0f, 320.0f, 0.0f), 20.0f, 280.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);  //�E�̂킸���Ȍ��Ԃ�����ǉ���
	SetBlock(D3DXVECTOR3(1100.0f, 160.0f, 0.0f), 60.0f, 20.0f, D3DXVECTOR3(0.0f, 2.2f, 0.0f), 280, BLOCK_NORMAL); //�E�̂킸���Ȍ��Ԃ�����Ǖt�߂̓�����
	SetBlock(D3DXVECTOR3(80.0f, 20.0f, 0.0f), 20.0f, 440.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);     //���̂킸���Ȍ��Ԃ������
	SetBlock(D3DXVECTOR3(80.0f, 460.0f, 0.0f), 320.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�����̈͂݃u���b�N��
	SetBlock(D3DXVECTOR3(120.0f, 480.0f, 0.0f), 20.0f, 100.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�����̈͂݃u���b�N�E
	SetBlock(D3DXVECTOR3(20.0f, 580.0f, 0.0f), 120.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�����̈͂݃u���b�N��
	SetBlock(D3DXVECTOR3(-80.0f, 180.0f, 0.0f), 80.0f, 20.0f, D3DXVECTOR3(1.2f, 0.0f, 0.0f), 160, BLOCK_NORMAL);  //���W�Q�p�u���b�N����
	SetBlock(D3DXVECTOR3(100.0f, 220.0f, 0.0f), 80.0f, 20.0f, D3DXVECTOR3(-0.3f, 0.0f, 0.0f), 220, BLOCK_NORMAL); //���W�Q�p�u���b�N�E��
	SetBlock(D3DXVECTOR3(240.0f, 340.0f, 0.0f), 60.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_ICE);		  //�X�^�[�g�n�_�����̕X�u���b�N
	SetBlock(D3DXVECTOR3(280.0f, 120.0f, 0.0f), 800.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);	  //�X�^�[�g�n�_��̏㑤�����u���b�N
	SetBlock(D3DXVECTOR3(560.0f, 20.0f, 0.0f), 20.0f, 40.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);     //�^�񒆏㍶����u���b�N
	SetBlock(D3DXVECTOR3(560.0f, 100.0f, 0.0f), 20.0f, 40.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�^�񒆏㍶�����u���b�N
	SetBlock(D3DXVECTOR3(600.0f, 30.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_WARP);       //�^�񒆏㍶�����[�v�z�[��
	SetBlock(D3DXVECTOR3(1110.0f, 610.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, BLOCK_WARP);     //�E�����[�v�z�[��
	SetBlock(D3DXVECTOR3(1080.0f, 600.0f, 0.0f), 20.0f, 100.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);  //�E���͂݃u���b�N�c
	SetBlock(D3DXVECTOR3(1080.0f, 580.0f, 0.0f), 180.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);  //�E���͂݃u���b�N��
	SetBlock(D3DXVECTOR3(640.0f, 20.0f, 0.0f), 20.0f, 100.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�^�񒆏��
	SetBlock(D3DXVECTOR3(680.0f, 30.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2, BLOCK_WARP);       //�^�񒆏�E�����[�v�z�[��
	SetBlock(D3DXVECTOR3(90.0f, 490.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, BLOCK_WARP);       //�������[�v�z�[��
	SetBlock(D3DXVECTOR3(80.0f, 620.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);	  //�L�����[�u���b�N�̃X�g�b�p�[
	SetBlock(D3DXVECTOR3(80.0f, 620.0f, 0.0f), 80.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_CARRY);      //�����L�����[�u���b�N
	SetBlock(D3DXVECTOR3(180.0f, 580.0f, 0.0f), 300.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //��������
	SetBlock(D3DXVECTOR3(480.0f, 480.0f, 0.0f), 20.0f, 60.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�^�񒆉��������Əo���̋�؂�
	SetBlock(D3DXVECTOR3(620.0f, 480.0f, 0.0f), 20.0f, 220.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�^�񒆋�؂�
	SetBlock(D3DXVECTOR3(520.0f, 500.0f, 0.0f), 80.0f, 20.0f, D3DXVECTOR3(0.0f, 640.0f, 0.0f), 0, BLOCK_DOWN);    //�^�񒆉���������������u���b�N
	SetBlock(D3DXVECTOR3(720.0f, 520.0f, 0.0f), 20.0f, 100.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�^�񒆉��E�c����
	SetBlock(D3DXVECTOR3(740.0f, 520.0f, 0.0f), 220.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�^�񒆉��E��
	SetBlock(D3DXVECTOR3(940.0f, 540.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�^�񒆉��E�c�E��
	SetBlock(D3DXVECTOR3(860.0f, 620.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�E���L�����[�u���b�N��[�߂�ꏊ
	SetBlock(D3DXVECTOR3(780.0f, 620.0f, 0.0f), 20.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);    //�E���L�����[�u���b�N�̃X�g�b�p�[
	SetBlock(D3DXVECTOR3(720.0f, 620.0f, 0.0f), 80.0f, 80.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_CARRY);     //�E���L�����[�u���b�N
	SetBlock(D3DXVECTOR3(960.0f, 520.0f, 0.0f), 80.0f, 20.0f, D3DXVECTOR3(0.0f, 320.0f, 0.0f), 0, BLOCK_UP);      //�X�^�[�g�n�_�����E�オ��u���b�N
	SetBlock(D3DXVECTOR3(420.0f, 240.0f, 0.0f), 500.0f, 20.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�X�^�[�g�n�_�̏�̉��������u���b�N
	SetBlock(D3DXVECTOR3(1060.0f, 140.0f, 0.0f), 20.0f, 100.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);  //�X�^�[�g�n�_�̏�̏c�E��
	SetBlock(D3DXVECTOR3(320.0f, 140.0f, 0.0f), 20.0f, 120.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, BLOCK_NORMAL);   //�X�^�[�g�n�_�̏�̏c����
	SetBlock(D3DXVECTOR3(340.0f, 250.0f, 0.0f), 80.0f, 20.0f, D3DXVECTOR3(0.0f, 400.0f, 0.0f), 0, BLOCK_DOWN);    //�^�񒆉���������������u���b�N
}