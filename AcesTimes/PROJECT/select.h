//=============================================================================
// �I���Ǘ�[select.h]
// Author : �O��q��
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "manager.h"
#include "scene.h"
#include "player.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;
class CKeyboard;
class CUI;

class CSelect : public CScene
{
public:
	//�퓬�@�̏��
	typedef struct
	{
		char aName[16];
		char aNickName[32];
		float fSpeed;
		int nHP;
		CPlayer::SHOTTYPE ShotType;
		int nTexType;
		int nHudTexType;
		int nShadowTex;
		int nMaxSlow;
		int nMaxReturn;
		int nMoney;
		int nExplainLines;
		char aExplain[4][128];
	} Aircraft;

	//�ǂ����I�񂾂�
	typedef enum
	{
		SELECT_NONE = 0,
		SELECT_LEFT,
		SELECT_RIGHT,
		SELECT_MAX
	} SELECT;

	CSelect(PRIORITY Priority);
	~CSelect();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }	//���

	//�g��Ȃ���
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR2 GetSize() { return D3DXVECTOR2(0.0f, 0.0f); }
	float GetSizeRot() { return 0.0f; }
	void Damage(int) { ; }
	int Damage() { return 0; }
	int GetHP() { return 0; }
	int GetMaxHP() { return 0; }
	bool GetEnemy() { return false; }
	void AddScore(int) { ; }
	//�g��Ȃ���

	static CSelect *Create();	//�쐬

	//�퓬�@�̏��擾
	static float GetSpeed() { return m_aAircraft[CManager::GetType()].fSpeed; }
	static int GetSelectHP() { return m_aAircraft[CManager::GetType()].nHP; }
	static CPlayer::SHOTTYPE GetShotType() { return m_aAircraft[CManager::GetType()].ShotType; }
	static int GetTexType() { return m_aAircraft[CManager::GetType()].nTexType; }
	static int GetHudTexType() { return m_aAircraft[CManager::GetType()].nHudTexType; }
	static int GetShadowTexType() { return m_aAircraft[CManager::GetType()].nShadowTex; }
	static int GetMaxSlow() { return m_aAircraft[CManager::GetType()].nMaxSlow; }
	static int GetMaxReturn() { return m_aAircraft[CManager::GetType()].nMaxReturn; }

	static Aircraft m_aAircraft[6];	//�퓬�@�̏��

private:
	void Load();			//�퓬�@�ǂݍ���
	void RankLoad();		//�����L���O�ǂݍ���
	void Select(int nAdd);	//�I�����ύX
	void StageSelect();		//�X�e�[�W�I���J�n
	void StageCancel();		//�X�e�[�W�I������
	void Buy();				//�@�̍w��
	void Text();			//���͕ύX

	CKeyboard *m_pKeyboard;		//�L�[�{�[�h
	CGamePad *m_pGamePad;		//�Q�[���p�b�h
	CUI *m_pUI[4 * 6 + 2 + 5];	//�@��UI
	CUI *m_pStageUI[5 * 3];		//�X�e�[�WUI
	char m_Name[128];			//���O����
	char m_Str[512];			//��������
	int m_nClear;				//�����̓����x
	bool m_bClear;				//�����x�Z�����邩�������邩
	int m_nSelect[2];			//�@�́A�X�e�[�W�ǂ�I��ł邩
	int m_nCntSelect;			//�I�񂾃J�E���g
	int m_nCntGauge;			//�Q�[�W�L�т�J�E���g
	int m_nCntChange;			//���͕ύX�J�E���g
	float m_fStageClear;		//�X�e�[�W�I��UI�����x
	bool m_bBuy;				//�w�����邩
	bool m_bStage;				//�X�e�[�W�I�𒆂�
	int m_nRank[3];				//�e�X�e�[�W�̃����L���O
	LPD3DXFONT m_pFont[4];		//�t�H���g�ւ̃|�C���^
	SELECT m_Select;			//�ǂ����I��������
};

#endif // _TITLE_H_
