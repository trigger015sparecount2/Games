//---------------------------
//Author:三上航世
//モデル(player.cpp)
//---------------------------
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"
#include "model.h"
#include "camera.h"
#include "fade.h"
#include "shadow.h"
#include "gamepad.h"
#include "game.h"
#include "sound.h"
#include "ui.h"
#include "pauseui.h"

//=============================================================================
//静的
//=============================================================================

//=============================================================================
//マクロ
//=============================================================================
#define MAX_JUMPMOVEX (10.0f)
#define MAX_JUMPMOVEY (20.0f)
#define MAX_GRAVITY (-30.0f)
#define REFLECT (-0.6f)
#define SCREEN_HEIGHT_DIFF (30.0f)	//ウィンドウ領域(枠全体)とクライアント領域(描画してる領域)の差(縦)
#define SCREEN_WIDTH_DIFF (8.0f)	//ウィンドウ領域(枠全体)とクライアント領域(描画してる領域)の差(横)

CPlayer::CPlayer(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CPlayer::~CPlayer()
{

}

//初期化処理
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	Load(aFileName);
	m_pBlackGauge[0] = CUI::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), 723.0f, 42.0f, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)); //画面上部ゲージの下地
	m_pBlackGauge[1] = CUI::Create(D3DXVECTOR3(500.0f, 474.0f, 0.0f), 42.0f, 170.0f, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)); //画面左ゲージの下地
	m_pBlackGauge[2] = CUI::Create(D3DXVECTOR3(780.0f, 474.0f, 0.0f), 42.0f, 170.0f, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)); //画面右ゲージの下地
	m_pGauge = CUI::Create(D3DXVECTOR3(280.0f, 100.0f, 0.0f), 0.0f, 40.0f, -1, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	int nCnt;
	for (nCnt = 0; nCnt < 20; nCnt++)
	{
		if (nCnt < 10)
		{
			m_pBlockGauge[nCnt] = CUI::Create(D3DXVECTOR3(500.0f, 550.0f - 17.0f * nCnt, 0.0f), 40.0f, 15.0f, -1, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));			//ジャンプ時の左右への移動量左側
		}
		else
		{
			m_pBlockGauge[nCnt] = CUI::Create(D3DXVECTOR3(780.0f, 550.0f - 17.0f * (nCnt - 10), 0.0f), 40.0f, 15.0f, -1, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));	//ジャンプ時の左右への移動量右側
		}
	}
	m_pPauseUI[0] = CPauseUI::Create(D3DXVECTOR3(640.0f, 260.0f, 0.0f), 200.0f, 50.0f, 1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)); //ポーズ中続ける
	m_pPauseUI[1] = CPauseUI::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 180.0f, 50.0f, 2, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f)); //ポーズ中リトライ
	m_pPauseUI[2] = CPauseUI::Create(D3DXVECTOR3(640.0f, 460.0f, 0.0f), 140.0f, 50.0f, 3, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f)); //ポーズ中終了

	SetPos(pos);
	SetRot(rot);
	m_rotDesh = rot;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RestartPos = pos;
	m_PosOld = pos;

	m_pKeyboard = CManager::GetKeyboard();
	//m_pGamePad = CManager::GetGamepad();
	m_pMouse = CManager::GetMouse();
	m_pCamera = CManager::GetRenderer()->GetCamera();

	m_pCamera->ResetRot();
	m_pCamera->SetPlayer(this);
	m_bLandObject = false;
	m_motionTypeOld = MOTIONTYPE_NEUTRAL;
	m_nRunStop = 0;
	m_nPauseSelect = 0;
	m_bGameClear = false;
	m_bEndSelect = false;
	D3DXVECTOR3 size;
	size.x = GetRadius();
	size.y = 0.0f;
	size.z = GetRadius();
	m_fShadowPosY = 1000000.0f;
	m_pShadow = CShadow::Create(size, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));
	MotionChange(MOTIONTYPE_RETURN);
	m_bLandField = false;
	m_bLanding = false;
	m_fChargeJump = 4.0f;
	m_ShadowRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCharge = false;
	m_bGaugeFade = false;
	m_bChargePlus = true;
	m_fJumpMoveX = 0.0f;
	m_fGaugeFade = 0.0f;
	m_nCntJump = 0;
	m_nFastMotion = 0;
	return S_OK;
}

//終了処理
void CPlayer::Uninit()
{
	if (m_pCamera != NULL)
	{
		m_pCamera = NULL;
	}
	/*if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}*/
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	int nCnt;
	for (nCnt = 0; nCnt < 32; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Uninit();
			m_pModel[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 20; nCnt++)
	{
		if (m_pBlockGauge[nCnt] != NULL)
		{
			m_pBlockGauge[nCnt] = NULL;
		}
	}
	if (m_pMouse != NULL)
	{
		m_pMouse = NULL;
	}
	if (m_pShadow != NULL)
	{
		m_pShadow->SetDeath(true);
		m_pShadow = NULL;
	}
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pPauseUI[nCnt] != NULL)
		{
			m_pPauseUI[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pBlackGauge[nCnt] != NULL)
		{
			m_pBlackGauge[nCnt] = NULL;
		}
	}
	if (m_pGauge != NULL)
	{
		m_pGauge = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CPlayer::Update()
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	m_PosOld = pos;
	bool bRun = false;
	m_fShadowPosY = -100000.0f;

	//ポーズ中じゃない
	if (CManager::GetPause() == false)
	{
		if (m_pKeyboard != NULL && m_pMouse != NULL)
		{
			//着地してる
			if (m_bLanding == true)
			{
				//左右への移動
				if (m_pKeyboard->GetPress(DIK_A) == true)
				{
					bRun = Move(-0.5f);
				}
				else if (m_pKeyboard->GetPress(DIK_D) == true)
				{
					bRun = Move(0.5f);
				}
				else
				{
					Stop();
				}
			}

			//ESCでポーズ
			if (m_pKeyboard->GetKey(DIK_ESCAPE) == true)
			{
				CSound::Play(8);
				CManager::SetPause(true);
			}

			//走ってる、着地してる、モーションが走る以外
			if (bRun == true && m_bLanding == true && m_motionType != MOTIONTYPE_RUN)
			{
				RunFirst();
			}

			//走ってない、走るモーション
			if (bRun == false && m_motionType == MOTIONTYPE_RUN)
			{
				RunStop();
			}

			//着地
			if (m_bLanding == true)
			{
				//ジャンプ
				JumpCharge();
			}
			//浮いてる
			else
			{
				//重力
				Gravity();
			}

			//マウスの左を押しておらず、右のみ押してる状態
			if (m_pMouse->GetPress(CMouse::DIM_L) != true && m_pMouse->GetPress(CMouse::DIM_R) == true)
			{
				//マウス動かしてる
				if (m_pMouse->MouseX() != 0.0f || m_pMouse->MouseY() != 0.0f)
				{
					//カメラ動かす
					m_pCamera->AddPosPlus(D3DXVECTOR3(m_pMouse->MouseX() * 0.7f, m_pMouse->MouseY() * -0.7f, 0.0f), &m_aCamera[0]);
				}
			}
			//左が押された、または右が離された
			else if(m_pMouse->GetMouseButton(CMouse::DIM_L) == true || m_pMouse->GetRelease(CMouse::DIM_R) == true)
			{
				//カメラの位置リセット
				m_pCamera->AddPosReset();
			}
		}
		pos += m_move;

		//着地してない
		if (m_bLanding == false)
		{
			//一定の移動量で横に移動し続ける
			pos.x += m_fJumpMoveX;
		}

		//当たり判定
		CollisionObject(&pos, m_PosOld);
		CollisionPlane(&pos, m_PosOld);

		//着地してるか
		if (m_bLandField == true || m_bLandObject == true)
		{
			m_bLanding = true;
		}
		else if(m_bLandField == false && m_bLandObject == false)
		{
			m_bLanding = false;
		}

		//着地してない
		if (m_bLanding == false)
		{
			//影動かす
			m_pShadow->MoveY(D3DXVECTOR3(pos.x, m_fShadowPosY, pos.z), m_ShadowRot);

			//モーション切り替える
			if (m_motionType != MOTIONTYPE_FRONTJUMP && m_motionType != MOTIONTYPE_BACKJUMP)
			{
				MotionChange(MOTIONTYPE_FRONTJUMP);
			}
		}

		//ゲージ類フェードインフェードアウト
		if (m_bGaugeFade == true)
		{
			GaugeFadeOut();
		}
		else
		{
			GaugeFadeIn();
		}

		#ifdef _DEBUG
		if (m_pKeyboard != NULL) //チートコマンド
		{
			if (m_pKeyboard->GetKey(DIK_RETURN) == true) //リスタート
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pos = m_RestartPos;
				m_fJumpMoveX = 0.0f;
			}
			if (m_pKeyboard->GetKey(DIK_LSHIFT) == true) //リスタートポイント更新
			{
				m_RestartPos = pos;
			}
			if (m_pKeyboard->GetKey(DIK_RSHIFT) == true) //ロードし直し
			{
				CFade::SetFade(CManager::MODE_GAME);
			}
		}
		#endif

		//rot狂わないようにする
		if (rot.y >= D3DX_PI)
		{
			rot.y -= D3DX_PI * 2;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2;
		}

		//今向いてる向きと目的の向きが違う場合、徐々に足していく
		if (rot.y != m_rotDesh.y)
		{
			if (m_rotDesh.y - rot.y < -D3DX_PI)
			{
				rot.y += (m_rotDesh.y - rot.y + D3DX_PI * 2) * 0.14f;
			}
			else if (m_rotDesh.y - rot.y > D3DX_PI)
			{
				rot.y += (m_rotDesh.y - rot.y - D3DX_PI * 2) * 0.14f;
			}
			else
			{
				rot.y += (m_rotDesh.y - rot.y) * 0.14f;
			}
		}

		//一定以上の高さ
		if (pos.y > 40000.0f)
		{
			CFade::SetFade(CManager::MODE_RESULT);
		}

		//設定
		SetPos(pos);
		m_pShadow->Move(pos.y);
		SetRot(rot);
		Motion();
	}
	//ポーズ中
	else
	{
		if (m_pKeyboard != NULL || m_pMouse != NULL)
		{
			if (m_pKeyboard != NULL)
			{
				//ポーズ選択切り替え
				if (m_pKeyboard->GetKey(DIK_W) == true)
				{
					PauseChange(-1);
				}
				if (m_pKeyboard->GetKey(DIK_S) == true)
				{
					PauseChange(1);
				}

				//決定
				if (m_pKeyboard->GetKey(DIK_RETURN) == true)
				{
					PauseSelect();
				}

				//ポーズ解除
				if (m_pKeyboard->GetKey(DIK_ESCAPE) == true)
				{
					CSound::Play(3);
					CManager::SetPause(false);
				}
			}

			if (m_pMouse != NULL)
			{
				//マウスを動かしたときの処理
				MouseSelect();

				//マウス選択
				if (m_pMouse->GetMouseButton(CMouse::DIM_L) == true)
				{
					PauseSelect();
				}
			}
		}
	}
}

//描画処理
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスのポインタ
	D3DXMATRIX mtxPlayer, mtxRot, mtxTrans;
	pDevice = CManager::GetRenderer()->GetDevice();		 //デバイスを取得する

	//プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxPlayer);
	//プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxRot);
	//プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);
	//プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);
	SetMatrix(mtxPlayer);
	int nCntModel;
	for (nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
}

