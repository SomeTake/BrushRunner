//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "Map.h"
#include "Camera.h"
#include "Collision.h"
#include "Input.h"
#include "MyLibrary.h"

//2d obj
#include "Frame01.h"
#include "Faceframe.h"
#include "CountDown.h"
#include "Item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �I�u�W�F�N�g�̃|�C���^
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneGame::SceneGame()
{
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

	// ���\������t���[���̏�����
	UIObject.push_back(new FaceFrame(FACEFRAME_POS01));
	UIObject.push_back(new FaceFrame(FACEFRAME_POS02));
	UIObject.push_back(new FaceFrame(FACEFRAME_POS03));
	UIObject.push_back(new FaceFrame(FACEFRAME_POS04));

	// �J�E���g�_�E���̏�����
	UIObject.push_back(new CountDown());

	// �A�C�e���\���̏�����
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		UIObject.push_back(new Item(ItemPos[i], pPlayer[i]));
	}

	// �G�t�F�N�g�}�l�[�W��
	pEffectManager = new EffectManager();
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
}

//=============================================================================
// �X�V
//=============================================================================
void SceneGame::Update()
{
	static int startframe = 0;

	// �X�^�[�g�^�C�}�[�X�V
	if (startframe < START_FRAME)
	{
		startframe++;
	}
	if (startframe == START_FRAME)
	{
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			pPlayer[i]->SetPlayable(true);
		}
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
}

//=============================================================================
// �`��
//=============================================================================
void SceneGame::Draw()
{
	// �}�b�v�̕`��
	pMap->Draw();

	// 2D�I�u�W�F�N�g�̕`��
	for (auto &Object : UIObject)
	{
		Object->Draw();
	}

	// �v���C���[�̕`��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}

	// �G�t�F�N�g�}�l�[�W���̕`��
	pEffectManager->Draw();
}

#if 1

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

#endif
