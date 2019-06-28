//=============================================================================
//
// シーンマネージャ [SceneManager.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "SceneTitle.h"
#include "SceneCharacterSelect.h"
#include "SceneGame.h"
#include "SceneResult.h"

//シーン遷移
enum SceneNum
{
	nSceneTitle,				// タイトル
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
private:
	SceneTitle * title;
	SceneCharacterSelect * charaselect;
	SceneGame * game;
	SceneResult * result;

public:
	SceneManager(HINSTANCE hInstance, HWND hWnd);
	~SceneManager();

	void Update();
	void Draw();
};

int GetScene();					// 現在のゲームシーンを取得する
void SetScene(int _scene);		// ゲームシーンを変更する


#endif
