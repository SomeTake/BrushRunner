//=============================================================================
//
// �V�[���}�l�[�W�� [SceneManager.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "SceneTitle.h"
#include "SceneCharacterSelect.h"
#include "SceneGame.h"
#include "SceneResult.h"

//�V�[���J��
enum SceneNum
{
	nSceneTitle,				// �^�C�g��
	nSceneCharacterSelect,	// �L�����N�^�[�Z���N�g
	nSceneGame,				// �Q�[��
	nSceneResult,			// ���U���g
	nSceneExit				// �Q�[���I��
};

//*****************************************************************************
// �N���X��`
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

int GetScene();					// ���݂̃Q�[���V�[�����擾����
void SetScene(int _scene);		// �Q�[���V�[����ύX����


#endif