//読み込み
void CPlayer::Load(const char *aFileName)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	int nParent;
	CModel *paModel[32];

	int nCntParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	int nCntCol = 0;
	char aFile[256];
	int nLoop = 0;
	int nGravity = 0;

	bool bChara = false;
	bool bParts = false;
	bool bMotion = false;
	bool bKey = false;
	bool bKeySet = false;
	int nIndex;

	FILE *pFile;
	pFile = fopen(aFileName, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);		//fscanfを繰り返してファイルを読み取っていく
			if (strcmp(&aFile[0], "#") == 0)	//スキップ
			{
				fscanf(pFile, "%s", &aFile[0]);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)	//モデルファイル読み込み
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				paModel[nCntParts] = CModel::Create(&aFile[0]);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET時
			{
				if (strcmp(&aFile[0], "NUM_PARTS") == 0)	//パーツ数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0)	//移動速度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0)	//ジャンプ力
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fJump);
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0)	//重力
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fGravity);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0)	//半径
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0)	//身長
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fHeight);
				}
				if (strcmp(&aFile[0], "PARTSSET") == 0)	//パーツ設定
				{
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)	//パーツ設定終了
				{
					bParts = false;
					nCntParts++;
				}
				if (bParts == true) //PARTSSET時
				{
					//if (strcmp(&aFile[0], "MOVEPARTS") == 0) //これが動くとg_playerのposも動く（いらないかも）
					//{
					//	g_player.nMoveParts = nCntParts;
					//}
					if (strcmp(&aFile[0], "INDEX") == 0)	//モデルファイル読み込みの時の、何番目のモデルを呼び出すか
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						m_pModel[nCntParts] = paModel[nIndex];
					}
					if (strcmp(&aFile[0], "PARENT") == 0)	//親モデル
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);
						if (nParent != -1)
						{
							m_pModel[nCntParts]->SetParent(m_pModel[nParent]);
						}
					}
					if (strcmp(&aFile[0], "POS") == 0)	//各パーツの場所
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntParts]->SetOriPos(pos);
					}
					if (strcmp(&aFile[0], "ROT") == 0)	//各パーツの角度
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntParts]->SetOriRot(rot);
					}
				}
			}
			if (bMotion == true && nCntMotion < MOTIONTYPE_RETURN)	//MOTIONSET時
			{
				if (strcmp(&aFile[0], "LOOP") == 0)	//そのモーションがループするか
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
					if (nLoop == 0)
					{
						m_aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0)	//重力が働くか
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nGravity);
					if (nGravity == 0)
					{
						m_aMotionInfo[nCntMotion].bGravity = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bGravity = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0)	//いくつキーがあるか
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "NON_OPE") == 0)	//操作不能時間
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNonOpe);
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)	//キー設定
				{
					bKeySet = true;
					m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove = 0.0f;
					m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fHeight = 0.0f;
					m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nSound = -1;
					nCntParts = 0;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)	//キー設定終了
				{
					bKeySet = false;
					nCntKey++;
				}

				if (bKeySet == true)	//KEYSET時
				{
					if (strcmp(&aFile[0], "FRAME") == 0)	//フレーム数
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "SOUND") == 0)	//音
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nSound);
					}
					if (strcmp(&aFile[0], "MOVE") == 0)	//移動量(横)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
					}
					if (strcmp(&aFile[0], "HEIGHT") == 0)	//移動量(縦)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fHeight);
					}
					if (strcmp(&aFile[0], "KEY") == 0)	//細かいキー設定
					{
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)	//細かいキー設定
					{
						bKey = false;
						nCntParts++;
					}
					if (bKey == true)	//KEY時
					{
						if (strcmp(&aFile[0], "POS") == 0)	//場所
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.x,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.y, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.z);
						}
						if (strcmp(&aFile[0], "ROT") == 0)	//角度
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.x,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.y, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.z);
						}
					}
				}
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)	//キャラ設定
			{
				bChara = true;
				nCntParts = 0;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)	//キャラ設定終了
			{
				bChara = false;
			}
			if (strcmp(&aFile[0], "MOTIONSET") == 0)	//モーション設定
			{
				bMotion = true;
				nCntKey = 0;
				nCntCol = 0;
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)	//モーション設定終了
			{
				bMotion = false;
				nCntMotion++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)	//終了の1文
			{
				break;
			}
		}
		fclose(pFile);
	}
	//「MOTIONTYPE_RETURN」は、ニュートラルモーションに戻る際に経由するモーション
	m_aMotionInfo[MOTIONTYPE_RETURN].bLoop = false;
	m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].nFrame = 10;
	m_aMotionInfo[MOTIONTYPE_RETURN].nNumKey = 1;
	m_aMotionInfo[MOTIONTYPE_RETURN].bGravity = true;
	m_aMotionInfo[MOTIONTYPE_RETURN].nNonOpe = 0;
	m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].nSound = -1;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts] = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[m_aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey - 1].aKey[nCntParts];
	}
}

//移動
bool CPlayer::Move(float fRotY)
{
	float fCameraRotY = m_pCamera->GetRotY();
	m_move.x += (sinf(fCameraRotY + D3DX_PI * fRotY) * m_fMove - m_move.x) * 0.1f;
	m_move.z += (cosf(fCameraRotY + D3DX_PI * fRotY) * m_fMove - m_move.z) * 0.1f;
	m_rotDesh.y = fCameraRotY + D3DX_PI * fRotY + D3DX_PI;
	if (m_rotDesh.y >= D3DX_PI)
	{
		m_rotDesh.y -= D3DX_PI * 2;
	}
	if (m_rotDesh.y < -D3DX_PI)
	{
		m_rotDesh.y += D3DX_PI * 2;
	}
	if (m_nRunStop > 0)
	{
		m_nRunStop = 0;
	}
	return true;
}

//停止
bool CPlayer::Stop()
{
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;
	return false;
}

//ジャンプ
void CPlayer::Jump()
{
	m_move.y = m_fChargeJump;
	m_bLanding = false;
	m_bLandField = false;
	m_bLandObject = false;
	m_bCharge = false;
	m_fChargeJump = 2.0f;

	//飛ぶ方向と向きが一致してる
	if ((m_fJumpMoveX <= 0.0f && GetRot().y > 0.0f) || (m_fJumpMoveX >= 0.0f && GetRot().y < 0.0f))
	{
		//前ジャンプモーション
		MotionChange(MOTIONTYPE_FRONTJUMP);
	}
	//飛ぶ方向と向きが反対
	else if((m_fJumpMoveX > 0.0f && GetRot().y > 0.0f) || (m_fJumpMoveX < 0.0f && GetRot().y < 0.0f))
	{
		//後ろジャンプモーション
		MotionChange(MOTIONTYPE_BACKJUMP);
	}
	//m_pGauge->SetBesideGauge(0.0f);
	m_nCntJump = 60;
}

//ジャンプ関連の処理
void CPlayer::JumpCharge()
{
	//マウスの左押す
	if (m_pMouse->GetMouseButton(CMouse::DIM_L) == true)
	{
		JumpFirst();
	}

	//チャージ中
	if (m_bCharge == true)
	{
		//左押してる
		if (m_pMouse->GetPress(CMouse::DIM_L) == true)
		{
			//ジャンプチャージ中
			JumpCharging();
		}
		//左離す
		else if (m_pMouse->GetRelease(CMouse::DIM_L) == true)
		{
			//ジャンプする
			Jump();
		}
	}
	//チャージしてない
	else
	{
		//チャージの値初期値にする
		if (m_fChargeJump > 4.0f)
		{
			m_fChargeJump = 4.0f;
		}

		//ジャンプしてからの時間減らす
		if (m_nCntJump > 0)
		{
			m_nCntJump--;
			if (m_nCntJump <= 0)
			{
				//ゲージ消す
				m_bGaugeFade = false;
			}
		}
	}
}

//ジャンプチャージの始まり
void CPlayer::JumpFirst()
{
	m_bCharge = true;
	m_bGaugeFade = true;
	MotionChange(MOTIONTYPE_CHARGE);
	m_pGauge->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	int nCnt;
	for (nCnt = 0; nCnt < 20; nCnt++)
	{
		m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
	}
}

//ジャンプチャージ中
void CPlayer::JumpCharging()
{
	//チャージ足す
	if (m_bChargePlus == true)
	{
		//足していく
		m_fChargeJump += 0.4f;
		if (m_fChargeJump > MAX_JUMPMOVEY)
		{
			//マックスで反転させる
			m_fChargeJump = MAX_JUMPMOVEY;
			m_bChargePlus = false;
		}
		//ゲージ設定
		m_pGauge->SetBesideGauge((m_fChargeJump - 4.0f) * 45.0f);
	}
	//チャージ減らす
	else
	{
		//減らしていく
		m_fChargeJump -= 0.4f;
		if (m_fChargeJump < 4.0f)
		{
			//加減で反転させる
			m_fChargeJump = 4.0f;
			m_bChargePlus = true;
		}
		//ゲージ設定
		m_pGauge->SetBesideGauge((m_fChargeJump - 4.0f) * 45.0f);
	}

	//マウス横動かしてる
	if (m_pMouse->MouseX() != 0.0f)
	{
		MouseMoveX();
	}
}

//マウス横移動
void CPlayer::MouseMoveX()
{
	int nCnt;

	//移動量に応じてプラス
	m_fJumpMoveX += m_pMouse->MouseX() * 0.015f;

	//0に近い場合、0にする
	if (-0.1f < m_fJumpMoveX && m_fJumpMoveX < 0.1f)
	{
		m_fJumpMoveX = 0.0f;
	}

	//上限突破しないようにする
	if (m_fJumpMoveX > MAX_JUMPMOVEX)
	{
		m_fJumpMoveX = MAX_JUMPMOVEX;
	}
	else if (m_fJumpMoveX < -MAX_JUMPMOVEX)
	{
		m_fJumpMoveX = -MAX_JUMPMOVEX;
	}

	//右側に飛ぶとき
	if (m_fJumpMoveX > 0.0f)
	{
		for (nCnt = 0; nCnt < 20; nCnt++)
		{
			//横移動ゲージ左側、消す
			if (nCnt < 10)
			{
				m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
			//右側
			else
			{
				//ゲージが横の移動量よりも低い部分
				if ((nCnt - 10) < floorf(m_fJumpMoveX))
				{
					m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				}
				//ゲージが横の移動量とちょうど重なってる場合、色を薄くする
				else if (floorf(m_fJumpMoveX) <= (nCnt - 10) && (nCnt - 10) < ceilf(m_fJumpMoveX))
				{
					m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f - (ceilf(m_fJumpMoveX) - m_fJumpMoveX)));
				}
				//ゲージが横の移動量よりも高い部分
				else if (m_fJumpMoveX < (nCnt - 10))
				{
					m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
				}
			}
		}
	}
	else if (m_fJumpMoveX < 0.0f) //左側に飛ぶとき
	{
		for (nCnt = 0; nCnt < 20; nCnt++)
		{
			//左側
			if (nCnt < 10)
			{
				//ゲージが横の移動量よりも低い部分
				if (nCnt < floorf(fabsf(m_fJumpMoveX)))
				{
					m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				}
				//ゲージが横の移動量とちょうど重なってる場合、色を薄くする
				else if (floorf(fabsf(m_fJumpMoveX)) <= nCnt && nCnt < ceilf(fabsf(m_fJumpMoveX)))
				{
					m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f - (m_fJumpMoveX + ceilf(fabsf(m_fJumpMoveX)))));
				}
				//ゲージが横の移動量よりも高い部分
				else if (fabsf(m_fJumpMoveX) < nCnt)
				{
					m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
				}
			}
			//横移動ゲージ右側、消す
			else
			{
				m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
		}
	}
	else //垂直ジャンプ
	{
		for (nCnt = 0; nCnt < 20; nCnt++)
		{
			//ゲージ消す
			m_pBlockGauge[nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
		}
	}
}

