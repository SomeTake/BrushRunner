//=============================================================================
//
// プレイヤーの状態管理（スリップ）[SlipState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SLIPSTATE_H_
#define _SLIPSTATE_H_

#include "PlayerState.h"
#include "Player.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************

class SlipState :
	public PlayerState
{
private:
	Player * owner_;	// 状態の所有者

public:
	SlipState(Player* owner);
	~SlipState();

	virtual void Update(int AnimCurtID)override;
};

#endif
