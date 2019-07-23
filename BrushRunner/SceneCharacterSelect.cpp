//=============================================================================
//
// �L�����N�^�[�Z���N�g��ʏ��� [SceneCharacterSelect.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneCharacterSelect.h"
#include "Input.h"
//2d obje
#include "_2dobj.h"
#include "SelectLogo.h"
#include "SceneManager.h"
#include "SceneGame.h"

#include "Sound.h"

enum
{
	logo,
	obj1p01,
	obj1p02,
	obj1p03,
	obj1p04,
	obj2p01,
	obj2p02,
	obj2p03,
	obj2p04,
	obj3p01,
	obj3p02,
	obj3p03,
	obj3p04,
	obj4p01,
	obj4p02,
	obj4p03,
	obj4p04,
	//obj4p01,
	//obj4p02,
	//obj4p03,
	//NumColorinkline02,
	//NumColorinkline03,
	//NumColorinkline04,


	// �ő吔
	_2dMx,
};
static int SelectCharacter[PLAYER_MAX];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneCharacterSelect::SceneCharacterSelect()
{
	// �Z���N�g��ʂ̃��S
	p2dobj.push_back(new SelectLogo());

	// �Z���N�g�p�̃J�[�\��
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			pCursor[playerNo][cursorNo] = new CursorObj(playerNo, cursorNo);
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneCharacterSelect::~SceneCharacterSelect()
{
	// 2D�I�u�W�F�N�g�̍폜
	for (auto &Object : p2dobj)
	{
		SAFE_DELETE(Object);
	}
	p2dobj.clear();
	ReleaseVector(p2dobj);

	// �J�[�\���̍폜
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			delete pCursor[playerNo][cursorNo];
		}
	}
}

//=============================================================================
// �X�V
//=============================================================================
void SceneCharacterSelect::Update(int SceneID)
{
//	if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	SetScene(nSceneGame);
	//}
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(playerNo, BUTTON_C))
		{
			SetScene(new SceneGame(), nSceneGame);
			return;
		}
	}

	// 2D�I�u�W�F�N�g�̍X�V
	for (auto & Obj : p2dobj)
	{
		Obj->Update();
	}

	// �J�[�\���̍X�V
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			pCursor[playerNo][cursorNo]->Update();
		}
	}

	// ��ԍ��̃J�[�\�����L�����N�^�[�Z���N�g�̔ԍ��Ƃ��Ďg�p����
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		SelectCharacter[playerNo] = pCursor[playerNo][0]->GetSelectNo();
	}
}

//=============================================================================
// �`��
//=============================================================================
void SceneCharacterSelect::Draw()
{
	// 2D�I�u�W�F�N�g�̕`��
	for (auto & Obj : p2dobj)
	{
		Obj->Draw();
	}

	// �J�[�\���̕`��
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		for (int cursorNo = 0; cursorNo < CURSOROBJ_MAX; cursorNo++)
		{
			pCursor[playerNo][cursorNo]->Draw();
		}
	}
}

//=============================================================================
// �L�����N�^�[�Z���N�g�ԍ��̃Q�b�^�[
//=============================================================================
int *GetSelectCharacter(int no)
{
	return &SelectCharacter[no];
}