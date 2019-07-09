//=============================================================================
//
// ゲーム画面処理 [SceneGame.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "Map.h"
#include "Camera.h"
#include "_2dobj.h"
#include "Effect.h"
#include "Quadtree.h"

#include "Player.h"
#include "Collision.h"
#include "Gravity.h"
#include "Input.h"
#include "MyLibrary.h"

//2d obj
#include "_2dobj.h"
#include "Frame01.h"
#include "Faceframe.h"
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


//*****************************************************************************
// オブジェクトのポインタ
//*****************************************************************************
static std::vector<_2dobj*> UIObject;
static Map		*pMap;							// マップ用のポインタ
static Effect	*pEffect[EffectMax];			// エフェクト用のポインタ
static Player	*pPlayer[PLAYER_MAX];			// プレイヤー用のポインタ
static QUADTREE *Quadtree = nullptr;

//static Pop		*pPop[PLAYER_MAX];				// ポップアップ用のポインタ
//static int Draw2dobjBuff[_2dMax];				// UIの描画順を変更するための配列

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitSceneGame()
{
	// プレイヤーの初期化
	for (int PlayerNo = 0; PlayerNo < PLAYER_MAX; PlayerNo++)
	{
		pPlayer[PlayerNo] = new Player(PlayerNo);
	}

	// マップの初期化
	pMap = new Map();

	// 四分木の初期化
	Quadtree = new QUADTREE(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	PaintManager::SetQuadtreePtr(Quadtree);

	// 2DUIの初期化
	// フレーム
	UIObject.push_back(new Frame());

	// 顔を表示するフレームの初期化
	UIObject.push_back(new FaceFrame(FACEFRAME_POS01));
	UIObject.push_back(new FaceFrame(FACEFRAME_POS02));
	UIObject.push_back(new FaceFrame(FACEFRAME_POS03));
	UIObject.push_back(new FaceFrame(FACEFRAME_POS04));

	// カウントダウンの初期化
	UIObject.push_back(new CountDown());

#if 0
	// ポップアップの初期化
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
	//	pPop[i] = new Pop(pPlayer[i]);
	//}

	// 黒インクの初期化
	//p2dobj[NumInkblack00] = new Ink(pPlayer[0], INKLINEBLACK_POS01, TEXTURE_INKGAUGEBLACK, BlackInk);
	//p2dobj[NumInkblack01] = new Ink(pPlayer[1], INKLINEBLACK_POS02, TEXTURE_INKGAUGEBLACK, BlackInk);
	//p2dobj[NumInkblack02] = new Ink(pPlayer[2], INKLINEBLACK_POS03, TEXTURE_INKGAUGEBLACK, BlackInk);
	//p2dobj[NumInkblack03] = new Ink(pPlayer[3], INKLINEBLACK_POS04, TEXTURE_INKGAUGEBLACK, BlackInk);

	// 黒インク用フレームの初期化
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS01));
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS02));
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS03));
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS04));

	//p2dobj[NumBlackFrame00] = new InkFrameBlack(BLACKINKFRAME_POS01);
	//p2dobj[NumBlackFrame01] = new InkFrameBlack(BLACKINKFRAME_POS02);
	//p2dobj[NumBlackFrame02] = new InkFrameBlack(BLACKINKFRAME_POS03);
	//p2dobj[NumBlackFrame03] = new InkFrameBlack(BLACKINKFRAME_POS04);

	// カラーインクの初期化
	//p2dobj[NumInkblue] = new Ink(pPlayer[0], INKLINEBLUE_POS, TEXTURE_INKGAUGERED, ColorInk);
	//p2dobj[NumInkred] = new Ink(pPlayer[1], INKLINERED_POS, TEXTURE_INKGAUGEBLUE, ColorInk);
	//p2dobj[NumInkyellow] = new Ink(pPlayer[2], INKLINEYELLOW_POS, TEXTURE_INKGAUGEYELLOW, ColorInk);
	//p2dobj[NumInkgreen] = new Ink(pPlayer[3], INKLINEGREEN_POS, TEXTURE_INKGAUGEGREEN, ColorInk);

	// カラーインク用フレームの初期化
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS01));
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS02));
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS03));
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS04));
	//p2dobj[NumColorFrame00] = new InkFrameColor(COLORINKFRAME_POS01);
	//p2dobj[NumColorFrame01] = new InkFrameColor(COLORINKFRAME_POS02);
	//p2dobj[NumColorFrame02] = new InkFrameColor(COLORINKFRAME_POS03);
	//p2dobj[NumColorFrame03] = new InkFrameColor(COLORINKFRAME_POS04);


	//p2dobj[NumFaceframe00] = new FaceFrame(FACEFRAME_POS01);
	//p2dobj[NumFaceframe01] = new FaceFrame(FACEFRAME_POS02);
	//p2dobj[NumFaceframe02] = new FaceFrame(FACEFRAME_POS03);
	//p2dobj[NumFaceframe03] = new FaceFrame(FACEFRAME_POS04);

	// カウントダウンの初期化
	//p2dobj[NumCountDown] = new CountDown();

	// ペイントシステムの初期化
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
	//	pPManager[i] = new PaintManager(pPlayer[i], Quadtree);
	//}

	// エフェクトの初期化
	pEffect[HitEffect] = new Effect(EFFECT_TEXTURE0, EFFECT0_SIZE, EFFET0_POS, TIME_ANIMATION_EFFECT0, EFFECT_PATTERN_X, EFFECT_PATTERN_Y);
	pEffect[Hit1Effect] = new Effect(EFFECT_TEXTURE1, EFFECT1_SIZE, EFFET1_POS, TIME_ANIMATION_EFFECT1, EFFECT1_PATTERN_X, EFFECT1_PATTERN_Y);
	pEffect[RunEffect] = new Effect(EFFECT_TEXTURE2, EFFECT2_SIZE, EFFET2_POS, TIME_ANIMATION_EFFECT2, EFFECT2_PATTERN_X, EFFECT2_PATTERN_Y);
	pEffect[ExpEffect] = new Effect(EFFECT_TEXTURE3, EFFECT3_SIZE, EFFET3_POS, TIME_ANIMATION_EFFECT3, EFFECT3_PATTERN_X, EFFECT3_PATTERN_Y);
	pEffect[ItemEffect] = new Effect(EFFECT_TEXTURE4, EFFECT4_SIZE, EFFET4_POS, TIME_ANIMATION_EFFECT4, EFFECT4_PATTERN_X, EFFECT4_PATTERN_Y);

	// 描画順の初期化
	//for (int i = 0; i < _2dMax; i++)
	//{
	//	Draw2dobjBuff[i] = i;
	//}