//ゲージフェードイン
void CPlayer::GaugeFadeIn()
{
	//色付きの場合
	if (m_fGaugeFade > 0.0f)
	{
		//色薄くする
		m_fGaugeFade -= 0.1f;
		if (m_fGaugeFade < 0.0f)
		{
			m_fGaugeFade = 0.0f;
		}
		int nCntUI;

		//ゲージ背景UI、ゲージ類薄くする
		for (nCntUI = 0; nCntUI < 3; nCntUI++)
		{
			m_pBlackGauge[nCntUI]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fGaugeFade));
		}
		for (nCntUI = 0; nCntUI < 20; nCntUI++)
		{
			m_pBlockGauge[nCntUI]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
		}
		m_pGauge->ColorChange(D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fGaugeFade));
	}
}

//ゲージフェードアウト
void CPlayer::GaugeFadeOut()
{
	//色が薄い場合
	if (m_fGaugeFade < 1.0f)
	{
		//濃くする
		m_fGaugeFade += 0.1f;
		if (m_fGaugeFade > 1.0f)
		{
			m_fGaugeFade = 1.0f;
		}
		int nCntUI;

		//ゲージ背景UI、ゲージ類薄くする
		for (nCntUI = 0; nCntUI < 3; nCntUI++)
		{
			m_pBlackGauge[nCntUI]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fGaugeFade));
		}
	}
}

//マウス選択
void CPlayer::MouseSelect()
{
	//マウス動かしてる
	if (m_pMouse->MouseX() != 0.0f || m_pMouse->MouseY() != 0.0f)
	{
		POINT CursorPoint;
		GetCursorPos(&CursorPoint);
		RECT Winrect;
		RECT Clirect;
		HWND hWnd = GethWnd();
		GetWindowRect(hWnd, &Winrect);	//ウィンドウ領域の取得
		GetClientRect(hWnd, &Clirect);	//クライアント領域の取得
		float fRatio[2];	//割合、アスペクト比のこと
		fRatio[0] = (Clirect.right - Clirect.left) / (float)SCREEN_WIDTH;	//横
		fRatio[1] = (Clirect.bottom - Clirect.top) / (float)SCREEN_HEIGHT;	//縦

		int nCntPause;
		//ポーズ中の選択肢UIどれかに当たっているか
		for (nCntPause = 0; nCntPause < 3; nCntPause++)
		{
			D3DXVECTOR3 UIPos = m_pPauseUI[nCntPause]->GetPos();
			D3DXVECTOR3 UIMinSize = m_pPauseUI[nCntPause]->GetVtxMin() * 0.5f;
			D3DXVECTOR3 UIMaxSize = m_pPauseUI[nCntPause]->GetVtxMax() * 0.5f;

			//UIにマウスカーソルが当たってる
			if ((Winrect.left + SCREEN_WIDTH_DIFF) + (UIPos.x + UIMinSize.x) * fRatio[0] <= CursorPoint.x && CursorPoint.x <= (Winrect.left + SCREEN_WIDTH_DIFF) + (UIPos.x + UIMaxSize.x) * fRatio[0] &&
				(Winrect.top + SCREEN_HEIGHT_DIFF) + (UIPos.y + UIMinSize.y) * fRatio[1] <= CursorPoint.y && CursorPoint.y <= (Winrect.top + SCREEN_HEIGHT_DIFF) + (UIPos.y + UIMaxSize.y) * fRatio[1])
			{
				//選んでるやつと当たってるやつが違う
				if (m_nPauseSelect != nCntPause)
				{
					//選択済みの奴を薄くする、選んだやつを濃くする
					m_pPauseUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f));
					m_nPauseSelect = nCntPause;
					m_pPauseUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
					CSound::Play(9);
				}
			}
		}
	}
}

//重力
void CPlayer::Gravity()
{
	if (m_move.y > MAX_GRAVITY)
	{
		m_move.y -= m_fGravity; //空中に居るときの重力が働く
		//落下速度が一定以上になると、モーションが速くなる
		if (m_move.y <= MAX_GRAVITY / 3.0f * 2.0f)
		{
			m_nFastMotion = -2;
		}
		else if (m_move.y <= MAX_GRAVITY / 3.0f)
		{
			m_nFastMotion = -1;
		}
	}
}

//走り始め
void CPlayer::RunFirst()
{
	m_bCharge = false;
	m_fChargeJump = 4.0f;
	MotionChange(MOTIONTYPE_RUN);
	m_fJumpMoveX = 0.0f;
	m_nCntJump = 10;
}

//走るの終わった
void CPlayer::RunStop()
{
	m_nRunStop++;
	if (m_nRunStop > 10)
	{
		MotionChange(MOTIONTYPE_RETURN);
		m_nRunStop = 0;
	}
}

//障害物との当たり判定
void CPlayer::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	D3DXVECTOR3 NextPos = *pPos;
	pScene = GetScene(PRIORITY_OBJECT);
	bool bLand = false;
	bool bStand;
	bool bHit;
	bool bShadow;
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//ブロック
		if (pScene->GetObjType() == CScene::OBJECTTYPE_BLOCK)
		{
			D3DXVECTOR3 pos = pScene->GetPos();

			//距離が近い
			if (fabsf(pPos->y - pos.y) < 1000.0f)
			{
				//当たり判定が球状
				if (pScene->GetCollision() == CScene::COLLISION_SPHERE)
				{
					float fRadius = pScene->GetRadius();
					float fLengthX = pPos->x - pos.x;
					float fLengthY = pPos->y - pos.y;
					float fLengthZ = pPos->z - pos.z;
					fLengthX = powf(fLengthX, 2.0f);
					fLengthY = powf(fLengthY, 2.0f);
					fLengthZ = powf(fLengthZ, 2.0f);

					//当たってる
					if (fLengthX + fLengthY + fLengthZ <= powf(m_fRadius + fRadius, 2.0f))
					{
						//移動させる
						float fRotY = atanf(pos.x - pPos->x);
						float fRotX = atan2f(pPos->y - pos.y, pos.x - pPos->x);
						pPos->x = pos.x - fabsf(sinf(fRotY)) * cosf(fRotX) * (m_fRadius + fRadius);
					}
				}
				//当たり判定が箱型
				else if (pScene->GetCollision() == CScene::COLLISION_SQUARE)
				{
					D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
					D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
					D3DXVECTOR3 rot = pScene->GetRot();
					D3DXVECTOR3 aPoint[8]; //オブジェクトの8頂点

					D3DXVECTOR2 MinSize = { 100000.0f,100000.0f };
					D3DXVECTOR2 MaxSize = { -100000.0f,-100000.0f };

					D3DXMATRIX mtxTrans, mtxWorld, mtxParent;
					mtxParent = pScene->GetMatrix();

					//8頂点取得
					int nCntPos;
					for (nCntPos = 0; nCntPos < 8; nCntPos++)
					{
						//ワールドマトリックスの初期化
						D3DXMatrixIdentity(&mtxWorld);
						switch (nCntPos)
						{
						case 0:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMax.y, VtxMax.z);
							break;
						case 1:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMax.y, VtxMax.z);
							break;
						case 2:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMax.y, VtxMin.z);
							break;
						case 3:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMax.y, VtxMin.z);
							break;
						case 4:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMin.y, VtxMax.z);
							break;
						case 5:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMin.y, VtxMax.z);
							break;
						case 6:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMin.y, VtxMin.z);
							break;
						case 7:
							//位置を反映
							D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMin.y, VtxMin.z);
							break;
						default:
							break;
						}
						D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

						//親のマトリックスと掛け合わせる
						D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

						//場所設定
						aPoint[nCntPos] = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
						
						//8頂点全ての中で最大値、最小値を記録する
						if (MaxSize.x < aPoint[nCntPos].x)
						{
							MaxSize.x = aPoint[nCntPos].x;
						}
						else if (MinSize.x > aPoint[nCntPos].x)
						{
							MinSize.x = aPoint[nCntPos].x;
						}
						if (MaxSize.y < aPoint[nCntPos].y)
						{
							MaxSize.y = aPoint[nCntPos].y;
						}
						else if (MinSize.y > aPoint[nCntPos].y)
						{
							MinSize.y = aPoint[nCntPos].y;
						}
					}

					//8頂点それぞれの最大値、最小値との当たり判定。(つまり回転してない真四角の当たり判定)
					if (MinSize.x <= pPos->x + m_fRadius && pPos->x - m_fRadius <= MaxSize.x && MinSize.y - m_fRadius <= pPos->y + m_fHeight && pPos->y <= MaxSize.y + m_fRadius)
					{
						bHit = true;
					}
					else
					{
						bHit = false;
					}

					//影がそこに映るか
					if (MinSize.x <= pPos->x + m_fRadius && pPos->x - m_fRadius <= MaxSize.x && MinSize.y <= pPos->y)
					{
						bShadow = true;
					}
					else
					{
						bShadow = false;
					}

					D3DXVECTOR3 aSquare[4];
					int nCnt;
					for(nCnt = 0; nCnt < 4; nCnt++)
					{
						switch (nCnt)
						{
						case 0:	//上の面
							aSquare[0] = aPoint[0];
							aSquare[1] = aPoint[1];
							aSquare[2] = aPoint[2];
							aSquare[3] = aPoint[3];
							break;
						case 1:	//右の面
							aSquare[0] = aPoint[1];
							aSquare[1] = aPoint[5];
							aSquare[2] = aPoint[3];
							aSquare[3] = aPoint[7];
							break;
						case 2:	//下の面
							aSquare[0] = aPoint[5];
							aSquare[1] = aPoint[4];
							aSquare[2] = aPoint[7];
							aSquare[3] = aPoint[6];
							break;
						case 3:	//左の面
							aSquare[0] = aPoint[4];
							aSquare[1] = aPoint[0];
							aSquare[2] = aPoint[6];
							aSquare[3] = aPoint[2];
							break;
						default:
							break;
						}

						//当たってる
						if (bHit == true)
						{
							//その面に立てる(ある程度面が上を向いている)のか計算
							bStand = CollisionBlock(&aSquare[0], pPos, posOld, &bLand, &NextPos);

							//立てないかつループ最後
							if (bStand == false && nCnt == 3)
							{
								//posを移動
								*pPos = NextPos;
							}
						}

						//影との当たり判定
						if (bShadow == true)
						{
							ShadowObject(&aSquare[0], pPos);
						}

						//立てる場合、そこでループ終了
						if (bStand == true)
						{
							break;
						}
					}
				}
				/*else if (pScene->GetCollision() == CScene::COLLISION_PALL)
				{
					D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
					D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
					float fRadius = pScene->GetRadius();
				}*/
			}
		}
		pScene = pSceneNext;
	}

	//立てない場合、障害物には乗ってないことにする
	if (bLand == false)
	{
		m_bLandObject = false;
	}
	//乗れた
	else
	{
		m_bLandObject = true;
	}
}

