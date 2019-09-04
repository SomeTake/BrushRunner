//=============================================================================
//
// チュートリアルシーン [SceneTutorial.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneTutorial.h"
#include "SceneManager.h"
#include "SceneStageSelect.h"
#include "Input.h"
#include "CircleSceneChanger.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SceneTutorial::SceneTutorial()
{

	// シーンチェンジの終了
	CircleSceneChanger::Instance()->SetChanger(false);
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneTutorial::~SceneTutorial()
{
}

//=============================================================================
// 更新
//=============================================================================
void SceneTutorial::Update(int SceneID)
{
	// シーン切り替え
	for (int padNo = 0; padNo < GAMEPAD_MAX; padNo++)
	{
		if (IsButtonTriggered(padNo, BUTTON_C) || GetKeyboardTrigger(DIK_RETURN))
		{
			CircleSceneChanger::Instance()->SetChanger(true, []() 
			{
				SetScene(new SceneStageSelect(), nSceneStageSelect);
			});
			break;
		}

	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneTutorial::Draw()
{

}