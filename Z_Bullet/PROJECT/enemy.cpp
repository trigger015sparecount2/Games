//---------------------------
//Author:三上航世
//モデル(player.cpp)
//---------------------------
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "gamepad.h"
#include "bullet.h"
#include "meshfield.h"
#include "object.h"
#include "rockon.h"
#include "player.h"
#include "wall.h"
#include "particle.h"
#include "fade.h"
#include "billboard.h"
#include "ui.h"
#include "sound.h"

//マクロ定義
#define CHARAFILENAME1 "data/motion_bird.txt"
#define CHARAFILENAME2 "data/motion_dog.txt"
#define CHARAFILENAME3 "data/motion_zombe.txt"
#define CHARAFILENAME4 "data/motion_spider.txt"
#define MAX_ENEMY (32)

//モーションの種類
typedef enum
{
	ENEMYMOTION_NEUTRAL = 0,
	ENEMYMOTION_WALK,
	ENEMYMOTION_ACTION,
	ENEMYMOTION_JUMP,
	ENEMYMOTION_LANDING,
	ENEMYMOTION_DAMAGE,
	ENEMYMOTION_RETURN, //ニュートラルモーションに戻る際のモーション。txtファイルに書く必要はない
	MAX_ENEMYMOTION
} ENEMYMOTION;

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;		//メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアル（材質情報）へのポインタ
	DWORD nNumMat;			//マテリアルの数
	LPDIRECT3DTEXTURE9 TextureModel[4] = {};	//テクスチャ
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOri;		//元々の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 rotOri;		//元々の向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nIdxModelParent;	//親モデルのインデックス
} Model;

//キーの構造体
typedef struct
{
	float fPosX; //位置X
	float fPosY; //位置Y
	float fPosZ; //位置Z
	float fRotX; //向きX
	float fRotY; //向きY
	float fRotZ; //向きZ
} KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;		//フレーム
	float fMove;	//そのキーの移動量
	KEY aKey[32];	//各モデルのキー要素 []内はパーツの最大数
} KEY_INFO;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nIdxModelParent;	//親モデルのインデックス
	float fRadius;			//当たり判定の大きさの半径
	int nStarttime;			//当たり判定が発生する時間
	int nFinishtime;		//当たり判定が消える時間
	int nDamage;			//ダメージ量
	int nDamageTime;		//ヒット間隔
	float fHClash;			//水平方向の吹っ飛ばし力
	float fVClash;			//垂直方向の吹っ飛ばし力
} Collision;

typedef struct
{
	D3DXVECTOR3 pos;		//軌跡の先端の位置
	D3DXMATRIX TipmtxWorld;	//先端のマトリックス
	D3DXVECTOR3 TipposOld;	//軌跡の先端の前回位置
	D3DXVECTOR3 posOld;		//軌跡の根元の前回位置
	int nTime;				//消えるまでの時間
	int nStartTime;			//発生する時間
	int nFinishTime;		//終了の時間
	int nIdxParent;			//親モデルの番号
} Orbit;

typedef struct
{
	D3DXVECTOR3 pos;		//発射根
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nLag;				//発射間隔
	int nBullet;			//
	int nStartBul;			//撃ち始めの時間
	int nFinishBul;			//終わりの時間
	int nIdxParent;			//親インデックス
	int nDamage;			//ダメージ量
	int nDamageTime;		//ヒット間隔
	float fHClash;			//水平方向の吹っ飛ばし力
	float fVClash;			//垂直方向の吹っ飛ばし力
} Bang;

//モーション情報の構造体
typedef struct
{
	bool bLoop;				//ループするかどうか
	int nNumKey;			//キーの総数
	Collision collision[4];	//当たり判定
	int nNumCol;			//当たり判定の数
	Orbit orbit[4];			//軌跡
	int nNumOrbit;			//軌跡の数
	Bang bang[4];			//弾の数
	int nNumBang;			//弾何個使うか
	KEY_INFO aKeyInfo[16];	//キー情報 []内はキーの最大数
} MOTION_INFO;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//前回位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 rotDesh;	//目的の向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 move;		//移動量
	Model aModel[32];		//モデル（パーツ）
	int nNumModel;			//モデル（パーツ）数
	int nShadow;			//影の番号
	MOTION_INFO aMotionInfo[MAX_ENEMYMOTION]; //モーション情報
	MOTION_INFO MotionInfo;	//現在のモーション情報
	int nNumMotion;			//モーション数
	ENEMYMOTION enemymotion;	//モーションタイプ
	int nKey;				//キーNo.
	int nCounterMotion;		//モーションのカウンター
	KEY aKeyDiff[32];		//差分 []内はパーツ数
	KEY KeyMove;			//モーション開始から体がどれだけ動いたか
	float fRadius;			//半径
	float fHeight;			//高さ
	float fMove;			//最大速度
	float fJump;			//ジャンプ力
	int nMoveParts;			//モデルの基準になる部位
	int nTotalTime;			//モーション開始から合計の時間
	int nDamageTime;		//被弾してからの時間
	int nHP;				//現在HP
	int nMaxHP;				//最大HP
	int nScore;				//スコア
	int nThinkTime;			//考える時間
	int nMoveTime;			//移動時間
	bool bAtk;				//攻撃する
	float fATKRange;		//攻撃する距離
	Enemytype enemytype;	//敵の種類
	bool bUse;				//使用中か
} Enemy;