//モーションの動作
void CPlayer::Motion()
{
	int nCntParts;
	m_nTotalTime++;
	m_nCntMotion++;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		D3DXVECTOR3 posOld;
		posOld = m_pModel[nCntParts]->GetPos();
		D3DXVECTOR3 rotOld;
		rotOld = m_pModel[nCntParts]->GetRot();
		if (m_nCntMotion == -m_nFastMotion + 1) //差分を求める(対応するキーの各パーツのpos(rot) - 今の各パーツのpos(rot))
		{
			m_aKeyDiff[nCntParts].pos.x = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.x - posOld.x;
			m_aKeyDiff[nCntParts].pos.y = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.y - posOld.y;
			m_aKeyDiff[nCntParts].pos.z = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.z - posOld.z;
			m_aKeyDiff[nCntParts].rot.x = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.x - rotOld.x;

			//角度が狂わないようにする
			if (m_aKeyDiff[nCntParts].rot.x < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.x += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.x > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.x -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].rot.y = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.y - rotOld.y;
			if (m_aKeyDiff[nCntParts].rot.y < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.y += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.y > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.y -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].rot.z = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.z - rotOld.z;
			if (m_aKeyDiff[nCntParts].rot.z < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.z += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.z > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.z -= D3DX_PI * 2;
			}

			//そのキーに音が設定されてる場合、音を鳴らす
			if (m_MotionInfo.aKeyInfo[m_nKey].nSound != -1)
			{
				CSound::Play(m_MotionInfo.aKeyInfo[m_nKey].nSound);
			}
		}
		//pos、rotを徐々に足す
		posOld.x += m_aKeyDiff[nCntParts].pos.x / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.y += m_aKeyDiff[nCntParts].pos.y / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.z += m_aKeyDiff[nCntParts].pos.z / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetPos(posOld);

		rotOld.x += m_aKeyDiff[nCntParts].rot.x / (m_MotionInfo.aKeyInfo[m_nKey].nFrame + m_nFastMotion);
		rotOld.y += m_aKeyDiff[nCntParts].rot.y / (m_MotionInfo.aKeyInfo[m_nKey].nFrame + m_nFastMotion);
		rotOld.z += m_aKeyDiff[nCntParts].rot.z / (m_MotionInfo.aKeyInfo[m_nKey].nFrame + m_nFastMotion);
		m_pModel[nCntParts]->SetRot(rotOld);
	}

	//モーションのフレームが上限
	if (m_nCntMotion == m_MotionInfo.aKeyInfo[m_nKey].nFrame)
	{
		//モーションフレームリセット(ファストモーションがあると最初から足される)
		m_nCntMotion = -m_nFastMotion;
		
		//キー数足す
		m_nKey++;

		//キー数が上限
		if (m_nKey == m_MotionInfo.nNumKey)
		{
			//ループしない
			if (m_MotionInfo.bLoop == false)
			{
				//着地してる
				if (m_bLanding == true)
				{
					//リターン以外の場合、リターン
					if (m_motionType != MOTIONTYPE_RETURN)
					{
						MotionChange(MOTIONTYPE_RETURN);
					}
					//ニュートラル
					else
					{
						MotionChange(MOTIONTYPE_NEUTRAL);
					}
				}
				//空中にいる
				else
				{
					//前ジャンプ
					if (m_motionType != MOTIONTYPE_FRONTJUMP)
					{
						MotionChange(MOTIONTYPE_FRONTJUMP);
					}
				}
			}
			m_nKey = 0;
		}
	}
}

//モーション切り替え
void CPlayer::MotionChange(MOTIONTYPE motionType)
{
	m_motionTypeOld = m_motionType;
	m_motionType = motionType;
	m_MotionInfo = m_aMotionInfo[motionType];
	m_nCntMotion = 0;
	m_nTotalTime = 0;
	m_nKey = 0;
	m_nFastMotion = 0;
}

//地面との当たり判定
bool CPlayer::CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene)
{
	D3DXVECTOR3 pos = pScene->GetPos();

	//距離が近い
	if (fabsf(pPos->y - pos.y) < 1000.0f)
	{
		D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
		D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
		D3DXVECTOR3 rot = pScene->GetRot();
		D3DXVECTOR3 aPoint[4]; //地面の4頂点

		D3DXMATRIX mtxTrans, mtxRot, mtxWorld, mtxParent;

		D3DXVECTOR3 MatMax = D3DXVECTOR3(-1000000.0f, -10000000.0f, -10000000.0f);
		D3DXVECTOR3 MatMin = D3DXVECTOR3(1000000.0f, 10000000.0f, 10000000.0f);

		mtxParent = pScene->GetMatrix();

		//4頂点取得
		int nCntPos;
		for (nCntPos = 0; nCntPos < 4; nCntPos++)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorld);
			switch (nCntPos)
			{
			case 0:
				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMax.y, VtxMin.z);
				break;
			case 1:
				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMax.y, VtxMin.z);
				break;
			case 2:
				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMin.y, VtxMax.z);
				break;
			case 3:
				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMin.y, VtxMax.z);
				break;
			default:
				break;
			}
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

			//地面のマトリックスと掛け合わせる
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

			//頂点
			aPoint[nCntPos] = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

			//各頂点の最大値、最小値を記憶する
			if (aPoint[nCntPos].x < MatMin.x)
			{
				MatMin.x = aPoint[nCntPos].x;
			}
			else if (MatMax.x < aPoint[nCntPos].x)
			{
				MatMax.x = aPoint[nCntPos].x;
			}
			if (aPoint[nCntPos].y < MatMin.y)
			{
				MatMin.y = aPoint[nCntPos].y;
			}
			else if (MatMax.y < aPoint[nCntPos].y)
			{
				MatMax.y = aPoint[nCntPos].y;
			}
			if (aPoint[nCntPos].z < MatMin.z)
			{
				MatMin.z = aPoint[nCntPos].z;
			}
			else if (MatMax.z < aPoint[nCntPos].z)
			{
				MatMax.z = aPoint[nCntPos].z;
			}
		}

		//大雑把に当たってる
		if (MatMin.x <= pPos->x + m_fRadius && pPos->x - m_fRadius <= MatMax.x && MatMin.z <= pPos->z - m_fRadius && pPos->z + m_fRadius <= MatMax.z)
		{
			D3DXVECTOR3 SubPoint[2];
			SubPoint[0] = aPoint[2] - aPoint[1];
			SubPoint[1] = aPoint[1] - aPoint[0];
			D3DXVECTOR3 Cross[3];
			D3DXVec3Cross(&Cross[0], &SubPoint[0], &SubPoint[1]);
			float fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);
			Cross[0].x /= fLength;
			Cross[0].y /= fLength;
			Cross[0].z /= fLength; //ここまで法線ベクトル

			Cross[1] = *pPos - aPoint[0]; //プレイヤーのposと地面の任意の点のベクトル

			float fDistance = (Cross[0].x * Cross[1].x) + (Cross[0].y * Cross[1].y) + (Cross[0].z * Cross[1].z);	//足元と地面との距離 プラスの時、表側にいる

			//地面の一番低い部分よりもプレイヤーが高いところにいる
			if (MatMin.y <= pPos->y)
			{
				//地面から見てプレイヤーが一番近い場所
				D3DXVECTOR3 Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance));
				
				//今の影の位置よりも上で計算した場所の方が上かつ上で計算した場所よりもプレイヤーが上にいる
				if (m_fShadowPosY < Point.y && Point.y < pPos->y)
				{
					m_fShadowPosY = Point.y;
					m_ShadowRot = rot;
				}
			}

			//今のプレイヤーの位置より地面の一番低い位置の方が高く、かつ地面の一番低い位置よりもプレイヤーの過去の位置の方が高い
			if (MatMin.y + 5.0f >= pPos->y && posOld.y >= MatMin.y - 5.0f)
			{
				Cross[2] = posOld - aPoint[0]; //プレイヤーのOldposと壁の任意の点のベクトル
				float fOldDistance = (Cross[0].x * Cross[2].x) + (Cross[0].y * Cross[2].y) + (Cross[0].z * Cross[2].z);	//過去位置足元と地面との距離 プラスの時、表側にいる
				
				//距離が非常に近いか、現在位置が裏側にいて過去位置が表側にいる(=すり抜けた)
				if (fabsf(fDistance) <= 2.0f || fDistance <= 2.0f && fOldDistance >= -2.0f)
				{
					//少し広げた四角形
					D3DXVECTOR3 aWideSquare[4];
					aWideSquare[0] = D3DXVECTOR3(aPoint[0].x - m_fRadius, aPoint[0].y, aPoint[0].z + m_fRadius);
					aWideSquare[1] = D3DXVECTOR3(aPoint[1].x + m_fRadius, aPoint[1].y, aPoint[1].z + m_fRadius);
					aWideSquare[2] = D3DXVECTOR3(aPoint[2].x - m_fRadius, aPoint[2].y, aPoint[2].z - m_fRadius);
					aWideSquare[3] = D3DXVECTOR3(aPoint[3].x + m_fRadius, aPoint[3].y, aPoint[3].z - m_fRadius);
					
					//床面上のプレイヤーの位置
					D3DXVECTOR3 Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance));
					D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance));
					
					//外積の当たり判定
					if (Collision(&aWideSquare[0], Point, OldPoint))
					{
						//床の位置まで高さ上げる
						pPos->y -= fDistance;
						m_pShadow->MoveY(D3DXVECTOR3(pPos->x, pPos->y + 0.2f, pPos->z), rot);
						m_move.y = 0.0f;

						//着地してない場合、着地する
						if (m_bLanding == false && m_bLandField == false)
						{
							m_bLandField = true;
							m_bCharge = false;
							m_fJumpMoveX = 0.0f;
							MotionChange(MOTIONTYPE_LANDING);
						}
						return true;
					}
				}
			}
			//現在位置の頭が地面の最高点より高く、過去位置の頭が地面の最高点より低い
			else if (MatMax.y <= pPos->y + m_fHeight && MatMax.y >= posOld.y + m_fHeight)
			{
				Cross[2] = posOld - aPoint[0]; //プレイヤーのOldposと壁の任意の点のベクトル
				if (fDistance >= -m_fHeight)
				{
					pPos->y += (fDistance - m_fHeight);
					m_move.y = 0.0f;
				}
			}
		}
	}
	return false;
}

