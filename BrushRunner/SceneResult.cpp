//=============================================================================
//
// ゲーム画面処理 [SceneGame.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneResult.h"
#include "Result.h"
#include "Input.h"
#include "SceneGame.h"
#include "Player.h"
#include "DebugWindow.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "ResultRank.h"
#include "ResultTimer.h"
#include "Podium.h"
#include "Trophy.h"

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
SceneResult::SceneResult()
{
	data = SceneGame::GetResultData(0);

	// 2Dオブジェクトのインスタンスを作成
	p2dObj.push_back(new RESULT());
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++, data++)
	{
		p2dObj.push_back(new ResultRank(data->rank));
		p2dObj.push_back(new ResultTimer(data->time, data->rank));
	}

	// 3Dモデルのインスタンス作成
	anim.push_back(new Podium());
	anim.push_back(new Trophy());
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneResult::~SceneResult()
{
	// 2Dオブジェクトの削除
	for (auto &Obj : p2dObj)
	{
		SAFE_DELETE(Obj);
	}
	p2dObj.clear();
	ReleaseVector(p2dObj);

	// 3Dオブジェクトの削除
	for (auto &Anim : anim)
	{
		SAFE_DELETE(Anim);
	}
	anim.clear();
	ReleaseVector(anim);
}

//=============================================================================
// 更新
//=============================================================================
void SceneResult::Update(int SceneID)
{
	// シーンチェンジ
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(i, BUTTON_C))
		{
			SetScene(new SceneTitle(), nSceneTitle);
			return;
		}
	}

	// 2Dオブジェクトの更新
	for (auto &Obj : p2dObj)
	{
		Obj->Update();
	}

	// 3Dオブジェクトの更新
	for (auto &Anim : anim)
	{
		Anim->Update();
	}

	Debug();
}

//=============================================================================
// 描画
//=============================================================================
void SceneResult::Draw()
{
	// 3Dオブジェクトの描画
	for (auto &Anim : anim)
	{
		Anim->Draw();
	}

	// 2Dオブジェクトの描画
	for (auto &Obj : p2dObj)
	{
		Obj->Draw();
	}
}

//=============================================================================
// デバッグ
//=============================================================================
void SceneResult::Debug()
{
#ifndef _DEBUG_
	BeginDebugWindow("Result");

	DebugText("No1:%d No2:%d No3:%d No4:%d", data[0].rank, data[1].rank, data[2].rank, data[3].rank);
	DebugText("ResultTime\nNo1:%d No2:%d No3:%d No4:%d", data[0].time, data[1].time, data[2].time, data[3].time);

	EndDebugWindow("Result");

#endif
}