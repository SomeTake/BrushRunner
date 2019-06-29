#include "RunningState.h"



RunningState::RunningState(Player *owner) : owner_(owner)
{
}


RunningState::~RunningState()
{
}

void RunningState::Update(int AnimCurtID)
{
	if (owner_->GetHitHorizon())
	{
		owner_->ChangeState(new IdleState(owner_), Idle);
	}
}