//壁との当たり判定
void CPlayer::CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene)
{
	D3DXVECTOR3 pos = pScene->GetPos();
	D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
	D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
	D3DXVECTOR3 rot = pScene->GetRot();
	D3DXVECTOR3 aPoint[4]; //壁の4頂点

	D3DXMATRIX mtxTrans, mtxWorld, mtxParent;
	mtxParent = pScene->GetMatrix();
	
	int nCntPos;
	//4頂点の場所反映
	for (nCntPos = 0; nCntPos < 4; nCntPos++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);
		switch (nCntPos)
		{
		case 0:
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMax.y, VtxMin.z);
			break;
		case 1:
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMax.y, VtxMax.z);
			break;
		case 2:
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, VtxMin.x, VtxMin.y, VtxMin.z);
			break;
		case 3:
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, VtxMax.x, VtxMin.y, VtxMax.z);
			break;
		default:
			break;
		}
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		//壁のマトリックスと掛け合わせる
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

		aPoint[nCntPos] = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	}

	/*
	aPoint[0] = D3DXVECTOR3(pos.x + VtxMin.x * cosf(rot.y) + VtxMax.y * sinf(rot.x), pos.y + VtxMax.y, pos.z + VtxMin.x * sinf(rot.y));
	aPoint[1] = D3DXVECTOR3(pos.x + VtxMax.x * cosf(rot.y) + VtxMax.y * sinf(rot.x), pos.y + VtxMax.y, pos.z + VtxMax.x * sinf(rot.y));
	aPoint[2] = D3DXVECTOR3(pos.x + VtxMin.x * cosf(rot.y) + VtxMin.y * sinf(rot.x), pos.y + VtxMin.y, pos.z + VtxMin.x * sinf(rot.y));
	aPoint[3] = D3DXVECTOR3(pos.x + VtxMax.x * cosf(rot.y) + VtxMin.y * sinf(rot.x), pos.y + VtxMin.y, pos.z + VtxMax.x * sinf(rot.y));
	*/

	if (aPoint[2].y <= pPos->y + m_fHeight && pPos->y <= aPoint[0].y || aPoint[0].y < posOld.y + m_fHeight && posOld.y < aPoint[2].y)
	{
		//D3DXVECTOR3 Cross[5];
		//D3DXVec3Cross(&Cross[0], &(aPoint[2] - aPoint[1]), &(aPoint[1] - aPoint[0]));
		//float fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);
		//Cross[0].x /= fLength;
		//Cross[0].y /= fLength;
		//Cross[0].z /= fLength; //ここまで法線ベクトル

		//Cross[1] = *pPos - aPoint[0]; //プレイヤーのposと壁面上の任意の点のベクトル
		//Cross[2] = posOld - aPoint[0]; //プレイヤーのOldposと壁面上の任意の点のベクトル

		//Cross[3] = D3DXVECTOR3(pPos->x - aPoint[0].x, (pPos->y + m_fHeight) - aPoint[0].y, pPos->z - aPoint[0].z);		//プレイヤーの頭と壁面上の任意の点のベクトル
		//Cross[4] = D3DXVECTOR3(posOld.x - aPoint[0].x, (posOld.y + m_fHeight) - aPoint[0].y, posOld.z - aPoint[0].z);	//プレイヤーの過去位置の頭と壁面上の任意の点のベクトル

		//float fDistance = Cross[0].x * Cross[1].x + Cross[0].y * Cross[1].y + Cross[0].z * Cross[1].z;		//足元と壁面との距離 マイナスの時、表側にいる
		//float fOldDistance = Cross[0].x * Cross[2].x + Cross[0].y * Cross[2].y + Cross[0].z * Cross[2].z;	//過去位置足元と壁面との距離 マイナスの時、表側にいる

		//float fHeadDistance = Cross[0].x * Cross[3].x + Cross[0].y * Cross[3].y + Cross[0].z * Cross[3].z;		//頭と壁面との距離 マイナスの時、表側にいる
		//float fHeadOldDistance = Cross[0].x * Cross[4].x + Cross[0].y * Cross[4].y + Cross[0].z * Cross[4].z;	//壁面との距離 マイナスの時、表側にいる

		//D3DXVECTOR3 Point; //壁面上のプレイヤーの位置
		//D3DXVECTOR3 OldPoint; //壁面上の1フレーム前のプレイヤーの位置

		////Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance)); //壁面上のプレイヤーの位置

		////D3DXVECTOR3 PosPoint = Point - *pPos;
		////D3DXVECTOR3 HeadPoint = D3DXVECTOR3(Point.x - pPos->x, Point.y - (pPos->y + m_fHeight) , Point.z - pPos->z);
		//if ((fabsf(fDistance) <= m_fRadius || fOldDistance <= -m_fRadius && fDistance >= -m_fRadius) || (fabsf(fHeadDistance) <= m_fRadius || fHeadOldDistance <= -m_fRadius && fHeadDistance >= -m_fRadius))
		//{
		//	if (fabsf(fDistance) <= m_fRadius || fOldDistance <= -m_fRadius && fDistance >= -m_fRadius)
		//	{
		//		Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance)); //壁面上のプレイヤーの位置
		//		OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance)); //壁面上の1フレーム前のプレイヤーの位置
		//		if (Collision(&aPoint[0], Point, OldPoint) == true)
		//		{
		//			pPos->x += sinf(rot.y) * (fabsf(fDistance) - m_fRadius);
		//			//pPos->z += cosf(rot.y) * (fabsf(fDistance) - m_fRadius);
		//			if (m_move.y > 0.0f && rot.x < 0.0f)
		//			{
		//				m_move.x = sinf(-rot.y) * sinf(rot.x) * m_move.y * 4.0f;
		//			}
		//		}
		//	}
		//	else if (fabsf(fHeadDistance) <= m_fRadius || fHeadOldDistance <= -m_fRadius && fHeadDistance >= -m_fRadius)
		//	{
		//		Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fHeadDistance), pPos->y - (Cross[0].y * fHeadDistance), pPos->z - (Cross[0].z * fHeadDistance)); //壁面上のプレイヤーの位置
		//		OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fHeadOldDistance), posOld.y - (Cross[0].y * fHeadOldDistance), posOld.z - (Cross[0].z * fHeadOldDistance)); //壁面上の1フレーム前のプレイヤーの位置
		//		if (Collision(&aPoint[0], Point, OldPoint) == true)
		//		{
		//			pPos->x += sinf(rot.y) * (fabsf(fHeadDistance) - m_fRadius);
		//			//pPos->z += cosf(rot.y) * (fabsf(fHeadDistance) - m_fRadius);
		//			if (m_move.y > 0.0f)
		//			{
		//				m_move.x = sinf(-rot.y) * sinf(rot.x) * m_move.y * 4.0f;
		//			}
		//		}
		//	}
		//}

		D3DXVECTOR3 Cross[5];
		D3DXVec3Cross(&Cross[0], &(aPoint[2] - aPoint[1]), &(aPoint[1] - aPoint[0]));
		float fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);
		Cross[0].x /= fLength;
		Cross[0].y /= fLength;
		Cross[0].z /= fLength; //ここまで法線ベクトル

		float fd = aPoint[0].x * Cross[0].x + aPoint[0].y * Cross[0].y + aPoint[0].z * Cross[0].z; //平面D
		D3DXVECTOR3 fDCross = Cross[0] * fd;	//平面上の点
		D3DXVECTOR3 PosD = fDCross - *pPos;
		D3DXVECTOR3 HeadD = D3DXVECTOR3(fDCross.x - pPos->x, fDCross.y - (pPos->y + m_fHeight), fDCross.x - pPos->z);
		float fDotPosD = PosD.x * Cross[0].x + PosD.y * Cross[0].y + PosD.z * Cross[0].z;
		float fDotHeadD = HeadD.x * Cross[0].x + HeadD.y * Cross[0].y + HeadD.z * Cross[0].z;
		Cross[1] = *pPos - aPoint[0]; //プレイヤーのposと壁面上の任意の点のベクトル
		Cross[2] = posOld - aPoint[0]; //プレイヤーのOldposと壁面上の任意の点のベクトル
		Cross[3] = D3DXVECTOR3(pPos->x - aPoint[0].x, (pPos->y + m_fHeight) - aPoint[0].y, pPos->z - aPoint[0].z);		//プレイヤーの頭と壁面上の任意の点のベクトル
		Cross[4] = D3DXVECTOR3(posOld.x - aPoint[0].x, (posOld.y + m_fHeight) - aPoint[0].y, posOld.z - aPoint[0].z);	//プレイヤーの過去位置の頭と壁面上の任意の点のベクトル

		float fDistance = Cross[0].x * Cross[1].x + Cross[0].y * Cross[1].y + Cross[0].z * Cross[1].z;			//足元と壁面上との距離 プラスの時、表側にいる
		float fOldDistance = Cross[0].x * Cross[2].x + Cross[0].y * Cross[2].y + Cross[0].z * Cross[2].z;		//過去位置足元と壁面上との距離 プラスの時、表側にいる
		float fHeadDistance = Cross[0].x * Cross[3].x + Cross[0].y * Cross[3].y + Cross[0].z * Cross[3].z;		//頭と壁面上との距離 マイナスの時、表側にいる
		float fHeadOldDistance = Cross[0].x * Cross[4].x + Cross[0].y * Cross[4].y + Cross[0].z * Cross[4].z;	//過去位置壁面上との距離 マイナスの時、表側にいる
		if ((fDotHeadD < 0.0f && fDotPosD > 0.0f) || (fDotHeadD > 0.0f && fDotPosD < 0.0f)) //壁で体が切れる場合
		{
			D3DXVECTOR3 Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance));				//壁面上のプレイヤーの位置
			D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance)); //壁面上の1フレーム前のプレイヤーの位置
			D3DXVECTOR3 LeftPoint = D3DXVECTOR3(Point.x - m_fRadius, Point.y, Point.z);					//壁面上のプレイヤーの位置
			D3DXVECTOR3 LeftOldPoint = D3DXVECTOR3(OldPoint.x - m_fRadius, OldPoint.y, OldPoint.z);		//壁面上の1フレーム前のプレイヤーの位置
			D3DXVECTOR3 RightPoint = D3DXVECTOR3(Point.x + m_fRadius, Point.y, Point.z);				//壁面上のプレイヤーの位置
			D3DXVECTOR3 RightOldPoint = D3DXVECTOR3(OldPoint.x + m_fRadius, OldPoint.y, OldPoint.z);	//壁面上の1フレーム前のプレイヤーの位置
			
			//左側の当たり判定
			if (Collision(&aPoint[0], LeftPoint, LeftOldPoint) == true)
			{
				pPos->x = aPoint[0].x + m_fRadius + 5.0f;
			}
			//右側の当たり判定
			else if (Collision(&aPoint[0], RightPoint, RightOldPoint) == true)
			{
				pPos->x = aPoint[2].x - m_fRadius + 10.0f;
			}
		}
		else
		{
			//距離が近いか、壁抜けた
			if (fabsf(fDistance) <= m_fRadius || fOldDistance <= -m_fRadius && fDistance >= -m_fRadius)
			{
				//壁面上の自分の位置
				D3DXVECTOR3 Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance)); //壁面上のプレイヤーの位置
				D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance)); //壁面上の1フレーム前のプレイヤーの位置
				
				//壁との当たり判定
				if (Collision(&aPoint[0], Point, OldPoint) == true)
				{
					//押しのける、空中にいた場合、反射する
					pPos->x += sinf(rot.y) * (fabsf(fDistance) - m_fRadius);
					if (m_bCharge == false)
					{
						m_fJumpMoveX *= REFLECT;
					}
					/*if (m_move.y > 0.0f && rot.x < 0.0f)
					{
						m_move.x = sinf(-rot.y) * sinf(rot.x) * m_move.y * 4.0f;
					}*/
					return;
				}
			}

			//頭側の距離が近いか、壁抜けた
			if (fabsf(fHeadDistance) <= m_fRadius || fHeadOldDistance <= -m_fRadius && fHeadDistance >= -m_fRadius)
			{
				D3DXVECTOR3 Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fHeadDistance), (pPos->y + m_fHeight) - (Cross[0].y * fHeadDistance), pPos->z - (Cross[0].z * fHeadDistance)); //壁面上のプレイヤーの位置
				D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fHeadOldDistance), (posOld.y + m_fHeight) - (Cross[0].y * fHeadOldDistance), posOld.z - (Cross[0].z * fHeadOldDistance)); //壁面上の1フレーム前のプレイヤーの位置
				if (Collision(&aPoint[0], Point, OldPoint) == true)
				{
					pPos->x += sinf(rot.y) * (fabsf(fHeadDistance) - m_fRadius);
					if (m_bCharge == false)
					{
						m_fJumpMoveX *= REFLECT;
					}
					/*if (m_move.y > 0.0f && rot.x < 0.0f)
					{
						m_move.x = sinf(-rot.y) * sinf(rot.x) * m_move.y * 4.0f;
					}*/
					return;
				}
			}
		}
	}
}

