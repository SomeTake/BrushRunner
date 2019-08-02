//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "Map.h"
#include "Camera.h"
#include "Collision.h"
#include "Input.h"
#include "DebugWindow.h"
#include "SceneResult.h"

// 2d obj
#include "Frame01.h"
#include "Face.h"
#include "CountDown.h"
#include "Item.h"

// 3d obj
#include "Sky.h"
#include "GoalFlag.h"

//*****************************************************************************
// �����o�ϐ��̏�����
//*****************************************************************************
ResultData SceneGame::data[PLAYER_MAX] = { NULL };		// ����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneGame::SceneGame()
{
	// �Q�[���̌��ʂ�������
	startframe = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		data[i].rank = -1;
		data[i].time = 0;
	}
	result = false;

	// �v���C���[�̏�����
	for (int PlayerNo = 0; PlayerNo < PLAYER_MAX; PlayerNo++)
	{
		pPlayer[PlayerNo] = new Player(PlayerNo);
	}

	// �}�b�v�̏�����
	pMap = new Map();

	// �l���؂̏�����
	Quadtree = new QUADTREE(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	PaintManager::SetQuadtreePtr(Quadtree);

	// 2DUI�̏�����
	// �t���[��
	UIObject.push_back(new Frame());

	// �A�C�e���\���̏�����
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		UIObject.push_back(new Item(ItemPos[i], pPlayer[i]));
	}

	// �J�E���g�_�E���̏�����
	UIObject.push_back(new CountDown());

	// �G�t�F�N�g�}�l�[�W��
	pEffectManager = new EffectManager();

	// 3D�I�u�W�F�N�g
	object3d.push_back(new Sky());
	object3d.push_back(new GoalFlag());

	// �^�C�}�[
	pTimer = new Timer();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneGame::~SceneGame()
{
	// �}�b�v�̍폜
	SAFE_DELETE(pMap);

	// �l���؂̍폜
	SAFE_DELETE(Quadtree);

	// �y�C���g�e�N�X�`���̍폜
	Paint::ReleaseTexture();

	// �v���C���[�̍폜
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		SAFE_DELETE(pPlayer[i]);
	}

	// 2D�I�u�W�F�N�g�̍폜
	for (auto &Object : UIObject)
	{
		SAFE_DELETE(Object);
	}
	UIObject.clear();
	ReleaseVector(UIObject);

	// �G�t�F�N�g�}�l�[�W���̍폜
	delete pEffectManager;

	// 3D�I�u�W�F�N�g�̍폜
	for (auto &Obj3D : object3d)
	{
		SAFE_DELETE(Obj3D);
	}
	object3d.clear();
	ReleaseVector(object3d);

	// �^�C�}�[�̍폜
	delete pTimer;
}

//=============================================================================
// �X�V
//=============================================================================
void SceneGame::Update(int SceneID)
{
	// �J�n����
	if (startframe < START_FRAME)
	{
		Start();
	}

	// �v���C���[���W�̒���X���ł��傫�����̂��J���������_�Ƃ���
	std::vector<float> vec(PLAYER_MAX);
	for (size_t i = 0; i < vec.size(); i++)
	{
		vec.at(i) = pPlayer[i]->GetPos().x;
	}
	auto max = std::max_element(vec.begin(), vec.end());
	size_t maxIdx = std::distance(vec.begin(), max);

	// �J�����̍X�V
	UpdateCamera(pPlayer[(int)maxIdx]->GetPos());

	// �}�b�v�̍X�V
	pMap->Update();

	// �v���C���[�̍X�V
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();
	}

	// �����蔻��̍X�V
	Collision();

	// 2D�I�u�W�F�N�g�̍X�V
	for (auto &Object : UIObject)
	{
		Object->Update();
	}

	// �G�t�F�N�g�}�l�[�W���̍X�V
	pEffectManager->Update();

	// 3D�I�u�W�F�N�g�̍X�V
	for (auto &Obj3D : object3d)
	{
		Obj3D->Update();
	}

	// �^�C�}�[�̍X�V
	pTimer->Update();

	// ���U���g��ʂ֑J�ڂ��Ă������m�F
	CheckResult();

	// �f�o�b�O
	Debug();
}

//=============================================================================
// �`��
//=============================================================================
void SceneGame::Draw()
{
	// �}�b�v�̕`��
	pMap->Draw();

	// �G�t�F�N�g�}�l�[�W���̕`��
	pEffectManager->Draw();

	// 3D�I�u�W�F�N�g�̕`��
	for (auto &Obj3D : object3d)
	{
		Obj3D->Draw();
	}

	// �v���C���[�̕`��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}

	// 2D�I�u�W�F�N�g�̕`��
	for (auto &Object : UIObject)
	{
		Object->Draw();
	}

	// �^�C�}�[�̕`��
	pTimer->Draw();
}

