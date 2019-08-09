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
#include "PaintGroup.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_FRAME (240)	// スタートするまでのタイマー


//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneGame
{
private:
	std::vector<_2dobj*> UIObject;
	Map *pMap;							// マップ用のポインタ
	Effect *pEffect[EffectMax];			// エフェクト用のポインタ
	Player *pPlayer[PLAYER_MAX];			// プレイヤー用のポインタ
	QUADTREE *Quadtree = nullptr;
	PaintGroup *paintGroup = nullptr;

	void Collision();

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

};

#endif