//プロトタイプ宣言
void EnemyLoad(int nCntEnemy, const char *FileName);	//読み込み
void EnemyMove(int nCntEnemy);	//移動
void EnemySlow(int nCntEnemy);	//遅くする
void EnemyMotionChange(int nCntEnemy, ENEMYMOTION enemymotion);	//モーション切り替え
void EnemyMotion(int nCntEnemy);	//モーション
void HitDamage(D3DXVECTOR3 Clash, int nDamage, int nDamageTime, int nCntEnemy);	//ダメージくらった
void EnemyAI(int nCntEnemy);		//敵の思考回路
bool EnemyAtkOver(void);			//敵が一定以上攻撃してるか
void CollisionPos(int nCntEnemy);	//当たり判定の場所
void CollisionEnemy(int nEnemy, float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move);	//敵との当たり判定
float BossHPRate(int nCntEnemy);	//ボスのHPの割合

//グローバル変数
Enemy g_enemy[MAX_ENEMY];	//敵の情報
Enemy g_enemymodel[8];		//敵のモデル
Model g_Emodel[32];			//モデルの情報
int g_nNumEnemyModel;		//キャラに使うモデルが何種類あるか

//初期化処理
HRESULT InitEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].bUse = false;
	}
	EnemyLoad(0, CHARAFILENAME1);
	EnemyLoad(1, CHARAFILENAME2);
	EnemyLoad(2, CHARAFILENAME3);
	EnemyLoad(3, CHARAFILENAME4);
	return S_OK;
}

//終了処理
void UninitEnemy(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < g_nNumEnemyModel; nCntModel++)
	{
		//テクスチャの破棄
		if (g_Emodel[nCntModel].pMesh != NULL)
		{
			g_Emodel[nCntModel].pMesh->Release();
			g_Emodel[nCntModel].pMesh = NULL;
		}
		//頂点バッファの破棄
		if (g_Emodel[nCntModel].pBuffMat != NULL)
		{
			g_Emodel[nCntModel].pBuffMat->Release();
			g_Emodel[nCntModel].pBuffMat = NULL;
		}
	}
}

//更新処理
void UpdateEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中
		if (g_enemy[nCntEnemy].bUse == true)
		{
			//過去位置記録
			g_enemy[nCntEnemy].posOld = g_enemy[nCntEnemy].pos;

			//現在の方向と目的の方向が違う
			if (g_enemy[nCntEnemy].rot.y != g_enemy[nCntEnemy].rotDesh.y)
			{
				//徐々に加算
				if (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y < -3.14f)
				{
					g_enemy[nCntEnemy].rot.y += (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y + 6.28f) * 0.14f;
				}
				else if (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y > 3.14f)
				{
					g_enemy[nCntEnemy].rot.y += (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y - 6.28f) * 0.14f;
				}
				else
				{
					g_enemy[nCntEnemy].rot.y += (g_enemy[nCntEnemy].rotDesh.y - g_enemy[nCntEnemy].rot.y) * 0.14f;
				}
			}

			//敵考える
			EnemyAI(nCntEnemy);

			//鳥の場合
			if (g_enemy[nCntEnemy].enemytype == ENEMYTYPE_BIRD)
			{
				//上下させる
				if (g_enemy[nCntEnemy].pos.y < 80.0f)
				{
					g_enemy[nCntEnemy].move.y = 0.3f;
				}
				else if(g_enemy[nCntEnemy].pos.y > 120.0f)
				{
					g_enemy[nCntEnemy].move.y = -0.3f;
				}
			}
			//鳥以外
			else
			{
				//重力
				g_enemy[nCntEnemy].move.y -= 0.4f;
			}

			//移動
			g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;
			g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;
			g_enemy[nCntEnemy].pos.z += g_enemy[nCntEnemy].move.z;
			
			//被弾してからの時間減らす
			if (g_enemy[nCntEnemy].nDamageTime > 0)
			{
				g_enemy[nCntEnemy].nDamageTime--;
			}

			//移動時間が0以下
			if (g_enemy[nCntEnemy].nMoveTime <= 0)
			{
				//敵遅くする、歩きモーションの場合、リターンモーションにする
				EnemySlow(nCntEnemy);
				if (g_enemy[nCntEnemy].enemymotion == ENEMYMOTION_WALK)
				{
					EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
				}
			}

			//今の番号とロックオンの番号が同じ
			if (nCntEnemy == RockNumber())
			{
				//ロックオン移動
				MoveRockon(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y + g_enemy[nCntEnemy].fHeight / 2, g_enemy[nCntEnemy].pos.z));
			}

			//影移動
			MoveShadow(g_enemy[nCntEnemy].nShadow, g_enemy[nCntEnemy].pos);
			
			//敵のモーション
			EnemyMotion(nCntEnemy);
			
			//地面、壁、敵との当たり判定
			CollisionField(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posOld, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fRadius);
			CollisionWall(&g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fRadius);
			CollisionEnemy(nCntEnemy, g_enemy[nCntEnemy].fRadius, &g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].move);
		}
	}
}

