//--------------------------
//Author:三上航世
//ゲーム画面の処理(game.cpp)
//--------------------------
#include "input.h"
#include "gamepad.h"
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "ui.h"
#include "fade.h"
#include "rockon.h"
#include "shadow.h"
#include "light.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "player.h"
#include "object.h"
#include "camera.h"
#include "sound.h"
#include "pauseui.h"
#include "particle.h"
#include "tutorialui.h"
#include "item.h"

//プロトタイプ宣言
void SetStage(void);
D3DXVECTOR3 RespornPoint(void);
void Resporn(int nEnemy, D3DXVECTOR3 pos);

//グローバル宣言
int g_nResporn;		//次敵がリスポーンするまでの時間
int g_nEnemytype;	//次に出す敵の種類
bool g_bStop;		//止まってるか
bool g_bTuto;		//チュートリアルか

//初期化処理
void InitGame(void)
{
	SetCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f);
	InitShadow();
	InitUi();
	InitBullet();
	InitEnemy();
	InitRockon();
	InitLight();
	InitWall();
	InitBillboard();
	InitMeshfield();
	InitPlayer();
	//InitObject();
	InitpauseUi();
	InitParticle();
	InitItem();
	InittutorialUi();
	
	g_bStop = false;
	g_bTuto = true;
	SetStage();
	g_nResporn = 0;
	g_nEnemytype = 0;
	PlaySound(SOUND_LABEL_BGM1);
}

//ゲーム画面の終了処理
void UninitGame(void)
{
	UninitLight();
	UninitShadow();
	UninitWall();
	UninitBillboard();
	UninitMeshfield();
	UninitBullet();
	UninitPlayer();
	//UninitObject();
	UninitEnemy();
	UninitUi();
	UninitRockon();
	UninitpauseUi();
	UninitParticle();
	UninittutorialUi();
	UninitItem();
}

//ゲーム画面の更新処理
void UpdateGame(void)
{
	D3DXVECTOR3 pos;

	//キーボードのESCかゲームパッドのSTART押す
	if (GetKeyboardKey(DIK_ESCAPE) == true || GetGamePadButton(DIP_START) == true)
	{
		//チュートリアル中
		if (g_bTuto == true)
		{
			PlaySound(SOUND_LABEL_OK);
			SetFade();
		}
		//チュートリアル中じゃなく、プレイヤーがまだやられてない
		else if(GetPlayerDie() == false)
		{
			//ポーズ中
			if (g_bStop == true)
			{
				//ポーズ解除
				g_bStop = false;
				PlaySound(SOUND_LABEL_CANCEL);
			}
			//ポーズ中じゃない
			else
			{
				//ポーズする
				PlaySound(SOUND_LABEL_MENU);
				g_bStop = true;
			}
		}
	}

	//ポーズしてない
	if (g_bStop == false)
	{
		//プレイヤーやられてない
		if (GetPlayerDie() == false)
		{
			//リスポーンカウント加算
			g_nResporn++;

			//120フレーム
			if (g_nResporn == 120)
			{
				//敵の数少ない場合、リスポーンする
				if (EnemyNum() < 7)
				{
					pos = RespornPoint();
					Resporn(5, pos);
				}
			}

			//300フレーム
			if (g_nResporn == 300)
			{
				//敵の数少ない場合、リスポーンする
				if (EnemyNum() < 14)
				{
					pos = RespornPoint();
					Resporn(3, pos);
				}
			}

			//420フレーム以上
			if (g_nResporn >= 420)
			{
				//敵の数が少ない場合、リスポーンする
				if (EnemyNum() < 20)
				{
					pos = RespornPoint();
					Resporn(1, pos);
				}
				g_nResporn = 0;
			}
			UpdateBullet();
			UpdateEnemy();
			UpdateParticle();
			UpdateItem();
			UpdateUi();
		}
		UpdateCamera();
		UpdateLight();
		UpdateShadow();
		UpdateWall();
		UpdateBillboard();
		UpdateMeshfield();
		UpdatePlayer();
		UpdateRockon();

		//チュートリアル中の場合のみ、チュートリアルUI更新する
		if (g_bTuto == true)
		{
			UpdatetutorialUi();
		}
	}
	//ポーズ中
	else
	{
		//ポーズUI
		UpdatepauseUi();

		//キーボードでENTERか、ゲームパッドのBボタン押す
		if (GetKeyboardKey(DIK_RETURN) == true || GetGamePadButton(DIP_B) == true)
		{
			PlaySound(SOUND_LABEL_OK);

			//選択肢番号によって
			switch (GetSelect())
			{
			case 0:
				g_bStop = false;
				break;
			case 1:
				SetFade();
				break;
			case 2:
				SetFade(MODE_TITLE);
				break;
			}
		}
	}
}

