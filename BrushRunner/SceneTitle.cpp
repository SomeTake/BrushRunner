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

//=============================================================================
// グローバル変数
//=============================================================================

static _2dobj *p2dObj[UIMax];					// 2Dオブジェクト用のポインタ
static bool IsOption;							// 選択肢フラグ

//=============================================================================
// コンストラクタ
//=============================================================================
SceneTitle::SceneTitle()
{
	
	IsOption = true;							// 選択肢フラグオン
	p2dObj[TitleLogo] = new TITLE(TitleLogo);
	p2dObj[TitleRunner] = new TITLE(TitleRunner);
	p2dObj[TitleMenu] = new TITLE(TitleMenu);

	p2dObj[TitleCursor] = new TITLECURSOR();

}

//=============================================================================
// デストラクタ
//=============================================================================
SceneTitle::~SceneTitle()
{
	for (int i = 0; i < UIMax; i++)
	{
		delete p2dObj[i];
	}
}

//=============================================================================
// 更新
//=============================================================================
void SceneTitle::Update(int SceneID)
{
	
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(playerNo, STICK_UP))
		{
			IsOption = true;
		}
		else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(playerNo, STICK_DOWN))
		{
			IsOption = false;
		}

		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			if (IsOption == true)
			{
				SetScene(new SceneCharacterSelect(), nSceneCharacterSelect);
				return;
			}
			else
			{
				// 追加予定
				//SetScene(new SceneExit(), nSceneExit);

				return;
			}
		}


	}

	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneTitle::Draw()
{
	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Draw();
	}

}