//=============================================================================
//
// キャラクターセレクト画面処理 [SceneCharacterSelect.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneCharacterSelect.h"
#include "Input.h"
//2d obje
#include "_2dobj.h"
#include "SelectLogo.h"
#include "SceneManager.h"
#include "SceneGame.h"

#include "Sound.h"

enum
{
	logo,
	obj1p01,
	obj1p02,
	obj1p03,
	obj1p04,
	obj2p01,
	obj2p02,
	obj2p03,
	obj2p04,
	obj3p01,
	obj3p02,
	obj3p03,
	obj3p04,
	obj4p01,
	obj4p02,
	obj4p03,
	obj4p04,
	//obj4p01,
	//obj4p02,
	//obj4p03,
	//NumColorinkline02,
	//NumColorinkline03,
	//NumColorinkline04,


	// 最大数
	_2dMx,
};
static int SelectCharacter[PLAYER_MAX];

//=============================================================================
// コンストラクタ
//=============================================================================
SceneCharacterSelect::SceneCharacterSelect()
{
	// セレクト画面のロゴ
	p2dobj.push_back(new SelectLogo());

	// セレクト用のカーソル
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			pCursor[playerNo][cursorNo] = new CursorObj(playerNo, cursorNo);
		}
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneCharacterSelect::~SceneCharacterSelect()
{
	// 2Dオブジェクトの削除
	for (auto &Object : p2dobj)
	{
		SAFE_DELETE(Object);
	}
	p2dobj.clear();
	ReleaseVector(p2dobj);

	// カーソルの削除
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			delete pCursor[playerNo][cursorNo];
		}
	}
}

//=============================================================================
// 更新
//=============================================================================
void SceneCharacterSelect::Update(int SceneID)
{
//	if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	SetScene(nSceneGame);
	//}
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			SetScene(new SceneGame(), nSceneGame);
			return;
		}
	}

	// 2Dオブジェクトの更新
	for (auto & Obj : p2dobj)
	{
		Obj->Update();
	}

	// カーソルの更新
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			pCursor[playerNo][cursorNo]->Update();
		}
	}

	// 一番左のカーソルをキャラクターセレクトの番号として使用する
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		SelectCharacter[playerNo] = pCursor[playerNo][0]->GetSelectNo();
	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneCharacterSelect::Draw()
{
	// 2Dオブジェクトの描画
	for (auto & Obj : p2dobj)
	{
		Obj->Draw();
	}

	// カーソルの描画
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			pCursor[playerNo][cursorNo]->Draw();
		}
	}
}

//=============================================================================
// キャラクターセレクト番号のゲッター
//=============================================================================
int *GetSelectCharacter(int no)
{
	return &SelectCharacter[no];
}