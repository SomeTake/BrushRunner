//=============================================================================
//
// �v���C���[�N���X[Player.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Input.h"
#include "SceneGame.h"
#include "Camera.h"
#include "DebugWindow.h"
#include "Map.h"
#include "Collision.h"
#include "PaintManager.h"
#include "IdleState.h"
#include "MyLibrary.h"
#include "JumpState.h"
#include "StopState.h"
#include "SlipState.h"
#include "Item.h"
#include "Timer.h"
#include "ResourceManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"						// �ǂݍ��ރ��f����(�t�@�C���p�X��)
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// �����̌���
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define MOVE_SPEED			(2.0f)										// �����X�s�[�h
//#define DefaultPosition		D3DXVECTOR3(145.0f, 0.0f, 0.0f)				// �v���C���[�����ʒu
#define DefaultPosition		D3DXVECTOR3(50.0f, 0.0f, 0.0f)				// �v���C���[�����ʒu
// ���ɒ������K�v�����Ȃ�
#define OBJECT_HIT_COUNTER	(5)											// �I�u�W�F�N�g�Ƀq�b�g�����Ƃ��L���ɂȂ�܂ł̃t���[����
#define MOVE_SPEED			(2.0f)										// �����X�s�[�h
#define FALL_VELOCITY_MAX	(20.0f)										// �ő�̗������x
#define STANDARD_GRAVITY	(0.98f)										// �d�͉����x
#define OBJECT_HIT_SIZE		D3DXVECTOR2(20.0f, 60.0f)					// �����蔻����擾����T�C�Y
#define JETPACK_VALUE		(1.5f)										// �W�F�b�g�p�b�N�������̏㏸�l
#define PowerBanana_VALUE	(2.0f)										// �p���[�o�i�i�g�p���̏㏸�l

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// ���[�V�����I��
	e_MotionChange,				// ���[�V������ύX����
};

//=====================================================================================================
// �R���X�g���N�^
//=====================================================================================================
Player::Player(int _CtrlNum, bool AIUse) : state(nullptr)
{
	// xFile��ǂݍ���
	ResourceManager::Instance()->GetMesh("Player", &model);

	// ���݂̃A�j���[�V�������A�C�h����ԂƂ���
	this->model->ChangeAnim(Idle);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	model->pos = DefaultPosition - D3DXVECTOR3(15.0f * _CtrlNum, 0.0f, 0.0f);
	model->rot = PLAYER_ROT;
	model->scl = ModelScl[KouhaiModel];
	hitGround = false;
	hitPaint = false;
	runSpd = 1.0f;
	jumpSpd = 0.0f;
	ctrlNum = _CtrlNum;
	if (AIUse)
	{
		this->AI = new CharacterAI(ctrlNum);
		this->AIUse = true;
		this->PaintSystem = new PaintManager(ctrlNum, true, this->AI);
	}
	else
	{
		this->AI = nullptr;
		this->AIUse = false;
		this->PaintSystem = new PaintManager(ctrlNum, false, nullptr);
	}
	this->playerUI = new PlayerUI(ctrlNum);
	hitHorizon = false;
	playable = false;
	onCamera = true;
	hitItem = false;
	//animSpd = 1.0f;
	hitObjCnt = 0;
	jumpValue = 1.0f;

	spike = false;
	//gun = false;
	blind = false;

	// �ҋ@��Ԃ���X�^�[�g����
	state = new IdleState(this);

	// �t�B�[���h��̃A�C�e���Ǘ��N���X������
	itemManager = new FieldItemManager();
}

//=====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
Player::~Player()
{
	SAFE_DELETE(this->AI);
	SAFE_DELETE(this->PaintSystem);
	SAFE_DELETE(this->state);
	SAFE_DELETE(this->itemManager);
	SAFE_DELETE(this->playerUI);
	model = nullptr;
}

//=====================================================================================================
// �X�V
//=====================================================================================================
void Player::Update()
{
	if (onCamera)
	{
		// �ړ�
		Move();

		// AI�̍X�V����
		if (AIUse)
		{
			AI->Update(this->model->pos);
		}

		// �y�C���g�V�X�e���̍X�V����
		PaintSystem->Update();

		// �v���C���[UI�̍X�V����
		playerUI->Update(this->model->pos);

		// �A�j���[�V�������X�V
		model->Update();

		// ��Ԓ��ۃC���^�[�t�F�[�X�̍X�V
		UpdateState(this->model->GetAnimCurtID());

		// �J����������
		CheckOnCamera();

		// �t�B�[���h��ɐ��������A�C�e���̍X�V
		itemManager->Update();
	}

	// �f�o�b�O�\��������
	Debug();
}

