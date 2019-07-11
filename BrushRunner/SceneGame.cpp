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
static std::vector<_2dobj*> UIObject;
static Map		*pMap;							// �}�b�v�p�̃|�C���^
static Effect	*pEffect[EffectMax];			// �G�t�F�N�g�p�̃|�C���^
static Player	*pPlayer[PLAYER_MAX];			// �v���C���[�p�̃|�C���^
static QUADTREE *Quadtree = nullptr;

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

	// �A�C�e���̏�����
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		UIObject.push_back(new Item(ItemPos[i], pPlayer[i]));
	}

#if 0
	// �|�b�v�A�b�v�̏�����
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
	//	pPop[i] = new Pop(pPlayer[i]);
	//}

	// ���C���N�̏�����
	//p2dobj[NumInkblack00] = new Ink(pPlayer[0], INKLINEBLACK_POS01, TEXTURE_INKGAUGEBLACK, BlackInk);
	//p2dobj[NumInkblack01] = new Ink(pPlayer[1], INKLINEBLACK_POS02, TEXTURE_INKGAUGEBLACK, BlackInk);
	//p2dobj[NumInkblack02] = new Ink(pPlayer[2], INKLINEBLACK_POS03, TEXTURE_INKGAUGEBLACK, BlackInk);
	//p2dobj[NumInkblack03] = new Ink(pPlayer[3], INKLINEBLACK_POS04, TEXTURE_INKGAUGEBLACK, BlackInk);

	// ���C���N�p�t���[���̏�����
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS01));
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS02));
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS03));
	//UIObject.push_back(new InkFrameBlack(BLACKINKFRAME_POS04));

	//p2dobj[NumBlackFrame00] = new InkFrameBlack(BLACKINKFRAME_POS01);
	//p2dobj[NumBlackFrame01] = new InkFrameBlack(BLACKINKFRAME_POS02);
	//p2dobj[NumBlackFrame02] = new InkFrameBlack(BLACKINKFRAME_POS03);
	//p2dobj[NumBlackFrame03] = new InkFrameBlack(BLACKINKFRAME_POS04);

	// �J���[�C���N�̏�����
	//p2dobj[NumInkblue] = new Ink(pPlayer[0], INKLINEBLUE_POS, TEXTURE_INKGAUGERED, ColorInk);
	//p2dobj[NumInkred] = new Ink(pPlayer[1], INKLINERED_POS, TEXTURE_INKGAUGEBLUE, ColorInk);
	//p2dobj[NumInkyellow] = new Ink(pPlayer[2], INKLINEYELLOW_POS, TEXTURE_INKGAUGEYELLOW, ColorInk);
	//p2dobj[NumInkgreen] = new Ink(pPlayer[3], INKLINEGREEN_POS, TEXTURE_INKGAUGEGREEN, ColorInk);

	// �J���[�C���N�p�t���[���̏�����
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS01));
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS02));
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS03));
	//UIObject.push_back(new InkFrameColor(COLORINKFRAME_POS04));
	//p2dobj[NumColorFrame00] = new InkFrameColor(COLORINKFRAME_POS01);
	//p2dobj[NumColorFrame01] = new InkFrameColor(COLORINKFRAME_POS02);
	//p2dobj[NumColorFrame02] = new InkFrameColor(COLORINKFRAME_POS03);
	//p2dobj[NumColorFrame03] = new InkFrameColor(COLORINKFRAME_POS04);


	//p2dobj[NumFaceframe00] = new FaceFrame(FACEFRAME_POS01);
	//p2dobj[NumFaceframe01] = new FaceFrame(FACEFRAME_POS02);
	//p2dobj[NumFaceframe02] = new FaceFrame(FACEFRAME_POS03);
	//p2dobj[NumFaceframe03] = new FaceFrame(FACEFRAME_POS04);


#endif

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

	// �G�t�F�N�g�̍폜
	for (int i = 0; i < EffectMax; i++)
	{
		SAFE_DELETE(pEffect[i]);
	}

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

	// �|�b�v�A�b�v�폜
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
	//	SAFE_DELETE(pPop[i]);
	//}
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

	// 2D�I�u�W�F�N�g�̍X�V
	for (auto &Object : UIObject)
	{
		Object->Update();
	}

	// �}�b�v�̍X�V
	pMap->Update();

	// �G�t�F�N�g�̍X�V
#if 0
	for (int i = 0; i < EffectMax; i++)
	{
		pEffect[i]->Update();
	}
#endif

	// �v���C���[�̍X�V
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();
	}

	// �����蔻��̍X�V
	Collision();

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

#if 0
	// �G�t�F�N�g�̕`��
	for (int i = 0; i < EffectMax; i++)
	{
		pEffect[i]->Draw();
	}
#endif
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
