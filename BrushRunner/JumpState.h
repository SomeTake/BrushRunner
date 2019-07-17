//=============================================================================
//
// プレイヤーの状態管理（ジャンプ中）[JumpState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _JUMPSTATE_H_
#define _JUMPSTATE_H_

#include "PlayerState.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
class JumpState :
	public PlayerState
{
private:
	Player * owner_;

public:
	JumpState(Player *owner);
	~JumpState();

	virtual void Update(int AnimCurtID)override;
};

#endif
