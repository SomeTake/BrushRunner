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
#include "PaintSystem.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �ǂݍ��ރL�����N�^�[���f��
static const char* CharaModel[] =
{
	"data/MODEL/Boy.x",
	"data/MODEL/Shachiku/Shachiku.x",
	"data/MODEL/Kouhai/Kouhai.x",
};

// �L�����N�^�[���f���̔ԍ�
enum CharaModelNum
{
	BoyModel,
	ShachikuModel,
	KouhaiModel,

	// ���f���̎��
	MaxModel
};

// ���f���̑傫���ݒ�
static D3DXVECTOR3 ModelScl[MaxModel] =
{
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(0.4f, 0.4f, 0.4f)
};

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// ���[�V�����I��
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
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hitGround = false;
	hitPaint = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;
	inkType = ColorInk;
	hitHorizon = true;
	playable = false;
	onCamera = true;

	for (int i = 0; i < InkNum; i++)
	{
		inkValue[i] = INK_MAX;
	}

	// �ҋ@��Ԃ���X�^�[�g����
	new IdleState(this);
}

//=====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
Player::~Player()
{
	delete state;
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

		// �A�j���[�V�����Ǘ�
		AnimationManager();

		// �J����������
		CheckOnCamera();

		// ��Ԓ��ۃC���^�[�t�F�[�X�̍X�V
		UpdateState(this->GetAnimCurtID());

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
void Player::ChangeState(PlayerState *NewState, int NextAnimID)
{
	delete state;
	state = NewState;

	// �A�j���[�V�����ύX
	if (this->GetAnimCurtID() != NextAnimID)
	{
		this->ChangeAnim(NextAnimID);
	}
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
	// �}�b�v�ƃy�C���g�ǂ��炩�ɓ������Ă���Βn�㔻��
	if(hitGround || hitPaint)
	{
		// �W�����v
		if (playable)
		{
			if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(ctrlNum, BUTTON_B))
			{
				hitGround = false;
				hitPaint = false;
				hitHorizon = false;
				jumpSpeed = JUMP_SPEED;
				this->ChangeAnim(Jump);
			}
		}
	}
	else
	{
		pos.y += jumpSpeed;
		// �d��
		//Gravity();
	}

	// �I�[�g�ړ�
	if (!hitHorizon && playable)
	{
		pos.x += MOVE_SPEED;
	}

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
// �A�j���[�V�����Ǘ�
//=====================================================================================================
void Player::AnimationManager()
{
	// ����s��
	if (!playable)
	{
		if (this->GetAnimCurtID() != Idle)
		{
			this->ChangeAnim(Idle);
		}
	}
	else
	{
		if (hitGround && hitPaint)
		{
			// ���s��
			if (!hitHorizon)
			{
				if (this->GetAnimCurtID() != Running)
				{
					this->ChangeAnim(Running);
				}
			}
			// �ҋ@��
			else
			{
				if (this->GetAnimCurtID() != Idle)
				{
					this->ChangeAnim(Idle);
				}
			}
		}
	}

	// �A�j���[�V�������X�V
	this->UpdateAnim(TIME_PER_FRAME);

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

			Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Running:

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Jump:

			AnimationSet->SetData("Jump", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Victory:

			AnimationSet->SetData("Victory", NULL, 1.5f, 0.1f, 0.0f);
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
	// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
	int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

	// �����蔻����m�F����}�b�v�`�b�v�̏ꏊ
	D3DXVECTOR3 mappos;
	mappos.x = MAP_POS.x + CHIP_SIZE * x;
	mappos.y = MAP_POS.y + CHIP_SIZE * y;
	mappos.z = 0.0f;

	// �v���C���[�̑����̃}�b�v�`�b�v����E��̃}�b�v�`�b�v�̔ԍ�
	int frontx = x + 1;
	int fronty = y + 1;

	// �O���̃I�u�W�F�N�g�Ɉ��������邩�`�F�b�N(�W�����v���̓`�F�b�N���Ȃ�)
	if (!hitGround && !hitPaint)
	{
		if (pMap->GetMapTbl(frontx, fronty) >= 0)
		{
			hitHorizon = false;
		}
		else
		{
			hitHorizon = true;
		}
		
		return;
	}

	// �}�b�v�O����
	if (!HitCheckBB(pos, GetMapCenterPos(), PLAYER_COLLISION_SIZE, D3DXVECTOR2(MAP_SIZE_X * CHIP_SIZE, MAP_SIZE_Y * CHIP_SIZE)))
	{
		hitHorizon = true;
		hitGround = false;
		return;
	}

	// ���ݍ��W������Ƃ���ɂȂɂ��I�u�W�F�N�g������΃q�b�g���Ă���
	if (pMap->GetMapTbl(x, y) >= 0)
	{
		// �߂荞�݂��C��
		pos.y = mappos.y + (CHIP_SIZE / 2) - 0.01f;
		jumpSpeed = 0.0f;
		hitGround = true;
		return;
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
		{
			continue;
		}

		// �ЂƂЂƂ̃y�C���g�ƃv���C���[�̓����蔻����s��
		if (HitSphere(pos, Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
		{
			// ���������ꍇ�A�v���C���[�̍��W���C��
			pos.y = Paint->GetPos().y + PAINT_WIDTH * 0.1f;
			jumpSpeed = 0.0f;
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
	
}


//=====================================================================================================
// �d�͏���
//=====================================================================================================
void Player::Gravity()
{
	// �����ő呬�x�����x���ꍇ�A�������x���d�͉����x�ɍ��킹�ĉ�������
	if (jumpSpeed > -FALL_VELOCITY_MAX)
	{
		jumpSpeed -= STANDARD_GRAVITY;
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

	DebugText("[%d] POS X:%f Y:%f Z:%d", ctrlNum, pos.x, pos.y, pos.z);
	DebugText("[%d] HitGround:%s HitPaint:%s", ctrlNum, hitGround ? "True" : "False", hitPaint ? "True" : "False");

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