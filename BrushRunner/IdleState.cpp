//=============================================================================
//
// プレイヤーの状態管理（待機中）[IdleState.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "IdleState.h"
#include "RunningState.h"
#include "VictoryState.h"
#include "JumpState.h"
#include "Input.h"
#include "Player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
IdleState::IdleState(Player* owner) : owner_(owner)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
IdleState::~IdleState()
{
}

//=============================================================================
// 更新
//=============================================================================
void IdleState::Update(int AnimCurtID)
{
	// 状態変化
	if (owner_->GetPlayable())
	{
		// 前方オブジェクトにあたっていない場合、ダッシュに移行
		if (!owner_->GetHitHorizon())
		{
			owner_->ChangeAnim(Running);
			owner_->ChangeState(new RunningState(owner_));
			return;
		}
		else
		{
			// 上キーを押してジャンプ
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