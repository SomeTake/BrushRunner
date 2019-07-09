//=============================================================================
//
// �v���C���[�N���X[Player.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Input.h"
#include "Gravity.h"
#include "SceneGame.h"
#include "D3DXAnimation.h"
#include "Camera.h"
#include "DebugWindow.h"
#include "Map.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"						// �ǂݍ��ރ��f����(�t�@�C���p�X��)
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// �����̌���
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define JUMP_SPEED			(12.0f)										// �W�����v�̏���
#define MOVE_SPEED			(2.0f)										// �����X�s�[�h
#define DefaultPosition		D3DXVECTOR3(45.0f, 0.0f, 0.0f)				// �v���C���[�����ʒu

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
Player::Player(int _CtrlNum)
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
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	jumpFlag = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;
	moveFlag = true;
	playable = false;
	use = true;
	this->ActionSpeed = 1.0f;
	this->AI = new CharacterAI(true);
	this->PaintSystem = new PaintManager(_CtrlNum);
	this->PopUp = new Pop(ctrlNum);
}

//=====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
Player::~Player()
{
	SAFE_DELETE(this->AI);
	SAFE_DELETE(this->PaintSystem);
	SAFE_DELETE(this->PopUp);
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

		// AI�̍X�V����
		AI->Update(this->pos, this->PaintSystem);

		// �y�C���g�V�X�e���̍X�V����
		PaintSystem->Update();

		// �|�b�v�A�b�v�̍X�V����
		PopUp->Update(this->pos);

		// �A�j���[�V�����Ǘ�
		AnimationManager();

		// �J����������
		CheckOnCamera();

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
	}
#endif
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

		// �y�C���g�̕`��
		this->PaintSystem->Draw();

		this->PopUp->Draw();

#if _DEBUG
		this->AI->Draw();
#endif
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
			//jumpSpeed = 100.0f;
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
		//pos.x += MOVE_SPEED;
	}

#if _DEBUG
	if (GetKeyboardPress(DIK_RIGHT))
	{
		pos.x += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		pos.x -= MOVE_SPEED;
	}
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
					this->ActionSpeed = 1.0f;
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
	this->UpdateAnim(TIME_PER_FRAME * ActionSpeed);
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

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Running:

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Jump:

			Keydata.push_back(KEYDATA{ 0.8f,e_MotionEnd });
			//Keydata.push_back(KEYDATA{ (23 / 32),e_MotionEnd });
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
// �A�j���[�V����CallbackKey�̏����C�x���g
//=====================================================================================================
HRESULT CALLBACK Player::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
{
	int EventNo = (int)pCallbackData;
	int i = 0;

	switch (EventNo)
	{
	case e_MotionEnd:
		this->ActionSpeed = 0.0f;
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