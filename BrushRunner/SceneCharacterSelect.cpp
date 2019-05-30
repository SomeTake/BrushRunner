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
#include "carsl_logo.h"
#include "carsl_obj.h"
#include "carsl_obj2.h"
#include "carsl_obj3.h"
enum
{
	logo,
	obj01,
	obj02,
	obj03,
	//NumColorinkline02,
	//NumColorinkline03,
	//NumColorinkline04,


	// 最大数
	_2dMx,
};


static _2dobj *c2dobj[_2dMx];			// 2Dオブジェクト用のポインタ
float a, b, c;
//=============================================================================
// 初期化
//=============================================================================
HRESULT InitSceneCharacterSelect()
{
	c2dobj[logo] = new Carsl_logo();
	c2dobj[obj01] = new Carsl_obj(CARSL_OBJ_POS01, TEXTURE_CARSL_OBJ);
	c2dobj[obj02] = new Carsl_obj2(CARSL_OBJ_POS02,TEXTURE_CARSL_OBJ2);
	c2dobj[obj03] = new Carsl_obj3(CARSL_OBJ_POS03,TEXTURE_CARSL_OBJ3);
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void UninitSceneCharacterSelect()
{
	// 2Dオブジェクトの削除
	for (int i = 0; i < _2dMx; i++)
	{
		delete c2dobj[i];
	}
}

//=============================================================================
// 更新
//=============================================================================
void UpdateSceneCharacterSelect()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetScene(SceneGame);
	}

	// 2Dオブジェクトの更新
	for (int i = 0; i < _2dMx; i++)
	{
		c2dobj[i]->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void DrawSceneCharacterSelect()
{
	// 2Dオブジェクトの描画
	for (int i = 0; i < _2dMx; i++)
	{
		c2dobj[i]->Draw();
	}
}

