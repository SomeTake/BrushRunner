//=============================================================================
//
// ステージ名表示 [StageName.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _STAGENAME_H_
#define _STAGENAME_H_

#include "_2dobj.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class StageName :
	public _2dobj
{
private:
	void MakeVertex();

public:
	StageName();
	~StageName();

	void Update()override;
	void Draw()override;
};

#endif
