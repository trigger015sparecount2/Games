//---------------------------
//Author:�O��q��
//�`���[�g���A��(tutorial.cpp)
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

//����������
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

//�I������
void CTutorial::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CTutorial::Update()
{
	//�|�[�Y���ĂȂ�
	if (CManager::GetPause() == false)
	{
		//�����ꍇ
		if (m_nMaxPattern > 0)
		{
			//��莞�Ԏ~�߂�
			if (m_nStopTime > 0)
			{
				m_nStopTime--;
			}
			//�~�ߏI������
			else
			{
				//�ړ�������
				D3DXVECTOR3 pos = GetPos();
				pos.x += m_Pattern[m_nCntPattern].move.x;
				pos.y += m_Pattern[m_nCntPattern].move.y;

				//�ړ��J�E���g
				if (m_nTime < m_Pattern[m_nCntPattern].nMaxTime)
				{
					m_nTime++;
				}
				//���E�܂ňړ�
				else
				{
					//�ړ��p�^�[���ύX�A�J�E���g���Z�b�g
					m_nCntPattern++;
					m_nTime = 0;
					m_nStopTime = 8;

					//�ړ��p�^�[��������ɂȂ�A���Z�b�g
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

//�`�揈��
void CTutorial::Draw()
{
	CPlane::Draw();
}

//�쐬
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