//=============================================================================
// �����蔻��̍X�V
//=============================================================================
void SceneGame::Collision()
{
	// �v���C���[�ƃ}�b�v�̓����蔻��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->GroundCollider();
		pPlayer[i]->HorizonCollider();
		pPlayer[i]->ObjectCollider();
		pPlayer[i]->ObjectItemCollider(pMap);
	}

	// �v���C���[�ƃy�C���g�}�l�[�W���̓����蔻��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->PaintCollider();
	}

	// �y�C���g�}�l�[�W�����m�̓����蔻��
	for (int TenDigit = 1; TenDigit <= 4; TenDigit++)
	{
		for (int OneDigit = 1; OneDigit <= 4; OneDigit++)
		{
			// ��ʂ�16�����A���ꂼ��̃I�u�W�F�N�g�𔻒肷��
			HitCheckSToS(Quadtree, (TenDigit * 10 + OneDigit));
		}
	}

	// �t�B�[���h��ɔ��������A�C�e���Ƃ̓����蔻��
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		for (int nItem = 0; nItem < PLAYER_MAX; nItem++)
		{
			if (nPlayer != nItem)
			{
				pPlayer[nPlayer]->FieldItemCollider(pPlayer[nItem]->GetFieldItemManager());
			}
		}
	}

	// �t�B�[���h�I�u�W�F�N�g�ƃy�C���g�}�l�[�W���̓����蔻��
	for (int TenDigit = 1; TenDigit <= 4; TenDigit++)
	{
		for (int OneDigit = 1; OneDigit <= 4; OneDigit++)
		{
			// ��ʂ�16�����A���ꂼ��̃I�u�W�F�N�g�𔻒肷��
			pMap->PaintCollider(Quadtree, (TenDigit * 10 + OneDigit));
		}
	}

	// �l���؂��X�V����
	Quadtree->Update();

}

//=============================================================================
// �J�n����
//=============================================================================
void SceneGame::Start()
{
	// �X�^�[�g�^�C�}�[�X�V
	startframe++;
	
	if (startframe == START_FRAME)
	{
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			pPlayer[i]->SetPlayable(true);
		}

		pTimer->Start();
	}
}

//=============================================================================
// ���U���g��ʂ֑J�ڂ��Ă������m�F
//=============================================================================
void SceneGame::CheckResult()
{
	// �S���S�[��or�Q�[���I�[�o�[�Ȃ�V�[���J�ډ\
	if (result)
	{
		// �^�C�}�[�X�g�b�v
		pTimer->Stop();

		for (int pNo = 0; pNo < PLAYER_MAX; pNo++)
		{
			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(pNo, BUTTON_C))
			{
				SetScene(new SceneResult(), nSceneResult);
				InitCamera();
				return;
			}
		}
	}

	// �S�����S�[��or�Q�[���I�[�o�[�ɂȂ������m�F
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (data[i].rank != -1)
		{
			result = true;
		}
		else
		{
			result = false;
			break;
		}
	}

	for (int pNo = 0; pNo < PLAYER_MAX; pNo++)
	{
		bool hit = false;
		// ���łɂ��̃v���C���[�̌��ʂ����U���g���ʔz��ɓo�^����Ă��邩�m�F
		for (int rNo = 0; rNo < PLAYER_MAX; rNo++)
		{
			if (data[rNo].rank != pNo)
			{
				hit = false;
			}
			else
			{
				hit = true;
				break;
			}
		}

		if (!hit)
		{
			// �܂����ʂ��o�^����Ă��Ȃ��ꍇ
			InsertResult(pNo);
		}
	}
}

//=============================================================================
// ���U���g���ʔz��Ƀf�[�^�̑}��
//=============================================================================
void SceneGame::InsertResult(int pNo)
{
	// �Q�[���I�[�o�[�m�F
	if (!pPlayer[pNo]->GetOnCamera())
	{
		// ���U���g���ʔz��̌�납�����Ă���
		for (int rNo = PLAYER_MAX - 1; rNo > 0; rNo--)
		{
			if (data[rNo].rank == -1)
			{
				data[rNo].rank = pNo;
				data[rNo].time = 359999;
				break;
			}
		}
	}

	// �S�[���m�F
	if (pPlayer[pNo]->GetPos().x >= GOAL_POS.x)
	{
		// ���U���g���ʔz��̑O�������Ă���
		for (int rNo = 0; rNo < PLAYER_MAX; rNo++)
		{
			if (data[rNo].rank == -1)
			{
				data[rNo].rank = pNo;
				data[rNo].time = pTimer->Check();
				break;
			}
		}
	}
}

//=============================================================================
// �f�o�b�O
//=============================================================================
void SceneGame::Debug()
{
#ifndef _DEBUG_
	BeginDebugWindow("Result");

	DebugText("All Goal or Gameover : %s", result ? "True" : "False");
	DebugText("No1:%d No2:%d No3:%d No4:%d", data[0].rank, data[1].rank, data[2].rank, data[3].rank);
	DebugText("ResultTime\nNo1:%d No2:%d No3:%d No4:%d", data[0].time, data[1].time, data[2].time, data[3].time);

	EndDebugWindow("Result");

#endif
}

//=============================================================================
// ���ʂ̃Q�b�^�[
//=============================================================================
ResultData *SceneGame::GetResultData(int playerNo)
{
	return &data[playerNo];
}