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
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int eScene = nSceneTitle;	// �Q�[���̊J�n�ʒu&�V�[���J��

//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
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
// �X�V
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
// �`��
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
// �V�[���J��
//=====================================================================================================
void SetScene(int _scene)
{
	eScene = _scene;
}

//=====================================================================================================
// �V�[���̃Q�b�^�[
//=====================================================================================================
int GetScene()
{
	return eScene;
}
