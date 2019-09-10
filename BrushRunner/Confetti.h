//=============================================================================
//
// 紙吹雪 [Confetti.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _CONFETTI_H_
#define _CONFETTI_H_

#include "Billboard.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Confetti :
	public Billboard
{
private:
	bool						use;			// 使用しているかどうか
	int							texNo;			// 使用するテクスチャ番号
	int							moveCnt;		// 動きをつけるタイミング
	HRESULT MakeVertex();

public:
	Confetti();
	~Confetti();

	void Update();
	void Draw();

	bool GetUse() { return use; };

};

#endif
