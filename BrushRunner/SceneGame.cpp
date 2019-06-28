//=============================================================================
//
// ゲーム画面処理 [SceneGame.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "Debugproc.h"
#include "Map.h"
#include "Camera.h"
#include "_2dobj.h"
#include "Effect.h"
#include "Quadtree.h"

#include "Player.h"
#include "Collision.h"
#include "Input.h"
#include "MyLibrary.h"

//2d obj
#include "_2dobj.h"
#include "Frame01.h"
#include "Faceframe.h"
#include "InkFrameColor.h"
#include "InkFrameBlack.h"
#include "Ink.h"
#include "Cursor.h"
#include "CountDown.h"

#include "PaintSystem.h"
#include "Pop.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// エフェクトの種類
enum {
	HitEffect,
	Hit1Effect,
	RunEffect,
	ExpEffect,
	ItemEffect,

	// エフェクトの個数
	EffectMax,
};

// プレイヤー初期位置
D3DXVECTOR3 firstpos[PLAYER_MAX] = {
	D3DXVECTOR3(45.0f, 0.0f, 0.0f),
	D3DXVECTOR3(30.0f, 0.0f, 0.0f),
	D3DXVECTOR3(15.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
};

//*****************************************************************************
// オブジェクトのポインタ
//*****************************************************************************
static _2dobj *p2dobj[_2dMax];				// 2Dオブジェクト用のポインタ
static Map *pMap;							// マップ用のポインタ
static Effect *pEffect[EffectMax];			// エフェクト用のポインタ
static Player *pPlayer[PLAYER_MAX];			// プレイヤー用のポインタ
static Cursor *pCursor[PLAYER_MAX];			// カーソル用のポインタ
static PaintManager *pPManager[PLAYER_MAX];	// ペイントシステム用のポインタ
static Pop *pPop[PLAYER_MAX];				// ポップアップ用のポインタ
static QUADTREE *Quadtree = nullptr;

static int Draw2dobjBuff[_2dMax];			// UIの描画順を変更するための配列

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitSceneGame()
{
	// プレイヤーの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i] = new Player(i, firstpos[i]);
	}

	// マップの初期化
	pMap = new Map();

	// 四分木の初期化
	Quadtree = new QUADTREE(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	// 2DUIの初期化
	// フレーム
	p2dobj[NumFrame] = new Frame();

	// 黒インクの初期化
	p2dobj[NumInkblack00] = new Ink(pPlayer[0], INKLINEBLACK_POS01, TEXTURE_INKGAUGEBLACK, BlackInk);
	p2dobj[NumInkblack01] = new Ink(pPlayer[1], INKLINEBLACK_POS02, TEXTURE_INKGAUGEBLACK, BlackInk);
	p2dobj[NumInkblack02] = new Ink(pPlayer[2], INKLINEBLACK_POS03, TEXTURE_INKGAUGEBLACK, BlackInk);
	p2dobj[NumInkblack03] = new Ink(pPlayer[3], INKLINEBLACK_POS04, TEXTURE_INKGAUGEBLACK, BlackInk);

	// 黒インク用フレームの初期化
	p2dobj[NumBlackFrame00] = new InkFrameBlack(BLACKINKFRAME_POS01);
	p2dobj[NumBlackFrame01] = new InkFrameBlack(BLACKINKFRAME_POS02);
	p2dobj[NumBlackFrame02] = new InkFrameBlack(BLACKINKFRAME_POS03);
	p2dobj[NumBlackFrame03] = new InkFrameBlack(BLACKINKFRAME_POS04);

	// カラーインクの初期化
	p2dobj[NumInkblue] = new Ink(pPlayer[0], INKLINEBLUE_POS, TEXTURE_INKGAUGERED, ColorInk);
	p2dobj[NumInkred] = new Ink(pPlayer[1], INKLINERED_POS, TEXTURE_INKGAUGEBLUE, ColorInk);
	p2dobj[NumInkyellow] = new Ink(pPlayer[2], INKLINEYELLOW_POS, TEXTURE_INKGAUGEYELLOW, ColorInk);
	p2dobj[NumInkgreen] = new Ink(pPlayer[3], INKLINEGREEN_POS, TEXTURE_INKGAUGEGREEN, ColorInk);

	// カラーインク用フレームの初期化
	p2dobj[NumColorFrame00] = new InkFrameColor(COLORINKFRAME_POS01);
	p2dobj[NumColorFrame01] = new InkFrameColor(COLORINKFRAME_POS02);
	p2dobj[NumColorFrame02] = new InkFrameColor(COLORINKFRAME_POS03);
	p2dobj[NumColorFrame03] = new InkFrameColor(COLORINKFRAME_POS04);

	// 顔を表示するフレームの初期化
	p2dobj[NumFaceframe00] = new FaceFrame(FACEFRAME_POS01);
	p2dobj[NumFaceframe01] = new FaceFrame(FACEFRAME_POS02);
	p2dobj[NumFaceframe02] = new FaceFrame(FACEFRAME_POS03);
	p2dobj[NumFaceframe03] = new FaceFrame(FACEFRAME_POS04);

	// カウントダウンの初期化
	p2dobj[NumCountDown] = new CountDown();

	// カーソルの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pCursor[i] = new Cursor(i, pPlayer[i]);
	}

	// ペイントシステムの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPManager[i] = new PaintManager(pCursor[i], pPlayer[i], Quadtree);
	}

	// ポップアップの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPop[i] = new Pop(pPlayer[i]);
	}

	// エフェクトの初期化
	pEffect[HitEffect] = new Effect(EFFECT_TEXTURE0, EFFECT0_SIZE, EFFET0_POS, TIME_ANIMATION_EFFECT0, EFFECT_PATTERN_X, EFFECT_PATTERN_Y);
	pEffect[Hit1Effect] = new Effect(EFFECT_TEXTURE1, EFFECT1_SIZE, EFFET1_POS, TIME_ANIMATION_EFFECT1, EFFECT1_PATTERN_X, EFFECT1_PATTERN_Y);
	pEffect[RunEffect] = new Effect(EFFECT_TEXTURE2, EFFECT2_SIZE, EFFET2_POS, TIME_ANIMATION_EFFECT2, EFFECT2_PATTERN_X, EFFECT2_PATTERN_Y);
	pEffect[ExpEffect] = new Effect(EFFECT_TEXTURE3, EFFECT3_SIZE, EFFET3_POS, TIME_ANIMATION_EFFECT3, EFFECT3_PATTERN_X, EFFECT3_PATTERN_Y);
	pEffect[ItemEffect] = new Effect(EFFECT_TEXTURE4, EFFECT4_SIZE, EFFET4_POS, TIME_ANIMATION_EFFECT4, EFFECT4_PATTERN_X, EFFECT4_PATTERN_Y);

	// 描画順の初期化
	for (int i = 0; i < _2dMax; i++)
	{
		Draw2dobjBuff[i] = i;
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void UninitSceneGame()
{
	// マップの削除
	SAFE_DELETE(pMap);

	// 四分木の削除
	SAFE_DELETE(Quadtree);

	// ペイントテクスチャの削除
	Paint::ReleaseTexture();

	// エフェクトの削除
	for (int i = 0; i < EffectMax; i++)
	{
		SAFE_DELETE(pEffect[i]);
	}

	// プレイヤーの削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		SAFE_DELETE(pPlayer[i]);
	}

	// 2Dオブジェクトの削除
	for (int i = 0; i < _2dMax; i++)
	{
		SAFE_DELETE(p2dobj[i]);
	}

	// カーソルの削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		SAFE_DELETE(pCursor[i]);
	}

	// ペイントシステムの削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		SAFE_DELETE(pPManager[i]);
	}

	// ポップアップ削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		SAFE_DELETE(pPop[i]);
	}
}