//平面との当たり判定
void CPlayer::CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = CScene::GetScene(CScene::PRIORITY_PLANE);
	CScene *pSceneNext;
	bool bLand = false;
	bool bCamera = false;
	while (pScene)
	{
		pSceneNext = pScene->GetNext();
		//壁
		if (pScene->GetObjType() == CScene::OBJECTTYPE_WALL)
		{
			CollisionWall(pPos, posOld, pScene);
		}
		//床かつ着地してない
		else if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD && bLand == false)
		{
			bLand = CollisionLand(pPos, posOld, pScene);
		}
		//カメラパネルかつまだ踏んでない
		else if (pScene->GetObjType() == CScene::OBJECTTYPE_CAMERAPANEL && bCamera == false)
		{
			bCamera = CollisionCamera(pPos, pScene);
		}
		pScene = pSceneNext;
	}
	m_bLandField = bLand;
}

//作成
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer(PRIORITY_CHARA);
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, rot, aFileName);
	}
	return pPlayer;
}

//ポーズ切り替え
void CPlayer::PauseChange(int nAdd)
{
	//変わる前のUI、色替え
	m_pPauseUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f));
	m_nPauseSelect += nAdd;
	if (m_nPauseSelect < 0)
	{
		m_nPauseSelect = 2;
	}
	else if (m_nPauseSelect > 2)
	{
		m_nPauseSelect = 0;
	}
	//変わった後のUI、色替え
	m_pPauseUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	CSound::Play(9);
}

//ポーズ選択肢
void CPlayer::PauseSelect()
{
	switch (m_nPauseSelect)
	{
	case 0:
		CManager::SetPause(false);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 2:
		CFade::SetFade(CManager::MODE_TITLE);
		break;
	default:
		break;
	}
	CSound::Play(7);
}

//終わった後の選択肢切り替え
void CPlayer::EndChange(int nAdd)
{
	m_nPauseSelect += nAdd;
	if (m_nPauseSelect < 0)
	{
		m_nPauseSelect = 1;
	}
	else if (m_nPauseSelect > 1)
	{
		m_nPauseSelect = 0;
	}
	//CSound::Play(CSound::SOUND_LABEL_SELECT);
}

//終わった後の選択肢決定
void CPlayer::EndSelect()
{
	switch (m_nPauseSelect)
	{
	case 0:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_TITLE);
		break;
	default:
		break;
	}
	//CSound::Play(CSound::SOUND_LABEL_OK);
}

//平面との当たり判定
bool CPlayer::Collision(D3DXVECTOR3 aPoint[4], D3DXVECTOR3 Point, D3DXVECTOR3 PointOld)
{
	D3DXVECTOR3 SubVector[12];
	SubVector[0] = D3DXVECTOR3(aPoint[1].x - aPoint[0].x, aPoint[1].y - aPoint[0].y, aPoint[1].z - aPoint[0].z);
	SubVector[1] = D3DXVECTOR3(aPoint[0].x - Point.x, aPoint[0].y - Point.y, aPoint[0].z - Point.z);
	SubVector[2] = D3DXVECTOR3(aPoint[0].x - PointOld.x, aPoint[0].y - PointOld.y, aPoint[0].z - PointOld.z);
	SubVector[3] = D3DXVECTOR3(aPoint[3].x - aPoint[1].x, aPoint[3].y - aPoint[1].y, aPoint[3].z - aPoint[1].z);
	SubVector[4] = D3DXVECTOR3(aPoint[1].x - Point.x, aPoint[1].y - Point.y, aPoint[1].z - Point.z);
	SubVector[5] = D3DXVECTOR3(aPoint[1].x - PointOld.x, aPoint[1].y - PointOld.y, aPoint[1].z - PointOld.z);
	SubVector[6] = D3DXVECTOR3(aPoint[2].x - aPoint[3].x, aPoint[2].y - aPoint[3].y, aPoint[2].z - aPoint[3].z);
	SubVector[7] = D3DXVECTOR3(aPoint[3].x - Point.x, aPoint[3].y - Point.y, aPoint[3].z - Point.z);
	SubVector[8] = D3DXVECTOR3(aPoint[3].x - PointOld.x, aPoint[3].y - PointOld.y, aPoint[3].z - PointOld.z);
	SubVector[9] = D3DXVECTOR3(aPoint[0].x - aPoint[2].x, aPoint[0].y - aPoint[2].y, aPoint[0].z - aPoint[2].z);
	SubVector[10] = D3DXVECTOR3(aPoint[2].x - Point.x, aPoint[2].y - Point.y, aPoint[2].z - Point.z);
	SubVector[11] = D3DXVECTOR3(aPoint[2].x - PointOld.x, aPoint[2].y - PointOld.y, aPoint[2].z - PointOld.z);

	D3DXVECTOR3 CrossVector[8];
	CrossVector[0] = D3DXVECTOR3(SubVector[0].y * SubVector[1].z - SubVector[1].y * SubVector[0].z, SubVector[0].z * SubVector[1].x - SubVector[1].z * SubVector[0].x, SubVector[0].x * SubVector[1].y - SubVector[1].x * SubVector[0].y);
	CrossVector[1] = D3DXVECTOR3(SubVector[0].y * SubVector[2].z - SubVector[2].y * SubVector[0].z, SubVector[0].z * SubVector[2].x - SubVector[2].z * SubVector[0].x, SubVector[0].x * SubVector[2].y - SubVector[2].x * SubVector[0].y);
	CrossVector[2] = D3DXVECTOR3(SubVector[3].y * SubVector[4].z - SubVector[4].y * SubVector[3].z, SubVector[3].z * SubVector[4].x - SubVector[4].z * SubVector[3].x, SubVector[3].x * SubVector[4].y - SubVector[4].x * SubVector[3].y);
	CrossVector[3] = D3DXVECTOR3(SubVector[3].y * SubVector[5].z - SubVector[5].y * SubVector[3].z, SubVector[3].z * SubVector[5].x - SubVector[5].z * SubVector[3].x, SubVector[3].x * SubVector[5].y - SubVector[5].x * SubVector[3].y);
	CrossVector[4] = D3DXVECTOR3(SubVector[6].y * SubVector[7].z - SubVector[7].y * SubVector[6].z, SubVector[6].z * SubVector[7].x - SubVector[7].z * SubVector[6].x, SubVector[6].x * SubVector[7].y - SubVector[7].x * SubVector[6].y);
	CrossVector[5] = D3DXVECTOR3(SubVector[6].y * SubVector[8].z - SubVector[8].y * SubVector[6].z, SubVector[6].z * SubVector[8].x - SubVector[8].z * SubVector[6].x, SubVector[6].x * SubVector[8].y - SubVector[8].x * SubVector[6].y);
	CrossVector[6] = D3DXVECTOR3(SubVector[9].y * SubVector[10].z - SubVector[10].y * SubVector[9].z, SubVector[9].z * SubVector[10].x - SubVector[10].z * SubVector[9].x, SubVector[9].x * SubVector[10].y - SubVector[10].x * SubVector[9].y);
	CrossVector[7] = D3DXVECTOR3(SubVector[9].y * SubVector[11].z - SubVector[11].y * SubVector[9].z, SubVector[9].z * SubVector[11].x - SubVector[11].z * SubVector[9].x, SubVector[9].x * SubVector[11].y - SubVector[11].x * SubVector[9].y);

	float fDot[8];
	//現在位置の方
	fDot[0] = CrossVector[0].x * CrossVector[2].x + CrossVector[0].y * CrossVector[2].y + CrossVector[0].z * CrossVector[2].z;
	fDot[1] = CrossVector[2].x * CrossVector[4].x + CrossVector[2].y * CrossVector[4].y + CrossVector[2].z * CrossVector[4].z;
	fDot[2] = CrossVector[4].x * CrossVector[6].x + CrossVector[4].y * CrossVector[6].y + CrossVector[4].z * CrossVector[6].z;
	fDot[3] = CrossVector[6].x * CrossVector[0].x + CrossVector[6].y * CrossVector[0].y + CrossVector[6].z * CrossVector[0].z;

	//過去位置の方
	fDot[4] = CrossVector[1].x * CrossVector[2].x + CrossVector[1].y * CrossVector[2].y + CrossVector[1].z * CrossVector[2].z;
	fDot[5] = CrossVector[3].x * CrossVector[4].x + CrossVector[3].y * CrossVector[4].y + CrossVector[3].z * CrossVector[4].z;
	fDot[6] = CrossVector[5].x * CrossVector[6].x + CrossVector[5].y * CrossVector[6].y + CrossVector[5].z * CrossVector[6].z;
	fDot[7] = CrossVector[7].x * CrossVector[0].x + CrossVector[7].y * CrossVector[0].y + CrossVector[7].z * CrossVector[0].z;
	if ((fDot[0] > 0.0f && fDot[1] > 0.0f && fDot[2] > 0.0f && fDot[3] > 0.0f) && (fDot[4] > 0.0f && fDot[5] > 0.0f && fDot[6] > 0.0f && fDot[7] > 0.0f))
	{
		return true;
	}
	return false;
}

