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
#include "Player.h"
#include "Collision.h"
#include "Gravity.h"

//2d obje
#include "_2dobj.h"
#include "Frame01.h"
#include "Faceframe.h"
#include "blackinkline.h"
#include "colorinkline.h"
enum
{
	NumFrame01,

	NumFaceframe01,
	NumFaceframe02,
	NumFaceframe03,
	NumFaceframe04,


	NumInklineblack01,
	NumInklineblack02,
	NumInklineblack03,
	NumInklineblack04,

	NumInklineblackframe01,
	NumInklineblackframe02,
	NumInklineblackframe03,
	NumInklineblackframe04,

	NumInklineblue,
	NumInklinered,
	NumInklineyellow,
	NumInklinegreen,

	NumColorinkline01,
	NumColorinkline02,
	NumColorinkline03,
	NumColorinkline04,


	// 最大数
	_2dMax,
};


static _2dobj *p2dobj[_2dMax];			// 2Dオブジェクト用のポインタ
// オブジェクトのポインタ
MAP *pMap;
PLAYER *pPlayer[PLAYER_MAX];

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
	p2dobj[NumFrame01] = new Frame01();

	// カラーインクの初期化
	p2dobj[NumInklineblue] = new Colorinkline(INKLINEBLUE_POS, TEXTURE_INKLINEBLUE);
	p2dobj[NumInklinered] = new Colorinkline(INKLINERED_POS, TEXTURE_INKLINERED);
	p2dobj[NumInklineyellow] = new Colorinkline(INKLINEYELLOW_POS, TEXTURE_INKLINEYELLOW);
	p2dobj[NumInklinegreen] = new Colorinkline(INKLINEGREEN_POS, TEXTURE_INKLINEGREEN);

	// カラーインク用フレームの初期化
	p2dobj[NumColorinkline01] = new Colorinkline(COLORINKFRAME_POS01, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline02] = new Colorinkline(COLORINKFRAME_POS02, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline03] = new Colorinkline(COLORINKFRAME_POS03, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline04] = new Colorinkline(COLORINKFRAME_POS04, TEXTURE_COLORINKFRAME);

	// 顔を表示するフレームの初期化
	p2dobj[NumFaceframe01] = new Faceframe(FACEFRAME_POS01);
	p2dobj[NumFaceframe02] = new Faceframe(FACEFRAME_POS02);
	p2dobj[NumFaceframe03] = new Faceframe(FACEFRAME_POS03);
	p2dobj[NumFaceframe04] = new Faceframe(FACEFRAME_POS04);

	// 黒インクの初期化
	p2dobj[NumInklineblack01] = new Colorinkline(INKLINEBLACK_POS01, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack02] = new Colorinkline(INKLINEBLACK_POS02, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack03] = new Colorinkline(INKLINEBLACK_POS03, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack04] = new Colorinkline(INKLINEBLACK_POS04, TEXTURE_INKLINEBLACK);
	
	// 黒インク用フレームの初期化
	p2dobj[NumInklineblackframe01] = new Colorinkline(COLORINKFRAME_POS01, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe02] = new Colorinkline(COLORINKFRAME_POS02, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe03] = new Colorinkline(COLORINKFRAME_POS03, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe04] = new Colorinkline(COLORINKFRAME_POS04, TEXTURE_BLACKINKFRAME);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void UninitSceneGame()
{
	delete pMap;

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

	// 2Dオブジェクトの更新
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[i]->Update();
	}
	UpdateCamera();

	pMap->Update();

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

	// デバッグ表示
#ifndef _DEBUG_

#endif
}

//=============================================================================
// 描画
//=============================================================================
void DrawSceneGame()
{

	// 2Dオブジェクトの描画
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[i]->Draw();
	}

	pMap->Draw();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}
}