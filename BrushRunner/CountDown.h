//=============================================================================
//
// カウントダウン処理 [CountDown.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _COWNTDOWN_H_
#define _COUNTDOWN_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_COUNTDOWN	("data/TEXTURE/countdown.png")
#define START_TIMER			(240)
#define SECOND_PER_FRAME	(60)
#define COUNTDOWN_SIZE		D3DXVECTOR2(360.0f, 360.0f)
#define COUNTDOWN_DIVIDE_X	(1)
#define COUNTDOWN_DIVIDE_Y	(4)
#define ANIM_COUNTDOWN_DIVIDE (COUNTDOWN_DIVIDE_X * COUNTDOWN_DIVIDE_Y)
#define COUNTDOWN_POS		D3DXVECTOR3(SCREEN_WIDTH / 2 - COUNTDOWN_SIZE.x / 2, SCREEN_HEIGHT / 2 - COUNTDOWN_SIZE.y / 2, 0.0f)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CountDown :
	public _2dobj
{
private:
	int starttimer;
	int startsecond;

public:
	CountDown();
	~CountDown();
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture();
};

#endif
