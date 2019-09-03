//=============================================================================
//
// �^�C�g����ʏ��� [SceneTitle.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneTitle.h"
#include "_2dobj.h"
#include "Title.h"
#include "Input.h"
#include "SceneManager.h"
#include "SceneStageSelect.h"
#include "Player.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static _2dobj *p2dObj[UIMax];					// 2D�I�u�W�F�N�g�p�̃|�C���^
bool IsOption;									// �I�����t���O

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneTitle::SceneTitle()
{
	
	IsOption = false;							// �I�����t���O
	p2dObj[TitleLogo] = new TITLE(TitleLogo);
	p2dObj[TitleRunner] = new TITLE(TitleRunner);
	p2dObj[TitleMenu] = new TITLE(TitleMenu);

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneTitle::~SceneTitle()
{
	for (int i = 0; i < UIMax; i++)
	{
		delete p2dObj[i];
	}
}

//=============================================================================
// �X�V
//=============================================================================
void SceneTitle::Update(int SceneID)
{
	
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(playerNo, STICK_UP))
		{
			p2dObj[TitleArrows] = new TITLE(TITLE_POS04 - TITLE_SIZE04 / 2, TITLE_SIZE04, TEXTURE_TITLE04);
			IsOption = true;
		}

		if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(playerNo, STICK_DOWN))
		{
			p2dObj[TitleArrows] = new TITLE(TITLE_POS05 - TITLE_SIZE04 / 2, TITLE_SIZE04, TEXTURE_TITLE04);
			IsOption = false;
		}

		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			if (IsOption == true)
			{
				SetScene(new SceneStageSelect(), nSceneStageSelect);
				return;
			}
			else
			{
				return;
			}
		}


	}

	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void SceneTitle::Draw()
{
	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Draw();
	}

}