//=============================================================================
//
// �V�[������ [scene.h]
// Author : �O��q��
//
//=============================================================================
#include "scene.h"
#include "Game.h"

//�ÓI�����o�ϐ�
CScene *CScene::m_pTop[PRIORITY] = {};
CScene *CScene::m_pCur[PRIORITY] = {};
int CScene::m_nNumAll = 0;
//bool CScene::m_bKey = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nPriority = nPriority;

	m_pNext[m_nPriority] = NULL;
	m_bDeath = false;
	if (m_pTop[m_nPriority] == NULL && m_pCur[m_nPriority] == NULL)
	{
		m_pPrev[m_nPriority] = NULL;
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
	}
	else if (m_pCur != NULL)
	{
		m_pCur[m_nPriority]->m_pNext[m_nPriority] = this;
		m_pPrev[m_nPriority] = m_pCur[m_nPriority];
		m_pCur[m_nPriority] = this;
	}
	m_nNumAll++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	//�G�t�F�N�g�ɕs����������ď���Ɏ����̂�ɕς��܂����A���܂�
	int Priority = m_nPriority;

	//�����Ώۂ�Top�ł���Cur�������ꍇ
	if (this == m_pTop[Priority] &&
		this == m_pCur[Priority])
	{
		m_pTop[Priority] = NULL;
		m_pNext[Priority] = NULL;
		m_pCur[Priority] = NULL;
		m_pPrev[Priority] = NULL;
	}
	//�����Ώۂ�Top
	else if (this == m_pTop[Priority])
	{
		m_pTop[Priority] = m_pNext[Priority];
		m_pPrev[Priority] = NULL;
		m_pNext[Priority]->m_pPrev[Priority] = NULL;
	}
	//�����Ώۂ�Cur
	else if (this == m_pCur[Priority])
	{
		m_pCur[Priority] = m_pPrev[Priority];
		m_pNext[Priority] = NULL;
		m_pPrev[Priority]->m_pNext[Priority] = NULL;
	}
	//����ȊO
	else
	{
		m_pNext[Priority]->m_pPrev[Priority] = m_pPrev[Priority];
		m_pPrev[Priority]->m_pNext[Priority] = m_pNext[Priority];
	}
}

//�S����
void CScene::ReleaseAll()
{
	//�`�揈�����𔻕�
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext[nCntPriority];
			pScene->Uninit();
			pScene = pSceneNext;
		}
	}
}

//�S���X�V
void CScene::UpdateAll()
{
	//CManager::MODE Mode = CManager::GetMode();

	//�`�揈�����𔻕�
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		//m_bKey = false;
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext[nCntPriority];
			pScene->Update();
			if (pScene->m_bDeath == true)
			{
				pScene->Uninit();
			}
			pScene = pSceneNext;
		}
	}
}

//�S���`��
void CScene::DrawAll()
{
	//�`�揈�����𔻕�
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{

		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext[nCntPriority];
			pScene->Draw();
			pScene = pSceneNext;
		}
	}
}

//�����[�X
void CScene::Release()
{
	delete this;
	m_nNumAll--;
}