//--------------------------
//Author:三上航世
//フェードアウトの処理(fade.cpp)
//--------------------------
#include "fade.h"
#include "game.h"
#include "ui.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//頂点バッファへのポインタ
FADE g_fade;									//フェードの状態
MODE g_modeNext;								//次の画面(モード)
D3DXCOLOR g_colorFade;							//フェードの色
int g_nBlackTime;								//暗くする時間
bool g_bSetMode;								//次のモードに移行するか

//初期化処理
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_bSetMode = true;
	g_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_nBlackTime = 0;
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = GetDevice();     //デバイスを取得する

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/シューティング操作説明.JPG",
		&g_pTextureFade);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx; //頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void **)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
}

//終了処理
void UninitFade(void)
{
	//テクスチャの破棄
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//更新処理
void UpdateFade(void)
{
	//通常じゃない
	if (g_fade != FADE_NONE)
	{
		//フェードイン
		if (g_fade == FADE_IN)
		{
			//色薄くする
			g_colorFade.a -= 0.02f;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		//フェードアウト
		else if (g_fade == FADE_OUT)
		{
			//色濃くする
			g_colorFade.a += 0.02f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_nBlackTime++;

				//一定時間待機
				if (g_nBlackTime >= 180)
				{
					g_nBlackTime = 0;
					g_fade = FADE_IN;
					//モードの設定する
					if (g_bSetMode == true)
					{
						SetMode(g_modeNext);
					}
					//モード切り替えない場合、次のステージに移行
					else
					{
						NextStage();
						NextGame();
					}
				}
			}
		}

		VERTEX_2D *pVtx; //頂点情報へのポインタ
		g_pVtxBuffFade->Lock(0, 0, (void **)&pVtx, 0);
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
		g_pVtxBuffFade->Unlock();
	}
}

//描画処理
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;                    //デバイスのポインタ
	pDevice = GetDevice();                        //デバイスを取得する
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureFade);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //開始する始点のインデックス
		2); //描画するプリミティブ数
}

//フェードの設定処理
void SetFade(MODE modeNext, bool bSetMode)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_bSetMode = bSetMode;
}

//フェードの取得処理
FADE GetFade(void)
{
	return g_fade;
}