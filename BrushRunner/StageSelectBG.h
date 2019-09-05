//=============================================================================
//
// ステージセレクト画面の背景 [StageSelectBG.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _STAGESELECTBG_H_
#define _STAGESELECTBG_H_

#include "_2dobj.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class StageSelectBG :
	public _2dobj
{
private:
	void MakeVertex();
	void SetTexture();
	void SetVertex();

	static int PatternAnim;

public:
	StageSelectBG();
	~StageSelectBG();

	void Update()override;
	void Draw()override;

	static int GetStageSelect() { return PatternAnim; };
};

#endif
