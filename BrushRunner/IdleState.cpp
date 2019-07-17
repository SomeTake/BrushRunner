//=============================================================================
//
// �v���C���[�̏�ԊǗ��i�ҋ@���j[IdleState.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "IdleState.h"
#include "RunningState.h"
#include "VictoryState.h"
#include "JumpState.h"
#include "Input.h"
#include "Player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
IdleState::IdleState(Player* owner) : owner_(owner)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
IdleState::~IdleState()
{
}

//=============================================================================
// �X�V
//=============================================================================
void IdleState::Update(int AnimCurtID)
{
	// ��ԕω�
	if (owner_->GetPlayable())
	{
		// �O���I�u�W�F�N�g�ɂ������Ă��Ȃ��ꍇ�A�_�b�V���Ɉڍs
		if (!owner_->GetHitHorizon())
		{
			owner_->ChangeAnim(Running);
			owner_->ChangeState(new RunningState(owner_));
			return;
		}
		else
		{
			// ��L�[�������ăW�����v
			if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(owner_->GetCtrlNum(), BUTTON_B))
			{
				float value = owner_->GetJumpValue();
				owner_->SetJumpSpeed(JUMP_SPEED * value);
				owner_->ChangeAnim(Jump);
				owner_->ChangeState(new JumpState(owner_));
				return;
			}
		}
	}
}