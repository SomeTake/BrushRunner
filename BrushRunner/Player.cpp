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
#include "D3DXAnimation.h"
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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"						// �ǂݍ��ރ��f����(�t�@�C���p�X��)
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// �����̌���
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define MOVE_SPEED			(2.0f)										// �����X�s�[�h
#define DefaultPosition		D3DXVECTOR3(145.0f, 0.0f, 0.0f)				// �v���C���[�����ʒu
// ���ɒ������K�v�����Ȃ�
#define OBJECT_HIT_COUNTER	(10)										// �I�u�W�F�N�g�Ƀq�b�g�����Ƃ��L���ɂȂ�܂ł̃t���[����
#define MOVE_SPEED			(2.0f)										// �����X�s�[�h
#define FALL_VELOCITY_MAX	(20.0f)										// �ő�̗������x
#define STANDARD_GRAVITY	(0.98f)										// �d�͉����x
#define OBJECT_HIT_SIZE		D3DXVECTOR2(20.0f, 60.0f)					// �����蔻����擾����T�C�Y
#define JETPACK_VALUE		(1.5f)										// �W�F�b�g�p�b�N�������̏㏸�l

// �ǂݍ��ރL�����N�^�[���f��
static const char* CharaModel[] =
{
	"data/MODEL/Shachiku/Shachiku.x",
	"data/MODEL/Kouhai/Kouhai.x",
};

// �L�����N�^�[���f���̔ԍ�
enum CharaModelNum
{
	ShachikuModel,
	KouhaiModel,

	// ���f���̎��
	MaxModel
};

// ���f���̑傫���ݒ�
static D3DXVECTOR3 ModelScl[MaxModel] =
{
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(0.4f, 0.4f, 0.4f)
};

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// ���[�V�����I��
	e_MotionChange,				// ���[�V������ύX����
};

//=====================================================================================================
// �R���X�g���N�^
//=====================================================================================================
Player::Player(int _CtrlNum) : state(nullptr)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// xFile��ǂݍ���
	this->Load_xFile(CharaModel[KouhaiModel], "Player");

	// �A�j���[�V�����Z�b�g��ݒu����
	this->CreateAnimSet();

	// ���݂̃A�j���[�V�������A�C�h����ԂƂ���
	this->ChangeAnim(Idle);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos = DefaultPosition - D3DXVECTOR3(15.0f * _CtrlNum, 0.0f, 0.0f);
	rot = PLAYER_ROT;
	scl = ModelScl[KouhaiModel];
	hitGround = false;
	hitPaint = false;
	runSpd = 1.0f;
	jumpSpd = 0.0f;
	ctrlNum = _CtrlNum;
	this->AI = new CharacterAI(true);
	this->PaintSystem = new PaintManager(ctrlNum, true);
	this->playerUI = new PlayerUI(ctrlNum);
	hitHorizon = false;
	playable = false;
	onCamera = true;
	hitItem = false;
	animSpd = 1.0f;
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
		AI->Update(this->pos, this->PaintSystem);

		// �y�C���g�V�X�e���̍X�V����
		PaintSystem->Update();

		// �v���C���[UI�̍X�V����
		playerUI->Update(this->pos);

		// �A�j���[�V�������X�V
		UpdateAnim(TIME_PER_FRAME * animSpd);

		// ��Ԓ��ۃC���^�[�t�F�[�X�̍X�V
		UpdateState(this->GetAnimCurtID());

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
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			D3DMATERIAL9 matDef;
			D3DXMATRIX WorldMtx, SclMtx, RotMtx, TransMtx;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&WorldMtx);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&SclMtx, scl.x, scl.y, scl.z);
			D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&SclMtx, rot.y, rot.x, rot.z);
			D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&TransMtx, pos.x, pos.y, pos.z);
			D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &TransMtx);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &WorldMtx);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �����_�����O
			this->DrawAnim(&WorldMtx);

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}

		// �v���C���[UI�̕`��
		playerUI->Draw(onCamera);

		// �y�C���g�̕`��
		PaintSystem->Draw();
	}
	else
	{
		// �v���C���[UI�̕`��(�v���C���[���S��UI)
		playerUI->Draw(onCamera);
	}

	// �t�B�[���h��ɐ��������A�C�e���̕`��
	itemManager->Draw();

