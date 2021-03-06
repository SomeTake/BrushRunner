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
#include "SceneExit.h"
#include "SceneStageSelect.h"
#include "SceneTutorial.h"
#include "ResourceManager.h"
#include "CircleSceneChanger.h"
#include "StageSelectBG.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static SceneNum eScene = nSceneTitle;		// ゲームの開始位置&シーン遷移
static Scene *scene;						// ゲームシーンのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
SceneManager::SceneManager(HINSTANCE hInstance, HWND hWnd)
{
	InitInput(hInstance, hWnd);
	InitCamera();
	InitLight();
	InitSound(hWnd);

	// リソースの読み込み
	LoadResource();

	// 開始位置に合わせて読み込み
	switch (eScene)
	{
	case nSceneTitle:
		PlaySound(BGM_TITLE);
		scene = new SceneTitle();
		break;
	case nSceneTutorial:
		PlaySound(BGM_TUTORIAL);
		scene = new SceneTutorial();
		break;
	case nSceneStageSelect:
		PlaySound(BGM_STAGESELECT);
		scene = new SceneStageSelect();
		break;
	case nSceneCharacterSelect:
		PlaySound(BGM_CHARSEL);
		scene = new SceneCharacterSelect();
		break;
	case nSceneGame:
		PlaySound(BGM_STAGE01);
		scene = new SceneGame();
		break;
	case nSceneResult:
		PlaySound(BGM_RESULT);
		scene = new SceneResult();
		break;
	case nSceneExit:
		scene = new SceneExit();
	default:
		break;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneManager::~SceneManager()
{
	SAFE_DELETE(scene);

	// リソースの削除
	ResourceManager::Instance()->AllRelease();

	UninitSound();

	UninitInput();
}

//=============================================================================
// 更新
//=============================================================================
void SceneManager::Update()
{
	UpdateInput();

	scene->Update(eScene);

	CircleSceneChanger::Instance()->Update();
}

//=============================================================================
// 描画
//=============================================================================
void SceneManager::Draw()
{
	SetCamera();

	// ステンシルマスクの描画
	CircleSceneChanger::Instance()->DrawMask();

	scene->Draw();

	// シーンチェンジャーの描画
	CircleSceneChanger::Instance()->DrawChanger();

}

//=============================================================================
// リソースの読み込み
//=============================================================================
void SceneManager::LoadResource()
{
	// リソース作成
	// 引数1:識別のためのタグ名(呼び出し先と合わせる) 引数2:ファイルのパス
	// SceneChanger
	ResourceManager::Instance()->LoadTexture("Mask", "data/TEXTURE/Circle.png");
	ResourceManager::Instance()->LoadTexture("Changer", "data/TEXTURE/Load.png");
	CircleSceneChanger::Instance()->LoadMaskTexture();
	CircleSceneChanger::Instance()->LoadChangeTexture();

	// SceneTitle
	ResourceManager::Instance()->LoadTexture("TitleLogo", "data/TEXTURE/Logo.png");
	ResourceManager::Instance()->LoadTexture("TitleRunner", "data/TEXTURE/Runner.png");
	ResourceManager::Instance()->LoadTexture("TitleMenu", "data/TEXTURE/TitleLogo.png");
	ResourceManager::Instance()->LoadTexture("TitleCursor", "data/TEXTURE/TitleCursor.png");

	// SceneTutorial
	ResourceManager::Instance()->LoadTexture("TutorialLogo", "data/TEXTURE/TutorialLogo.png");
	ResourceManager::Instance()->LoadTexture("Tutorial", "data/TEXTURE/Tutorial.png");
	ResourceManager::Instance()->LoadTexture("Arrow", "data/TEXTURE/Arrow.png");

	// SceneStageSelect
	ResourceManager::Instance()->LoadTexture("StageSelectBG", "data/TEXTURE/StageSelectBG.png");
	ResourceManager::Instance()->LoadTexture("StageName", "data/TEXTURE/StageName.png");
	ResourceManager::Instance()->LoadTexture("StageSelectLogo", "data/TEXTURE/StageSelectLogo.png");

	// SceneCharacterSelect
	ResourceManager::Instance()->LoadTexture("SelectLogo", "data/TEXTURE/CharSelectLogo.png");
	ResourceManager::Instance()->LoadTexture("SelectCursor", "data/TEXTURE/CharSelectCursor.png");	// SceneGameのFaceにも使う
	ResourceManager::Instance()->LoadTexture("CPUIcon", "data/TEXTURE/CpuLogo.png");
	ResourceManager::Instance()->LoadTexture("CharacterSelect", "data/TEXTURE/CharSelectBg.png");
	ResourceManager::Instance()->LoadTexture("CharSelectFrame", "data/TEXTURE/CharSelectFrame.png");

	// SceneGame
	ResourceManager::Instance()->LoadTexture("UIFrame", "data/texture/frame000.png");
	ResourceManager::Instance()->LoadTexture("CountDown", "data/TEXTURE/countdown.png");
	ResourceManager::Instance()->LoadTexture("Item", "data/TEXTURE/Item.png");
	ResourceManager::Instance()->LoadTexture("Finish", "data/TEXTURE/Finish.png");
	ResourceManager::Instance()->LoadTexture("Sky", "data/MAP/BG000.png");
	ResourceManager::Instance()->LoadTexture("GoalFlag", "data/TEXTURE/GoalFlag.png");
	ResourceManager::Instance()->LoadTexture("Digit", "data/TEXTURE/Digit.png");					// SceneResultのResultDigitにも使う
	ResourceManager::Instance()->LoadTexture("MapChip", "data/MAP/tilea5.png");
	ResourceManager::Instance()->LoadTexture("ObjectChip", "data/MAP/mapchip_object.png");
	ResourceManager::Instance()->LoadTexture("HitEffect", "data/EFFECT/anmef000.png");
	ResourceManager::Instance()->LoadTexture("DeadEffect", "data/EFFECT/anmef001.png");
	ResourceManager::Instance()->LoadTexture("RunEffect", "data/EFFECT/anmef002.png");
	ResourceManager::Instance()->LoadTexture("ExplosionEffect", "data/EFFECT/explo000.png");
	ResourceManager::Instance()->LoadTexture("ItemEffect", "data/EFFECT/ief001.png");
	ResourceManager::Instance()->LoadTexture("Item1Ettect", "data/EFFECT/ief000.png");
	ResourceManager::Instance()->LoadTexture("ChargeEffect", "data/EFFECT/Charge.png");
	ResourceManager::Instance()->LoadTexture("Paint", "data/TEXTURE/paint.png");
	ResourceManager::Instance()->LoadTexture("Cursor", "data/TEXTURE/brush.png");
	ResourceManager::Instance()->LoadTexture("InkGauge", "data/texture/InkGauge.png");
	ResourceManager::Instance()->LoadTexture("ColorInkFrame", "data/texture/colorinkframe.png");
	ResourceManager::Instance()->LoadTexture("BlackInkFrame", "data/texture/blackinkframe.png");
	ResourceManager::Instance()->LoadTexture("FaceFrame", "data/texture/faceframe.png");
	ResourceManager::Instance()->LoadTexture("MiniPlayer", "data/TEXTURE/MiniPlayer.png");
	ResourceManager::Instance()->LoadTexture("Pop", "data/TEXTURE/pointer.png");
	ResourceManager::Instance()->LoadTexture("FieldItem", "data/TEXTURE/FieldItem.png");

	// SceneResult
	ResourceManager::Instance()->LoadTexture("ResultRank", "data/TEXTURE/ResultPlayer.png");
	ResourceManager::Instance()->LoadTexture("SkyBox", "data/TEXTURE/SkyBox.png");
	ResourceManager::Instance()->LoadTexture("MeshField", "data/TEXTURE/Block.jpg");
	ResourceManager::Instance()->LoadTexture("Result", "data/TEXTURE/Result.png");

}

//=====================================================================================================
// シーン遷移
//=====================================================================================================
void SetScene(SceneNum _scene)
{
	eScene = _scene;
	SAFE_DELETE(scene)

	switch (_scene)
	{
	case nSceneTitle:
		StopSound(BGM_RESULT);
		scene = new SceneTitle();
		PlaySound(BGM_TITLE);
		break;
	case nSceneTutorial:
		StopSound(BGM_TITLE);
		scene = new SceneTutorial();
		PlaySound(BGM_TUTORIAL);
		break;
	case nSceneStageSelect:
		StopSound(BGM_TUTORIAL);
		scene = new SceneStageSelect();
		PlaySound(BGM_STAGESELECT);
		break;
	case nSceneCharacterSelect:
		StopSound(BGM_STAGESELECT);
		scene = new SceneCharacterSelect();
		PlaySound(BGM_CHARSEL);
		break;
	case nSceneGame:
		StopSound(BGM_CHARSEL);
		scene = new SceneGame();
		break;
	case nSceneResult:
		switch (StageSelectBG::GetStageSelect())
		{
		case 0:
			StopSound(BGM_STAGE01);
			break;
		case 1:
			StopSound(BGM_STAGE02);
			break;
		case 2:
			StopSound(BGM_STAGE03);
			break;
		}
		scene = new SceneResult();
		PlaySound(BGM_RESULT);
		break;
	case nSceneExit:
		StopSound(BGM_TITLE);
		scene = new SceneExit();
		break;
	default:
		break;
	}
}

//=====================================================================================================
// シーンのゲッター
//=====================================================================================================
int GetScene()
{
	return eScene;
}
