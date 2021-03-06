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
#include "TutorialLogo.h"
#include "Arrow.h"
#include "Tutorial.h"
#include "Sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SceneTutorial::SceneTutorial()
{
	// 説明
	obj.push_back(new Tutorial());

	// ロゴ
	obj.push_back(new TutorialLogo());

	// 左右選択矢印
	obj.push_back(new Arrow(true));
	obj.push_back(new Arrow(false));


/*****************************************************************************/
	// シーンチェンジの終了
	CircleSceneChanger::Instance()->SetChanger(false);
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneTutorial::~SceneTutorial()
{
	// 2Dオブジェクトの開放
	for (auto &Object : obj)
	{
		SAFE_DELETE(Object);
	}
	obj.clear();
	ReleaseVector(obj);
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
			PlaySound(SE_CHOICE);

			CircleSceneChanger::Instance()->SetChanger(true, []() 
			{
				SetScene(nSceneStageSelect);
			});
			break;
		}
	}

	// 2Dオブジェクトの更新
	for (auto Object : obj)
	{
		Object->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneTutorial::Draw()
{
	// 2Dオブジェクトの描画
	for (auto Object : obj)
	{
		Object->Draw();
	}
}