//描画処理
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef;		 //現在のマテリアル保存用
	D3DXMATERIAL *pMat;			 //マテリアルデータへのポインタ
	int nCntModel;
	pDevice = GetDevice();		 //デバイスを取得する
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中
		if (g_enemy[nCntEnemy].bUse == true)
		{
			//プレイヤーとの距離が近い
			if (PlayerDistance(g_enemy[nCntEnemy].pos) < 1800.0f)
			{
				//敵のワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_enemy[nCntEnemy].mtxWorld);
				
				//敵の向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_enemy[nCntEnemy].rot.y, g_enemy[nCntEnemy].rot.x, g_enemy[nCntEnemy].rot.z);
				D3DXMatrixMultiply(&g_enemy[nCntEnemy].mtxWorld, &g_enemy[nCntEnemy].mtxWorld, &mtxRot);
				
				//敵の位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
				D3DXMatrixMultiply(&g_enemy[nCntEnemy].mtxWorld, &g_enemy[nCntEnemy].mtxWorld, &mtxTrans);
				
				//敵のワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_enemy[nCntEnemy].mtxWorld);
				
				for (nCntModel = 0; nCntModel < g_enemy[nCntEnemy].nNumModel; nCntModel++)
				{
					D3DXMATRIX mtxRotParts, mtxTransParts; //パーツ用計算用マトリックス
					D3DXMATRIX mtxParent; //親のマトリックス
					
					//パーツのワールドマトリックスの初期化
					D3DXMatrixIdentity(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld);
					
					//パーツの向きを反映
					D3DXMatrixRotationYawPitchRoll(&mtxRot, g_enemy[nCntEnemy].aModel[nCntModel].rot.y + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.y,
						g_enemy[nCntEnemy].aModel[nCntModel].rot.x + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.x, g_enemy[nCntEnemy].aModel[nCntModel].rot.z + g_enemy[nCntEnemy].aModel[nCntModel].rotOri.z);
					D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRot);
					
					//パーツの位置を反映
					D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].aModel[nCntModel].pos.x + g_enemy[nCntEnemy].aModel[nCntModel].posOri.x, g_enemy[nCntEnemy].aModel[nCntModel].pos.y + g_enemy[nCntEnemy].aModel[nCntModel].posOri.y, g_enemy[nCntEnemy].aModel[nCntModel].pos.z + g_enemy[nCntEnemy].aModel[nCntModel].posOri.z);
					D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTrans);
					
					//各パーツの親のマトリックスを設定
					if (g_enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
					{
						mtxParent = g_enemy[nCntEnemy].aModel[g_enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
					}
					else
					{
						mtxParent = g_enemy[nCntEnemy].mtxWorld; //敵のマトリックスを設定
					}
					
					//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
					D3DXMatrixMultiply(&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
						&g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
						&mtxParent);
					
					//各パーツのワールドマトリックスの設定
					pDevice->SetTransform(D3DTS_WORLD, &g_enemy[nCntEnemy].aModel[nCntModel].mtxWorld);
					
					//パーツの現在のマテリアルを取得
					pDevice->GetMaterial(&matDef);
					
					//パーツのマテリアルデータへのポインタの反映
					pMat = (D3DXMATERIAL*)g_enemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();
					
					int nCntMat;
					for (nCntMat = 0; nCntMat < (int)g_enemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
					{
						int nCntTex = 0;
						//敵のマテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
						//for (int nCntMat = 0; nCntMat < (int)g_enemy[nCntEnemy].aModel[nCntModel].nNumMat; nCntMat++)
						//{
						if (pMat[nCntMat].pTextureFilename != NULL)
						{
							pDevice->SetTexture(0, g_enemy[nCntEnemy].aModel[nCntModel].TextureModel[nCntTex]);
							nCntTex++;
						}
						else
						{
							//テクスチャの設定
							pDevice->SetTexture(0, NULL);
						}
						//}
						//敵のモデル（パーツ）の描画
						g_enemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
					}
				}
				//保存していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);

				//当たり判定の場所計算
				CollisionPos(nCntEnemy);
			}
		}
	}
}

