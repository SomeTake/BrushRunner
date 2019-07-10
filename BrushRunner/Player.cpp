//=============================================================================
//
// �v���C���[�N���X[Player.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Debugproc.h"
#include "Input.h"
#include "SceneGame.h"
#include "D3DXAnimation.h"
#include "Camera.h"
#include "DebugWindow.h"
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
// ���ɒ������K�v�����Ȃ�
#define OBJECT_HIT_COUNTER	(10)				// �I�u�W�F�N�g�Ƀq�b�g�����Ƃ��L���ɂȂ�܂ł̃t���[����
#define MOVE_SPEED			(2.0f)				// �����X�s�[�h

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
Player::Player(int _CtrlNum, D3DXVECTOR3 firstpos) : state(nullptr)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// xFile��ǂݍ���
	this->Load_xFile(CharaModel[KouhaiModel], "Player");

	// �A�j���[�V�����Z�b�g��ݒu����
	this->CreateAnimSet();

	// ���݂̃A�j���[�V�������A�C�h����ԂƂ���
	this->ChangeAnim(Idle);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos = firstpos;
	rot = PLAYER_ROT;
	scl = ModelScl[KouhaiModel];
	hitGround = false;
	hitPaint = false;
	runSpd = 1.0f;
	jumpSpd = 0.0f;
	ctrlNum = _CtrlNum;
	inkType = ColorInk;
	hitHorizon = false;
	playable = false;
	onCamera = true;
	hitItem = false;
	animSpd = 1.0f;
	hitObjCnt = 0;
	jumpValue = 1.0f;

	spike = false;
	gun = false;
	blind = false;
	spink = false;

	for (int i = 0; i < InkNum; i++)
	{
		inkValue[i] = INK_MAX;
	}

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
	delete state;
	delete itemManager;
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

		// �C���N�ύX
		ChangeInk();

		// �A�j���[�V�������X�V
		this->UpdateAnim(TIME_PER_FRAME * animSpd);

		// ��Ԓ��ۃC���^�[�t�F�[�X�̍X�V
		UpdateState(this->GetAnimCurtID());

		// �J����������
		CheckOnCamera();

		// �t�B�[���h��ɐ��������A�C�e���̍X�V
		itemManager->Update();
		
		// �t�B�[���h��ɐ��������A�C�e���̃`�F�b�N
		itemManager->Check();
	}

	// �f�o�b�O�\��������
	Debug();
}

