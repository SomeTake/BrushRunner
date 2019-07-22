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
#include "carsl_obj4.h"
#include "SceneManager.h"

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


static _2dobj *c2dobj[_2dMx];			// 2Dオブジェクト用のポインタ
float a, b, c;
//=============================================================================
// コンストラクタ
//=============================================================================
SceneCharacterSelect::SceneCharacterSelect()
{
	c2dobj[logo] = new Carsl_logo();
	c2dobj[obj1p01] = new Carsl_obj(CARSL_OBJ_POS01, TEXTURE_CARSL_OBJ);
	c2dobj[obj1p02] = new Carsl_obj(CARSL_OBJ_POS02,TEXTURE_CARSL_OBJ2);
	c2dobj[obj1p03] = new Carsl_obj(CARSL_OBJ_POS03,TEXTURE_CARSL_OBJ3);
	c2dobj[obj1p04] = new Carsl_obj(CARSL_OBJ_POS04, TEXTURE_CARSL_OBJ4);
	c2dobj[obj2p01] = new Carsl_obj2(CARSL_OBJ2_POS01, TEXTURE_CARSL_OBJ);
	c2dobj[obj2p02] = new Carsl_obj2(CARSL_OBJ2_POS02, TEXTURE_CARSL_OBJ2);
	c2dobj[obj2p03] = new Carsl_obj2(CARSL_OBJ2_POS03, TEXTURE_CARSL_OBJ3);
	c2dobj[obj2p04] = new Carsl_obj2(CARSL_OBJ2_POS04, TEXTURE_CARSL_OBJ4);
	c2dobj[obj3p01] = new Carsl_obj3(CARSL_OBJ3_POS01, TEXTURE_CARSL_OBJ);
	c2dobj[obj3p02] = new Carsl_obj3(CARSL_OBJ3_POS02, TEXTURE_CARSL_OBJ2);
	c2dobj[obj3p03] = new Carsl_obj3(CARSL_OBJ3_POS03, TEXTURE_CARSL_OBJ3);
	c2dobj[obj3p04] = new Carsl_obj3(CARSL_OBJ3_POS04, TEXTURE_CARSL_OBJ4);
	c2dobj[obj4p01] = new Carsl_obj4(CARSL_OBJ4_POS01, TEXTURE_CARSL_OBJ);
	c2dobj[obj4p02] = new Carsl_obj4(CARSL_OBJ4_POS02, TEXTURE_CARSL_OBJ2);
	c2dobj[obj4p03] = new Carsl_obj4(CARSL_OBJ4_POS03, TEXTURE_CARSL_OBJ3);
	c2dobj[obj4p04] = new Carsl_obj4(CARSL_OBJ4_POS04, TEXTURE_CARSL_OBJ4);
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneCharacterSelect::~SceneCharacterSelect()
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
void SceneCharacterSelect::Update()
{
//	if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	SetScene(nSceneGame);
	//}

	// 2Dオブジェクトの更新
	for (int i = 0; i < _2dMx; i++)
	{
		c2dobj[i]->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void SceneCharacterSelect::Draw()
{
	// 2Dオブジェクトの描画
	for (int i = 0; i < _2dMx; i++)
	{
		c2dobj[i]->Draw();
	}
}

