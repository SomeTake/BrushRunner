//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneResult.h"
#include "Camera.h"
#include "Result.h"
#include "Input.h"
#include "SceneGame.h"
#include "Player.h"
#include "DebugWindow.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "ResultRank.h"
#include "ResultTimer.h"
#include "Podium.h"
#include "Trophy.h"
#include "ResultPlayer.h"
#include "SkyBox.h"
#include "MeshField.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneResult::SceneResult()
{
	// 2D�I�u�W�F�N�g�̃C���X�^���X���쐬
	Obj2d.push_back(new RESULT());
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		Obj2d.push_back(new ResultRank(SceneGame::GetResultData(playerNo)->rank));
		Obj2d.push_back(new ResultTimer(SceneGame::GetResultData(playerNo)->time, SceneGame::GetResultData(playerNo)->rank));
	}

	// 3D���f���̃C���X�^���X�쐬
	anim.push_back(new Podium());
	anim.push_back(new Trophy());
	for (int playerNo = 0; playerNo < PLAYER_MAX; playerNo++)
	{
		anim.push_back(new ResultPlayer(SceneGame::GetResultData(playerNo)->rank, playerNo));
	}

	// 3D�|���S���̃C���X�^���X�쐬
	Obj3d.push_back(new SkyBox());
	Obj3d.push_back(new MeshField());
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneResult::~SceneResult()
{
	// 2D�I�u�W�F�N�g�̍폜
	for (auto &Obj : Obj2d)
	{
		SAFE_DELETE(Obj);
	}
	Obj2d.clear();
	ReleaseVector(Obj2d);

	// 3D���f���̍폜
	for (auto &Anim : anim)
	{
		SAFE_DELETE(Anim);
	}
	anim.clear();
	ReleaseVector(anim);

	// 3D�|���S���̍폜
	for (auto &Obj : Obj3d)
	{
		SAFE_DELETE(Obj);
	}
	Obj3d.clear();
	ReleaseVector(Obj3d);

}

//=============================================================================
// �X�V
//=============================================================================
void SceneResult::Update(int SceneID)
{
	// �J�����̍X�V
	UpdateCamera();

	// �V�[���`�F���W
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(i, BUTTON_C))
		{
			SetScene(new SceneTitle(), nSceneTitle);
			return;
		}
	}

	// 2D�I�u�W�F�N�g�̍X�V
	for (auto &Obj : Obj2d)
	{
		Obj->Update();
	}

	// 3D���f���̍X�V
	for (auto &Anim : anim)
	{
		Anim->Update();
	}

	// 3D�|���S���̍X�V
	for (auto &Obj : Obj3d)
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
	// 3D���f���̕`��
	for (auto &Anim : anim)
	{
		Anim->Draw();
	}

	// 3D�|���S���̕`��
	for (auto &Obj : Obj3d)
	{
		Obj->Draw();
	}

	// 2D�I�u�W�F�N�g�̕`��
	for (auto &Obj : Obj2d)
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

	DebugText("No1:%d No2:%d No3:%d No4:%d", SceneGame::GetResultData(0)->rank, SceneGame::GetResultData(1)->rank, SceneGame::GetResultData(2)->rank, SceneGame::GetResultData(3)->rank);
	DebugText("ResultTime\nNo1:%d No2:%d No3:%d No4:%d", SceneGame::GetResultData(0)->time, SceneGame::GetResultData(1)->time, SceneGame::GetResultData(2)->time, SceneGame::GetResultData(3)->time);

	EndDebugWindow("Result");

#endif
}