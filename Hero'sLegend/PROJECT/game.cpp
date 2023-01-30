//--------------------------
//Author:�O��q��
//�Q�[����ʂ̏���(game.cpp)
//--------------------------
#include "input.h"
#include "gamepad.h"
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "ui.h"
#include "fade.h"
#include "rockon.h"
#include "shadow.h"
#include "light.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "particle.h"
#include "player.h"
#include "object.h"
#include "orbit.h"
#include "camera.h"
#include "sound.h"
#include "pauseui.h"

//�O���[�o���錾
D3DXVECTOR3 g_resporn[4];
bool g_bStop;

//����������
void InitGame(void)
{
	ResetCamera();
	ResetShadow();
	InitBullet();
	InitEnemy();
	InitExplosion();
	InitUi();
	InitRockon();
	InitShadow();
	InitLight();
	InitWall();
	InitBillboard();
	InitMeshfield();
	InitParticle();
	InitPlayer();
	InitObject();
	InitOrbit();
	InitpauseUi();
	g_bStop = false;
	g_resporn[0] = D3DXVECTOR3(0.0f, 0.0f, 1200.0f);
	g_resporn[1] = D3DXVECTOR3(1200.0f, 0.0f, 0.0f);
	g_resporn[2] = D3DXVECTOR3(0.0f, 0.0f, -1200.0f);
	g_resporn[3] = D3DXVECTOR3(-1200.0f, 0.0f, 0.0f);
	PlaySound(SOUND_LABEL_BGM2);
}

//�Q�[����ʂ̏I������
void UninitGame(void)
{
	UninitLight();
	UninitShadow();
	UninitWall();
	UninitBillboard();
	UninitMeshfield();
	UninitBullet();
	UninitExplosion();
	UninitParticle();
	UninitPlayer();
	UninitObject();
	UninitEnemy();
	UninitUi();
	UninitOrbit();
	UninitRockon();
	UninitpauseUi();
}

//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
	//�|�[�Y
	if (GetKeyboardKey(DIK_O) == true || GetGamePadButton(DIP_START) == true)
	{
		if (g_bStop == true)
		{
			g_bStop = false;
		}
		else
		{
			Setpause();
			g_bStop = true;
		}
	}

	if (g_bStop == false)
	{
		UpdateLight();
		UpdateShadow();
		UpdateWall();
		UpdateBillboard();
		UpdateMeshfield();
		UpdateBullet();
		UpdateExplosion();
		UpdateParticle();
		UpdateObject();
		UpdateEnemy();
		UpdatePlayer();
		UpdateUi();
		UpdateOrbit();
		UpdateRockon();
	}
	else
	{
		UpdatepauseUi();
	}

	//�v���C���[�̓|��������100�������G�̐���500����
	if (PlayerKill() + EnemyNum() < 100 && EnemyNum() < 50)
	{
		SetEnemy(g_resporn[rand() % 4], rand() % 2);
	}

	//�v���C���[��100�̓|���A�܂��̓v���C���[��HP��0�ɂȂ�
	if (PlayerKill() >= 100 || PlayerHP() <= 0)
	{
		SetFade(MODE_RESULT);
	}
}

//�`�揈��
void DrawGame(void)
{
	DrawWall();
	DrawMeshfield();
	DrawShadow();
	DrawExplosion();
	DrawBullet();
	DrawParticle();
	DrawPlayer();
	DrawEnemy();
	DrawOrbit();
	DrawObject();
	DrawRockon();
	if (g_bStop == true)
	{
		DrawpauseUi();
	}
}