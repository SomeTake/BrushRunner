//=============================================================================
//
// ステージセレクト用カーソル [StageSelectCursor.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _STAGESELECTCURSOR_H_
#define _STAGESELECTCURSOR_H_

#include "_2dobj.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class StageSelectCursor :
	public _2dobj
{
private:
	void MakeVertex();
	void SetVertex();

public:
	StageSelectCursor();
	~StageSelectCursor();

	void Update()override;
	void Draw()override;
};

#endif
