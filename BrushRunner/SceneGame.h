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
#include "Sky.h"

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
	std::vector<_2dobj*> UIObject;			// UI
	Map		*pMap;							// マップ
	Player	*pPlayer[PLAYER_MAX];			// プレイヤー
	QUADTREE *Quadtree = nullptr;			// 四分木
	EffectManager *pEffectManager;			// 2Dエフェクト管理
	Sky		*pSky;							// 空

	void Collision();

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

};

#endif