#if _DEBUG
	this->AI->Draw();
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
		if (!hitHorizon && playable && pos.x < GOAL_POS.x && GetAnimCurtID() != Slip && GetAnimCurtID() != Stop)
		{
			pos.x += MOVE_SPEED * runSpd;
		}
	}
		// �󒆔���
		JumpMove();

#if _DEBUG
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
#endif
}

//=====================================================================================================
// �W�����v�ړ�
//=====================================================================================================
void Player::JumpMove()
{
	pos.y += jumpSpd;
	// �����ő呬�x�����x���ꍇ�A�������x���d�͉����x�ɍ��킹�ĉ�������
	if (jumpSpd > -FALL_VELOCITY_MAX)
	{
		jumpSpd -= STANDARD_GRAVITY;
	}

	// �W�F�b�g�p�b�N�������̓W�����v�̓A�b�v
	if (jet)
	{
		jumpValue = JETPACK_VALUE;
	}
}

//=====================================================================================================
// �A�j���[�V�����̃Z�b�g
//=====================================================================================================
void Player::CreateAnimSet()
{
	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
	vector<KEYDATA>Keydata;
	Keydata.reserve(Keydata_Max);

	for (int Set_No = 0; Set_No < GetAnimSetNum(); Set_No++)
	{
		switch (Set_No)
		{
		case Idle:

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Running:

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Jump:

			Keydata.push_back(KEYDATA{ 0.80f, e_MotionEnd });
			AnimationSet->SetData("Jump", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Victory:

			AnimationSet->SetData("Victory", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Slip:

			Keydata.push_back(KEYDATA{ 0.95f, e_MotionChange });
			AnimationSet->SetData("Slip", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Stop:

			AnimationSet->SetData("Stop", NULL, 1.5f, 0.1f, 0.0f);
			break;

		default:
			break;
		}

		this->SetupCallbackKeys(&Keydata, AnimationSet->GetSetName());

		AnimationSet->SetAnimSetPtr(this->AnimController);

		this->AnimSet.push_back(*AnimationSet);

		Keydata.clear();
	}

	SAFE_DELETE(AnimationSet);
	ReleaseVector(Keydata);
}

//=====================================================================================================
// �A�j���[�V����CallbackKey�̏����C�x���g
//=====================================================================================================
HRESULT CALLBACK Player::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
{
	int eventNo = (int)pCallbackData;

	switch (eventNo)
	{
	case e_MotionEnd:
		animSpd = 0.0f;
		break;
	case e_MotionChange:
		playable = true;
		ChangeAnim(Idle);
		ChangeState(new IdleState(this));
		break;
	default:
		break;
	}

	return S_OK;
}

//=====================================================================================================
// �J����������
//=====================================================================================================
void Player::CheckOnCamera()
{
	CAMERA *camera = GetCamera();

	// �c
	if (pos.x > camera->at.x - DRAW_RANGE.x)
	{
		onCamera = true;
	}
	else
	{
		onCamera = false;
		playerUI->SetPlayerDeadTexture();

		// �G�t�F�N�g����
		D3DXVECTOR3 setpos = pos;
		setpos.z -= 1.0f;
		std::vector<Effect3D*> *Effect3DVector = GetEffect3DVector();
		Effect3D *effect = new Effect3D(ExplosionEffect3D, setpos, 3);
		Effect3DVector->push_back(effect);
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
		Map::GetMapChipXY(pos, &x, &y);

		D3DXVECTOR3 mappos = Map::GetMapChipPos(x, y, eCenterUp);

		//// �}�b�v�O����
		//if (x < 0 || y > 0)
		//{
		//	hitGround = false;
		//	return;
		//}

		// ���ݍ��W������Ƃ���ɂȂɂ��I�u�W�F�N�g������΃q�b�g���Ă���
		if (Map::GetMapTbl(x, y) >= 0)
		{
			// �߂荞�݂��C��
			pos.y = max(mappos.y - 0.01f, pos.y);
			jumpSpd = 0.0f;
			animSpd = 1.0f;
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
	for (auto &Paint : PaintSystem->GetColorPaint())
	{
		if (!Paint->GetUse())
			continue;

		// �ЂƂЂƂ̃y�C���g�ƃv���C���[�̓����蔻����s��
		if (HitSphere(pos, Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
		{
			// ���������ꍇ�A�v���C���[�̍��W���C��
			pos.y = max(Paint->GetPos().y + PAINT_WIDTH * 0.1f, pos.y);
			jumpSpd = 0.0f;
			animSpd = 1.0f;
			hitPaint = true;
			return;
		}
		else
		{
			hitPaint = false;
		}
	}

}

//=====================================================================================================
// �O���̃}�b�v�Ƃ̓����蔻��
//=====================================================================================================
void Player::HorizonCollider()
{
	// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
	int x, y;
	Map::GetMapChipXY(pos, &x, &y);

	// �������猩�ĉE��Ȃ̂�
	x++;
	y--;

	// �}�b�v�O
	//if (x < 0 || y > 0)
	//{
	//	hitHorizon = false;
	//	return;
	//}

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
	Map::GetMapChipXY(pos, &x, &y);

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
		return;

	D3DXVECTOR3 colliderpos = pos;
	colliderpos.y += OBJECT_HIT_SIZE.y * 0.5f;

	for (auto &Obj : pMap->GetObjectChip())
	{
		if (Obj->GetTextureNum() != eObjItem)
			continue;

		if (HitCheckBB(colliderpos, Obj->GetPos(), OBJECT_HIT_SIZE, D3DXVECTOR2(CHIP_SIZE, CHIP_SIZE)))
		{
			hitItem = true;
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
		if (HitCheckBB(pos, item->GetPos(), PLAYER_COLLISION_SIZE, FIELDITEM_SIZE))
		{
			switch (item->GetTexNo())
			{
				// �o�i�i�̔�
			case NumKawa:
				playable = false;
				ChangeAnim(Slip);
				ChangeState(new SlipState(this));
				break;
				// �g�����`�K��
			case NumGun:
				playable = false;
				ChangeAnim(Stop);
				ChangeState(new StopState(this));
				break;
			default:
				break;
			}
			item->SetUse(false);
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
		ChangeAnim(Jump);
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
#ifndef _DEBUG_

	ImGui::SetNextWindowPos(ImVec2(5, 120), ImGuiSetCond_Once);

	BeginDebugWindow("Player");

	ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
	if (ImGui::TreeNode((void*)(intptr_t)ctrlNum, "Player %d", ctrlNum))
	{
		if (ImGui::TreeNode("Position"))
		{
			DebugText("Pos X:%.2f\nPos Y:%.2f\nPos Z:%.2f\n", pos.x, pos.y, pos.z);
			ImGui::TreePop();
		}

		DebugText("AnimSetName:%s\nCurrentFrame:%d / %d", this->GetCurtAnimName(), this->GetAnimCurtFrame(), this->GetAnimPeriodFrame());

		int x = 0, y = 0;
		Map::GetMapChipXY(pos, &x, &y);
		DebugText("X : %d  Y : %d", x, y);
		DebugText("MapTable : %d\nMapTable_Up : %d", Map::GetMapTbl(pos, eCenter), Map::GetMapTbl(pos, eCenterUp));

		ImGui::TreePop();
	}

	EndDebugWindow("Player");

#endif

}