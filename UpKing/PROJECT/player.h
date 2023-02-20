//=============================================================================
//
// シーン処理 [player.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene3d.h"
#include "model.h"

class CKeyboard;
//class CGamePad;
class CMouse;
class CCamera;
class CShadow;
class COrbit;
class CRockon;
class CUI;
class CPauseUI;

class CPlayer : public CScene3D
{
	//モーションの種類
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,
		//MOTIONTYPE_AIRNUETRAL,
		MOTIONTYPE_RUN,
		MOTIONTYPE_CHARGE,
		MOTIONTYPE_FRONTJUMP,
		MOTIONTYPE_BACKJUMP,
		MOTIONTYPE_LANDING,
		MOTIONTYPE_RETURN, //ニュートラルモーションに戻る際のモーション。txtファイルに書く必要はない
		MAX_MOTION
	} MOTIONTYPE;

	//キーの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	} KEY;

	//キー情報の構造体
	typedef struct
	{
		int nFrame;		//フレーム
		int nSound;		//何の音が鳴るか
		float fMove;	//そのキーの水平移動量
		float fHeight;	//そのキーの垂直移動量
		KEY aKey[32];	//各モデルのキー要素 []内はパーツの最大数
	} KEY_INFO;

	//モーション情報の構造体
	typedef struct
	{
		bool bLoop;		//ループするかどうか
		bool bGravity;	//重力が働くか
		int nNumKey;	//キーの総数
		int nNonOpe;	//操作不能時間
		KEY_INFO aKeyInfo[16];	//キー情報 []内はキーの最大数
	} MOTION_INFO;

public:
	CPlayer(PRIORITY Priority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }									//種類
	float GetRadius() { return m_fRadius; }												//半径
	float GetHeight() { return m_fHeight; }												//身長
	D3DXMATRIX GetMatrix(int nPart) { return m_pModel[nPart]->GetMatrix(); }			//パーツのマトリックス
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//作成

private:
	void Load(const char *aFileName);	//モデルなど読み込み
	bool Move(float fRotY);				//移動
	bool Stop();						//停止
	void Jump();						//ジャンプ
	void GaugeFadeIn();					//ゲージをフェードインさせる
	void GaugeFadeOut();				//ゲージをフェードアウトさせる
	void MouseSelect();					//マウスによる選択
	void JumpCharge();					//ジャンプのチャージ関連
	void JumpFirst();					//チャージ開始
	void JumpCharging();				//チャージ中
	void MouseMoveX();					//マウス横移動
	void Gravity();						//重力
	void RunFirst();					//走り始め
	void RunStop();						//走るの止める
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);					//オブジェクトとの当たり判定
	void CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);						//平面との当たり判定
	bool CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);		//床との当たり判定
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);		//壁との当たり判定
	bool Collision(D3DXVECTOR3 aPoint[4], D3DXVECTOR3 Point, D3DXVECTOR3 PointOld);	//点と四角形との当たり判定
	bool CollisionBlock(D3DXVECTOR3 aPoint[4], D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, bool *bLand, D3DXVECTOR3 *Nextpos);	//ブロックの当たり判定
	bool CollisionCamera(D3DXVECTOR3 *pPos, CScene *pScene);		//カメラゾーンとの当たり判定
	void ShadowObject(D3DXVECTOR3 aPoint[4], D3DXVECTOR3 *pPos);	//障害物の対する影の描画
	void Motion();								//モーション
	void MotionChange(MOTIONTYPE motionType);	//モーション切り替え
	void PauseChange(int nAdd);					//ポーズ選択肢切り替え
	void PauseSelect();							//ポーズ決定
	void EndChange(int nAdd);					//終了選択肢切り替え
	void EndSelect();							//終了決定

	D3DXVECTOR3 m_PosOld;			//過去位置
	D3DXVECTOR3 m_move;				//移動
	D3DXVECTOR3 m_rotDesh;			//目的方向
	D3DXVECTOR3 m_RestartPos;		//リスタート場所
	float m_fMove;					//移動
	float m_fChargeJump;			//チャージのジャンプ力
	float m_fGravity;				//重力
	float m_fJump;					//ジャンプ力
	float m_fHeight;				//身長
	float m_fRadius;				//半径
	float m_fJumpMoveX;				//チャージのジャンプ力
	float m_fGaugeFade;				//ゲージの透明度
	bool m_bCharge;					//チャージ中か
	bool m_bLanding;				//着地してるか
	bool m_bLandObject;				//オブジェクトに着地
	bool m_bLandField;				//地面に着地
	bool m_bChargePlus;				//チャージがプラスかマイナスか
	bool m_bGaugeFade;				//ゲージ明るいか透明か
	int m_nFastMotion;				//何フレームモーションが速いか
	int m_nNumModel;				//モデル数
	int m_nTotalTime;				//モーションの合計フレーム
	MOTIONTYPE m_motionType;		//モーションの種類
	MOTIONTYPE m_motionTypeOld;		//過去のモーションの種類
	int m_nCntMotion;				//現在のモーション数
	MOTION_INFO m_aMotionInfo[32];	//モーションの情報
	MOTION_INFO m_MotionInfo;		//現在モーションの情報
	int m_nNeutralTime;				//ニュートラルの時間
	KEY m_aKeyDiff[32];				//パーツの違い
	int m_nKey;						//現在キー
	CModel *m_pModel[32];			//モデル（パーツ）
	CKeyboard *m_pKeyboard;			//キーボード
	//CGamePad *m_pGamePad;
	CMouse *m_pMouse;				//マウス
	CCamera *m_pCamera;				//カメラ
	CShadow *m_pShadow;				//影
	int m_nRunStop;					//走るの止めたフレーム
	D3DXVECTOR3 m_MotionMove;		//モーションの動き
	bool m_bGameClear;				//ゲームクリアしたか
	bool m_bEndSelect;				//終了の選択肢
	int m_nPauseSelect;				//ポーズの選択番号
	float m_fShadowPosY;			//影の高さ
	int m_nCntJump;					//滞空時間
	D3DXVECTOR3 m_ShadowRot;		//影の向き
	CPauseUI *m_pPauseUI[3];		//ポーズUI
	CUI *m_pBlackGauge[3];			//ゲージ類背景
	CUI *m_pGauge;					//ゲージ
	CUI *m_pBlockGauge[20];			//左右の移動量のゲージ
	D3DXVECTOR2 m_aCamera[2];		//カメラ移動量
};
#endif