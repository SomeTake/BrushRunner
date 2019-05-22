//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "Debugproc.h"
#include "Map.h"
#include "Camera.h"
#include "Player.h"
#include "Collision.h"
#include "Gravity.h"

// �I�u�W�F�N�g�̃|�C���^
MAP *pMap;
PLAYER *pPlayer[PLAYER_MAX];

//=============================================================================
// ������
//=============================================================================
HRESULT InitSceneGame()
{
	pMap = new MAP();


	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i] = new PLAYER(i);
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void UninitSceneGame()
{
	delete pMap;

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		delete pPlayer[i];
	}
}

//=============================================================================
// �X�V
//=============================================================================
void UpdateSceneGame()
{
	UpdateCamera();

	pMap->Update();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();

		// �n�ʂɐڂ��Ă��邩�m�F
		if (HitCheckPToM(pPlayer[i], pMap))
		{
			pPlayer[i]->SetJumpFlag(false);
		}
		// �n�ʂɐڂ��Ă��Ȃ��̂ŁA��������
		else
		{
			GravityFall(pPlayer[i]);
		}
	}

	// �f�o�b�O�\��
#ifndef _DEBUG_

#endif
}

//=============================================================================
// �`��
//=============================================================================
void DrawSceneGame()
{
	pMap->Draw();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}
}