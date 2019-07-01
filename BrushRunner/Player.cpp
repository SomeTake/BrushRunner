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
#include "Gravity.h"
#include "SceneGame.h"
#include "D3DXAnimation.h"
#include "Camera.h"

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
Player::Player(int _CtrlNum, D3DXVECTOR3 firstpos)
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
	jumpFlag = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;
	inkType = ColorInk;
	moveFlag = true;
	playable = false;
	use = true;

	for (int i = 0; i < InkNum; i++)
	{
		inkValue[i] = INK_MAX;
	}

}

//=====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
Player::~Player()
{

}

//=====================================================================================================
// �X�V
//=====================================================================================================
void Player::Update()
{
	if (use)
	{
		// �ړ�
		Move();

		// �C���N�ύX
		ChangeInk();

		// �A�j���[�V�����Ǘ�
		AnimationManager();

		// �J����������
		CheckOnCamera();

#ifndef _DEBUG_
		PrintDebugProc("PLAYER[%d] POS X:%f, Y:%f, Z:%f\n", ctrlNum, pos.x, pos.y, pos.z);
		//PrintDebugProc("PLAYER[%d] MOVE X:%f, Y:%f, Z:%f\n", ctrlNum, move.x, move.y, move.z);
		//PrintDebugProc("PLAYER[%d] INK TYPE %s\n", ctrlNum, inkType ? "Balck" : "Color");
		//PrintDebugProc("PLAYER[%d] INK VALUE COLOR %d\n", ctrlNum, inkValue[ColorInk]);
		//PrintDebugProc("PLAYER[%d] INK VALUE BLACK %d\n", ctrlNum, inkValue[BlackInk]);
		//PrintDebugProc("PLAYER[%d] JUMP FLAG:%d\n", ctrlNum, jumpFlag);
		//PrintDebugProc("PLAYER[%d] JUMP SPEED:%f\n", ctrlNum, jumpSpeed);
		PrintDebugProc("PLAYER[%d] OnCamera:%s\n", ctrlNum, use ? "OnCamera" : "OffCamera");
#endif

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
	}
}

//=====================================================================================================
// �`��
//=====================================================================================================
void Player::Draw()
{
	if (use)
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
	// �W�����v
	if (playable)
	{
		if ((GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(ctrlNum, BUTTON_B)) && (!jumpFlag))
		{
			jumpFlag = true;
			moveFlag = true;
			jumpSpeed = JUMP_SPEED;
			this->ChangeAnim(Jump);
		}
	}

	// �n��ɂ���Ƃ�
	if (!jumpFlag)
	{
		jumpSpeed = 0;
	}
	// �󒆂ɂ���Ƃ�
	else
	{
		pos.y += jumpSpeed;
	}

	// �I�[�g�ړ�
	if (moveFlag && playable)
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
	// �ҋ@���
	if (!playable)
	{
		if (this->GetAnimCurtID() != Idle)
		{
			this->ChangeAnim(Idle);
		}
	}
	else
	{
		if (!jumpFlag)
		{
			// ���s��
			if (moveFlag)
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

	PrintDebugProc("Player Animation�F%s\n", this->GetCurtAnimName());
}

void Player::CreateAnimSet(void)
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
			use = true;
		}
		else
		{
			use = false;
		}
	}
	else
	{
		use = false;
	}
}