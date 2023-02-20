//---------------------------
//Author:三上航世
//カメラ(camera.h)
//---------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitCamera(void);			//初期化
void UninitCamera(void);			//終了
void UpdateCamera(void);			//更新
void SetCamera(D3DXVECTOR3 ref, float fDistance);	//設定
float CameraRot(void);				//方向
float CameraPosV(int nRot);			//視点の場所
D3DXVECTOR3 CameraPosR(void);		//注視点の場所
float CameraDistance(void);			//カメラの距離
D3DXVECTOR3 CameraVector(void);		//カメラの方向
void CameraRotReset(float fRoty);	//方向リセット
void CameraRot(float fRot);			//方向
void PlayerDieCamera(float fRot);	//やられた時のカメラ処理
#endif _CAMERA_H_