//描画処理
void DrawGame(void)
{
	DrawWall();
	DrawMeshfield();
	DrawShadow();
	DrawBullet();
	DrawPlayer();
	DrawEnemy();
	//DrawObject();
	DrawRockon();
	DrawParticle();
	DrawItem();
	DrawBillboard();
	DrawUi();

	if (g_bTuto == true)
	{
		DrawtutorialUi();
	}
	if (g_bStop == true)
	{
		DrawpauseUi();
	}
}

bool GetStop(void)
{
	return g_bStop;
}

bool GetTuto(void)
{
	return g_bTuto;
}

void ResetGame(void)
{
	ResetBullet();
	ResetEnemy();
	ResetShadow();
	ResetParticle();
	ResetItem();
	ResetBillbourd();
	ResetPlayer();
	ResetUI();
	ResetpauseUi();
	ResetWall();
	ResetField();
	StopSound();
	PlaySound(SOUND_LABEL_BGM1);
	g_bTuto = false;

	SetCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f);

	SetStage();
	g_bStop = false;
}

void SetStage(void)
{
	g_nEnemytype = 0;
	g_nResporn = 0;
	SetItem(D3DXVECTOR3(0.0f, 60.0f, -100.0f));
	SetItem(D3DXVECTOR3(300.0f, 60.0f, -600.0f));
	SetItem(D3DXVECTOR3(600.0f, 60.0f, 500.0f));
	SetItem(D3DXVECTOR3(-500.0f, 60.0f, -400.0f));
	if (g_bTuto == false)
	{
		SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 300.0f), ENEMYTYPE_SPIDER);
	}
	SetEnemy(D3DXVECTOR3(200.0f, 0.0f, 300.0f), ENEMYTYPE_BIRD);
	SetEnemy(D3DXVECTOR3(-200.0f, 0.0f, 300.0f), ENEMYTYPE_DOG);
	SetEnemy(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), ENEMYTYPE_ZOMBE);
}

D3DXVECTOR3 RespornPoint(void)
{
	float fRot;
	D3DXVECTOR3 Resporn;
	fRot = atan2f(PlayerPos().x, PlayerPos().z);
	if (fRot < 0.0f)
	{
		fRot += D3DX_PI;
	}
	else
	{
		fRot -= D3DX_PI;
	}
	Resporn = D3DXVECTOR3(500.0f * sinf(fRot), 0.0f, 500.0f * cosf(fRot));
	return Resporn;
}

void Resporn(int nEnemy, D3DXVECTOR3 pos)
{
	int nCntEnemy;
	D3DXVECTOR3 Respos;
	for (nCntEnemy = 0; nCntEnemy < nEnemy; nCntEnemy++)
	{
		Respos = D3DXVECTOR3(pos.x + sinf(D3DX_PI * (float)(nCntEnemy / ((float)nEnemy / 2.0f))) * 80.0f, 0.0f, pos.z + cosf(D3DX_PI * (float)(nCntEnemy / ((float)nEnemy / 2.0f))) * 80.0f);
		switch (g_nEnemytype)
		{
		case 0:
			SetEnemy(Respos, ENEMYTYPE_BIRD);
			break;
		case 1:
			SetEnemy(Respos, ENEMYTYPE_DOG);
			break;
		case 2:
			SetEnemy(Respos, ENEMYTYPE_ZOMBE);
			break;
		default:
			SetEnemy(Respos, ENEMYTYPE_BIRD);
			break;
		}
		if (g_nEnemytype >= 2)
		{
			g_nEnemytype = 0;
		}
		else
		{
			g_nEnemytype++;
		}
	}
}