//=============================================================================
// 更新
//=============================================================================
void UpdateSceneGame()
{
	static int startframe = 0;

	// スタートタイマー更新
	if (startframe < START_FRAME)
	{
		startframe++;
	}
	if (startframe == START_FRAME)
	{
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			pPlayer[i]->SetPlayable(true);
		}
	}

	// プレイヤー座標の中でXが最も大きいものをカメラ注視点とする
	std::vector<float> vec(PLAYER_MAX);
	for (size_t i = 0; i < vec.size(); i++)
	{
		vec[i] = pPlayer[i]->GetPos().x;
	}
	auto max = std::max_element(vec.begin(), vec.end());
	size_t maxIdx = std::distance(vec.begin(), max);

	// カメラの更新
	UpdateCamera(pPlayer[(int)maxIdx]->GetPos());

	// 2Dオブジェクトの更新
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[i]->Update();
	}

	// カーソルの更新
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pCursor[i]->Update();
	}

	// ペイントシステムの更新
	static bool PressMode = false;

	if (GetKeyboardTrigger(DIK_F1))
	{
		PressMode = PressMode ? false : true;
	}

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPManager[i]->Update(PressMode);
	}

	// マップの更新
	pMap->Update();

	// エフェクトの更新
	for (int i = 0; i < EffectMax; i++)
	{
		pEffect[i]->Update();
	}

	// プレイヤーの更新
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();
	}

	// ポップアップの更新
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPop[i]->Update();
	}

	// 当たり判定の更新
	CollisionSceneGame();

