//---------------------------
//Author:三上航世
//チュートリアル(tutorial.cpp)
//---------------------------
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"

CTutorial::CTutorial(PRIORITY Priority) : CPlane::CPlane(Priority)
{

}

CTutorial::~CTutorial()
{

}

//初期化処理
HRESULT CTutorial::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, CTutorial::Pattern Pattern[6], int nLoop, int nMaxPattern)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f), false);
	int nCntPattern;
	for (nCntPattern = 0; nCntPattern < nMaxPattern; nCntPattern++)
	{
		m_Pattern[nCntPattern] = Pattern[nCntPattern];
	}
	m_nLoop = nLoop;
	m_nMaxPattern = nMaxPattern;
	m_nCntPattern = 0;
	m_nStopTime = 0;
	return S_OK;
}

//終了処理
void CTutorial::Uninit()
{
	CPlane::Uninit();
}

//更新処理
void CTutorial::Update()
{
	//ポーズしてない
	if (CManager::GetPause() == false)
	{
		//動く場合
		if (m_nMaxPattern > 0)
		{
			//一定時間止める
			if (m_nStopTime > 0)
			{
				m_nStopTime--;
			}
			//止め終えたら
			else
			{
				//移動させる
				D3DXVECTOR3 pos = GetPos();
				pos.x += m_Pattern[m_nCntPattern].move.x;
				pos.y += m_Pattern[m_nCntPattern].move.y;

				//移動カウント
				if (m_nTime < m_Pattern[m_nCntPattern].nMaxTime)
				{
					m_nTime++;
				}
				//限界まで移動
				else
				{
					//移動パターン変更、カウントリセット
					m_nCntPattern++;
					m_nTime = 0;
					m_nStopTime = 8;

					//移動パターンが上限になる、リセット
					if (m_nCntPattern >= m_nMaxPattern)
					{
						m_nCntPattern = m_nLoop;
					}
				}
				SetPos(pos);
			}
		}
	}
}

//描画処理
void CTutorial::Draw()
{
	CPlane::Draw();
}

//作成
CTutorial *CTutorial::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, CTutorial::Pattern aPattern[6], int nLoop, int nMaxPattern, int nTex)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial(PRIORITY_PLANE);
	if (pTutorial != NULL)
	{
		pTutorial->Init(size, pos, aPattern, nLoop, nMaxPattern);
		pTutorial->SetTexture(nTex);
	}
	return pTutorial;
}