//---------------------------
//Author:三上航世
//カメラ(camera.cpp)
//---------------------------
#include "camera.h"
#include "input.h"
#include "gamepad.h"
#include "mouse.h"
#include "player.h"
#include "fade.h"

//カメラの構造体
typedef struct
{
	D3DXVECTOR3 posV;		//現在の視点
	D3DXVECTOR3 posVDest;	//目的の視点
	D3DXVECTOR3 posR;		//現在の注視点
	D3DXVECTOR3 posRDest;	//目的の注視点
	D3DXVECTOR3 vecU;		//上方向ベクトル
	D3DXVECTOR3 rot;		//カメラの向き
	float fLength;			//距離
	bool bDie;				//やられたか
	int nDieTime;			//やられた時間
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス
} Camera;

//グローバル変数
Camera g_camera; //カメラの情報

//初期化処理
HRESULT InitCamera(void)
{
	//色々設定
	g_camera.posV = D3DXVECTOR3(0.0f, 140.0f, -200.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 140.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fLength = 400.0f;
	g_camera.nDieTime = 0;
	g_camera.bDie = false;
	return S_OK;
}

//終了処理
void UninitCamera(void)
{

}

//更新処理
void UpdateCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();     //デバイスを取得する

	//まだやられてない
	if (g_camera.bDie == false)
	{
		//マウスを横に移動させると、カメラ左右に動く
		g_camera.rot.y += MouseX() * 0.003f;
		if (GamePad() == true)
		{
			g_camera.rot.y += RightStickX() * 0.05f;
		}

		//目的の視点、注視点設定
		g_camera.posRDest = D3DXVECTOR3(PlayerPos().x + PlayerGetMove().x * 8.0f, PlayerPos().y + GetPlayerHeight(), PlayerPos().z + PlayerGetMove().z * 8.0f);
		g_camera.posVDest.x = PlayerPos().x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = PlayerPos().y + g_camera.fLength;
		g_camera.posVDest.z = PlayerPos().z - cosf(g_camera.rot.y) * g_camera.fLength;
		
		//目的の注視点と現在の注視点が違う場合、合わせる
		if (g_camera.posRDest.x != g_camera.posR.x)
		{
			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.2f;
		}
		if (g_camera.posRDest.y != g_camera.posR.y)
		{
			g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.2f;
		}
		if (g_camera.posRDest.z != g_camera.posR.z)
		{
			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.2f;
		}

		//角度が狂わないようにする
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2;
		}
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2;
		}

		//現在視点計算
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.y = g_camera.posR.y + g_camera.fLength * (1.0f / 10.0f);
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	//やられてる場合
	else
	{
		//カウントする
		g_camera.nDieTime++;

		//カウントが一定以上、リザルトに移行
		if (g_camera.nDieTime >= 200)
		{
			SetFade(MODE_RESULT);
		}

		//現在視点、注視点出す
		g_camera.posR = D3DXVECTOR3(PlayerPos().x, PlayerPos().y + 50.0f, PlayerPos().z);
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * 250.0f;
		g_camera.posV.y = g_camera.posR.y + 100.0f;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * 250.0f;
	}

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//設定処理
void SetCamera(D3DXVECTOR3 ref, float fDistance)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();     //デバイスを取得する

	//色々設定
	g_camera.posR = ref;
	g_camera.bDie = false;
	g_camera.nDieTime = 0;
	if (fDistance > 100.0f)
	{
		g_camera.fLength = fDistance;
	}
	g_camera.rot.y = 0.0f;

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);
	//プロジェクションマトリックス作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 3000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//カメラの方向
float CameraRot(void)
{
	return g_camera.rot.y;
}

//視点の場所
float CameraPosV(int nRot)
{
	switch (nRot)
	{
	case 0:
		return g_camera.posV.x;
		break;
	case 1:
		return g_camera.posV.y;
		break;
	case 2:
		return g_camera.posV.z;
		break;
	}
	return 0.0f;
}

//注視点の場所
D3DXVECTOR3 CameraPosR(void)
{
	return g_camera.posR;
}

//視点と注視点の距離
float CameraDistance(void)
{
	float fDistance;
	float fHDistance;
	float fLengthX;
	float fLengthY;
	float fLengthZ;
	fLengthX = powf(g_camera.posR.x - g_camera.posV.x, 2);
	fLengthY = powf(g_camera.posR.y - g_camera.posV.y, 2);
	fLengthZ = powf(g_camera.posR.z - g_camera.posV.z, 2);
	fHDistance = fLengthX + fLengthZ;
	fDistance = sqrtf(fLengthY + fHDistance);
	return fDistance;
}

//カメラの方向取得
D3DXVECTOR3 CameraVector(void)
{
	return g_camera.vecU;
}

//方向設定
void CameraRotReset(float fRoty)
{
	g_camera.rot.y = fRoty;
}

//方向加算
void CameraRot(float fRot)
{
	if (fRot - g_camera.rot.y < -3.14f)
	{
		g_camera.rot.y += (fRot - g_camera.rot.y + 6.28f) * 0.01f;
	}
	else if (fRot - g_camera.rot.y > 3.14f)
	{
		g_camera.rot.y += (fRot - g_camera.rot.y - 6.28f) * 0.01f;
	}
	else
	{
		g_camera.rot.y += (fRot - g_camera.rot.y) * 0.01f;
	}
}

//プレイヤーがやられたときのカメラ
void PlayerDieCamera(float fRot)
{
	g_camera.bDie = true;
	g_camera.rot.y = fRot + 0.8f;
}