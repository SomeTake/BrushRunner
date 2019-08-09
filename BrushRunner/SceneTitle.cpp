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

//=============================================================================
// グローバル変数
//=============================================================================

enum
{	
	TitleLogo,
	TitleRunner,
	TitleMenu,
	UIMax,										// UI表示の最大数
};


static _2dobj *p2dObj[UIMax];					// 2Dオブジェクト用のポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
SceneTitle::SceneTitle()
{
	p2dObj[TitleRunner] = new TITLE(TITLE_POS01 - TITLE_SIZE01/2,TITLE_SIZE01,TEXTURE_TITLE01);
	p2dObj[TitleLogo] = new TITLE(TITLE_POS02 - TITLE_SIZE02/2, TITLE_SIZE02, TEXTURE_TITLE02);
	p2dObj[TitleMenu] = new TITLE(TITLE_POS03 - TITLE_SIZE03/2, TITLE_SIZE03, TEXTURE_TITLE03);

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
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			SetScene(new SceneCharacterSelect(), nSceneCharacterSelect);
			return;
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