//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class CKeyboard;
class CMouse;
class CScene;

class CCamera
{
public:
	//カメラの構造体
	typedef struct
	{
		D3DXVECTOR3 posV;			//現在の視点
		D3DXVECTOR3 posVDest;		//目的の視点
		D3DXVECTOR3 posR;			//現在の注視点
		D3DXVECTOR3 posRDest;		//目的の注視点
		D3DXVECTOR3 posPlus;		//pos足す
		D3DXVECTOR3 vecU;			//上方向ベクトル
		D3DXVECTOR3 rot;			//カメラの向き
		D3DXVECTOR3 rotDesh;		//カメラの目的向き
		float fLength;				//距離
		D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
		D3DXMATRIX mtxView;			//ビューマトリックス
		bool bRot[2];				//XとY
		bool bAdd[2];				//XとY
	} Camera;
	CCamera();
	~CCamera();
	HRESULT Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//初期化
	void Uninit();	//終了
	void Update();	//更新

	float GetRotY() { return m_camera.rot.y; }	//方向Y取得
	float GetRotX() { return m_camera.rot.x; }	//方向X取得
	void SetPosV(D3DXVECTOR3 pos);				//視点設定
	void SetPosR(D3DXVECTOR3 pos);				//注視点設定
	void SetRot(D3DXVECTOR3 rot) { m_camera.rot = rot; }			//方向設定
	void SetLength(float fLength) { m_camera.fLength = fLength; }	//距離設定
	D3DXVECTOR3 GetPosR() { return m_camera.posR; }					//現在注視点取得
	D3DXVECTOR3 GetPosV() { return m_camera.posV; }					//現在視点取得
	void AddRotY(float fRotY);	//方向Y加算
	void AddRotX(float fRotX);	//方向X加算
	void MoveX(float fMove);	//移動X
	void MoveZ(float fMove);	//移動Z
	void ResetRot() { m_camera.rot = D3DXVECTOR3(0.8f, 0.0f, 0.0f); }	//方向リセット
	void SetPlayer(CScene *pPlayer) { m_pPlayer = pPlayer; }			//プレイヤー設定
	void SetRotDeshX(float fRotX);	//目的の向きX設定
	void SetRotDeshY(float fRotY);	//目的の向きY設定
	void SetAdd(bool bAdd);			//足していくか設定
	void AddLength(float fLength) { m_camera.fLength += fLength; }				//距離加算
	void AddPosReset(void){ m_camera.posPlus = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//場所加算値リセット
	void AddPosPlus(D3DXVECTOR3 pos, D3DXVECTOR2 aCamera[2]);					//場所加算地を加算させる

	static CCamera *Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//作成

private:
	Camera m_camera;	//カメラ
	CScene *m_pPlayer;	//プレイヤー
};

#endif