//=====================================================================================================
// �`��
//=====================================================================================================
void Player::Draw()
{
	if (onCamera && !blind)
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

	// �t�B�[���h��ɐ��������A�C�e���̕`��
	itemManager->Draw();
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
// �C���N�̎�ތ���
//=====================================================================================================
void Player::ChangeInk()
{
	if (GetKeyboardTrigger(DIK_P) || IsButtonTriggered(ctrlNum, BUTTON_R1))
	{
		// �����J���[
		if (inkType == BlackInk)
		{
			inkType = ColorInk;
		}
		// �J���[����
		else
		{
			inkType = BlackInk;
		}

		// �C���N�o�[�̕`�揇�����ւ�
		ChangeDrawOrder(NumInkblack00 + ctrlNum, NumInkblue + ctrlNum);
		// �t���[���̕`�揇�����ւ�
		ChangeDrawOrder(NumBlackFrame00 + ctrlNum, NumColorFrame00 + ctrlNum);
	}
}

//=====================================================================================================
// �ړ�
//=====================================================================================================
void Player::Move()
{
	// �I�[�g�ړ�
	if (!hitHorizon && playable && pos.x < GOAL_POS.x && GetAnimCurtID() != Slip)
	{
		pos.x += MOVE_SPEED * runSpd;
	}

	// �󒆔���
	JumpMove();

#if _DEBUG
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	pos.x += MOVE_SPEED;
	//}
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	pos.x -= MOVE_SPEED;
	//}
#endif
}

//=====================================================================================================
// �W�����v�ړ�
//=====================================================================================================
void Player::JumpMove()
{
	pos.y += jumpSpd * jumpValue;
	// �����ő呬�x�����x���ꍇ�A�������x���d�͉����x�ɍ��킹�ĉ�������
	if (jumpSpd > -FALL_VELOCITY_MAX)
	{
		jumpSpd -= STANDARD_GRAVITY;
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
// �A�j���[�V�����̃R�[���o�b�N
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
	if ((pos.x > camera->at.x - DRAW_RANGE.x) && (pos.x < camera->at.x + DRAW_RANGE.x))
	{
		// ��
		if ((pos.y > camera->at.y - DRAW_RANGE.y) && (pos.y < camera->at.y + DRAW_RANGE.y))
		{
			onCamera = true;
		}
		else
		{
			onCamera = false;
		}
	}
	else
	{
		onCamera = false;
	}
}

//=====================================================================================================
// �}�b�v�Ƃ̓����蔻��
//=====================================================================================================
void Player::GroundCollider(Map *pMap)
{
	// �㏸���͔��肵�Ȃ�
	if (jumpSpd <= 0)
	{
		// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
		int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
		int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

		// �����蔻����m�F����}�b�v�`�b�v�̏ꏊ
		D3DXVECTOR3 mappos;
		mappos.x = MAP_POS.x + CHIP_SIZE * x;
		mappos.y = MAP_POS.y + CHIP_SIZE * y;
		mappos.z = 0.0f;

		// �}�b�v�O����
		if (x < 0 || y > 0)
		{
			hitGround = false;
			return;
		}

		// ���ݍ��W������Ƃ���ɂȂɂ��I�u�W�F�N�g������΃q�b�g���Ă���
		if (pMap->GetMapTbl(x, y) >= 0)
		{
			// �߂荞�݂��C��
			pos.y = max(mappos.y + (CHIP_SIZE / 2) - 0.01f, pos.y);
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
void Player::PaintCollider(PaintManager *pPManager)
{
	for (auto &Paint : pPManager->GetColorPaint())
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
void Player::HorizonCollider(Map *pMap)
{
	// �v���C���[�̍��W���瓖���蔻����擾����}�b�v�`�b�v�̔ԍ����擾
	int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

	// �������猩�ĉE��Ȃ̂�
	x++;
	y++;

	// �}�b�v�O
	if (x < 0 || y > 0)
	{
		hitHorizon = false;
		return;
	}

	// �e�[�u���𒲂ׂ�0�ȏ�Ȃ�q�b�g
	if (pMap->GetMapTbl(x,y) >= 0)
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
// �t�B�[���h�I�u�W�F�N�g�Ƃ̓����蔻��
//=====================================================================================================
void Player::ObjectCollider(Map *pMap)
{
	// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
	int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

	// �}�b�v�O����
	if (x < 0 || y > 0)
	{
		runSpd = 1.0f;
		hitObjCnt = 0;
		return;
	}

	int objType = pMap->GetObjTbl(x, -y);

	HitObjectInfluence(objType);

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
	case OBJ_NUM_SPDUP:
		if (!spike)
		{
			runSpd = 2.0f;
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_SPDDOWN:
		if (!spike)
		{
			runSpd = 0.5f;
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_NUMA:
		if (!spike)
		{
			runSpd = 0.5f;
			jumpValue = 0.5f;
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		hitObjCnt = 0;
		break;

	case OBJ_NUM_JUMP:
		jumpSpd = JUMP_SPEED;
		ChangeAnim(Jump);
		ChangeState(new JumpState(this));

	case OBJ_NUM_DRAIN:
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				inkValue[BlackInk] = max(--inkValue[BlackInk], 0);
				inkValue[ColorInk] = max(--inkValue[ColorInk], 0);
			}
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_HEAL:
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				inkValue[BlackInk] = min(++inkValue[BlackInk], INK_MAX);
				inkValue[ColorInk] = min(++inkValue[ColorInk], INK_MAX);
			}
		}

		// ���̃X�e�[�^�X�̓��Z�b�g
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_ITEM:
		hitItem = true;

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
	//PrintDebugProc("PLAYER[%d] POS X:%f, Y:%f, Z:%f\n", ctrlNum, pos.x, pos.y, pos.z);
	//PrintDebugProc("PLAYER[%d] MOVE X:%f, Y:%f, Z:%f\n", ctrlNum, move.x, move.y, move.z);
	//PrintDebugProc("PLAYER[%d] INK TYPE %s\n", ctrlNum, inkType ? "Balck" : "Color");
	//PrintDebugProc("PLAYER[%d] INK VALUE COLOR %d\n", ctrlNum, inkValue[ColorInk]);
	//PrintDebugProc("PLAYER[%d] INK VALUE BLACK %d\n", ctrlNum, inkValue[BlackInk]);
	//PrintDebugProc("PLAYER[%d] JUMP FLAG:%d\n", ctrlNum, jumpFlag);
	//PrintDebugProc("PLAYER[%d] JUMP SPEED:%f\n", ctrlNum, jumpSpeed);
	//PrintDebugProc("PLAYER[%d] OnCamera:%s\n", ctrlNum, use ? "OnCamera" : "OffCamera");

	BeginDebugWindow("Player");

	DebugText("[%d] POS X:%f Y:%f Z:%d\n", ctrlNum, pos.x, pos.y, pos.z);
	DebugText("[%d] HitGround:%s HitPaint:%s HitHorizon:%s\n", ctrlNum, hitGround ? "True" : "False", hitPaint ? "True" : "False", hitHorizon ? "True" : "False");
	DebugText("[%d] AnimID:%d",ctrlNum, this->GetAnimCurtID());
	DebugText("[%d] HitObjCnt:%d", ctrlNum, hitObjCnt);

	EndDebugWindow("Player");

	if (GetKeyboardPress(DIK_LEFT))
	{
		if (inkValue[inkType] > 0)
		{
			inkValue[inkType]--;
		}
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		if (inkValue[inkType] < INK_MAX)
		{
			inkValue[inkType]++;
		}
	}
#endif

}