//敵のデータ読み込み
void EnemyLoad(int nCntEnemy, const char *FileName)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();     //デバイスを取得する
	int nCntParts = 0;
	int nCntModelParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	int nCntCol = 0;
	int nCntBullet = 0;
	int nCntOrbit = 0;
	char aFile[256];
	bool bChara = false;
	bool bParts = false;
	bool bMotion = false;
	bool bKey = false;
	bool bKeySet = false;
	bool bColSet = false;
	bool bCol = false;
	bool bBulletSet = false;
	bool bBullet = false;
	bool bOrbit = false;
	bool bOrbitSet = false;
	int nIndex;
	int nLoop;
	FILE *pFile;
	pFile = fopen(FileName, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //モデル数
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_nNumEnemyModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //モデルファイル読み込み
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXLoadMeshFromX(&aFile[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_Emodel[nCntParts].pBuffMat,
					NULL,
					&g_Emodel[nCntParts].nNumMat,
					&g_Emodel[nCntParts].pMesh);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET時
			{
				if (strcmp(&aFile[0], "NUM_PARTS") == 0) //パーツ数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //移動速度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //ジャンプ力
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fJump);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //半径
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //身長
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fHeight);
				}
				if (strcmp(&aFile[0], "HP") == 0) //HP
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].nHP);
					g_enemymodel[nCntEnemy].nMaxHP = g_enemymodel[nCntEnemy].nHP;
				}
				if (strcmp(&aFile[0], "SCORE") == 0) //スコア
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].nScore);
				}
				if (strcmp(&aFile[0], "ATKRANGE") == 0) //攻撃範囲
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].fATKRange);
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
					if (strcmp(&aFile[0], "MOVEPARTS") == 0) //これが動くとg_playerのposも動く（いらないかも）
					{
						g_enemy[0].nMoveParts = nCntParts;
					}
					if (strcmp(&aFile[0], "INDEX") == 0) //モデルファイル読み込みの時の、何番目のモデルを呼び出すか
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						g_enemymodel[nCntEnemy].aModel[nCntParts].pBuffMat = g_Emodel[nIndex].pBuffMat;
						g_enemymodel[nCntEnemy].aModel[nCntParts].nNumMat = g_Emodel[nIndex].nNumMat;
						g_enemymodel[nCntEnemy].aModel[nCntParts].pMesh = g_Emodel[nIndex].pMesh;
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //親モデル
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].aModel[nCntParts].nIdxModelParent);
					}
					if (strcmp(&aFile[0], "POS") == 0) //各パーツの場所
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aModel[nCntParts].posOri.x, &g_enemymodel[nCntEnemy].aModel[nCntParts].posOri.y, &g_enemymodel[nCntEnemy].aModel[nCntParts].posOri.z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //各パーツの角度
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aModel[nCntParts].rotOri.x, &g_enemymodel[nCntEnemy].aModel[nCntParts].rotOri.y, &g_enemymodel[nCntEnemy].aModel[nCntParts].rotOri.z);
					}
				}
			}
			if (bMotion == true) //MOTIONSET時
			{
				if (strcmp(&aFile[0], "LOOP") == 0) //そのモーションがループするか
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
					if (nLoop == 0)
					{
						g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //いくつキーがあるか
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "COLLISIONSET") == 0)	//当たり判定設定
				{
					bColSet = true;
					nCntCol = 0;
				}
				if (strcmp(&aFile[0], "END_COLLISIONSET") == 0)	//当たり判定設定終了
				{
					g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumCol = nCntCol;
					bColSet = false;
				}
				if (strcmp(&aFile[0], "ORBITSET") == 0)	//軌跡設定
				{
					bOrbitSet = true;
					nCntOrbit = 0;
				}
				if (strcmp(&aFile[0], "END_ORBITSET") == 0)	//軌跡設定終了
				{
					g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumOrbit = nCntOrbit;
					bOrbitSet = false;
				}
				if (strcmp(&aFile[0], "BULLET") == 0)	//弾設定
				{
					bBulletSet = true;
					nCntBullet = 0;
				}
				if (strcmp(&aFile[0], "END_BULLETSET") == 0)	//弾設定終了
				{
					g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].nNumBang = nCntBullet;
					bBulletSet = false;
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)	//キー設定
				{
					bKeySet = true;
					nCntParts = 0;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)	//キー設定終了
				{
					bKeySet = false;
					nCntKey++;
				}
				if (bColSet == true) //COLLISIONSET時
				{
					if (strcmp(&aFile[0], "COLLISION") == 0)	//設定開始
					{
						bCol = true;
					}
					if (strcmp(&aFile[0], "END_COLLISION") == 0)	//設定終了
					{
						bCol = false;
						nCntCol++;
					}
					if (bCol == true)
					{
						if (strcmp(&aFile[0], "COL") == 0) //当たり判定（親のインデックス、場所、大きさ、時間）
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %f %f %f %f %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nIdxModelParent,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].pos.x, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].pos.y, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].pos.z,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].fRadius, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nStarttime, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nFinishtime);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //当たり判定（水平吹っ飛ばし力、垂直吹っ飛ばし力、ダメージ量、ヒット間隔）
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].fHClash, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].fVClash,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nDamage, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].collision[nCntCol].nDamageTime);
						}
					}
				}
				if (bOrbitSet == true) //ORBITSET時
				{
					if (strcmp(&aFile[0], "ORBIT") == 0)	//設定開始
					{
						bOrbit = true;
					}
					if (strcmp(&aFile[0], "END_ORBIT") == 0)	//設定終了
					{
						bOrbit = false;
						nCntOrbit++;
					}
					if (strcmp(&aFile[0], "OBT") == 0) //軌跡（場所、表示時間、発生時間）
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d %f %f %f %d %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nIdxParent,
							&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.x, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.y,
							&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].pos.z, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nTime,
							&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nStartTime, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].orbit[nCntOrbit].nFinishTime);
					}
				}
				if (bBulletSet == true) //BULLETSET時
				{
					if (strcmp(&aFile[0], "BULLET") == 0)	//設定開始
					{
						bBullet = true;
					}
					if (strcmp(&aFile[0], "END_BULLET") == 0)	//設定終了
					{
						bBullet = false;
						nCntBullet++;
					}
					if (bBullet == true)
					{
						if (strcmp(&aFile[0], "BUL") == 0) //弾丸（親のインデックス、場所、大きさ、時間）
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %f %f %f %d %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nIdxParent,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].pos.x, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].pos.y,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].pos.z, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nStartBul,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nFinishBul, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nLag);
						}
						if (strcmp(&aFile[0], "DMG") == 0) //弾丸（水平吹っ飛ばし力、垂直吹っ飛ばし力、ダメージ量、ヒット間隔）
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].fHClash, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].fVClash,
								&g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nDamage, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].bang[nCntBullet].nDamageTime);
						}
					}
				}
				if (bKeySet == true) //KEYSET時
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //フレーム数
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "MOVE") == 0) //移動量
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
					}
					if (strcmp(&aFile[0], "KEY") == 0)
					{
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)
					{
						bKey = false;
						nCntParts++;
					}
					if (bKey == true) //KEY時
					{
						if (strcmp(&aFile[0], "POS") == 0) //場所
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //角度
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &g_enemymodel[nCntEnemy].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)	//モーション設定終了
			{
				bMotion = false;
				nCntMotion++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //終了の1文
			{
				break;
			}
		}
		fclose(pFile);
	}

	D3DXMATERIAL *pMat;
	//「MOTIONTYPE_RETURN」は、ニュートラルモーションに戻る際に経由するモーション
	g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].bLoop = false;
	g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].nFrame = 14;
	g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].nNumKey = 1;
	g_enemymodel[nCntEnemy].KeyMove.fPosX = 0.0f;
	g_enemymodel[nCntEnemy].KeyMove.fPosY = 0.0f;
	g_enemymodel[nCntEnemy].KeyMove.fPosZ = 0.0f;
	g_enemymodel[nCntEnemy].nDamageTime = 0;
	
	for (nCntParts = 0; nCntParts < g_enemymodel[nCntEnemy].nNumModel; nCntParts++)
	{
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosX = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosY = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotX = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotY = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_RETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = g_enemymodel[nCntEnemy].aMotionInfo[ENEMYMOTION_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)g_enemymodel[nCntEnemy].aModel[nCntParts].pBuffMat->GetBufferPointer();
		int nCntTex = 0;
		for (int nCntMat = 0; nCntMat < (int)g_enemymodel[nCntEnemy].aModel[nCntParts].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_enemymodel[nCntEnemy].aModel[nCntParts].TextureModel[nCntTex]);
				nCntTex++;
			}
		}
	}

	//posなど設定
	g_enemymodel[nCntEnemy].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].rotDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemymodel[nCntEnemy].nTotalTime = 0;
	g_enemymodel[nCntEnemy].nDamageTime = 0;
	g_enemymodel[nCntEnemy].nThinkTime = 100;
	g_enemymodel[nCntEnemy].nMoveTime = 0;
	g_enemymodel[nCntEnemy].bAtk = false;
	g_enemymodel[nCntEnemy].bUse = true;
}

