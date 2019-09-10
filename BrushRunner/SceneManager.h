//=============================================================================
//
// シーンマネージャ [SceneManager.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "Scene.h"

//シーン遷移番号
enum SceneNum
{
	nSceneTitle,			// タイトル
	nSceneTutorial,			// チュートリアル
	nSceneStageSelect,		// ステージセレクト
	nSceneCharacterSelect,	// キャラクターセレクト
	nSceneGame,				// ゲーム
	nSceneResult,			// リザルト
	nSceneExit				// ゲーム終了
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneManager
{
public:
	SceneManager(HINSTANCE hInstance, HWND hWnd);
	~SceneManager();

	void Update();
	void Draw();

	void LoadResource();
};

int GetScene();									// 現在のゲームシーンを取得する
//void SetScene(Scene *NewScene, int _scene);		// ゲームシーンを変更する
void SetScene(int _scene);		// ゲームシーンを変更する

#endif
