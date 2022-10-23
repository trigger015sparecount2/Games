//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "boss.h"
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"
#include "ui.h"
#include "pauseui.h"
#include "shadow.h"
#include "fade.h"
#include "sound.h"
#include "prize.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBoss::m_pTexture = NULL;

CBoss::CBoss(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CBoss::~CBoss(void)
{

}

HRESULT CBoss::Init(void)
{
	CScene2D::Init(BOSS_SIZE, BOSS_SIZE, D3DXVECTOR3(SCREEN_WIDTH / 2, -BOSS_SIZE, 0.0f), 1.0f);
	CScene2D::SetObjType(CScene::OBJTYPE_ENEMY);
	m_pShadowScene = CShadow::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 60.0f, -BOSS_SIZE + 60.0f, 0.0f), BOSS_SIZE / 2, BOSS_SIZE / 2, CShadow::SHADOW_RAFALE);
	m_move = D3DXVECTOR3(2.5f, 1.8f, 0.0f);
	m_nBullet = 0;
	m_nBulletInter = 160;
	m_nHP = 600;
	m_nScore = 1000;
	m_fScale = 1.0f;
	m_nDTime = 0;
	m_nType = 3;
	m_nSlide = 0;
	m_nCycle = 0;
	m_nBTime = 0;
	m_bSlide = true;
	m_bDrop = true;
	m_bUninit = false;
	m_bLeft = true;
	return S_OK;
}

void CBoss::Uninit(void)
{
	CScene2D::Uninit();
}

void CBoss::Update(void)
{
	if (CPauseUi::GetPause() == false)
	{
		if (m_bUninit == false)
		{
			D3DXVECTOR3 pos;
			pos = GetPos();
			if (m_bDrop == true)
			{
				pos.y += 2.0f;
				if (pos.y > 100.0f)
				{
					m_bDrop = false;
				}
			}
			else
			{
				if (m_nHP > 0)
				{
					//�e����
					m_nBullet++;
					if (m_nBulletInter <= m_nBullet)
					{
						Shot(pos);
					}

					//��e������
					if (m_nDamageTime > 0)
					{
						m_nDamageTime--;
						if (m_nDamageTime <= 0)
						{
							ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						}
					}

					//�ړ�����
					Move(pos);
					pos += m_move;
				}
				else
				{
					m_fScale -= 0.001f;
					m_nSlide++;
					if (m_nSlide <= 0)
					{
						if (m_bSlide == true)
						{
							pos.x += 3.0f;
							m_bSlide = false;
						}
						else
						{
							pos.x -= 3.0f;
							m_bSlide = true;
						}
						m_nSlide = 0;
					}

					m_nDTime++;
					if (m_nDTime >= 10)
					{
						float fWidth;
						float fHeight;
						fWidth = (rand() % (int)BOSS_SIZE * 2) - BOSS_SIZE;
						fHeight = (rand() % (int)BOSS_SIZE * 2) - BOSS_SIZE;
						D3DXVECTOR3 Expos;
						Expos.x = pos.x + fWidth;
						Expos.y = pos.y + fHeight;
						CExplosion::Create(Expos);
						m_nDTime = 0;
					}

					if (m_nDamageTime <= 0)
					{
						pos.y += 2.0f;
						if (pos.y > SCREEN_HEIGHT)
						{
							CFade::SetFade(CManager::MODE_RESULT);
						}
					}
					else
					{
						m_nDamageTime--;
					}
				}
			}

			Set(BOSS_SIZE * m_fScale, BOSS_SIZE * m_fScale, pos);
			m_pShadowScene->Set(BOSS_SIZE / 2.0f * m_fScale, BOSS_SIZE / 2.0f * m_fScale, D3DXVECTOR3(pos.x + 60.0f * m_fScale, pos.y + 60.0f * m_fScale, 0.0f));
		}
		else
		{
			m_pShadowScene->Uninit();
			m_pShadowScene = NULL;
			Uninit();
		}
	}
}

void CBoss::Draw(void)
{
	CScene2D::Draw();
}

CBoss *CBoss::Create(void)
{
	CBoss *pBoss;
	pBoss = new CBoss(PRIORITY_CHARA);
	if (pBoss != NULL)
	{
		pBoss->Init();
		pBoss->BindTexture(m_pTexture);
	}
	return pBoss;
}

HRESULT CBoss::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RAFALE.png",
		&m_pTexture);
	return S_OK;
}

void CBoss::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CBoss::Damage(int nDamage)
{
	m_nHP -= nDamage;
	if (m_nHP <= 0)
	{
		//���Ď�����
		D3DXVECTOR3 pos;
		pos = GetPos();
		//UI�֘A
		CUi::SetKill();
		CUi::SetScore(m_nScore * 100);
		CSound::Play(CSound::SOUND_LABEL_SHATDOWNBGM);
		m_nDamageTime = 60;
		ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_nDamageTime = 5;
		CUi::SetScore(m_nScore * nDamage);
		ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		CSound::Play(CSound::SOUND_LABEL_ENEMYDAMAGE);
	}
}

bool CBoss::GetDamage(void)
{
	if (m_nHP <= 0)
	{
		return false;
	}
	return true;
}