#ifndef _DEBUG_
	if (PressMode)
	{
		PrintDebugProc("Paint Mode：Press\n");
	}
	else
	{
		PrintDebugProc("Paint Mode：Trigger\n");
	}
#endif
}

//=============================================================================
// 描画
//=============================================================================
void DrawSceneGame()
{
	// マップの描画
	pMap->Draw();

	// プレイヤーの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}

	// カーソルの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pCursor[i]->Draw();
	}

	// ポップアップの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPop[i]->Draw();
	}

	// 2Dオブジェクトの描画
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[Draw2dobjBuff[i]]->Draw();
	}

	// ペイントシステムの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPManager[i]->Draw();
	}

	// エフェクトの描画
	for (int i = 0; i < EffectMax; i++)
	{
		pEffect[i]->Draw();
	}
}

//=============================================================================
// 当たり判定の更新
//=============================================================================
void CollisionSceneGame()
{

	// プレイヤーとマップの当たり判定
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Collision(pMap);
	}

	// プレイヤーとペイントシステムの当たり判定
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Collision(pPManager[i]);
	}

	// ペイントシステム同士の当たり判定
	for (int TenDigit = 1; TenDigit <= 4; TenDigit++)
	{
		for (int OneDigit = 1; OneDigit <= 4; OneDigit++)
		{
			// 画面を16分割、それぞれのオブジェクトを判定する
			HitCheckSToS(Quadtree, (TenDigit * 10 + OneDigit));
		}
	}

	// 四分木を更新する
	Quadtree->Update();

}

//=============================================================================
// 2Dオブジェクトの描画順を取得
//=============================================================================
int GetDraw2dobjBuff(int _num)
{
	return Draw2dobjBuff[_num];
}

//=============================================================================
// 2Dオブジェクトの描画順をセット
//=============================================================================
void SetDraw2dobjBuff(int _BuffNum, int _DrawNum)
{
	Draw2dobjBuff[_BuffNum] = _DrawNum;
}

//=============================================================================
// 描画順を入れ替える
//=============================================================================
void ChangeDrawOrder(int _NumA, int _NumB)
{
	int change = GetDraw2dobjBuff(_NumA);
	SetDraw2dobjBuff(_NumA, GetDraw2dobjBuff(_NumB));
	SetDraw2dobjBuff(_NumB, change);

}