//移動速度
void EnemyMove(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.x -= (sinf(g_enemy[nCntEnemy].rotDesh.y) * g_enemy[nCntEnemy].fMove + g_enemy[nCntEnemy].move.x) * 0.1f;
	g_enemy[nCntEnemy].move.z -= (cosf(g_enemy[nCntEnemy].rotDesh.y) * g_enemy[nCntEnemy].fMove + g_enemy[nCntEnemy].move.z) * 0.1f;
}

//移動速度低下
void EnemySlow(int nCntEnemy)
{
	g_enemy[nCntEnemy].move.x -= g_enemy[nCntEnemy].move.x * 0.1f;
	g_enemy[nCntEnemy].move.z -= g_enemy[nCntEnemy].move.z * 0.1f;
}

//モーションを切り替える関数
void EnemyMotionChange(int nCntEnemy, ENEMYMOTION enemymotion)
{
	g_enemy[nCntEnemy].enemymotion = enemymotion;
	g_enemy[nCntEnemy].nCounterMotion = 0;
	g_enemy[nCntEnemy].MotionInfo = g_enemy[nCntEnemy].aMotionInfo[enemymotion];
	g_enemy[nCntEnemy].nKey = 0;
	g_enemy[nCntEnemy].KeyMove.fPosX = 0.0f;
	g_enemy[nCntEnemy].KeyMove.fPosY = 0.0f;
	g_enemy[nCntEnemy].KeyMove.fPosZ = 0.0f;
	g_enemy[nCntEnemy].nTotalTime = 0;
}

//モーションの動作
void EnemyMotion(int nCntEnemy)
{
	int nCntParts;
	g_enemy[nCntEnemy].nCounterMotion++;
	g_enemy[nCntEnemy].nTotalTime++;
	for (nCntParts = 0; nCntParts < g_enemy[nCntEnemy].nNumModel; nCntParts++)
	{
		//差分を求める(対応するキーの各パーツのpos(rot) - 今の各パーツのpos(rot))
		if (g_enemy[nCntEnemy].nCounterMotion == 1)
		{
			if (nCntParts != g_enemy[nCntEnemy].nMoveParts)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosX = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosX - g_enemy[nCntEnemy].aModel[nCntParts].pos.x;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosY - g_enemy[nCntEnemy].aModel[nCntParts].pos.y;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosZ = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosZ - g_enemy[nCntEnemy].aModel[nCntParts].pos.z;
			}
			else
			{
				g_enemy[nCntEnemy].KeyMove.fPosX = sinf(D3DX_PI + g_enemy[nCntEnemy].rot.y) * g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].fMove;
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fPosY - g_enemy[nCntEnemy].aModel[nCntParts].pos.y;
				g_enemy[nCntEnemy].KeyMove.fPosZ = cosf(D3DX_PI + g_enemy[nCntEnemy].rot.y) * g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].fMove;
			}

			//角度計算、狂わないようにする
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotX - g_enemy[nCntEnemy].aModel[nCntParts].rot.x;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX -= 6.28f;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotY - g_enemy[nCntEnemy].aModel[nCntParts].rot.y;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY -= 6.28f;
			}
			g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ = g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].aKey[nCntParts].fRotZ - g_enemy[nCntEnemy].aModel[nCntParts].rot.z;
			if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ < -3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ += 6.28f;
			}
			else if (g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ > 3.14f)
			{
				g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ -= 6.28f;
			}
		}

		//今のパーツが動くパーツと一緒じゃない
		if (nCntParts != g_enemy[nCntEnemy].nMoveParts)
		{
			//モデルのposを動かす
			g_enemy[nCntEnemy].aModel[nCntParts].pos.x += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosX / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.z += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosZ / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		}
		else
		{
			//実際のposを動かす
			g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].KeyMove.fPosX / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].aModel[nCntParts].pos.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fPosY / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
			g_enemy[nCntEnemy].pos.z += g_enemy[nCntEnemy].KeyMove.fPosZ / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		}

		//方向加算
		g_enemy[nCntEnemy].aModel[nCntParts].rot.x += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotX / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		g_enemy[nCntEnemy].aModel[nCntParts].rot.y += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotY / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
		g_enemy[nCntEnemy].aModel[nCntParts].rot.z += g_enemy[nCntEnemy].aKeyDiff[nCntParts].fRotZ / g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame;
	}

	//今のモーションカウンタと現在モーションの現在キー
	if (g_enemy[nCntEnemy].nCounterMotion == g_enemy[nCntEnemy].MotionInfo.aKeyInfo[g_enemy[nCntEnemy].nKey].nFrame)
	{
		//カウントリセット、キー加算
		g_enemy[nCntEnemy].nCounterMotion = 0;
		g_enemy[nCntEnemy].nKey++;

		//現在キーが現在モーションの最大キーと同じになる
		if (g_enemy[nCntEnemy].nKey == g_enemy[nCntEnemy].MotionInfo.nNumKey)
		{
			//ループしない
			if (g_enemy[nCntEnemy].MotionInfo.bLoop == false)
			{
				//リターンモーション以外の場合、リターンモーションにする
				if (g_enemy[nCntEnemy].enemymotion != ENEMYMOTION_RETURN)
				{
					EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
				}
				//リターンモーションの場合、ニュートラルにする
				else
				{
					EnemyMotionChange(nCntEnemy, ENEMYMOTION_NEUTRAL);
				}
			}
			//キーリセット
			g_enemy[nCntEnemy].nKey = 0;
		}
	}
}

