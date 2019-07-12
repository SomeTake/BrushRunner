//=============================================================================
//
// ゲーム画面処理 [SceneGame.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

// ポインタとして取得する必要のあるクラス
#include "Map.h"
#include "_2dobj.h"
#include "Quadtree.h"
#include "Player.h"
#include "PaintManager.h"
#include "EffectManager.h"

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

	// アイテム表示
	NumItem00,
	NumItem01,
	NumItem02,
	NumItem03,

	// ----- 最大数 -----
	_2dMax,
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneGame
{
private:
	std::vector<_2dobj*> UIObject;			// UI
	Map		*pMap;							// マップ
	Player	*pPlayer[PLAYER_MAX];			// プレイヤー
	QUADTREE *Quadtree = nullptr;			// 四分木
	EffectManager *pEffectManager;			// 2Dエフェクト管理

	void Collision();

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

};

#endif
