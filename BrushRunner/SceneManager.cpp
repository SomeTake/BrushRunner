//=============================================================================
//
// シーンマネージャ [SceneManager.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SceneManager.h"
#include "Input.h"
#include "Camera.h"
#include "Light.h"
#include "Sound.h"
#include "SceneTitle.h"
#include "SceneCharacterSelect.h"
#include "SceneGame.h"
#include "SceneResult.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int eScene = nSceneTitle;	// ゲームの開始位置&シーン遷移
static Scene *scene;				// ゲームシーンのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
SceneManager::SceneManager(HINSTANCE hInstance, HWND hWnd)
{
	InitInput(hInstance, hWnd);
	InitCamera();
	InitLight();

	//title = new SceneTitle();
	//scene = new SceneCharacterSelect();
	//game = new SceneGame();
	//result = new SceneResult();
	switch (eScene)
	{
	case nSceneTitle:
		scene = new SceneTitle();
		break;
	case nSceneCharacterSelect:
		scene = new SceneCharacterSelect();
		break;
	case nSceneGame:
		scene = new SceneGame();
		break;
	case nSceneResult:
		scene = new SceneResult();
		break;
	default:
		break;
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
SceneManager::~SceneManager()
{
	//delete title;
	//delete charaselect;
	//delete game;
	//delete result;

	delete scene;

	UninitInput();
}

//=============================================================================
// 更新
//=============================================================================
void SceneManager::Update()
{
	UpdateInput();

	//switch (eScene)
	//{
	//case nSceneTitle:
	//	title->Update();
	//	break;
	//case nSceneCharacterSelect:
	//	charaselect->Update();
	//	break;
	//case nSceneGame:
	//	game->Update();
	//	break;
	//case nSceneResult:
	//	result->Update();
	//	break;
	//default:
	//	break;
	//}

	scene->Update(eScene);
}

//=============================================================================
// 描画
//=============================================================================
void SceneManager::Draw()
{
	SetCamera();

	//switch (eScene)
	//{
	//case nSceneTitle:
	//	title->Draw();
	//	break;
	//case nSceneCharacterSelect:
	//	charaselect->Draw();
	//	break;
	//case nSceneGame:
	//	game->Draw();
	//	break;
	//case nSceneResult:
	//	result->Draw();
	//	break;
	//default:
	//	break;
	//}

	scene->Draw();
}

//=====================================================================================================
// シーン遷移
//=====================================================================================================
void SetScene(Scene *NewScene, int _scene)
{
	eScene = _scene;
	delete scene;
	scene = NewScene;
}

//=====================================================================================================
// シーンのゲッター
//=====================================================================================================
int GetScene()
{
	return eScene;
}
