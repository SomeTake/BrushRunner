#include "IdleState.h"
#include "RunningState.h"
#include "VictoryState.h"
#include "JumpState.h"
#include "Input.h"

IdleState::IdleState(Player* owner) : owner_(owner)
{
}


IdleState::~IdleState()
{
}

void IdleState::Update(int AnimCurtID)
{

	// 操作可能なら走る
	if (owner_->GetPlayable())
	{
		owner_->ChangeState(new RunningState(owner_), Running);
	}
}