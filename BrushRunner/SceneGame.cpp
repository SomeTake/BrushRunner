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

//2d obj
#include "Frame01.h"
#include "Face.h"
#include "Face2.h"
#include "Face3.h"
#include "Face4.h"
#include "CountDown.h"
#include "Item.h"

#include "Sound.h"
static int ResultRank[PLAYER_MAX];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneGame::SceneGame()
{
	startframe = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		ResultRank[i] = -1;
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

	// ��
	pSky = new Sky();
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

	// ��̍폜
	delete pSky;
}

//=============================================================================
// �X�V
//=============================================================================
void SceneGame::Update()
{
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

	// ��̍X�V
	pSky->Update();

	// ���U���g��ʂ֑J�ڂ��Ă������m�F
	CheckResult();

	Debug();
}

//=============================================================================
// �`��
//=============================================================================
void SceneGame::Draw()
{
	// ��̕`��
	pSky->Draw();

	// �}�b�v�̕`��
	pMap->Draw();

	// �G�t�F�N�g�}�l�[�W���̕`��
	pEffectManager->Draw();

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
		for (int pNo = 0; pNo < PLAYER_MAX; pNo++)
		{
			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(pNo, BUTTON_C))
			{
				SetScene(nSceneResult);
				StopSound(BGM_TRAINING);
			}
		}

		return;
	}

	// �S�����S�[��or�Q�[���I�[�o�[�ɂȂ������m�F
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (ResultRank[i] != -1)
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
			if (ResultRank[rNo] != pNo)
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
			if (ResultRank[rNo] == -1)
			{
				ResultRank[rNo] = pNo;
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
			if (ResultRank[rNo] == -1)
			{
				ResultRank[rNo] = pNo;
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
	DebugText("No1:%d No2:%d No3:%d No4:%d", ResultRank[0], ResultRank[1], ResultRank[2], ResultRank[3]);

	EndDebugWindow("Result");

#endif
}

//=============================================================================
// ���ʌ��ʂ̃Q�b�^�[
//=============================================================================
int *GetResultRank(int no)
{
	return &ResultRank[no];
}