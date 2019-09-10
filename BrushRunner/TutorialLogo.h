//=============================================================================
//
// チュートリアル画面のロゴ [TitleLogo.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _TUTORIALLOGO_H_
#define _TUTORIALLOGO_H_

#include "_2dobj.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class TutorialLogo :
	public _2dobj
{
private:
	int cntFlash;
	bool flash;		// 点滅させるフラグ(true = 表示)

	void MakeVertex();

public:
	TutorialLogo();
	~TutorialLogo();

	void Update()override;
	void Draw()override;
};

#endif
