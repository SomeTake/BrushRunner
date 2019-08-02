//=============================================================================
//
// ゲーム画面処理 [SceneGame.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "Map.h"
#include "Camera.h"
#include "Collision.h"
#include "Input.h"
#include "DebugWindow.h"
#include "SceneResult.h"

// 2d obj
#include "Frame01.h"
#include "Face.h"
#include "CountDown.h"
#include "Item.h"

// 3d obj
#include "Sky.h"
#include "GoalFlag.h"

//*****************************************************************************
// メンバ変数の初期化
//*****************************************************************************
ResultData SceneGame::data[PLAYER_MAX] = { NULL };		// 結果

//=============================================================================
// コンストラクタ
//=============================================================================
SceneGame::SceneGame()
{
	// ゲームの結果を初期化
	startframe = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		data[i].rank = -1;
		data[i].time = 0;
	}
	result = false;

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

	// アイテム表示の初期化
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		UIObject.push_back(new Item(ItemPos[i], pPlayer[i]));
	}

	// カウントダウンの初期化
	UIObject.push_back(new CountDown());

	// エフェクトマネージャ
	pEffectManager = new EffectManager();

	// 3Dオブジェクト
	object3d.push_back(new Sky());
	object3d.push_back(new GoalFlag());

	// タイマー
	pTimer = new Timer();
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneGame::~SceneGame()
{
	// マップの削除
	SAFE_DELETE(pMap);

	// 四分木の削除
	SAFE_DELETE(Quadtree);

	// ペイントテクスチャの削除
	Paint::ReleaseTexture();

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

	// エフェクトマネージャの削除
	delete pEffectManager;

	// 3Dオブジェクトの削除
	for (auto &Obj3D : object3d)
	{
		SAFE_DELETE(Obj3D);
	}
	object3d.clear();
	ReleaseVector(object3d);

	// タイマーの削除
	delete pTimer;
}

//=============================================================================
// 更新
//=============================================================================
void SceneGame::Update(int SceneID)
{
	// 開始処理
	if (startframe < START_FRAME)
	{
		Start();
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

	// マップの更新
	pMap->Update();

	// プレイヤーの更新
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();
	}

	// 当たり判定の更新
	Collision();

	// 2Dオブジェクトの更新
	for (auto &Object : UIObject)
	{
		Object->Update();
	}

	// エフェクトマネージャの更新
	pEffectManager->Update();

	// 3Dオブジェクトの更新
	for (auto &Obj3D : object3d)
	{
		Obj3D->Update();
	}

	// タイマーの更新
	pTimer->Update();

	// リザルト画面へ遷移していいか確認
	CheckResult();

	// デバッグ
	Debug();
}

//=============================================================================
// 描画
//=============================================================================
void SceneGame::Draw()
{
	// マップの描画
	pMap->Draw();

	// エフェクトマネージャの描画
	pEffectManager->Draw();

	// 3Dオブジェクトの描画
	for (auto &Obj3D : object3d)
	{
		Obj3D->Draw();
	}

	// プレイヤーの描画
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}

	// 2Dオブジェクトの描画
	for (auto &Object : UIObject)
	{
		Object->Draw();
	}

	// タイマーの描画
	pTimer->Draw();
}

