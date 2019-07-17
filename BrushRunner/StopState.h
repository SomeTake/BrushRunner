//=============================================================================
//
// プレイヤーの状態管理（停止状態）[StopState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _STOPSTATE_H_
#define _STOPSTATE_H_

#include "PlayerState.h"
#include "Player.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class StopState :
	public PlayerState
{
private:
	Player * owner_;	// 状態の所有者
	int cnt;

public:
	StopState(Player* owner);
	~StopState();

	virtual void Update(int AnimID)override;
};

#endif