//敵のAI
void EnemyAI(int nCntEnemy)
{
	//考える時間0以下
	if (g_enemy[nCntEnemy].nThinkTime <= 0)
	{
		//プレイヤーと距離が離れている場合、プレイヤーのところに移動する
		if (PlayerDistance(g_enemy[nCntEnemy].pos) > 700.0f + g_enemy[nCntEnemy].fRadius)
		{
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
			g_enemy[nCntEnemy].nMoveTime = 120;
			g_enemy[nCntEnemy].nThinkTime = 120;
			g_enemy[nCntEnemy].bAtk = false;
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
		//攻撃する敵が2体以下の場合かつ蜘蛛以外
		else if (EnemyAtkOver() == false && g_enemy[nCntEnemy].enemytype != ENEMYTYPE_SPIDER)
		{
			if (rand() % 3 == 0)
			{
				//攻撃する
				g_enemy[nCntEnemy].bAtk = true;
				g_enemy[nCntEnemy].nThinkTime = 240;
				g_enemy[nCntEnemy].nMoveTime = 240;
				g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
			}
			else
			{
				//適当な方向に移動
				g_enemy[nCntEnemy].bAtk = false;
				g_enemy[nCntEnemy].rotDesh.y = D3DX_PI * (float)(rand() % 361 - 180) / 180.0f;
				g_enemy[nCntEnemy].nThinkTime = 120 + (rand() % 10) * 20;
				g_enemy[nCntEnemy].nMoveTime = g_enemy[nCntEnemy].nThinkTime / 2;
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
			}
		}
		//蜘蛛以外
		else if(g_enemy[nCntEnemy].enemytype != ENEMYTYPE_SPIDER)
		{
			//適当な方向に移動
			g_enemy[nCntEnemy].bAtk = false;
			g_enemy[nCntEnemy].rotDesh.y = D3DX_PI * (float)(rand() % 361 - 180) / 180.0f;
			g_enemy[nCntEnemy].nThinkTime = 120 + (rand() % 10) * 20;
			g_enemy[nCntEnemy].nMoveTime = g_enemy[nCntEnemy].nThinkTime / 2;
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
		//蜘蛛の場合
		else
		{
			//攻撃する
			g_enemy[nCntEnemy].bAtk = true;
			g_enemy[nCntEnemy].nThinkTime = 600;
			g_enemy[nCntEnemy].nMoveTime = 420;
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_WALK);
		}
	}
	//考える時間が1以上
	else
	{
		//カウント減らす
		g_enemy[nCntEnemy].nThinkTime--;
		g_enemy[nCntEnemy].nMoveTime--;

		//攻撃する
		if (g_enemy[nCntEnemy].bAtk == true)
		{
			//プレイヤーに向かって移動する
			g_enemy[nCntEnemy].rotDesh.y = atan2f(g_enemy[nCntEnemy].pos.x - PlayerPos().x, g_enemy[nCntEnemy].pos.z - PlayerPos().z);
			if (PlayerDistance(g_enemy[nCntEnemy].pos) < g_enemy[nCntEnemy].fATKRange + g_enemy[nCntEnemy].fRadius + GetPlayerRadius())
			{
				//攻撃する
				g_enemy[nCntEnemy].bAtk = false;
				g_enemy[nCntEnemy].nMoveTime = 0;
				g_enemy[nCntEnemy].nThinkTime = 420;
				EnemyMotionChange(nCntEnemy, ENEMYMOTION_ACTION);
			}
		}

		//移動時間が0より高い
		if (g_enemy[nCntEnemy].nMoveTime > 0)
		{
			EnemyMove(nCntEnemy);
		}
	}
}

//同時攻撃するのが何体いるのか調べる
bool EnemyAtkOver(void)
{
	int nCntEnemy;
	int nAtkEnemy = 0;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中かつ攻撃フラグがtrue
		if (g_enemy[nCntEnemy].bUse == true && g_enemy[nCntEnemy].bAtk == true)
		{
			//カウントアップ
			nAtkEnemy++;

			//カウントが一定以上でtrue返す
			if (nAtkEnemy > 3)
			{
				return true;
			}
		}
	}
	return false;
}

//敵との当たり判定
void CoillisionEnemy(float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move)
{
	float fLengthX;		//誰かとオブジェクトのX方向の長さ
	float fLengthZ;		//誰かとオブジェクトのZ方向の長さ
	bool bPlusX;		//fLengthXがプラスか
	bool bPlusZ;		//fLengthZがプラスか
	float fDistance;	//誰かとオブジェクトの距離
	float fshort;		//誰かとオブジェクトが当たっている場合の、足りない長さの倍率
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中
		if (g_enemy[nCntEnemy].bUse == true)
		{
			fLengthX = powf(pPos->x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthZ = powf(pPos->z - g_enemy[nCntEnemy].pos.z, 2);
			if (pPos->x - g_enemy[nCntEnemy].pos.x < 0.0f)
			{
				bPlusX = false;
			}
			else
			{
				bPlusX = true;
			}
			if (pPos->z - g_enemy[nCntEnemy].pos.z < 0.0f)
			{
				bPlusZ = false;
			}
			else
			{
				bPlusZ = true;
			}

			//平面の距離計算
			fDistance = sqrtf(fLengthX + fLengthZ);

			//オブジェクトに当たったとき
			if (fDistance <= fRadius + g_enemy[nCntEnemy].fRadius)
			{

				//めり込まないようにする
				g_enemy[nCntEnemy].pos.x += move.x / 5.0f;
				g_enemy[nCntEnemy].pos.z += move.z / 5.0f;
				fLengthX = sqrtf(fLengthX);
				fLengthZ = sqrtf(fLengthZ);
				fshort = (fRadius + g_enemy[nCntEnemy].fRadius) / fDistance - 1.0f;
				fLengthX *= fshort;
				fLengthZ *= fshort;
				if (bPlusX == true)
				{
					pPos->x += fLengthX;
				}
				else
				{
					pPos->x -= fLengthX;
				}
				if (bPlusZ == true)
				{
					pPos->z += fLengthZ;
				}
				else
				{
					pPos->z -= fLengthZ;
				}
			}
		}
	}
}

