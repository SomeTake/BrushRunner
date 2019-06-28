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
#include "Effect.h"
#include "Quadtree.h"
#include "Player.h"
#include "PaintSystem.h"
#include "Pop.h"

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
// クラス定義
//*****************************************************************************
class SceneGame
{
private:
	_2dobj *p2dobj[_2dMax];				// 2Dオブジェクト用のポインタ
	Map *pMap;							// マップ用のポインタ
	Effect *pEffect[EffectMax];			// エフェクト用のポインタ
	Player *pPlayer[PLAYER_MAX];			// プレイヤー用のポインタ
	Cursor *pCursor[PLAYER_MAX];			// カーソル用のポインタ
	PaintManager *pPManager[PLAYER_MAX];	// ペイントシステム用のポインタ
	Pop *pPop[PLAYER_MAX];				// ポップアップ用のポインタ
	QUADTREE *Quadtree = nullptr;

	void Collision();

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

};

int GetDraw2dobjBuff(int _num);						// 2Dオブジェクトの描画順を取得
void SetDraw2dobjBuff(int _BuffNum, int _DrawNum);	// 2Dオブジェクトの描画順をセット
void ChangeDrawOrder(int _NumA, int _NumB);			// 描画順を入れ替える


#endif
