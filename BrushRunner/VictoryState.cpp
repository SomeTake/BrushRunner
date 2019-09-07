//=============================================================================
//
// プレイヤーの状態管理（ガッツポーズ中）[VictoryState.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "VictoryState.h"
#include "IdleState.h"
#include "RunningState.h"
#include "JumpState.h"

//=============================================================================
// コンストラクタ
//=============================================================================
VictoryState::VictoryState(Player * owner) : owner_(owner)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
VictoryState::~VictoryState()
{
	owner_ = nullptr;
}

//=============================================================================
// 更新
//=============================================================================
void VictoryState::Update(int AnimCurtID)
{

}