//=====================================================================================================
// �`��
//=====================================================================================================
void Player::Draw()
{
	if (onCamera)
	{
		if (!blind)
		{
			// ���f���̕`��
			model->Draw();
		}

		// �v���C���[UI�̕`��
		//playerUI->Draw(onCamera, blind);

		// �y�C���g�̕`��
		PaintSystem->Draw();

		// �v���C���[UI�̕`��
		playerUI->Draw(onCamera, blind);

	}
	// �v���C���[���S��UI
	else
	{
		// �v���C���[UI�̕`��()
		playerUI->Draw(onCamera, blind);
	}

	// �t�B�[���h��ɐ��������A�C�e���̕`��
	itemManager->Draw();

#if _DEBUG
	if (this->AI != nullptr)
	{
		AI->Draw();
	}
#endif
}

//=====================================================================================================
// ��Ԓ��ۃC���^�[�t�F�[�X�̍X�V
//=====================================================================================================
void Player::UpdateState(int AnimCurtID)
{
	state->Update(AnimCurtID);
}

//=====================================================================================================
// ��Ԓ��ۃC���^�[�t�F�[�X�̕ύX
//=====================================================================================================
void Player::ChangeState(PlayerState *NewState)
{
	delete state;
	state = NewState;
}

//=====================================================================================================
// �ړ�
//=====================================================================================================
void Player::Move()
{
	if (onCamera)
	{
		// �I�[�g�ړ�
		if (!hitHorizon && playable && model->pos.x < GOAL_POS.x && model->GetAnimCurtID() != Slip && model->GetAnimCurtID() != Stop)
		{
			if (!PowerBanana)
			{
				model->pos.x += MOVE_SPEED * runSpd;
			}
			else
			{
				model->pos.x += MOVE_SPEED * 2.0f;
			}
		}
	}

	// �󒆔���
	JumpMove();
}

//=====================================================================================================
// �W�����v�ړ�
//=====================================================================================================
void Player::JumpMove()
{
	model->pos.y += jumpSpd;
	// �����ő呬�x�����x���ꍇ�A�������x���d�͉����x�ɍ��킹�ĉ�������
	if (jumpSpd > -FALL_VELOCITY_MAX)
	{
		jumpSpd -= STANDARD_GRAVITY;
	}

	//// �W�F�b�g�p�b�N�������̓W�����v�̓A�b�v
	//if (jet)
	//{
	//	jumpValue = JETPACK_VALUE;
	//}
	//else if (PowerBanana)
	//{
	//	jumpValue = PowerBanana_VALUE;
	//}
	//else
	//{
	//	jumpValue = 1.0f;
	//}
}

////=====================================================================================================
//// �A�j���[�V�����̃Z�b�g
////=====================================================================================================
//void Player::CreateAnimSet()
//{
//	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
//	vector<KEYDATA>Keydata;
//	Keydata.reserve(Keydata_Max);
//
//	for (int Set_No = 0; Set_No < GetAnimSetNum(); Set_No++)
//	{
//		switch (Set_No)
//		{
//		case Idle:
//
//			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
//			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Running:
//
//			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
//			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Jump:
//
//			Keydata.push_back(KEYDATA{ 0.80f, e_MotionEnd });
//			AnimationSet->SetData("Jump", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Victory:
//
//			AnimationSet->SetData("Victory", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Slip:
//
//			Keydata.push_back(KEYDATA{ 0.95f, e_MotionChange });
//			AnimationSet->SetData("Slip", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Stop:
//
//			AnimationSet->SetData("Stop", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		default:
//			break;
//		}
//
//		this->SetupCallbackKeys(&Keydata, AnimationSet->GetSetName());
//
//		AnimationSet->SetAnimSetPtr(this->AnimController);
//
//		this->AnimSet.push_back(*AnimationSet);
//
//		Keydata.clear();
//	}
//
//	SAFE_DELETE(AnimationSet);
//	ReleaseVector(Keydata);
//}
//
////=====================================================================================================
//// �A�j���[�V����CallbackKey�̏����C�x���g
////=====================================================================================================
//HRESULT CALLBACK Player::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
//{
//	int eventNo = (int)pCallbackData;
//
//	switch (eventNo)
//	{
//	case e_MotionEnd:
//		animSpd = 0.0f;
//		break;
//	case e_MotionChange:
//		playable = true;
//		ChangeAnim(Idle);
//		ChangeState(new IdleState(this));
//		break;
//	default:
//		break;
//	}
//
//	return S_OK;
//}

//=====================================================================================================
// �J����������
//=====================================================================================================
void Player::CheckOnCamera()
{
	CAMERA *camera = GetCamera();

	// �c
	if (model->pos.x > camera->at.x - DRAW_RANGE.x)
	{
		onCamera = true;
	}
	else
	{
		onCamera = false;
		playerUI->SetPlayerDeadTexture();

		// �G�t�F�N�g����
		D3DXVECTOR3 setpos = model->pos;
		setpos.z -= 1.0f;
		setpos.x += 150.0f;
		std::vector<Effect3D*> *Effect3DVector = GetEffect3DVector();
		Effect3D *effect = new Effect3D(DeadEffect3D, setpos, 1);
		Effect3DVector->push_back(effect);

		// PlaySound(������)
	}
}