//ダメージ判定との当たり判定
bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, D3DXVECTOR3 Clash, int nDamage, int nDamageTime)
{
	int nCntEnemy;
	float fLengthX; //当たり判定と敵のX方向の長さ
	float fLengthY; //当たり判定と敵のY方向の長さ
	float fLengthZ; //当たり判定と敵のZ方向の長さ
	float fHDistance; //当たり判定と敵の水平方向の距離
	float fDistance; //当たり判定と敵の距離
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中かつダメージ時間が0以下
		if (g_enemy[nCntEnemy].bUse == true && g_enemy[nCntEnemy].nDamageTime <= 0)
		{
			//距離計算
			fLengthX = powf(pos.x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthY = powf(pos.y - (g_enemy[nCntEnemy].pos.y + g_enemy[nCntEnemy].fHeight / 2), 2);
			fLengthZ = powf(pos.z - g_enemy[nCntEnemy].pos.z, 2);
			fHDistance = fLengthX + fLengthZ;
			fDistance = sqrtf(fLengthY + fHDistance);

			//距離が近い場合、ダメージ食らう
			if (fDistance <= fRadius + g_enemy[nCntEnemy].fHeight / 2)
			{
				HitDamage(Clash, nDamage, nDamageTime, nCntEnemy);
				return true;
			}
		}
	}
	return false;
}

//敵のpos返す
float EnemyPos(int nRot, int nCntEnemy)
{
	switch (nRot)
	{
	case 0:
		return g_enemy[nCntEnemy].pos.x;
		break;
	case 1:
		return g_enemy[nCntEnemy].pos.y + (g_enemy[nCntEnemy].fHeight / 2);
		break;
	case 2:
		return g_enemy[nCntEnemy].pos.z;
		break;
	}
	return 0.0f;
}

//ロックオン処理
int RockOn(D3DXVECTOR3 pos, float fRotY)
{
	int nCntEnemy;
	int nEnemy = -1;
	float fRot;
	float fLengthX;
	float fLengthZ;
	float fDistance;
	float fMinDistance = 20000.0f;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中
		if (g_enemy[nCntEnemy].bUse == true)
		{
			//方向と距離計算
			fRot = fRotY - atan2f(pos.x - g_enemy[nCntEnemy].pos.x, pos.z - g_enemy[nCntEnemy].pos.z);
			if (fRot > D3DX_PI)
			{
				fRot -= D3DX_PI * 2;
			}
			if (fRot < -D3DX_PI)
			{
				fRot += D3DX_PI * 2;
			}
			fLengthX = powf(pos.x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthZ = powf(pos.z - g_enemy[nCntEnemy].pos.z, 2);
			fDistance = sqrtf(fLengthX + fLengthZ);

			//角度が正面方向、近すぎず、一番近い
			if (fabsf(fRot) < D3DX_PI * (15.0f / 180.0f) && 50.0f < fDistance && fDistance < fMinDistance)
			{
				//番号返す
				nEnemy = nCntEnemy;
				fMinDistance = fDistance;
			}
		}
	}

	//ロックオンする敵がいる
	if (nEnemy > -1)
	{
		//ロックオン設定
		SetRockon(D3DXVECTOR3(g_enemy[nEnemy].pos.x, g_enemy[nEnemy].pos.y + g_enemy[nEnemy].fHeight / 2, g_enemy[nEnemy].pos.z), nEnemy);
		return nEnemy;
	}
	return -1;
}

//ロックオン時の弾丸
float RockBullet(D3DXVECTOR3 pos, int nCntEnemy)
{
	//方向計算
	float fRot = 0.0f;
	fRot = atan2f(pos.x - g_enemy[nCntEnemy].pos.x, pos.z - g_enemy[nCntEnemy].pos.z);
	return fRot;
}

//敵の設定
void SetEnemy(D3DXVECTOR3 pos, Enemytype enemyType)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//未使用
		if (g_enemy[nCntEnemy].bUse == false)
		{
			//設定
			g_enemy[nCntEnemy] = g_enemymodel[enemyType];
			g_enemy[nCntEnemy].enemytype = enemyType;
			g_enemy[nCntEnemy].pos = pos;
			if (enemyType == ENEMYTYPE_BIRD)
			{
				g_enemy[nCntEnemy].pos.y += 90.0f;
			}
			if (enemyType == ENEMYTYPE_SPIDER)
			{
				BossHPUISet();
				BossHPUI(BossHPRate(nCntEnemy));
			}
			g_enemy[nCntEnemy].nShadow = SetShadow(pos, g_enemymodel[enemyType].fRadius);
			EnemyMotionChange(nCntEnemy, ENEMYMOTION_RETURN);
			PlaySound(SOUND_LABEL_RESPORN);
			SetParticle(g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fHeight);
			break;
		}
	}
}

