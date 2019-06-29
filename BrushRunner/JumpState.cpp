#include "JumpState.h"
#include "RunningState.h"
#include "IdleState.h"
#include "VictoryState.h"

JumpState::JumpState(Player *owner) : owner_(owner)
{
}


JumpState::~JumpState()
{
}

void JumpState::Update(int AnimCurtID)
{
	if (owner_->GetHitGround() || owner_->GetHitPaint())
	{
		owner_->ChangeState(new RunningState(owner_), Running);
	}
}