//=====================================================================================================
// �}�b�v�Ƃ̓����蔻��
//=====================================================================================================
void Player::GroundCollider()
{
	// �㏸���͔��肵�Ȃ�
	if (jumpSpd <= 0)
	{
		// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
		int x, y;
		Map::GetMapChipXY(model->pos, &x, &y);

		D3DXVECTOR3 mappos = Map::GetMapChipPos(x, y, eCenterUp);

		// ���ݍ��W������Ƃ���ɂȂɂ��I�u�W�F�N�g������΃q�b�g���Ă���
		if (Map::GetMapTbl(x, y) >= 0)
		{
			// �߂荞�݂��C��
			model->pos.y = max(mappos.y - 0.01f, model->pos.y);
			jumpSpd = 0.0f;
			model->SetAnimSpd(1.0f);
			hitGround = true;
			return;
		}
		else
		{
			hitGround = false;
		}
	}
	else
	{
		hitGround = false;
	}
}

//=====================================================================================================
// �y�C���g�Ƃ̓����蔻��
//=====================================================================================================
void Player::PaintCollider()
{
	// �㏸���͔��肵�Ȃ�
	if (jumpSpd <= 0)
	{
		for (auto &Paint : PaintSystem->GetColorPaint())
		{
			if (!Paint->GetUse())
				continue;

			// �ЂƂЂƂ̃y�C���g�ƃv���C���[�̓����蔻����s��
			if (HitSphere(model->pos, Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
			{
				// ���������ꍇ�A�v���C���[�̍��W���C��
				model->pos.y = max(Paint->GetPos().y + PAINT_WIDTH * 0.1f, model->pos.y);
				jumpSpd = 0.0f;
				model->SetAnimSpd(1.0f);
				hitPaint = true;
				return;
			}
			else
			{
				hitPaint = false;
			}
		}
	}
	else
	{
		hitPaint = false;
	}
}

//=====================================================================================================
// �O���̃}�b�v�Ƃ̓����蔻��
//=====================================================================================================
void Player::HorizonCollider()
{
	// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
	int x, y;
	Map::GetMapChipXY(model->pos, &x, &y);

	// �������猩�ĉE��Ȃ̂�
	x++;
	y--;

	// �e�[�u���𒲂ׂ�0�ȏ�Ȃ�q�b�g
	if (Map::GetMapTbl(x, y) >= 0)
	{
		hitHorizon = true;
		return;
	}
	else
	{
		hitHorizon = false;
		return;
	}
}

//=====================================================================================================
// �t�B�[���h�I�u�W�F�N�g�i�����j�Ƃ̓����蔻��
//=====================================================================================================
void Player::ObjectCollider()
{
	// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
	int x, y;
	Map::GetMapChipXY(model->pos, &x, &y);

	int objType = Map::GetObjTbl(x, y);

	HitObjectInfluence(objType);
}

//=====================================================================================================
// �t�B�[���h�I�u�W�F�N�g�i�A�C�e���j�Ƃ̓����蔻��
//=====================================================================================================
void Player::ObjectItemCollider(Map *pMap)
{
	// �A�C�e�����擾���Ă����ԂȂ画�肵�Ȃ�
	if (hitItem)
	{
		return;
	}

	D3DXVECTOR3 colliderpos = model->pos;
	colliderpos.y += OBJECT_HIT_SIZE.y * 0.5f;

	for (auto &Obj : pMap->GetObjectChip())
	{
		if (Obj->GetTextureNum() != eObjItem)
		{
			continue;
		}

		if (HitCheckBB(colliderpos, Obj->GetPos(), OBJECT_HIT_SIZE, D3DXVECTOR2(CHIP_SIZE, CHIP_SIZE)))
		{
			hitItem = true;
			// PlaySound(�A�C�e���擾��)
			return;
		}
	}

	hitItem = false;
	return;
}

//=====================================================================================================
// �t�B�[���h��ɔ��������A�C�e���Ƃ̓����蔻��
//=====================================================================================================
void Player::FieldItemCollider(FieldItemManager *pFIManager)
{
	for (auto &item : pFIManager->GetItem())
	{
		if (HitCheckBB(model->pos, item->GetPos(), PLAYER_COLLISION_SIZE, FIELDITEM_SIZE))
		{
			switch (item->GetTexNo())
			{
				// �o�i�i�̔�
			case NumKawa:
				playable = false;
				model->ChangeAnim(Slip);
				ChangeState(new SlipState(this));
				break;
				// �g�����`�K��
			case NumGun:
				playable = false;
				model->ChangeAnim(Stop);
				ChangeState(new StopState(this));
				break;
			default:
				break;
			}
			item->SetUse(false);

			// �G�t�F�N�g�𔭐�
			std::vector<Effect3D*> *Effect3DVector = GetEffect3DVector();
			Effect3D *effect = new Effect3D(ExplosionEffect3D, model->pos, 1);
			Effect3DVector->push_back(effect);

			// PlaySound(�A�C�e���q�b�g��)
		}
	}
}

//=====================================================================================================
// �I�u�W�F�N�g�Ƀq�b�g���Ă���Ƃ��̌���
//=====================================================================================================
void Player::HitObjectInfluence(int type)
{
	// �������݂��Ȃ��Ƃ�
	if (type == -1)
	{
		runSpd = 1.0f;
		jumpValue = 1.0f;
		hitObjCnt = 0;
		return;
	}

	// �I�u�W�F�N�g�̎�ނɍ��킹�Č��ʕύX
	switch (type)
	{
	case eObjSpdup:

		if (!spike)
		{
			runSpd = 2.0f;
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case eObjSpddown:

		if (!spike)
		{
			runSpd = 0.5f;
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case eObjNuma:

		if (!spike)
		{
			runSpd = 0.5f;
			jumpValue = 0.5f;
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		hitObjCnt = 0;
		break;

	case eObjJump:

		jumpSpd = JUMP_SPEED * jumpValue;
		model->ChangeAnim(Jump);
		ChangeState(new JumpState(this));

	case eObjDrain:

		// ���Ԍo�߂ŃC���N����
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				int ink = PaintSystem->GetInkValue(BlackInk);
				PaintSystem->SetInkValue(max(--ink, 0), BlackInk);
				ink = PaintSystem->GetInkValue(ColorInk);
				PaintSystem->SetInkValue(max(--ink, 0), ColorInk);

				// PlaySound(�C���N�����鉹)
			}
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case eObjHeal:

		// ���Ԍo�߂ŃC���N����
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				int ink = PaintSystem->GetInkValue(BlackInk);
				PaintSystem->SetInkValue(min(++ink, INK_MAX), BlackInk);
				ink = PaintSystem->GetInkValue(ColorInk);
				PaintSystem->SetInkValue(min(++ink, INK_MAX), ColorInk);

				// PlaySound(�C���N���񕜂��鉹)
			}
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case eObjItem:

		// ���̃X�e�[�^�X�̓��Z�b�g
		hitObjCnt = 0;
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	default:
		break;
	}
}

//=====================================================================================================
// �f�o�b�O�\��&����
//=====================================================================================================
void Player::Debug()
{
#if _DEBUG

	if (!AIUse)
	{
		if (GetKeyboardPress(DIK_RIGHT))
		{
			switch (ctrlNum)
			{
			case 0:
				pos.x += MOVE_SPEED;
				break;
			case 1:
				pos.x += MOVE_SPEED * 0.8f;
				break;
			case 2:
				pos.x += MOVE_SPEED * 0.5f;
				break;
			case 3:
				pos.x += MOVE_SPEED * 0.2f;
				break;
			default:
				break;
			}
		}
		if (GetKeyboardPress(DIK_LEFT))
		{
			switch (ctrlNum)
			{
			case 0:
				pos.x -= MOVE_SPEED;
				break;
			case 1:
				pos.x -= MOVE_SPEED * 0.8f;
				break;
			case 2:
				pos.x -= MOVE_SPEED * 0.5f;
				break;
			case 3:
				pos.x -= MOVE_SPEED * 0.2f;
				break;
			default:
				break;
			}
		}
	}

	ImGui::SetNextWindowPos(ImVec2(5, 120), ImGuiSetCond_Once);

	BeginDebugWindow("Player");

	ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
	if (ImGui::TreeNode((void*)(intptr_t)ctrlNum, "Player %d", ctrlNum))
	{
		if (ImGui::TreeNode("Position"))
		{
			DebugText("Pos X:%.2f\nPos Y:%.2f\nPos Z:%.2f\n", model->pos.x, model->pos.y, model->pos.z);
			ImGui::TreePop();
		}

		DebugText("AnimSetName:%s\nCurrentFrame:%d / %d", this->model->GetCurtAnimName(), this->model->GetAnimCurtFrame(), this->model->GetAnimPeriodFrame());

		int x = 0, y = 0;
		Map::GetMapChipXY(model->pos, &x, &y);
		DebugText("X : %d  Y : %d", x, y);
		DebugText("MapTable : %d\nMapTable_Up : %d", Map::GetMapTbl(model->pos, eCenter), Map::GetMapTbl(model->pos, eCenterUp));

		ImGui::TreePop();
	}

	EndDebugWindow("Player");

#endif

}