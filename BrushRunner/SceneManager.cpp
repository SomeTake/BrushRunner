//=============================================================================
//
// �V�[���}�l�[�W�� [SceneManager.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
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
// �O���[�o���ϐ�
//*****************************************************************************
//static int eScene = nSceneGame;	// �Q�[���̊J�n�ʒu&�V�[���J��
//static Scene *scene;						// �Q�[���V�[���̃|�C���^
static int eScene = nSceneTitle;	// �Q�[���̊J�n�ʒu&�V�[���J��
static Scene *scene;				// �Q�[���V�[���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneManager::SceneManager(HINSTANCE hInstance, HWND hWnd)
{
	InitInput(hInstance, hWnd);
	InitCamera();
	InitLight();
	InitSound(hWnd);

	//title = new SceneTitle();
	//scene = new SceneCharacterSelect();
	//game = new SceneGame();
	//result = new SceneResult();
	switch (eScene)
	{
	case nSceneTitle:
		PlaySound(BGM_TITLE);
		scene = new SceneTitle();
		break;
	case nSceneCharacterSelect:
		//StopSound(BGM_TITLE);
		PlaySound(BGM_CHARSEL);
		scene = new SceneCharacterSelect();
		break;
	case nSceneGame:
		//StopSound(BGM_CHARSEL);
		PlaySound(BGM_TRAINING);
		scene = new SceneGame();
		break;
	case nSceneResult:
		//StopSound(BGM_TRAINING);
		scene = new SceneResult();
		break;
	default:
		break;
	}

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneManager::~SceneManager()
{
	//delete title;
	//delete charaselect;
	//delete game;
	//delete result;

	delete scene;
	UninitSound();

	UninitInput();
}

//=============================================================================
// �X�V
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
// �`��
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
// �V�[���J��
//=====================================================================================================
void SetScene(Scene *NewScene, int _scene)
{
	eScene = _scene;
	switch (eScene)
	{
	case nSceneTitle:
		PlaySound(BGM_TITLE);
		break;
	case nSceneCharacterSelect:
		StopSound(BGM_TITLE);
		PlaySound(BGM_CHARSEL);
		break;
	case nSceneGame:
		StopSound(BGM_CHARSEL);
		PlaySound(BGM_TRAINING);
		break;
	case nSceneResult:
		StopSound(BGM_TRAINING);
		break;
	default:
		break;
	}
	delete scene;
	scene = NewScene;
}

//=====================================================================================================
// �V�[���̃Q�b�^�[
//=====================================================================================================
int GetScene()
{
	return eScene;
}
