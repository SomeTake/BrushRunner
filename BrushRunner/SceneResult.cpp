//=============================================================================
//
// ゲーム画面処理 [SceneGame.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneResult.h"
#include "_2dobj.h"
#include "Result.h"
#include "Input.h"
#include "SceneGame.h"
#include "Player.h"
#include "DebugWindow.h"
#include "SceneManager.h"

//=============================================================================
// グローバル変数
//=============================================================================
enum
{
	ResultBG,
	UIMax,										// UI表示の最大数
};

static _2dobj *p2dObj[UIMax];					// 2Dオブジェクト用のポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
SceneResult::SceneResult()
{
	ResultRank = GetResultRank(0);

	p2dObj[ResultBG] = new RESULT(RESULT_POS01, RESULT_SIZE01, TEXTURE_RESULT01);
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneResult::~SceneResult()
{
	for (int i = 0; i < UIMax; i++)
	{
		delete p2dObj[i];
	}

}

//=============================================================================
// 更新
//=============================================================================
void SceneResult::Update()
{
	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Update();

	}
	Debug();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(i, BUTTON_C))
		{
			SetScene(nSceneTitle);
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneResult::Draw()
{
	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Draw();
	}

}

//=============================================================================
// デバッグ
//=============================================================================
void SceneResult::Debug()
{
#ifndef _DEBUG_
	BeginDebugWindow("Result");

	DebugText("No1:%d No2:%d No3:%d No4:%d", ResultRank[0], ResultRank[1], ResultRank[2], ResultRank[3]);

	EndDebugWindow("Result");

#endif
}