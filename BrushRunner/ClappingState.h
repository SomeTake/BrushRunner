//=============================================================================
//
// プレイヤーの状態管理（拍手中）[ClappingState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _CLAPPINGSTATE_H_
#define _CLAPPINGSTATE_H_

#include "PlayerState.h"
#include "Player.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class ClappingState :
	public PlayerState
{
private:
	Player * owner_;

public:
	ClappingState(Player* owner);
	~ClappingState();

	virtual void Update(int AnimCurtID);
};

#endif