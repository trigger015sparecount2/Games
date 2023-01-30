//=============================================================================
//
//�{�X�p�[�c���� [bossparts.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "bossparts.h"
#include "bullet.h"
#include "renderer.h"
#include "ui.h"
#include "pauseui.h"
#include "shadow.h"
#include "sound.h"
#include "explosion.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

CBossParts::CBossParts(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CBossParts::~CBossParts(void)
{

}

//������
HRESULT CBossParts::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nFireTex, int nHP, int nMoney, int nScore)
{
	CScene2D::Init(pos);
	CScene2D::SetSize(size);
	CScene2D::Set();
	m_nHP = nHP;
	m_nMoney = nMoney;
	m_nScore = nScore;
	m_pFire = CShadow::Create(D3DXVECTOR3(50.0f, 80.0f, 0.0f), pos, nFireTex);
	m_pFire->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pFire->Set();
	m_nCntFire = 10;
	m_nCntDeath = 0;
	m_bFire = false;
	return S_OK;
}

//�I��
void CBossParts::Uninit(void)
{
	if (m_pFire != NULL)
	{
		m_pFire->SetDeath(true);
		m_pFire = NULL;
	}
	CScene2D::Uninit();
}

//�X�V
void CBossParts::Update(void)
{
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();

		//�J�E���g�i�񂾂猳�̐F�ɖ߂�
		if (m_nDamageTime > 0)
		{
			m_nDamageTime--;
			if (m_nDamageTime <= 0)
			{
				ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//�܂������Ă�
		if (m_nHP > 0)
		{
			//�e�Ƃ̓����蔻��
			CollisionBullet(pos);

			//�o�b�N�t�@�C�A��召����
			if (m_nCntFire > 0)
			{
				m_nCntFire--;
				if (m_nCntFire <= 0)
				{
					m_nCntFire = 10;
					if (m_bFire == true)
					{
						m_bFire = false;
						m_pFire->SetSize(D3DXVECTOR2(55.0f, 88.0f));
					}
					else
					{
						m_bFire = true;
						m_pFire->SetSize(D3DXVECTOR2(50.0f, 80.0f));
					}
				}
			}

			//�o�b�N�t�@�C�A�ʒu�ݒ�
			if (m_bFire == true)
			{
				m_pFire->SetPos(D3DXVECTOR3(pos.x, pos.y + 92.0f, 0.0f));
			}
			else
			{
				m_pFire->SetPos(D3DXVECTOR3(pos.x, pos.y + 98.0f, 0.0f));
			}
			m_pFire->Set();
		}
		//���ꂽ
		else
		{
			//���J�E���g�������G�t�F�N�g�쐬
			m_nCntDeath++;
			D3DXVECTOR2 size = GetSize();
			if (m_nCntDeath % 8 == 0)
			{
				m_nCntDeath = 0;
				D3DXVECTOR3 ExPos = (D3DXVECTOR3(pos.x + size.x * (((float)(rand() % 100)) - 50.0f) * 0.016f, pos.y + size.y * (((float)(rand() % 100)) - 50.0f) * 0.016f, 0.0f));
				CExplosion::Create(ExPos, 50.0f, 4);
			}
		}
		Set();
	}
}

//�`��
void CBossParts::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CBossParts *CBossParts::Create(D3DXVECTOR3 pos, int nTexType, int nFireTex, D3DXVECTOR2 size, int nHP, int nMoney, int nScore)
{
	CBossParts *pBossParts;
	pBossParts = new CBossParts(PRIORITY_CHARA);
	if (pBossParts != NULL)
	{
		pBossParts->Init(pos, size, nFireTex, nHP, nMoney, nScore);
		pBossParts->SetTexture(nTexType);
	}
	return pBossParts;
}

//�e�Ƃ̓����蔻��
void CBossParts::CollisionBullet(D3DXVECTOR3 pos)
{
	CScene *pScene;
	CScene *pSceneNext;
	pScene = GetScene(PRIORITY_BULLET);
	while (pScene)
	{
		pSceneNext = pScene->GetNext();
		//�e��������
		if (pScene->GetObjType() == OBJECTTYPE_BULLET)
		{
			//�G�̂���Ȃ�������
			if (pScene->GetEnemy() == false)
			{
				D3DXVECTOR3 BulletPos = pScene->GetPos();
				D3DXVECTOR3 BulletSize = pScene->GetSize();
				D3DXVECTOR3 EnemySize = GetSize() * 0.65f;
				D3DXVECTOR3 Relpos;
				Relpos = pos - BulletPos;
				float fRotY = pScene->GetRot().y;
				D3DXVECTOR3 TransPos;
				TransPos.x = cosf(fRotY * D3DX_PI) * Relpos.x + sinf(fRotY * D3DX_PI) * Relpos.y;
				TransPos.y = -sinf(fRotY * D3DX_PI) * Relpos.x + cosf(fRotY * D3DX_PI) * Relpos.y;
				//�������Ă���
				if (BulletSize.x * sinf(-0.12f * D3DX_PI) <= TransPos.x + EnemySize.x * sinf(0.25f * D3DX_PI) && TransPos.x - EnemySize.x * sinf(0.25f * D3DX_PI) <= BulletSize.x * sinf(0.12f * D3DX_PI) &&
					BulletSize.y * cosf(0.88f * D3DX_PI) <= TransPos.y + EnemySize.y * cosf(0.25f * D3DX_PI) && TransPos.y - EnemySize.x * cosf(0.25f * D3DX_PI) <= BulletSize.y * cosf(0.12f * D3DX_PI))
				{
					Damage(1);
					pScene->SetDeath(true);
				}
			}
		}
		pScene = pSceneNext;
	}
}

//�_���[�W����
void CBossParts::Damage(int nDamage)
{
	//�̗͌��炷
	m_nHP -= nDamage;
	//���ꂽ
	if (m_nHP <= 0)
	{
		CScene *pScene;
		CScene *pSceneNext;
		pScene = GetScene(PRIORITY_CHARA);
		while (pScene)
		{
			pSceneNext = pScene->GetNext();
			//�v���C���[��������
			if (pScene->GetObjType() == OBJECTTYPE_PLAYER)
			{
				//�X�R�A�ǉ�
				pScene->AddScore(m_nScore);
				break;
			}
		}

		//�����G�t�F�N�g�쐬�A�����ǉ��A���ĉ�����
		CExplosion::Create(GetPos(), 50.0f, 4);
		CManager::AddMoney(m_nMoney);
		m_bDeath = true;
		CSound::Play(CSound::SOUND_LABEL_ENEMYSHATDOWN);
		m_pFire->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	//�܂������Ă�
	else
	{
		CScene *pScene;
		CScene *pSceneNext;
		pScene = GetScene(PRIORITY_CHARA);
		while (pScene)
		{
			pSceneNext = pScene->GetNext();
			//�v���C���[��������
			if (pScene->GetObjType() == OBJECTTYPE_PLAYER)
			{
				//�X�R�A�ǉ�
				pScene->AddScore(m_nScore / 50);
				break;
			}
		}

		//���������Ԃ�����
		m_nDamageTime = 5;
		ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		CSound::Play(CSound::SOUND_LABEL_ENEMYDAMAGE);
	}
}