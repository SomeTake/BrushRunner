//=============================================================================
//
// プレイヤーの状態管理（ダッシュ中）[RunningState.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "RunningState.h"
#include "JumpState.h"
#include "IdleState.h"
#include "VictoryState.h"
#include "Input.h"
#include "Map.h"

//=============================================================================
// コンストラクタ
//=============================================================================
RunningState::RunningState(Player *owner) : owner_(owner)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
RunningState::~RunningState()
{
}

//=============================================================================
// 更新
//=============================================================================
void RunningState::Update(int AnimCurtID)
{	
	// 状態変化
	// ゴールに到達したのでガッツポーズ
	if (owner_->GetPos().x >= GOAL_POS.x)
	{
		owner_->ChangeAnim(Victory);
		owner_->ChangeState(new VictoryState(owner_));
		return;
	}

	// 上キーを押してジャンプ
	if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(owner_->GetCtrlNum(), BUTTON_B)
		|| owner_->GetAIAction() == eActJump)
	{
		owner_->SetJumpSpeed(JUMP_SPEED);
		owner_->ChangeAnim(Jump);
		owner_->ChangeState(new JumpState(owner_));
		return;
	}

	// 前方オブジェクトにヒットしているので待機状態へ
	if (owner_->GetHitHorizon())
	{
		owner_->ChangeAnim(Idle);
		owner_->ChangeState(new IdleState(owner_));
		return;
	}
}