//=============================================================================
//
// ランナー [Runner.cpp]
// Author : HAL東京 GP12B332 19 染谷武志
//
//=============================================================================
#ifndef _RUNNER_H_
#define _RUNNER_H_

#include "_2dobj.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Runner :
	public _2dobj
{
private:
	void MakeVertex();
	void SetVertex();

public:
	Runner();
	~Runner();

	void Update()override;
	void Draw()override;
};

#endif
