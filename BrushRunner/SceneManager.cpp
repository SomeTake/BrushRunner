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
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int eScene = nSceneTitle;	// ゲームの開始位置&シーン遷移

//=============================================================================
// コンストラクタ
//=============================================================================
SceneManager::SceneManager(HINSTANCE hInstance, HWND hWnd)
{
	InitInput(hInstance, hWnd);
	InitCamera();
	InitLight();

	title = new SceneTitle();
	charaselect = new SceneCharacterSelect();
	game = new SceneGame();
	result = new SceneResult();
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneManager::~SceneManager()
{
	delete title;
	delete charaselect;
	delete game;
	delete result;

	UninitInput();
}

//=============================================================================
// 更新
//=============================================================================
void SceneManager::Update()
{
	UpdateInput();

	switch (eScene)
	{
	case nSceneTitle:
		title->Update();
		break;
	case nSceneCharacterSelect:
		charaselect->Update();
		break;
	case nSceneGame:
		game->Update();
		break;
	case nSceneResult:
		result->Update();
		break;
	default:
		break;
	}

}

//=============================================================================
// 描画
//=============================================================================
void SceneManager::Draw()
{
	SetCamera();

	switch (eScene)
	{
	case nSceneTitle:
		title->Draw();
		break;
	case nSceneCharacterSelect:
		charaselect->Draw();
		break;
	case nSceneGame:
		game->Draw();
		break;
	case nSceneResult:
		result->Draw();
		break;
	default:
		break;
	}
}

//=====================================================================================================
// シーン遷移
//=====================================================================================================
void SetScene(int _scene)
{
	eScene = _scene;
}

//=====================================================================================================
// シーンのゲッター
//=====================================================================================================
int GetScene()
{
	return eScene;
}