//障害物との当たり判定
bool CPlayer::CollisionBlock(D3DXVECTOR3 aSquare[4], D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, bool *bLand, D3DXVECTOR3 *Nextpos)
{
	D3DXVECTOR3 SubPoint[2];
	D3DXVECTOR3 Cross[5];
	float fLength;
	float fDistance;
	float fOldDistance;
	float fHeadDistance;
	float fHeadOldDistance;

	SubPoint[0] = aSquare[2] - aSquare[1];
	SubPoint[1] = aSquare[1] - aSquare[0];
	D3DXVec3Cross(&Cross[0], &SubPoint[0], &SubPoint[1]);
	if (fabsf(Cross[0].x) < 0.01f)
	{
		Cross[0].x = 0.0f;
	}
	if (fabsf(Cross[0].y) < 0.01f)
	{
		Cross[0].y = 0.0f;
	}
	if (fabsf(Cross[0].z) < 0.01f)
	{
		Cross[0].z = 0.0f;
	}
	fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);
	Cross[0].x /= fLength;
	Cross[0].y /= fLength;
	Cross[0].z /= fLength; //ここまで法線ベクトル 値が大きい方向を向いている Xは左でプラス右でマイナス Yは下でマイナス上でプラス

	Cross[1] = *pPos - aSquare[0];	//プレイヤーのposと壁の任意の点のベクトル
	fDistance = (Cross[0].x * Cross[1].x) + (Cross[0].y * Cross[1].y) + (Cross[0].z * Cross[1].z);		//足元と地面との距離 プラスの時、表側にいる
	Cross[2] = posOld - aSquare[0];	//プレイヤーのOldposと壁の任意の点のベクトル
	fOldDistance = (Cross[0].x * Cross[2].x) + (Cross[0].y * Cross[2].y) + (Cross[0].z * Cross[2].z);	//過去位置足元と地面との距離 プラスの時、表側にいる

	if (Cross[0].y < 0.0f)	//垂直よりも表を向いている
	{
		//距離が近いか、すり抜けたかつ下に落ちてる
		if ((fabsf(fDistance) <= 3.0f || fOldDistance <= 2.0f && fDistance >= -2.0f) && m_move.y <= 0.0f)
		{
			//四角形広げる
			D3DXVECTOR3 aWideSquare[4];
			aWideSquare[0] = D3DXVECTOR3(aSquare[0].x - m_fRadius, aSquare[0].y, aSquare[0].z + m_fRadius);
			aWideSquare[1] = D3DXVECTOR3(aSquare[1].x + m_fRadius, aSquare[1].y, aSquare[1].z + m_fRadius);
			aWideSquare[2] = D3DXVECTOR3(aSquare[2].x - m_fRadius, aSquare[2].y, aSquare[2].z - m_fRadius);
			aWideSquare[3] = D3DXVECTOR3(aSquare[3].x + m_fRadius, aSquare[3].y, aSquare[3].z - m_fRadius);

			//壁面上のプレイヤーの場所
			D3DXVECTOR3 SquarePos;
			SquarePos.x = pPos->x - Cross[0].x * fDistance;
			SquarePos.y = pPos->y - Cross[0].y * fDistance;
			SquarePos.z = pPos->z - Cross[0].z * fDistance;
			D3DXVECTOR3 SquareOldPos;
			SquareOldPos.x = posOld.x - Cross[0].x * fOldDistance;
			SquareOldPos.y = posOld.y - Cross[0].y * fOldDistance;
			SquareOldPos.z = posOld.z - Cross[0].z * fOldDistance;

			//当たり判定
			if (Collision(&aWideSquare[0], SquarePos, SquareOldPos) == true)
			{
				if (Cross[0].y < -0.7f) //大体傾き45度まで
				{
					//影の設定、立ち位置設定
					D3DXVECTOR3 ShadowRot = D3DXVECTOR3(Cross[0].z, 0.0f, Cross[0].x * 1.11f);
					m_move.y = 0.0f;
					pPos->y += fDistance;
					m_pShadow->MoveY(D3DXVECTOR3(pPos->x, pPos->y + 3.0f, pPos->z), ShadowRot);

					//着地してない
					if (m_bLanding == false && m_bLandObject == false)
					{
						//着地する
						MotionChange(MOTIONTYPE_LANDING);
						m_bLandObject = true;
						m_bCharge = false;
						m_fJumpMoveX = 0.0f;
					}
					*bLand = true;
					return true;
				}
				else
				{
					//弾かれる
					pPos->x -= fDistance;
					if (m_bCharge == false)
					{
						m_fJumpMoveX *= REFLECT;
					}
					return false;
				}
			}
		}
	}
	else if(Cross[0].y > 0.0f) //面が下を向いている
	{
		Cross[3] = *pPos - aSquare[0]; //プレイヤーのposと壁の任意の点のベクトル
		Cross[3].y += m_fHeight;
		fHeadDistance = (Cross[0].x * Cross[3].x) + (Cross[0].y * Cross[3].y) + (Cross[0].z * Cross[3].z);	//頭と地面との距離 プラスの時、表側にいる
		Cross[4] = posOld - aSquare[0]; //プレイヤーのOldposと壁の任意の点のベクトル
		Cross[4].y += m_fHeight;
		fHeadOldDistance = (Cross[0].x * Cross[4].x) + (Cross[0].y * Cross[4].y) + (Cross[0].z * Cross[4].z);	//頭と地面との距離 プラスの時、表側にいる
		
		//距離が近いか、すり抜けた
		if (fabsf(fHeadDistance) < 2.0f || fHeadOldDistance <= 2.0f && fHeadDistance >= -2.0f)
		{
			//広げた四角形
			D3DXVECTOR3 aWideSquare[4];
			aWideSquare[0] = D3DXVECTOR3(aSquare[0].x + m_fRadius * 0.6f, aSquare[0].y, aSquare[0].z + m_fRadius * 0.6f);
			aWideSquare[1] = D3DXVECTOR3(aSquare[1].x - m_fRadius * 0.6f, aSquare[1].y, aSquare[1].z + m_fRadius * 0.6f);
			aWideSquare[2] = D3DXVECTOR3(aSquare[2].x + m_fRadius * 0.6f, aSquare[2].y, aSquare[2].z - m_fRadius * 0.6f);
			aWideSquare[3] = D3DXVECTOR3(aSquare[3].x - m_fRadius * 0.6f, aSquare[3].y, aSquare[3].z - m_fRadius * 0.6f);

			//壁面上のプレイヤーの頭の位置
			D3DXVECTOR3 HeadPos = D3DXVECTOR3(pPos->x - Cross[0].x * fHeadDistance, (pPos->y + m_fHeight) - Cross[0].y * fHeadDistance, pPos->z - Cross[0].z * fHeadDistance);
			D3DXVECTOR3 HeadOldPos = D3DXVECTOR3(posOld.x - Cross[0].x * fHeadOldDistance, (posOld.y + m_fHeight) - Cross[0].y * fHeadOldDistance, posOld.z - Cross[0].z * fHeadOldDistance);
			if (Collision(&aWideSquare[0], HeadPos, HeadOldPos) == true)
			{
				//押しのける、上昇速度反転
				Nextpos->y = pPos->y - fabsf(fHeadDistance) - 2.2f;
				m_move.y *= -0.4f;
				return false;
			}
		}
	}

	D3DXVECTOR3 VtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
	int nCntPoint;
	for (nCntPoint = 0; nCntPoint < 4; nCntPoint++)
	{
		if (VtxMax.x < aSquare[nCntPoint].x)
		{
			VtxMax.x = aSquare[nCntPoint].x; //4頂点のうち、一番右の点
		}
		else if (VtxMin.x > aSquare[nCntPoint].x)
		{
			VtxMin.x = aSquare[nCntPoint].x; //4頂点のうち、一番左の点
		}
		if (VtxMax.y < aSquare[nCntPoint].y)
		{
			VtxMax.y = aSquare[nCntPoint].y; //4頂点のうち、一番上の点
		}
		else if (VtxMin.y > aSquare[nCntPoint].y)
		{
			VtxMin.y = aSquare[nCntPoint].y; //4頂点のうち、一番下の点
		}
		if (VtxMax.z < aSquare[nCntPoint].z)
		{
			VtxMax.z = aSquare[nCntPoint].z; //4頂点のうち、一番奥の点
		}
		else if (VtxMin.z > aSquare[nCntPoint].z)
		{
			VtxMin.z = aSquare[nCntPoint].z; //4頂点のうち、一番手前の点
		}
	}

	//大雑把に当たってたら
	if (VtxMin.y < pPos->y + m_fHeight && pPos->y < VtxMax.y && VtxMin.x < pPos->x + m_fRadius && pPos->x - m_fRadius < VtxMax.x/* && (posOld.x + m_fRadius <= VtxMin.x || VtxMax.x <= posOld.x - m_fRadius)*/)
	{
		//乗れない面だったら
		if (fabsf(Cross[0].y) < 0.7f)
		{
			float fD = aSquare[0].x * Cross[0].x + aSquare[0].y * Cross[0].y + aSquare[0].z * Cross[0].z; //平面方程式のD
			D3DXVECTOR3 fDCross = Cross[0] * fD;	//平面の点Pの位置
			D3DXVECTOR3 LeftPosD = D3DXVECTOR3(fDCross.x - (pPos->x - m_fRadius), fDCross.y - pPos->y				, fDCross.z - pPos->z);
			D3DXVECTOR3 LeftHeadD = D3DXVECTOR3(fDCross.x - (pPos->x - m_fRadius), fDCross.y - (pPos->y + m_fHeight), fDCross.z - pPos->z);
			D3DXVECTOR3 RightPosD = D3DXVECTOR3(fDCross.x - (pPos->x + m_fRadius), fDCross.y - pPos->y				, fDCross.z - pPos->z);
			D3DXVECTOR3 RightHeadD = D3DXVECTOR3(fDCross.x - (pPos->x + m_fRadius), fDCross.y - (pPos->y + m_fHeight), fDCross.z - pPos->z);
			float fDotLeftPosD = LeftPosD.x * Cross[0].x + LeftPosD.y * Cross[0].y + LeftPosD.z * Cross[0].z;
			float fDotLeftHeadD = LeftHeadD.x * Cross[0].x + LeftHeadD.y * Cross[0].y + LeftHeadD.z * Cross[0].z;
			float fDotRightPosD = RightPosD.x * Cross[0].x + RightPosD.y * Cross[0].y + RightPosD.z * Cross[0].z;
			float fDotRightHeadD = RightHeadD.x * Cross[0].x + RightHeadD.y * Cross[0].y + RightHeadD.z * Cross[0].z;
			//if (fDotLeftPosD > 0.0f && fDotLeftHeadD < 0.0f || fDotLeftPosD < 0.0f && fDotLeftHeadD > 0.0f) //平面と直線(左側足元から頭)との当たり判定
			//{
			//	D3DXVECTOR3 PlayerVector = D3DXVECTOR3(0.0f, m_fHeight, 0.0f);	//頭のpos - pos
			//	float fRatio = fabsf(fDotLeftPosD) / (fabsf(fDotLeftHeadD) + fabsf(fDotLeftPosD)); //平面と2点の交点からの長さの比率
			//	D3DXVECTOR3 PlanePos = D3DXVECTOR3((pPos->x - m_fRadius) + PlayerVector.x * fRatio, pPos->y + PlayerVector.y * fRatio, pPos->z + PlayerVector.z * fRatio);			//平面と直線の交点
			//	D3DXVECTOR3 PlanePosOld = D3DXVECTOR3((posOld.x - m_fRadius) + PlayerVector.x * fRatio, posOld.y + PlayerVector.y * fRatio, posOld.z + PlayerVector.z * fRatio);	//平面と直線の交点
			//	if (Collision(&aSquare[0], PlanePos, PlanePosOld) == true)
			//	{
			//		Nextpos->x =  VtxMax.x + m_fRadius; //右側に押し出す
			//		m_fJumpMoveX *= -0.8f;
			//		return false;
			//	}
			//}
			//else if (fDotRightPosD > 0.0f && fDotRightHeadD < 0.0f || fDotRightPosD < 0.0f && fDotRightHeadD > 0.0f) //平面と直線(右側足元から頭)との当たり判定
			//{
			//	D3DXVECTOR3 PlayerVector = D3DXVECTOR3(0.0f, m_fHeight, 0.0f);	//頭のpos - pos
			//	float fRatio = fabsf(fDotRightPosD) / (fabsf(fDotRightHeadD) + fabsf(fDotRightPosD)); //平面と2点の交点からの長さの比率
			//	D3DXVECTOR3 PlanePos = D3DXVECTOR3((pPos->x + m_fRadius) + PlayerVector.x * fRatio, pPos->y + PlayerVector.y * fRatio, pPos->z + PlayerVector.z * fRatio);			//平面と直線の交点
			//	D3DXVECTOR3 PlanePosOld = D3DXVECTOR3((posOld.x + m_fRadius) + PlayerVector.x * fRatio, posOld.y + PlayerVector.y * fRatio, posOld.z + PlayerVector.z * fRatio);	//平面と直線の交点
			//	if (Collision(&aSquare[0], PlanePos, PlanePosOld) == true)
			//	{
			//		Nextpos->x = VtxMin.x - m_fRadius; //左側に押し出す
			//		m_fJumpMoveX *= -0.8f;
			//		return false;
			//	}
			//}
			if (fDotLeftPosD > 0.0f && fDotRightPosD < 0.0f || fDotLeftPosD < 0.0f && fDotRightPosD > 0.0f) //平面と直線(足元左から右)との当たり判定
			{
				D3DXVECTOR3 PlayerVector = D3DXVECTOR3(-m_fRadius * 2.0f, 0.0f, 0.0f);	//pos左 - pos右
				float fRatio = fabsf(fDotLeftPosD) / (fabsf(fDotRightPosD) + fabsf(fDotLeftPosD)); //平面と2点の交点からの長さの比率
				D3DXVECTOR3 PlanePos = D3DXVECTOR3(pPos->x + PlayerVector.x * fRatio, pPos->y + PlayerVector.y * fRatio, pPos->z + PlayerVector.z * fRatio);		//平面と直線の交点
				D3DXVECTOR3 PlanePosOld = D3DXVECTOR3(posOld.x + PlayerVector.x * fRatio, posOld.y + PlayerVector.y * fRatio, posOld.z + PlayerVector.z * fRatio);	//平面と直線の交点
				
				//当たり判定
				if (Collision(&aSquare[0], PlanePos, PlanePosOld) == true)
				{
					//過去位置が壁の左側より左にあった
					if (posOld.x < VtxMin.x)
					{
						Nextpos->x = VtxMin.x - m_fRadius; //左側に押し出す

						//左右の移動量反転
						if (m_fJumpMoveX > 0.0f)
						{
							m_fJumpMoveX *= REFLECT;
						}
						return false;
					}

					//過去位置が壁の右側より右にあった
					if (VtxMax.x < posOld.x)
					{
						Nextpos->x = VtxMax.x + m_fRadius; //右側に押し出す

														   //左右の移動量反転
						if (m_fJumpMoveX < 0.0f)
						{
							m_fJumpMoveX *= REFLECT;
						}
						return false;
					}
				}
			}
			else if (fDotLeftHeadD > 0.0f && fDotRightHeadD < 0.0f || fDotLeftHeadD < 0.0f && fDotRightHeadD > 0.0f) //平面と直線(頭左から右)との当たり判定
			{
				D3DXVECTOR3 PlayerVector = D3DXVECTOR3(-m_fRadius * 2.0f, 0.0f, 0.0f);	//pos左 - pos右
				float fRatio = fabsf(fDotLeftHeadD) / (fabsf(fDotRightHeadD) + fabsf(fDotLeftHeadD)); //平面と2点の交点からの長さの比率
				D3DXVECTOR3 PlanePos = D3DXVECTOR3(pPos->x + PlayerVector.x * fRatio, pPos->y + PlayerVector.y * fRatio, pPos->z + PlayerVector.z * fRatio);		//平面と直線の交点
				D3DXVECTOR3 PlanePosOld = D3DXVECTOR3(posOld.x + PlayerVector.x * fRatio, posOld.y + PlayerVector.y * fRatio, posOld.z + PlayerVector.z * fRatio);	//平面と直線の交点
				
				//当たり判定
				if (Collision(&aSquare[0], PlanePos, PlanePosOld) == true)
				{
					//過去位置が左側より左
					if (posOld.x < VtxMin.x)
					{
						Nextpos->x = VtxMin.x - m_fRadius; //左側に押し出す

						//左右移動量反転
						if (m_fJumpMoveX > 0.0f)
						{
							m_fJumpMoveX *= REFLECT;
						}
						return false;
					}

					//過去位置が左側より左
					if (VtxMax.x < posOld.x)
					{
						Nextpos->x = VtxMax.x + m_fRadius; //右側に押し出す

						//左右移動量反転
						if (m_fJumpMoveX < 0.0f)
						{
							m_fJumpMoveX *= REFLECT;
						}
						return false;
					}
				}
			}

		}
		else //乗れる面のとき
		{
			if (posOld.x < VtxMin.x)		//過去位置が平面の左側より左にあったとき
			{
				Nextpos->x = VtxMin.x - m_fRadius; //左側に押し出す
				if (m_fJumpMoveX > 0.0f)
				{
					m_fJumpMoveX *= REFLECT;
				}
				return false;
			}
			else if (VtxMax.x < posOld.x)	//過去位置が平面の右側より右にあったとき
			{
				Nextpos->x = VtxMax.x + m_fRadius; //右側に押し出す
				if (m_fJumpMoveX < 0.0f)
				{
					m_fJumpMoveX *= REFLECT;
				}
				return false;
			}
		}
	}
	return false;
}

