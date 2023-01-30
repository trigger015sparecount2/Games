//=============================================================================
//
// 弾丸処理 [bullet.cpp]
// Author : 三上航世
//
//=============================================================================
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "enemy.h"
#include "player.h"
#include "pauseui.h"
#include "keyboard.h"

CBullet::CBullet(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CBullet::~CBullet(void)
{

}

//初期化
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, bool bEnemy)
{
	CScene2D::Init(pos);
	SetSize(D3DXVECTOR2(26.0f, 26.0f));
	SetSizeRot(0.08f);
	AddRot(-rot.y);
	m_move = D3DXVECTOR3(sinf(rot.y * D3DX_PI) * fSpeed, cosf(rot.y * D3DX_PI) * -fSpeed, 0.0f);
	m_bEnemy = bEnemy;
	m_bSlow = false;
	return S_OK;
}

//終了
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//更新
void CBullet::Update(void)
{
	//ポーズ中じゃない
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		//移動。爆弾に当たっていたら、遅くする
		if (m_bSlow == true)
		{
			pos += m_move * 0.01f;
		}
		else
		{
			pos += m_move;
		}
		SetPos(pos);
		Set();
		m_bSlow = CollisionBomb(pos);
		//画面外にいったら消す
		if (pos.y < -GetSize().y || SCREEN_HEIGHT + GetSize().y < pos.y || pos.x < -GetSize().x || SCREEN_WIDTH + GetSize().x < pos.x)
		{
			SetDeath(true);
		}
	}
}

//描画
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//爆弾との当たり判定
bool CBullet::CollisionBomb(D3DXVECTOR3 pos)
{
	if (m_bEnemy == true)
	{
		CScene *pScene;
		CScene *pSceneNext;
		pScene = GetScene(PRIORITY_EFFECT);
		while (pScene)
		{
			pSceneNext = pScene->GetNext();
			//爆弾だったら
			if (pScene->GetObjType() == OBJECTTYPE_BOMB)
			{
				D3DXVECTOR3 BombPos = pScene->GetPos();
				D3DXVECTOR3 BombSize = pScene->GetSize() * 0.65f;
				D3DXVECTOR3 BulletSize = GetSize();
				D3DXVECTOR3 Relpos;
				Relpos = pos - BombPos;
				float fRotY = GetRot().y;
				D3DXVECTOR3 TransPos;
				//回転座標
				TransPos.x = cosf(fRotY * D3DX_PI) * Relpos.x + sinf(fRotY * D3DX_PI) * Relpos.y;
				TransPos.y = -sinf(fRotY * D3DX_PI) * Relpos.x + cosf(fRotY * D3DX_PI) * Relpos.y;
				//大雑把に当たってる
				if (BulletSize.x * sinf(-0.12f * D3DX_PI) <= TransPos.x + BombSize.x && TransPos.x - BombSize.x <= BulletSize.x * sinf(0.12f * D3DX_PI) &&
					BulletSize.y * cosf(0.88f * D3DX_PI) <= TransPos.y + BombSize.y && TransPos.y - BombSize.y <= BulletSize.y * cosf(0.12f * D3DX_PI))
				{
					float fDistance;
					//細かく見ていって当たっているか(最初2つは四角、そのあと角の円)
					if (BulletSize.x * sinf(-0.12f * D3DX_PI) <= TransPos.x + BombSize.x && TransPos.x - BombSize.x <= BulletSize.x * sinf(0.12f * D3DX_PI) &&
						BulletSize.y * cosf(0.88f * D3DX_PI) <= TransPos.y && TransPos.y <= BulletSize.y * cosf(0.12f * D3DX_PI))
					{
						return true;
					}
					if (BulletSize.x * sinf(-0.12f * D3DX_PI) <= TransPos.x && TransPos.x <= BulletSize.x * sinf(0.12f * D3DX_PI) &&
						BulletSize.y * cosf(0.88f * D3DX_PI) <= TransPos.y + BombSize.y && TransPos.y - BombSize.y <= BulletSize.y * cosf(0.12f * D3DX_PI))
					{
						return true;
					}
					fDistance = sqrtf(powf(BulletSize.x * sinf(-0.12f * D3DX_PI) - TransPos.x, 2.0f) + powf(BulletSize.y * cosf(-0.12f * D3DX_PI) - TransPos.y, 2.0f));
					if (fDistance <= BombSize.x)
					{
						return true;
					}
					fDistance = sqrtf(powf(BulletSize.x * sinf(0.12f * D3DX_PI) - TransPos.x, 2.0f) + powf(BulletSize.y * cosf(0.12f * D3DX_PI) - TransPos.y, 2.0f));
					if (fDistance <= BombSize.x)
					{
						return true;
					}
					fDistance = sqrtf(powf(BulletSize.x * sinf(0.88f * D3DX_PI) - TransPos.x, 2.0f) + powf(BulletSize.y * cosf(0.88f * D3DX_PI) - TransPos.y, 2.0f));
					if (fDistance <= BombSize.x)
					{
						return true;
					}
					fDistance = sqrtf(powf(BulletSize.x * sinf(-0.88f * D3DX_PI) - TransPos.x, 2.0f) + powf(BulletSize.y * cosf(-0.88f * D3DX_PI) - TransPos.y, 2.0f));
					if (fDistance <= BombSize.x)
					{
						return true;
					}
				}
			}
			pScene = pSceneNext;
		}
	}
	return false;
}

//作成
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, bool bEnemy)
{
	CBullet *pBullet;
	pBullet = new CBullet(CScene::PRIORITY_BULLET);
	if (pBullet != NULL)
	{
		pBullet->Init(pos, rot, fSpeed, bEnemy);
		if (bEnemy == true)
		{
			pBullet->SetTexture(48);
		}
		else
		{
			pBullet->SetTexture(2);
		}
	}
	return pBullet;
}