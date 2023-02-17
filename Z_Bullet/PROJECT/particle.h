//---------------------------
//Author:三上航世
//パーティクル処理(particle.h)
//---------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitParticle(void);	//初期化
void UninitParticle(void);	//終了
void UpdateParticle(void);	//更新
void DrawParticle(void);	//描画
void SetParticle(D3DXVECTOR3 pos, float fHeight);	//設定
void ResetParticle(void);	//リセット
#endif _PARTICLE_H_