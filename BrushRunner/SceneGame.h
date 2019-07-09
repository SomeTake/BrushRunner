//=============================================================================
//
// ゲーム画面処理 [SceneGame.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_FRAME (240)	// スタートするまでのタイマー

// 2dobjの個数(描画順先→後)
enum Num2dobj
{
	// 一番外のフレーム
	NumFrame,

	// 黒インク
	NumInkblack00,
	NumInkblack01,
	NumInkblack02,
	NumInkblack03,

	// 黒インクのフレーム
	NumBlackFrame00,
	NumBlackFrame01,
	NumBlackFrame02,
	NumBlackFrame03,

	// カラーインク
	NumInkblue,
	NumInkred,
	NumInkyellow,
	NumInkgreen,

	// カラーインクのフレーム
	NumColorFrame00,
	NumColorFrame01,
	NumColorFrame02,
	NumColorFrame03,

	// 顔のフレーム
	NumFaceframe00,
	NumFaceframe01,
	NumFaceframe02,
	NumFaceframe03,

	// カウントダウン
	NumCountDown,

	// ----- 最大数 -----
	_2dMax,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSceneGame();
void UninitSceneGame();
void UpdateSceneGame();
void DrawSceneGame();

void ChangeDrawOrder(int NumA, int NumB);			// 描画順を入れ替える

#endif
