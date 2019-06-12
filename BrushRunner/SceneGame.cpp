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

#include "Player.h"
#include "Collision.h"
#include "Gravity.h"
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

//*****************************************************************************
// オブジェクトのポインタ
//*****************************************************************************
static _2dobj *p2dobj[_2dMax];				// 2Dオブジェクト用のポインタ
static MAP *pMap;							// マップ用のポインタ
static EFFECT *pEffect[EffectMax];			// エフェクト用のポインタ
static PLAYER *pPlayer[PLAYER_MAX];			// プレイヤー用のポインタ
static CURSOR *pCursor[PLAYER_MAX];			// カーソル用のポインタ
static PAINTSYSTEM *pPSystem[PLAYER_MAX];	// ペイントシステム用のポインタ
static POP *pPop[PLAYER_MAX];				// ポップアップ用のポインタ

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

	// 黒インクの初期化
	p2dobj[NumInkblack00] = new INK(pPlayer[0], INKLINEBLACK_POS01, TEXTURE_INKGAUGEBLACK, BlackInk);
	p2dobj[NumInkblack01] = new INK(pPlayer[1], INKLINEBLACK_POS02, TEXTURE_INKGAUGEBLACK, BlackInk);
	p2dobj[NumInkblack02] = new INK(pPlayer[2], INKLINEBLACK_POS03, TEXTURE_INKGAUGEBLACK, BlackInk);
	p2dobj[NumInkblack03] = new INK(pPlayer[3], INKLINEBLACK_POS04, TEXTURE_INKGAUGEBLACK, BlackInk);

	// 黒インク用フレームの初期化
	p2dobj[NumBlackFrame00] = new INKFRAMEBLACK(BLACKINKFRAME_POS01);
	p2dobj[NumBlackFrame01] = new INKFRAMEBLACK(BLACKINKFRAME_POS02);
	p2dobj[NumBlackFrame02] = new INKFRAMEBLACK(BLACKINKFRAME_POS03);
	p2dobj[NumBlackFrame03] = new INKFRAMEBLACK(BLACKINKFRAME_POS04);

	// カラーインクの初期化
	p2dobj[NumInkblue] = new INK(pPlayer[0], INKLINEBLUE_POS, TEXTURE_INKGAUGERED, ColorInk);
	p2dobj[NumInkred] = new INK(pPlayer[1], INKLINERED_POS, TEXTURE_INKGAUGEBLUE, ColorInk);
	p2dobj[NumInkyellow] = new INK(pPlayer[2], INKLINEYELLOW_POS, TEXTURE_INKGAUGEYELLOW, ColorInk);
	p2dobj[NumInkgreen] = new INK(pPlayer[3], INKLINEGREEN_POS, TEXTURE_INKGAUGEGREEN, ColorInk);

	// カラーインク用フレームの初期化
	p2dobj[NumColorFrame00] = new INKFRAMECOLOR(COLORINKFRAME_POS01);
	p2dobj[NumColorFrame01] = new INKFRAMECOLOR(COLORINKFRAME_POS02);
	p2dobj[NumColorFrame02] = new INKFRAMECOLOR(COLORINKFRAME_POS03);
	p2dobj[NumColorFrame03] = new INKFRAMECOLOR(COLORINKFRAME_POS04);

	// 顔を表示するフレームの初期化
	p2dobj[NumFaceframe00] = new FACEFRAME(FACEFRAME_POS01);
	p2dobj[NumFaceframe01] = new FACEFRAME(FACEFRAME_POS02);
	p2dobj[NumFaceframe02] = new FACEFRAME(FACEFRAME_POS03);
	p2dobj[NumFaceframe03] = new FACEFRAME(FACEFRAME_POS04);
	
	// カウントダウンの初期化
	p2dobj[NumCountDown] = new COUNTDOWN();

	// カーソルの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pCursor[i] = new CURSOR(i, pPlayer[i]);
	}

	// ペイントシステムの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPSystem[i] = new PAINTSYSTEM(pCursor[i], pPlayer[i]);
	}

	// ポップアップの初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPop[i] = new POP(pPlayer[i]);
	}

	// エフェクトの初期化
	pEffect[HitEffect] = new EFFECT(EFFECT_TEXTURE0, EFFECT0_SIZE, EFFET0_POS, TIME_ANIMATION_EFFECT0, EFFECT_PATTERN_X, EFFECT_PATTERN_Y);
	pEffect[Hit1Effect] = new EFFECT(EFFECT_TEXTURE1, EFFECT1_SIZE, EFFET1_POS, TIME_ANIMATION_EFFECT1, EFFECT1_PATTERN_X, EFFECT1_PATTERN_Y);
	pEffect[RunEffect] = new EFFECT(EFFECT_TEXTURE2, EFFECT2_SIZE, EFFET2_POS, TIME_ANIMATION_EFFECT2, EFFECT2_PATTERN_X, EFFECT2_PATTERN_Y);
	pEffect[ExpEffect] = new EFFECT(EFFECT_TEXTURE3, EFFECT3_SIZE, EFFET3_POS, TIME_ANIMATION_EFFECT3, EFFECT3_PATTERN_X, EFFECT3_PATTERN_Y);
	pEffect[ItemEffect] = new EFFECT(EFFECT_TEXTURE4, EFFECT4_SIZE, EFFET4_POS, TIME_ANIMATION_EFFECT4, EFFECT4_PATTERN_X, EFFECT4_PATTERN_Y);

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

	// エフェクトの削除
	for (int i = 0; i < EffectMax; i++)
	{
		delete pEffect[i];
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

	// カーソルの削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		delete pCursor[i];
	}

	// ペイントシステムの削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		delete pPSystem[i];
	}

	// ポップアップ削除
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		delete pPop[i];
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


	// カメラの更新
	UpdateCamera(CompareXPos());

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
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPSystem[i]->Update();
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
			if (HitCheckPToS(pPlayer[i], pPSystem[i]))
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
	for (int nBlack = 0; nBlack < PLAYER_MAX; nBlack++)
	{
		for (int nColor = 0; nColor < PLAYER_MAX; nColor++)
		{
			// 自分が使用しているカラー以外との判定を行う
			if (nBlack != nColor)
			{
				//HitCheckSToS(pPSystem[nBlack], pPSystem[nColor]);
			}
		}
	}

	// ポップアップの更新
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPop[i]->Update();
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

	// カーソルの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pCursor[i]->Draw();
	}

	// 2Dオブジェクトの描画
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[Draw2dobjBuff[i]]->Draw();
	}

	// ペイントシステムの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPSystem[i]->Draw();
	}

	// ポップアップの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPop[i]->Draw();
	}

	// エフェクトの描画
	for (int i = 0; i < EffectMax; i++)
	{
		pEffect[i]->Draw();
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

//=============================================================================
// X座標を比較して、大きい2つの中心座標を返す
//=============================================================================
D3DXVECTOR3 CompareXPos()
{
	float CmpPos[PLAYER_MAX];

	// プレイヤーの座標を格納
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		CmpPos[i] = pPlayer[i]->GetPos().x;
	}

	// QuickSort関数 引数1 比較する配列の先頭要素
	//				 引数2 配列の要素数
	//				 引数3 型のサイズ
	//				 引数4 比較用の関数
	qsort(CmpPos, PLAYER_MAX, sizeof(float), CmpDescendf);

	float CmpY[2];

	// 1つめの要素確定
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (CmpPos[0] == pPlayer[i]->GetPos().x)
		{
			CmpY[0] = pPlayer[i]->GetPos().y;
			break;
		}
	}

	// 2つめの要素確定
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (CmpPos[1] == pPlayer[i]->GetPos().x)
		{
			CmpY[1] = pPlayer[i]->GetPos().y;
			break;
		}
	}

	return D3DXVECTOR3((CmpPos[0] + CmpPos[1]) * 0.5f, (CmpY[0] + CmpY[1]) * 0.5f, 0.0f);
}
