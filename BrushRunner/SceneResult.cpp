//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneResult.h"
#include "_2dobj.h"
#include "Result.h"
#include "Input.h"
#include "SceneGame.h"
#include "Player.h"
#include "DebugWindow.h"
#include "SceneManager.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
enum
{
	ResultBG,
	UIMax,										// UI�\���̍ő吔
};

static _2dobj *p2dObj[UIMax];					// 2D�I�u�W�F�N�g�p�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneResult::SceneResult()
{
	ResultRank = GetResultRank(0);

	p2dObj[ResultBG] = new RESULT(RESULT_POS01, RESULT_SIZE01, TEXTURE_RESULT01);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneResult::~SceneResult()
{
	for (int i = 0; i < UIMax; i++)
	{
		delete p2dObj[i];
	}

}

//=============================================================================
// �X�V
//=============================================================================
void SceneResult::Update()
{
	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Update();

	}
	Debug();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(i, BUTTON_C))
		{
			SetScene(nSceneTitle);
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void SceneResult::Draw()
{
	for (int i = 0; i < UIMax; i++)
	{
		p2dObj[i]->Draw();
	}

}

//=============================================================================
// �f�o�b�O
//=============================================================================
void SceneResult::Debug()
{
#ifndef _DEBUG_
	BeginDebugWindow("Result");

	DebugText("No1:%d No2:%d No3:%d No4:%d", ResultRank[0], ResultRank[1], ResultRank[2], ResultRank[3]);

	EndDebugWindow("Result");

#endif
}