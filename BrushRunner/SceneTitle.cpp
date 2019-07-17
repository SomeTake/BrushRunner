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
#include "SceneCharacterSelect.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

enum
{	
	TitleLogo,
	TitleRunner,
	TitleMenu,
	UIMax,										// UI�\���̍ő吔
};


static _2dobj *p2dObj[UIMax];					// 2D�I�u�W�F�N�g�p�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneTitle::SceneTitle()
{
	p2dObj[TitleRunner] = new TITLE(TITLE_POS01 - TITLE_SIZE01/2,TITLE_SIZE01,TEXTURE_TITLE01);
	p2dObj[TitleLogo] = new TITLE(TITLE_POS02 - TITLE_SIZE02/2, TITLE_SIZE02, TEXTURE_TITLE02);
	p2dObj[TitleMenu] = new TITLE(TITLE_POS03 - TITLE_SIZE03/2, TITLE_SIZE03, TEXTURE_TITLE03);

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
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			SetScene(new SceneCharacterSelect(), nSceneCharacterSelect);
			return;
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