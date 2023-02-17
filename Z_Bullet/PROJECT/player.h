//---------------------------
//Author:三上航世
//プレイヤー(player.h)
//---------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitPlayer(void);	//初期化
void UninitPlayer(void);	//終了
void UpdatePlayer(void);	//更新
void DrawPlayer(void);		//描画

D3DXVECTOR3 PlayerPos(void);		//プレイヤーの場所
float PlayerRot(void);				//プレイヤーの向き
float ClashRot(D3DXVECTOR3 pos);	//吹き飛ぶ方向
D3DXVECTOR3 PlayerGetMove(void);	//プレイヤーの移動量
float GetPlayerHeight(void);		//プレイヤーの身長
float GetPlayerRadius(void);		//プレイヤーの半径
float PlayerRotDesh(void);			//プレイヤーの目的の向き
bool TargetRockon(void);			//ロックオンしてるか
int NumParts(void);					//パーツ数
D3DXMATRIX CollisionPlayerPos(int nCntParts);	//プレイヤーの当たり判定
float PlayerLookEnemy(void);			//プレイヤーから見た敵の方向
void ScoreAdd(int nScore);				//スコア加算
float PlayerDistance(D3DXVECTOR3 pos);	//プレイヤーの距離
void PlayerDamage(int nDamage, int nDamageTime, D3DXVECTOR3 Clash, float fRot);	//プレイヤーがダメージ食らった
bool PlayerDamage(D3DXVECTOR3 pos, float fRadius);	//プレイヤーがダメージ食らうか
float PlayerClashRot(D3DXVECTOR3 pos);	//プレイヤーが吹き飛ぶ方向
void ResetPlayer(void);		//リセット
void AddItem(void);			//アイテム加算
int PlayerScore(void);		//スコア取得
bool GetPlayerDie(void);	//プレイヤーがやられたか
#endif _PLAYER_H_