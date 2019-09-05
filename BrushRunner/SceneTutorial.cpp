//=============================================================================
//
// �`���[�g���A���V�[�� [SceneTutorial.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneTutorial.h"
#include "SceneManager.h"
#include "SceneStageSelect.h"
#include "Input.h"
#include "CircleSceneChanger.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneTutorial::SceneTutorial()
{

	// �V�[���`�F���W�̏I��
	CircleSceneChanger::Instance()->SetChanger(false);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneTutorial::~SceneTutorial()
{
}

//=============================================================================
// �X�V
//=============================================================================
void SceneTutorial::Update(int SceneID)
{
	// �V�[���؂�ւ�
	for (int padNo = 0; padNo < GAMEPAD_MAX; padNo++)
	{
		if (IsButtonTriggered(padNo, BUTTON_C) || GetKeyboardTrigger(DIK_RETURN))
		{
			CircleSceneChanger::Instance()->SetChanger(true, []() 
			{
				SetScene(new SceneStageSelect(), nSceneStageSelect);
			});
			break;
		}

	}
}

//=============================================================================
// �`��
//=============================================================================
void SceneTutorial::Draw()
{

}