void CBoss::Shot(D3DXVECTOR3 pos)
{
	if (m_nCycle <= 0)
	{
		m_nType = rand() % 4;
		switch (m_nType)
		{
		case 0:
			m_nCycle = 2;
			m_nBTime = 3;
			break;
		case 1:
			m_nCycle = 3;
			m_nBTime = 15;
			break;
		case 2:
			m_nCycle = 1;
			m_nBTime = 0;
			break;
		case 3:
			m_nCycle = 3;
			m_nBTime = 50;
			break;
		default:
			break;
		}
	}
	if (m_nBTime > 0)
	{
		m_nBTime--;
	}
	if (m_nBTime <= 0)
	{
		switch (m_nType)
		{
		case 0:
			//��
			if (m_bLeft == true)
			{
				CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(2.0f + m_nCntBullet * (1.0f / 7.0f)), -3.0f * cosf(2.0f + m_nCntBullet * (1.0f / 7.0f)), 0.0f), true, CScene::ELEMENT_FIRE);
			}
			else
			{
				CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(-2.0f - m_nCntBullet * (1.0f / 7.0f)), -3.0f * cosf(-2.0f - m_nCntBullet * (1.0f / 7.0f)), 0.0f), true, CScene::ELEMENT_FIRE);
			}
			m_nCntBullet++;
			m_nBTime = 3;
			if (m_nCntBullet > 10)
			{
				if (m_bLeft == true)
				{
					m_bLeft = false;
				}
				else
				{
					m_bLeft = true;
					m_nCycle--;
				}
				m_nCntBullet = 0;
			}
			break;
		case 1:
			//�X
			m_fRotY = SearchPlayer(pos);
			CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(m_fRotY + 0.2f * D3DX_PI), -3.0f * cosf(m_fRotY + 0.2f * D3DX_PI), 0.0f), true, CScene::ELEMENT_ICE);
			CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(m_fRotY + 0.1f * D3DX_PI), -3.0f * cosf(m_fRotY + 0.1f * D3DX_PI), 0.0f), true, CScene::ELEMENT_ICE);
			CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(m_fRotY), -3.0f * cosf(m_fRotY), 0.0f), true, CScene::ELEMENT_ICE);
			CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(m_fRotY - 0.1f * D3DX_PI), -3.0f * cosf(m_fRotY - 0.1f * D3DX_PI), 0.0f), true, CScene::ELEMENT_ICE);
			CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(m_fRotY - 0.2f * D3DX_PI), -3.0f * cosf(m_fRotY - 0.2f * D3DX_PI), 0.0f), true, CScene::ELEMENT_ICE);
			m_nCycle--;
			m_nBTime = 15;
			break;
		case 2:
			//��
			int nCntBullet;
			for (nCntBullet = 0; nCntBullet < 40; nCntBullet++)
			{
				CBullet::Create(pos, D3DXVECTOR3(2.5f * sinf(m_fRotY + nCntBullet * (1.0f / 20.0f) * D3DX_PI), -2.5f * cosf(m_fRotY + nCntBullet * (1.0f / 20.0f) * D3DX_PI), 0.0f), true, CScene::ELEMENT_THUNDER);
			}
			m_nCycle--;
			break;
		case 3:
			//��
			m_fRotY = SearchPlayer(pos);
			if (m_nCycle == 1)
			{
				CBullet::Create(pos, D3DXVECTOR3(10.0f * sinf(m_fRotY), -10.0f * cosf(m_fRotY), 0.0f), true, CScene::ELEMENT_WATER);
			}
			else
			{
				CBullet::Create(pos, D3DXVECTOR3(6.0f * sinf(m_fRotY), -6.0f * cosf(m_fRotY), 0.0f), true, CScene::ELEMENT_WATER);
			}
			m_nCycle--;
			if (m_nCycle == 1)
			{
				m_nBTime = 100;
			}
			else
			{
				m_nBTime = 50;
			}
			break;
		default:
			break;
		}
		if (m_nCycle <= 0)
		{
			m_nBullet = 0;
		}
		CSound::Play(CSound::SOUND_LABEL_GUN);
	}
}

void CBoss::Move(D3DXVECTOR3 pos)
{
	if (pos.x < BOSS_SIZE * sinf(0.25f * D3DX_PI))
	{
		m_move.x = 2.5f;
	}
	else if (SCREEN_WIDTH - BOSS_SIZE * sinf(0.25f * D3DX_PI) < pos.x)
	{
		m_move.x = -2.5f;
	}
	if (pos.y < BOSS_SIZE * cosf(0.25f * D3DX_PI))
	{
		m_move.y = 1.8f;
	}
	else if (200.0f < pos.y)
	{
		m_move.y = -1.8f;
	}
}

float CBoss::SearchPlayer(D3DXVECTOR3 pos)
{
	float fRotY;
	int nCntScene;
	for (nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		pScene = GetScene(PRIORITY_CHARA, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType;
			objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer;
				posPlayer = pScene->GetPos();
				fRotY = atan2f(posPlayer.x - pos.x, pos.y - posPlayer.y);
				return fRotY;
			}
		}
	}
	return 0.0f;
}