//=============================================================================
//
// ステージセレクト [SceneStageSelect.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneStageSelect.h"
#include "SceneManager.h"
#include "SceneCharacterSelect.h"
#include "Input.h"

#include "StageSelectBG.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SceneStageSelect::SceneStageSelect()
{
	// 背景
	obj.push_back(new StageSelectBG());
	// カーソル

	// ステージ名

}

//=============================================================================
// デストラクタ
//=============================================================================
SceneStageSelect::~SceneStageSelect()
{
	// 2Dオブジェクトの削除
	for (auto &UI : obj)
	{
		SAFE_DELETE(UI);
	}
	obj.clear();
	ReleaseVector(obj);

}

//=============================================================================
// 更新
//=============================================================================
void SceneStageSelect::Update(int SceneID)
{
	// シーン遷移
	for (int playerNo = 0; playerNo < GAMEPAD_MAX; playerNo++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			SetScene(new SceneCharacterSelect(), nSceneCharacterSelect);
			return;
		}
	}

	// 2Dオブジェクトの更新
	for (auto & UI : obj)
	{
		UI->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneStageSelect::Draw()
{
	// 2Dオブジェクトの描画
	for (auto & UI : obj)
	{
		UI->Draw();
	}
}