//ダメージ食らう
void HitDamage(D3DXVECTOR3 Clash, int nDamage, int nDamageTime, int nCntEnemy)
{
	//色々設定
	g_enemy[nCntEnemy].move = Clash;
	g_enemy[nCntEnemy].nHP -= nDamage;
	g_enemy[nCntEnemy].nDamageTime = nDamageTime;
	g_enemy[nCntEnemy].rot.y = ClashRot(g_enemy[nCntEnemy].pos);
	g_enemy[nCntEnemy].rotDesh.y = g_enemy[nCntEnemy].rot.y;
	EnemyMotionChange(nCntEnemy, ENEMYMOTION_DAMAGE);
	g_enemy[nCntEnemy].nMoveTime = 0;
	g_enemy[nCntEnemy].nThinkTime = 9000;

	//蜘蛛の場合
	if (g_enemy[nCntEnemy].enemytype == ENEMYTYPE_SPIDER)
	{
		//HPUIいじる
		BossHPUI(BossHPRate(nCntEnemy));
	}

	//倒した
	if (g_enemy[nCntEnemy].nHP <= 0)
	{
		//やられた音出す、スコア加算、影外す、パーティクル出す
		PlaySound(SOUND_LABEL_DEATH);
		ScoreAdd(g_enemy[nCntEnemy].nScore);
		g_enemy[nCntEnemy].bUse = false;
		RemoveShadow(g_enemy[nCntEnemy].nShadow);
		SetParticle(g_enemy[nCntEnemy].pos, g_enemy[nCntEnemy].fHeight);

		//蜘蛛の場合、リザルトに移行する
		if (g_enemy[nCntEnemy].enemytype == ENEMYTYPE_SPIDER)
		{
			SetFade(MODE_RESULT);
		}
	}
}

//当たり判定の場所計算
void CollisionPos(int nCntEnemy)
{
	int nCntCol;
	for (nCntCol = 0; nCntCol < g_enemy[nCntEnemy].MotionInfo.nNumCol; nCntCol++)
	{
		if (g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nStarttime <= g_enemy[nCntEnemy].nTotalTime &&
			g_enemy[nCntEnemy].nTotalTime < g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nFinishtime)
		{
			D3DXMATRIX mtxTrans; //パーツ用計算用マトリックス
			D3DXMATRIX mtxParent; //親のマトリックス

			//当たり判定のワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld);
			
			//当たり判定の位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].pos.x, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].pos.y, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].pos.z);
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld, &g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld, &mtxTrans);
			
			//親のマトリックス取得
			mtxParent = g_enemy[nCntEnemy].aModel[g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nIdxModelParent].mtxWorld;
			
			//算出した各当たり判定のワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld,
				&g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld,
				&mtxParent);
			
			//プレイヤーに当たった
			if (PlayerDamage(D3DXVECTOR3(g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld._41, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld._42, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].mtxWorld._43),
				g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fRadius) == true)
			{
				//方向計算、プレイヤーにダメージ
				float fRoty;
				D3DXVECTOR3 Clash;
				fRoty = PlayerClashRot(g_enemy[nCntEnemy].pos);
				Clash.x = sinf(fRoty) * g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fHClash;
				Clash.y = g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fVClash;
				Clash.z = cosf(fRoty) * g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].fHClash;
				PlayerDamage(g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nDamage, g_enemy[nCntEnemy].MotionInfo.collision[nCntCol].nDamageTime, Clash, fRoty);
			}

		}
	}
}

//敵リセット
void ResetEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].bUse = false;
	}
}

//敵との当たり判定
void CollisionEnemy(int nEnemy, float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move)
{
	float fLengthX;		//誰かとオブジェクトのX方向の長さ
	float fLengthZ;		//誰かとオブジェクトのZ方向の長さ
	bool bPlusX;		//fLengthXがプラスか
	bool bPlusZ;		//fLengthZがプラスか
	float fDistance;	//誰かとオブジェクトの距離
	float fshort;		//誰かとオブジェクトが当たっている場合の、足りない長さの倍率
	
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中かつ、自分の番号と今の敵の番号が一致してない
		if (g_enemy[nCntEnemy].bUse == true && nCntEnemy != nEnemy)
		{
			//距離計算
			fLengthX = powf(pPos->x - g_enemy[nCntEnemy].pos.x, 2);
			fLengthZ = powf(pPos->z - g_enemy[nCntEnemy].pos.z, 2);
			if (pPos->x - g_enemy[nCntEnemy].pos.x < 0.0f)
			{
				bPlusX = false;
			}
			else
			{
				bPlusX = true;
			}
			if (pPos->z - g_enemy[nCntEnemy].pos.z < 0.0f)
			{
				bPlusZ = false;
			}
			else
			{
				bPlusZ = true;
			}
			fDistance = sqrtf(fLengthX + fLengthZ);

			//オブジェクトに当たったとき
			if (fDistance <= fRadius + g_enemy[nCntEnemy].fRadius)
			{
				//押しのける
				g_enemy[nCntEnemy].pos.x += move.x / 10.0f;
				g_enemy[nCntEnemy].pos.z += move.z / 10.0f;
				fLengthX = sqrtf(fLengthX);
				fLengthZ = sqrtf(fLengthZ);
				fshort = (fRadius + g_enemy[nCntEnemy].fRadius) / fDistance - 1.0f;
				fLengthX *= fshort;
				fLengthZ *= fshort;
				if (bPlusX == true)
				{
					pPos->x += fLengthX;
				}
				else
				{
					pPos->x -= fLengthX;
				}
				if (bPlusZ == true)
				{
					pPos->z += fLengthZ;
				}
				else
				{
					pPos->z -= fLengthZ;
				}
			}
		}
	}
}

//敵の数取得
int EnemyNum(void)
{
	int nEnemy = 0;
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使用中の敵がいたらカウントアップ
		if (g_enemy[nCntEnemy].bUse == true)
		{
			nEnemy++;
		}
	}
	return nEnemy;
}

//ボスのHP割合取得
float BossHPRate(int nCntEnemy)
{
	float fRate;
	if (g_enemy[nCntEnemy].nHP > 0)
	{
		fRate = (float)g_enemy[nCntEnemy].nHP / (float)g_enemy[nCntEnemy].nMaxHP;
	}
	else
	{
		fRate = 0.0f;
	}
	return fRate;
}