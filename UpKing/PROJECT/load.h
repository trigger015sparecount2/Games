//=============================================================================
//
// ロード処理 [load.h]
// Author : 三上航世
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
	static void Load(const char *aFileName);		//読み込み
	static void SoundLoad(const char *aFileName);	//音声読み込み
	static void RankLoad(const char *aFileName);	//ランキング読み込み
private:
};

#endif