//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneResult.h"
#include "Result.h"
#include "Input.h"
#include "SceneGame.h"
#include "Player.h"
#include "DebugWindow.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "ResultRank.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneResult::SceneResult()
{
	data = SceneGame::GetResultData(0);

	p2dObj.push_back(new RESULT());
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++, data++)
	{
		p2dObj.push_back(new ResultRank(data->rank));
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneResult::~SceneResult()
{
	// 2D�I�u�W�F�N�g�̍폜
	for (auto &Obj : p2dObj)
	{
		SAFE_DELETE(Obj);
	}
	p2dObj.clear();
	ReleaseVector(p2dObj);

}

//=============================================================================
// �X�V
//=============================================================================
void SceneResult::Update(int SceneID)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(i, BUTTON_C))
		{
			SetScene(new SceneTitle(), nSceneTitle);
			return;
		}
	}

	// 2D�I�u�W�F�N�g�̍X�V
	for (auto &Obj : p2dObj)
	{
		Obj->Update();
	}

	Debug();
}

//=============================================================================
// �`��
//=============================================================================
void SceneResult::Draw()
{
	// 2D�I�u�W�F�N�g�̕`��
	for (auto &Obj : p2dObj)
	{
		Obj->Draw();
	}
}

//=============================================================================
// �f�o�b�O
//=============================================================================
void SceneResult::Debug()
{
#ifndef _DEBUG_
	BeginDebugWindow("Result");

	DebugText("No1:%d No2:%d No3:%d No4:%d", data[0].rank, data[1].rank, data[2].rank, data[3].rank);
	DebugText("ResultTime\nNo1:%d No2:%d No3:%d No4:%d", data[0].time, data[1].time, data[2].time, data[3].time);

	EndDebugWindow("Result");

#endif
}