//カメラの当たり判定
bool CPlayer::CollisionCamera(D3DXVECTOR3 *pPos, CScene *pScene)
{
	D3DXVECTOR3 pos = pScene->GetPos();
	D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
	D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
	D3DXVECTOR2 aPoint[4]; //スペースの4頂点

	int nCntPos;
	//4頂点反映
	for (nCntPos = 0; nCntPos < 4; nCntPos++)
	{
		switch (nCntPos)
		{
		case 0:
			//位置を反映
			aPoint[nCntPos] = D3DXVECTOR2(pos.x + VtxMin.x, pos.y + VtxMax.y);
			break;
		case 1:
			//位置を反映
			aPoint[nCntPos] = D3DXVECTOR2(pos.x + VtxMax.x, pos.y + VtxMax.y);
			break;
		case 2:
			//位置を反映
			aPoint[nCntPos] = D3DXVECTOR2(pos.x + VtxMin.x, pos.y + VtxMin.y);
			break;
		case 3:
			//位置を反映
			aPoint[nCntPos] = D3DXVECTOR2(pos.x + VtxMax.x, pos.y + VtxMin.y);
			break;
		default:
			break;
		}
	}

	//プレイヤーがこの中に入ってる
	if (aPoint[0].x <= pPos->x && pPos->x <= aPoint[1].x && aPoint[2].y <= pPos->y && pPos->y <= aPoint[0].y)
	{
		m_aCamera[0] = aPoint[2];
		m_aCamera[1] = aPoint[1];
		return true;
	}
	return false;
}

//障害物に対する影の描画
void CPlayer::ShadowObject(D3DXVECTOR3 aSquare[4], D3DXVECTOR3 *pPos)
{
	D3DXVECTOR3 PlayerVector = D3DXVECTOR3(0.0f, m_fShadowPosY - pPos->y, 0.0f); //プレイヤーからずっと下へのベクトル
	D3DXVECTOR3 BlockVector = aSquare[1] - aSquare[0]; //四角形の1辺のベクトル
	D3DXVECTOR3 Cross[2];
	float fLength;
	fLength = powf((PlayerVector.x * PlayerVector.x) + (PlayerVector.y * PlayerVector.y) + (PlayerVector.z * PlayerVector.z), 0.5f);
	Cross[0] = PlayerVector / fLength;	//プレイヤーのベクトルの単位ベクトル
	fLength = powf((BlockVector.x * BlockVector.x) + (BlockVector.y * BlockVector.y) + (BlockVector.z * BlockVector.z), 0.5f);
	Cross[1] = BlockVector / fLength;	//四角形1辺のベクトルの単位ベクトル
	
	float fWork1 = Cross[0].x * Cross[1].x + Cross[0].y * Cross[1].y + Cross[0].z * Cross[1].z; //上2つの単位ベクトルの内積
	float fWork2 = 1.0f - fWork1 * fWork1;
	
	if (fWork2 == 0.0f) //0だと平行
	{
		return;
	}
	
	D3DXVECTOR3 PlayerBlock = aSquare[0] - *pPos; //プレイヤーと四角形の1点とのベクトル
	float fD1 = ((PlayerBlock.x * Cross[0].x + PlayerBlock.y * Cross[0].y + PlayerBlock.z * Cross[0].z) - fWork1 * (PlayerBlock.x * Cross[1].x + PlayerBlock.y * Cross[1].y + PlayerBlock.z * Cross[1].z)) / fWork2;
	float fD2 = (fWork1 * (PlayerBlock.x * Cross[0].x + PlayerBlock.y * Cross[0].y + PlayerBlock.z * Cross[0].z) - (PlayerBlock.x * Cross[1].x + PlayerBlock.y * Cross[1].y + PlayerBlock.z * Cross[1].z)) / fWork2;

	D3DXVECTOR3 MostVertex[2];
	//プレイヤーベクトル上の最近点
	MostVertex[0].x = pPos->x + fD1 * Cross[0].x;
	MostVertex[0].y = pPos->y + fD1 * Cross[0].y;
	MostVertex[0].z = pPos->z + fD1 * Cross[0].z;

	//1辺の最近点
	MostVertex[1].x = aSquare[0].x + fD2 * Cross[1].x;
	MostVertex[1].y = aSquare[0].y + fD2 * Cross[1].y;
	MostVertex[1].z = 0.0f;

	//交差しているかの判定
	if (powf(MostVertex[1].x - MostVertex[0].x, 2.0f) + powf(MostVertex[1].y - MostVertex[0].y, 2.0f) + powf(MostVertex[1].z - MostVertex[0].z, 2.0f) < 0.001f)
	{
		//元々の影の場所より高く、プレイヤーより低い
		if (m_fShadowPosY < MostVertex[0].y && MostVertex[0].y < pPos->y)
		{
			//広い四角形
			D3DXVECTOR3 aWideSquare[4];
			aWideSquare[0] = D3DXVECTOR3(aSquare[0].x - m_fRadius, aSquare[0].y, aSquare[0].z + m_fRadius);
			aWideSquare[1] = D3DXVECTOR3(aSquare[1].x + m_fRadius, aSquare[1].y, aSquare[1].z + m_fRadius);
			aWideSquare[2] = D3DXVECTOR3(aSquare[2].x - m_fRadius, aSquare[2].y, aSquare[2].z - m_fRadius);
			aWideSquare[3] = D3DXVECTOR3(aSquare[3].x + m_fRadius, aSquare[3].y, aSquare[3].z - m_fRadius);
			
			//四角形と1点の当たり判定
			if (Collision(&aWideSquare[0], MostVertex[0], MostVertex[1]) == true)
			{
				D3DXVECTOR3 SubPoint[2];
				SubPoint[0] = aSquare[2] - aSquare[1];
				SubPoint[1] = aSquare[1] - aSquare[0];
				D3DXVec3Cross(&Cross[0], &SubPoint[0], &SubPoint[1]);
				fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f); //単位ベクトル
				Cross[0].x /= fLength;
				Cross[0].y /= fLength;
				Cross[0].z /= fLength; //ここまで法線ベクトル 値が大きい方向を向いている
				m_fShadowPosY = MostVertex[0].y + 1.0f;
				m_ShadowRot.x = Cross[0].z;
				m_ShadowRot.y = Cross[0].y;
				m_ShadowRot.z = Cross[0].x * 1.11f;
			}
		}
	}
}