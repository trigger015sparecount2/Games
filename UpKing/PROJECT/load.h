//=============================================================================
//
// ���[�h���� [load.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "main.h"

class CLoad
{
public:
	CLoad();
	~CLoad();
	static void Load(const char *aFileName);		//�ǂݍ���
	static void SoundLoad(const char *aFileName);	//�����ǂݍ���
	static void RankLoad(const char *aFileName);	//�����L���O�ǂݍ���
private:
};

#endif