//=============================================================================
// 当たり判定の更新
//=============================================================================
void SceneGame::Collision()
{
	// プレイヤーとマップの当たり判定
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->GroundCollider();
		pPlayer[i]->HorizonCollider();
		pPlayer[i]->ObjectCollider();
		pPlayer[i]->ObjectItemCollider(pMap);
	}

	// プレイヤーとペイントマネージャの当たり判定
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->PaintCollider();
	}

	// ペイントマネージャ同士の当たり判定
	for (int TenDigit = 1; TenDigit <= 4; TenDigit++)
	{
		for (int OneDigit = 1; OneDigit <= 4; OneDigit++)
		{
			// 画面を16分割、それぞれのオブジェクトを判定する
			HitCheckSToS(Quadtree, (TenDigit * 10 + OneDigit));
		}
	}

	// フィールド上に発生したアイテムとの当たり判定
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		for (int nItem = 0; nItem < PLAYER_MAX; nItem++)
		{
			if (nPlayer != nItem)
			{
				pPlayer[nPlayer]->FieldItemCollider(pPlayer[nItem]->GetFieldItemManager());
			}
		}
	}

	// フィールドオブジェクトとペイントマネージャの当たり判定
	for (int TenDigit = 1; TenDigit <= 4; TenDigit++)
	{
		for (int OneDigit = 1; OneDigit <= 4; OneDigit++)
		{
			// 画面を16分割、それぞれのオブジェクトを判定する
			pMap->PaintCollider(Quadtree, (TenDigit * 10 + OneDigit));
		}
	}

	// 四分木を更新する
	Quadtree->Update();

}

//=============================================================================
// 開始処理
//=============================================================================
void SceneGame::Start()
{
	// スタートタイマー更新
	startframe++;
	
	if (startframe == START_FRAME)
	{
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			pPlayer[i]->SetPlayable(true);
		}

		pTimer->Start();
	}
}

//=============================================================================
// リザルト画面へ遷移していいか確認
//=============================================================================
void SceneGame::CheckResult()
{
	// 全員ゴールorゲームオーバーならシーン遷移可能
	if (result)
	{
		// タイマーストップ
		pTimer->Stop();

		for (int pNo = 0; pNo < PLAYER_MAX; pNo++)
		{
			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(pNo, BUTTON_C))
			{
				SetScene(new SceneResult(), nSceneResult);
				InitCamera();
				return;
			}
		}
	}

	// 全員がゴールorゲームオーバーになったか確認
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (data[i].rank != -1)
		{
			result = true;
		}
		else
		{
			result = false;
			break;
		}
	}

	for (int pNo = 0; pNo < PLAYER_MAX; pNo++)
	{
		bool hit = false;
		// すでにそのプレイヤーの結果がリザルト順位配列に登録されているか確認
		for (int rNo = 0; rNo < PLAYER_MAX; rNo++)
		{
			if (data[rNo].rank != pNo)
			{
				hit = false;
			}
			else
			{
				hit = true;
				break;
			}
		}

		if (!hit)
		{
			// まだ順位が登録されていない場合
			InsertResult(pNo);
		}
	}
}

//=============================================================================
// リザルト順位配列にデータの挿入
//=============================================================================
void SceneGame::InsertResult(int pNo)
{
	// ゲームオーバー確認
	if (!pPlayer[pNo]->GetOnCamera())
	{
		// リザルト順位配列の後ろから入れていく
		for (int rNo = PLAYER_MAX - 1; rNo > 0; rNo--)
		{
			if (data[rNo].rank == -1)
			{
				data[rNo].rank = pNo;
				data[rNo].time = 359999;
				break;
			}
		}
	}

	// ゴール確認
	if (pPlayer[pNo]->GetPos().x >= GOAL_POS.x)
	{
		// リザルト順位配列の前から入れていく
		for (int rNo = 0; rNo < PLAYER_MAX; rNo++)
		{
			if (data[rNo].rank == -1)
			{
				data[rNo].rank = pNo;
				data[rNo].time = pTimer->Check();
				break;
			}
		}
	}
}

//=============================================================================
// デバッグ
//=============================================================================
void SceneGame::Debug()
{
#ifndef _DEBUG_
	BeginDebugWindow("Result");

	DebugText("All Goal or Gameover : %s", result ? "True" : "False");
	DebugText("No1:%d No2:%d No3:%d No4:%d", data[0].rank, data[1].rank, data[2].rank, data[3].rank);
	DebugText("ResultTime\nNo1:%d No2:%d No3:%d No4:%d", data[0].time, data[1].time, data[2].time, data[3].time);

	EndDebugWindow("Result");

#endif
}

//=============================================================================
// 結果のゲッター
//=============================================================================
ResultData *SceneGame::GetResultData(int playerNo)
{
	return &data[playerNo];
}