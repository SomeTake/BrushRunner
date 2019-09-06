//=============================================================================
//
// タイトル画面処理 [SceneTitle.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneTitle.h"
#include "_2dobj.h"
#include "Title.h"
#include "Input.h"
#include "SceneManager.h"
#include "SceneCharacterSelect.h"
#include "TitleCursor.h"
#include "SceneTutorial.h"
#include "Player.h"
#include "CircleSceneChanger.h"
#include "SceneExit.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SceneTitle::SceneTitle()
{
	
	IsOption = true;							// 選択肢フラグオン
	p2dObj.push_back(new TITLE(TitleLogo));
	p2dObj.push_back(new TITLE(TitleRunner));
	p2dObj.push_back(new TITLE(TitleMenu));
	p2dObj.push_back(new TITLECURSOR());

/*****************************************************************************/
	// シーンチェンジの終了
	CircleSceneChanger::Instance()->SetChanger(false);
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneTitle::~SceneTitle()
{
	for (auto &UI : p2dObj)
	{
		SAFE_DELETE(UI);
	}
	p2dObj.clear();
	ReleaseVector(p2dObj);
}

//=============================================================================
// 更新
//=============================================================================
void SceneTitle::Update(int SceneID)
{
	
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		if (GetKeyboardTrigger(DIK_W) || IsButtonTriggered(playerNo, STICK_UP))
		{
			IsOption = true;
			break;
		}
		else if (GetKeyboardTrigger(DIK_S) || IsButtonTriggered(playerNo, STICK_DOWN))
		{
			IsOption = false;
			break;
		}

		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			if (IsOption == true)
			{
				CircleSceneChanger::Instance()->SetChanger(true, []()
				{
					SetScene(new SceneTutorial(), nSceneTutorial);
				});
				return;
			}
			else
			{
				//SetScene(new SceneExit(), nSceneExit);

				CircleSceneChanger::Instance()->SetChanger(true, []()
				{
					SetScene(new SceneExit(), nSceneExit);
				});
				return;
			}
		}


	}

	for (auto &UI : p2dObj)
	{
		UI->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneTitle::Draw()
{
	for (auto &UI : p2dObj)
	{
		UI->Draw();
	}
}