//---------------------------
//Author:三上航世
//敵（階層構造あり）(enemy.h)
//---------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//敵の種類
typedef enum
{
	ENEMYTYPE_BIRD = 0,
	ENEMYTYPE_DOG,
	ENEMYTYPE_ZOMBE,
	ENEMYTYPE_SPIDER,
	ENEMYTYPE_MAX
} Enemytype;

//プロトタイプ宣言
HRESULT InitEnemy(void);	//初期化
void UninitEnemy(void);		//終了
void UpdateEnemy(void);		//更新
void DrawEnemy(void);		//描画
void CoillisionEnemy(float fRadius, D3DXVECTOR3 *pPos, D3DXVECTOR3 move);	//敵との当たり判定
bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, D3DXVECTOR3 Clash, int nDamage, int nDamageTime);	//ダメージとの当たり判定
float EnemyPos(int nRot, int nCntEnemy);				//敵の場所
int RockOn(D3DXVECTOR3 pos, float fRotY);				//どのロックオンするか
float RockBullet(D3DXVECTOR3 pos, int nCntEnemy);		//ロックオン中の弾の動き
void SetEnemy(D3DXVECTOR3 pos, Enemytype enemyType);	//敵設定
void ResetEnemy(void);	//リセット
int EnemyNum(void);		//敵の数
#endif _ENEMY_H_