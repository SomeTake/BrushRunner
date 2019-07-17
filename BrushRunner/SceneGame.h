//=============================================================================
//
// ゲーム画面処理 [SceneGame.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

#include "Scene.h"

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
class SceneGame :
	public Scene
{
private:
	std::vector<_2dobj*> UIObject;			// UI
	Map		*pMap;							// マップ
	Player	*pPlayer[PLAYER_MAX];			// プレイヤー
	QUADTREE *Quadtree = nullptr;			// 四分木
	EffectManager *pEffectManager;			// 2Dエフェクト管理
	Sky		*pSky;							// 空
	int		startframe;						// 開始カウントダウン
	bool	result;							// 終了フラグ

	void Start();
	void Collision();
	void CheckResult();
	void InsertResult(int pNo);

	void Debug();

public:
	SceneGame();
	~SceneGame();
	void Update(int SceneID);
	void Draw();

};

int *GetResultRank(int no);					// 順位結果を取得

#endif
