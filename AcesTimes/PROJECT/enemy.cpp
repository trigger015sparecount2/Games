//=============================================================================
//
// �G���� [enemy.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "enemy.h"
#include "bullet.h"
#include "renderer.h"
#include "ui.h"
#include "pauseui.h"
#include "shadow.h"
#include "sound.h"
#include "explosion.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
//int CEnemy::m_nEnemy = 0;

CEnemy::CEnemy(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{
	//m_nEnemy++;
}

CEnemy::~CEnemy(void)
{
	//m_nEnemy--;
}

//������
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float fRotY, float fInterval, float fSpeed, D3DXVECTOR2 size, int nShadowTex, int nHP, float fBulletMax, int nMoney, int nScore, float fBulletSpeed, int nBulletType)
{
	CScene2D::Init(pos);
	CScene2D::SetSize(size);
	CScene2D::AddRot(fRotY);
	m_fRot = fRotY;
	CScene2D::Set();
	m_fSpeed = fSpeed;
	m_nHP = nHP;
	m_fBullet = fInterval;
	m_fBulletMax = fBulletMax;
	m_nMoney = nMoney;
	m_nScore = nScore;
	m_bSlow = false;
	m_nBulletType = nBulletType;
	m_fBulletSpeed = fBulletSpeed;
	m_pShadow = CShadow::Create(D3DXVECTOR3(size.x * 0.6f, size.y * 0.6f, 0.0f), D3DXVECTOR3(pos.x + 80.0f, pos.y + 80.0f, 0.0f), nShadowTex);
	m_pShadow->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pShadow->AddRot(fRotY);
	m_pShadow->Set();
	return S_OK;
}

//�I��
void CEnemy::Uninit(void)
{
	if (m_pShadow != NULL)
	{
		m_pShadow->SetDeath(true);
		m_pShadow = NULL;
	}
	CScene2D::Uninit();
}

//�X�V
void CEnemy::Update(void)
{
	//�|�[�Y������Ȃ�
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos = GetPos();

		//�_���[�W������ď��������Ԃ��Ȃ�A���̐F�ɖ߂�
		if (m_nDamageTime > 0)
		{
			m_nDamageTime--;
			if (m_nDamageTime <= 0)
			{
				ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//�J�E���g�i�߂�
		if (m_fBullet > 0.0f)
		{
			//���e�ɓ������Ă�����J�E���g��i�߂�̂�x������
			if (m_bSlow == true)
			{
				m_fBullet -= 0.01f;
			}
			else
			{
				m_fBullet -= 1.0f;
			}

			//�J�E���g���i�񂾂�e�������ăJ�E���g���Z�b�g����
			if (m_fBullet <= 0.0f)
			{
				m_fBullet = m_fBulletMax;
				Shot(pos);
			}
		}

		//�ړ�(���e�ɓ������Ă�����x������)
		if (m_bSlow == true)
		{
			move = SlowMove();
		}
		else
		{
			move = Move();
		}
		pos += move;

		//�e�A���e�̓����蔻��
		CollisionBullet(pos);
		m_bSlow = CollisionBomb(pos);

		//�e�܂߂ďꏊ�̐ݒ�
		SetPos(pos);
		m_pShadow->SetPos(D3DXVECTOR3(pos.x + 80.0f, pos.y + 80.0f, 0.0f));
		m_pShadow->Set();
		Set();

		//��ʊO�ɂ����������
		if (pos.x < -GetSize().x * 2.0f || SCREEN_WIDTH + GetSize().x * 2.0f < pos.x ||
			pos.y < -GetSize().y * 2.0f || SCREEN_HEIGHT + GetSize().y * 2.0f < pos.y)
		{
			SetDeath(true);
		}
	}
}

//�`��
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, int nTexType, int nShadowTex, float fRotY, float fInterval, float fSpeed, D3DXVECTOR2 size, int nHP, float fBulletMax, int nMoney, int nScore, float fBulletSpeed, int nBulletType)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy(PRIORITY_CHARA);
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, fRotY, fInterval, fSpeed, size, nShadowTex, nHP, fBulletMax, nMoney, nScore, fBulletSpeed, nBulletType);
		pEnemy->SetTexture(nTexType);
	}
	return pEnemy;
}

//�ړ�
D3DXVECTOR3 CEnemy::Move()
{
	D3DXVECTOR3 move;
	move.x = -m_fSpeed * sinf(m_fRot * D3DX_PI);
	move.y = -m_fSpeed * cosf(m_fRot * D3DX_PI);
	return move;
}