#endif

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
	for (auto &Object : UIObject)
	{
		SAFE_DELETE(Object);
	}
	UIObject.clear();
	ReleaseVector(UIObject);

	// ポップアップ削除
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
	//	SAFE_DELETE(pPop[i]);
	//}
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
		vec.at(i) = pPlayer[i]->GetPos().x;
	}
	auto max = std::max_element(vec.begin(), vec.end());
	size_t maxIdx = std::distance(vec.begin(), max);

	// カメラの更新
	UpdateCamera(pPlayer[(int)maxIdx]->GetPos());

	// 2Dオブジェクトの更新
	for (auto &Object : UIObject)
	{
		Object->Update();
	}

	// マップの更新
	pMap->Update();

	// エフェクトの更新
#if 0
	for (int i = 0; i < EffectMax; i++)
	{
		pEffect[i]->Update();
	}
#endif

	// プレイヤーの更新
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();

		bool gravflag = false;

		// 地面に接しているか確認
		if (HitCheckPToM(pPlayer[i], pMap))
		{
			pPlayer[i]->SetJumpFlag(false);
			gravflag = false;
		}
		else
		{
			gravflag = true;
		}
		// ペイントシステムとの当たり判定
		if (pPlayer[i]->GetJumpSpeed() >= 0.0f)
		{
			if (HitCheckPToS(pPlayer[i]))
			{
				pPlayer[i]->SetJumpFlag(false);
				gravflag = false;
			}
			else
			{
				gravflag = true;
			}
		}

		// 重力が有効
		if (gravflag)
		{
			GravityFall(pPlayer[i]);
		}
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

	// ポップアップの更新
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
	//	pPop[i]->Update();
	//}
}

//=============================================================================
// 描画
//=============================================================================
void DrawSceneGame()
{
	// マップの描画
	pMap->Draw();

	// ポップアップの描画
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
	//	pPop[i]->Draw();
	//}

	// 2Dオブジェクトの描画
	for (auto &Object : UIObject)
	{
		Object->Draw();
	}

	// プレイヤーの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}

#if 0
	// エフェクトの描画
	for (int i = 0; i < EffectMax; i++)
	{
		pEffect[i]->Draw();
	}
#endif
}

#if 0
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
void ChangeDrawOrder(int NumA, int NumB)
{
	int Temp = Draw2dobjBuff[NumA];
	Draw2dobjBuff[NumA] = NumB;
	Draw2dobjBuff[NumB] = Temp;
}
#endif
