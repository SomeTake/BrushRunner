//=============================================================================
//
// プレイヤーの状態管理（ダッシュ中）[RunningState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _RUNNINGSTATE_H_
#define _RUNNINGSTATE_H_

#include "PlayerState.h"
#include "Player.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RunningState :
	public PlayerState
{
private:
	Player * owner_;

public:
	RunningState(Player *owner);
	~RunningState();

	virtual void Update(int AnimCurtID)override;
};

#endif