//�x���ړ�
D3DXVECTOR3 CEnemy::SlowMove()
{
	D3DXVECTOR3 move;
	move.x = -m_fSpeed * sinf(m_fRot * D3DX_PI) * 0.01f;
	move.y = -m_fSpeed * cosf(m_fRot * D3DX_PI) * 0.01f;
	return move;
}

//����
void CEnemy::Shot(D3DXVECTOR3 pos)
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
			D3DXVECTOR3 PlayerPos = pScene->GetPos();
			float fRotY = atan2f(PlayerPos.x - pos.x, pos.y - PlayerPos.y);

			//�v���C���[�̕����Ɍ����Č���
			fRotY /= D3DX_PI;
			switch (m_nBulletType)
			{
			case 0:
				CBullet::Create(pos, D3DXVECTOR3(0.0f, fRotY, 0.0f), m_fBulletSpeed, true);
				break;
			case 1:
				CBullet::Create(pos, D3DXVECTOR3(0.0f, fRotY + 0.15f, 0.0f), m_fBulletSpeed, true);
				CBullet::Create(pos, D3DXVECTOR3(0.0f, fRotY - 0.15f, 0.0f), m_fBulletSpeed, true);
				break;
			case 2:
				CBullet::Create(pos, D3DXVECTOR3(0.0f, fRotY + 0.2f, 0.0f), m_fBulletSpeed, true);
				CBullet::Create(pos, D3DXVECTOR3(0.0f, fRotY, 0.0f), m_fBulletSpeed, true);
				CBullet::Create(pos, D3DXVECTOR3(0.0f, fRotY - 0.2f, 0.0f), m_fBulletSpeed, true);
				break;
			default:
				break;
			}
			CSound::Play(CSound::SOUND_LABEL_GUN);
			break;
		}
		pScene = pSceneNext;
	}
}

//�e�Ƃ̓����蔻��
void CEnemy::CollisionBullet(D3DXVECTOR3 pos)
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
			if (pScene->GetEnemy() == false)
			{
				//�G�̂���Ȃ�������
				D3DXVECTOR3 BulletPos = pScene->GetPos();
				D3DXVECTOR3 BulletSize = pScene->GetSize();
				D3DXVECTOR3 EnemySize = GetSize() * 0.65f;
				D3DXVECTOR3 Relpos;
				Relpos = pos - BulletPos;
				float fRotY = pScene->GetRot().y;
				D3DXVECTOR3 TransPos;
				//��]���W
				TransPos.x = cosf(fRotY * D3DX_PI) * Relpos.x + sinf(fRotY * D3DX_PI) * Relpos.y;
				TransPos.y = -sinf(fRotY * D3DX_PI) * Relpos.x + cosf(fRotY * D3DX_PI) * Relpos.y;
				//�������Ă�����
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

//���e�Ƃ̓����蔻��
bool CEnemy::CollisionBomb(D3DXVECTOR3 pos)
{
	CScene *pScene;
	CScene *pSceneNext;
	pScene = GetScene(PRIORITY_EFFECT);
	while (pScene)
	{
		pSceneNext = pScene->GetNext();
		//���e��������
		if (pScene->GetObjType() == OBJECTTYPE_BOMB)
		{
			D3DXVECTOR3 BombPos = pScene->GetPos();
			float fRadius = pScene->GetSize().x * sinf(0.25f * D3DX_PI) - 20.0f;
			float fEnemyRadius = GetSize().x * sinf(0.25f * D3DX_PI);
			float fDistance = sqrtf(powf(BombPos.x - pos.x, 2.0f) + powf(BombPos.y - pos.y, 2.0f));
			//�������Ă�����
			if (fDistance <= fRadius + fEnemyRadius)
			{
				return true;
			}
		}
		pScene = pSceneNext;
	}
	return false;
}

//�_���[�W����
void CEnemy::Damage(int nDamage)
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
				//�X�R�A���Z
				pScene->AddScore(m_nScore);
				break;
			}
		}
		//�����G�t�F�N�g�쐬�A���ǉ��A���ĉ�����
		CExplosion::Create(GetPos(), 50.0f, 4);
		CManager::AddMoney(m_nMoney);
		SetDeath(true);
		CSound::Play(CSound::SOUND_LABEL_ENEMYSHATDOWN);
	}
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
				//�X�R�A���Z(��������)
				pScene->AddScore(m_nScore / 50);
				break;
			}
		}
		//���������Ԃ�����A������
		m_nDamageTime = 5;
		ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		CSound::Play(CSound::SOUND_LABEL_ENEMYDAMAGE);
	}
}