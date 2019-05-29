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

enum {
	HitEffect,
	Hit1Effect,
	RunEffect,
	ExpEffect,
	ItemEffect,

	// エフェクトの個数
	EffectMax,
};
#include "Player.h"
#include "Collision.h"
#include "Gravity.h"
#include "Input.h"

//2d obj
#include "_2dobj.h"
#include "Frame01.h"
#include "Faceframe.h"
#include "blackinkline.h"
#include "colorinkline.h"
#include "Ink.h"
#include "Cursor.h"


// オブジェクトのポインタ
static _2dobj *p2dobj[_2dMax];			// 2Dオブジェクト用のポインタ
MAP *pMap;
EFFECT *pEFFECT[EffectMax];
PLAYER *pPlayer[PLAYER_MAX];

static int Draw2dobjBuff[_2dMax];			// UIの描画順を変更するための配列

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitSceneGame()
{
	// プレイヤーの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i] = new PLAYER(i);
	}

	// マップの初期化
	pMap = new MAP();

	// 2DUIの初期化
	// フレーム
	p2dobj[NumFrame] = new FRAME();

	// カラーインクの初期化
	p2dobj[NumInkblue] = new INK(pPlayer[0], INKLINEBLUE_POS, TEXTURE_INKLINEBLUE, ColorInk);
	p2dobj[NumInkred] = new INK(pPlayer[1], INKLINERED_POS, TEXTURE_INKLINERED, ColorInk);
	p2dobj[NumInkyellow] = new INK(pPlayer[2], INKLINEYELLOW_POS, TEXTURE_INKLINEYELLOW, ColorInk);
	p2dobj[NumInkgreen] = new INK(pPlayer[3], INKLINEGREEN_POS, TEXTURE_INKLINEGREEN, ColorInk);

	// カラーインク用フレームの初期化
	p2dobj[NumColorFrame00] = new INKFRAME(COLORINKFRAME_POS01, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorFrame01] = new INKFRAME(COLORINKFRAME_POS02, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorFrame02] = new INKFRAME(COLORINKFRAME_POS03, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorFrame03] = new INKFRAME(COLORINKFRAME_POS04, TEXTURE_COLORINKFRAME);

	// 顔を表示するフレームの初期化
	p2dobj[NumFaceframe00] = new FACEFRAME(FACEFRAME_POS01);
	p2dobj[NumFaceframe01] = new FACEFRAME(FACEFRAME_POS02);
	p2dobj[NumFaceframe02] = new FACEFRAME(FACEFRAME_POS03);
	p2dobj[NumFaceframe03] = new FACEFRAME(FACEFRAME_POS04);

	// 黒インクの初期化
	p2dobj[NumInkblack00] = new INK(pPlayer[0], INKLINEBLACK_POS01, TEXTURE_INKLINEBLACK, BlackInk);
	p2dobj[NumInkblack01] = new INK(pPlayer[1], INKLINEBLACK_POS02, TEXTURE_INKLINEBLACK, BlackInk);
	p2dobj[NumInkblack02] = new INK(pPlayer[2], INKLINEBLACK_POS03, TEXTURE_INKLINEBLACK, BlackInk);
	p2dobj[NumInkblack03] = new INK(pPlayer[3], INKLINEBLACK_POS04, TEXTURE_INKLINEBLACK, BlackInk);
	
	// エフェクトの初期化
	pEFFECT[HitEffect] = new EFFECT(EFFECT_TEXTURE0, EFFECT0_SIZE, EFFET0_POS, TIME_ANIMATION_EFFECT0, EFFECT_PATTERN_X, EFFECT_PATTERN_Y);
	pEFFECT[Hit1Effect] = new EFFECT(EFFECT_TEXTURE1, EFFECT1_SIZE, EFFET1_POS, TIME_ANIMATION_EFFECT1, EFFECT1_PATTERN_X, EFFECT1_PATTERN_Y);
	pEFFECT[RunEffect] = new EFFECT(EFFECT_TEXTURE2, EFFECT2_SIZE, EFFET2_POS, TIME_ANIMATION_EFFECT2, EFFECT2_PATTERN_X, EFFECT2_PATTERN_Y);
	pEFFECT[ExpEffect] = new EFFECT(EFFECT_TEXTURE3, EFFECT3_SIZE, EFFET3_POS, TIME_ANIMATION_EFFECT3, EFFECT3_PATTERN_X, EFFECT3_PATTERN_Y);
	pEFFECT[ItemEffect] = new EFFECT(EFFECT_TEXTURE4, EFFECT4_SIZE, EFFET4_POS, TIME_ANIMATION_EFFECT4, EFFECT4_PATTERN_X, EFFECT4_PATTERN_Y);

	// カーソルの初期化
	for (int i = Cursor0; i < Cursor0 + PLAYER_MAX; i++)
	{
		p2dobj[i] = new CURSOR(i - Cursor0, pPlayer[i - Cursor0]);
	}

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
	delete pMap;
	for (int i = 0; i < EffectMax; i++)
	{
		delete pEFFECT[i];
	}

	// プレイヤーの削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		delete pPlayer[i];
	}

	// 2Dオブジェクトの削除
	for (int i = 0; i < _2dMax; i++)
	{
		delete p2dobj[i];
	}

}

//=============================================================================
// 更新
//=============================================================================
void UpdateSceneGame()
{
	// カメラの更新
	UpdateCamera();

	// 2Dオブジェクトの更新
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[i]->Update();
	}

	// マップの更新
	pMap->Update();
	for (int i = 0; i < EffectMax; i++)
	{
		pEFFECT[i]->Update();
	}

	// プレイヤーの更新
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();

		// 地面に接しているか確認
		if (HitCheckPToM(pPlayer[i], pMap))
		{
			pPlayer[i]->SetJumpFlag(false);
		}
		// 地面に接していないので、落下する
		else
		{
			GravityFall(pPlayer[i]);
		}
	}

#ifndef _DEBUG_

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

	// 2Dオブジェクトの描画
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[Draw2dobjBuff[i]]->Draw();
	}

	// エフェクトの描画
	for (int i = 0; i < EffectMax; i++)
	{
		pEFFECT[i]->Draw();

		for (int i = 0; i < PLAYER_MAX; i++)
		{
			pPlayer[i]->Draw();
		}
	}
}
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
