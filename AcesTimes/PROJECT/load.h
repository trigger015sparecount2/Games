//=============================================================================
// �I���Ǘ�[select.h]
// Author : �O��q��
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "manager.h"
#include "scene.h"
#include "player.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;
class CKeyboard;
class CUI;

class CLoad : public CScene
{
	typedef enum
	{
		TEXTTYPE_NONE = 0,
		TEXTTYPE_LOAD,
		TEXTTYPE_NODATA,
		TEXTTYPE_MAX
	} TEXTTYPE;


public:
	CLoad(PRIORITY Priority);
	~CLoad();

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

	static CLoad *Create();	//�쐬

private:
	void Select(int nAdd);				//�I�����ύX
	void Load();						//�ŏ��̊e�f�[�^�̓ǂݍ���
	HRESULT DataLoad();					//�f�[�^�ǂݍ���(���̃f�[�^��ǂݍ��񂾃f�[�^�ɂ���)
	void TextChange(TEXTTYPE Texttype);	//���͕ύX

	CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	CGamePad *m_pGamePad;	//�Q�[���p�b�h
	CUI *m_pUI[30];			//UI
	bool m_aData[3];		//�f�[�^�����݂��Ă邩
	int m_nMoney[3];		//�e�f�[�^�̋�
	int m_nNumAircraft[3];	//�e�f�[�^�̐퓬�@�̐�
	int m_nTexAircraft[6];	//�e�퓬�@�̃e�N�X�`��
	bool m_aAircraft[6][3];	//�e�f�[�^�̐퓬�@���g���邩
	char m_Str[256];		//���̐�������
	int m_nSelect;			//���I��ł邩
	LPD3DXFONT m_pFont[4];	//�e����
	bool m_bLoad;			//���[�h���邩
	int m_nCntChange;		//���͕ς��Ă��牽�t���[���o������
	int m_nClear[3];		//�f�[�^�̕��͂̓����x
};

#endif // _TITLE_H_
