//=============================================================================
//
// 矢印 [Arrow.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

#include "_2dobj.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Arrow :
	public _2dobj
{
private:
	bool reverse;
	bool draw;
	int cntFlash;
	bool flash;		// 点滅させるフラグ(true = 表示)

	void MakeVertex();

public:
	Arrow(bool reverse);
	~Arrow();

	void Update()override;
	void Draw()override;
};

#endif
