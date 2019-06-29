#include "VictoryState.h"
#include "IdleState.h"
#include "RunningState.h"
#include "JumpState.h"

VictoryState::VictoryState(Player * owner) : owner_(owner)
{
}


VictoryState::~VictoryState()
{
}

void VictoryState::Update(int AnimCurtID)
{

}