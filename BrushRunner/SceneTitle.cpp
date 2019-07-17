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
// ������
//=============================================================================
HRESULT InitSceneTitle()
{
	p2dObj[TitleRunner] = new TITLE(TITLE_POS01 - TITLE_SIZE01/2,TITLE_SIZE01,TEXTURE_TITLE01);
	p2dObj[TitleLogo] = new TITLE(TITLE_POS02 - TITLE_SIZE02/2, TITLE_SIZE02, TEXTURE_TITLE02);
	p2dObj[TitleMenu] = new TITLE(TITLE_POS03 - TITLE_SIZE03/2, TITLE_SIZE03, TEXTURE_TITLE03);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void UninitSceneTitle()
{
	for (int i = 0; i < UIMax; i++)
	{
		delete p2dObj[i];
	}
}

//=============================================================================
// �X�V
//=============================================================================
void UpdateSceneTitle()
{

	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Update();

		if (GetKeyboardTrigger(DIK_SPACE))
		{
			SetScene(SceneCharacterSelect);
		}

	}
}

//=============================================================================
// �`��
//=============================================================================
void DrawSceneTitle()
{
	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Draw();
	}

}