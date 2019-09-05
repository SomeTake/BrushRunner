//=============================================================================
//
// リザルト画面でのタイマー表示 [ResultTimer.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _RESULTTIMER_H_
#define  RESULTTIMER_H_

#include "Timer.h"
#include "ResultDigit.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultTimer :
	public Timer
{
private:
	ResultDigit*		time[DIGIT_MAX];	// それぞれの桁を表示するオブジェクトのポインタ
	int					Rank;				// ランク
	static LPD3DXFONT	Font[2];			// テキスト用フォント

public:
	ResultTimer(DWORD _time, int _rank);
	~ResultTimer();

	void Update()override;
	void Draw()override;
};

#endif
