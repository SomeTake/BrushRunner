//=============================================================================
//
// プレイヤーの状態管理（負けポーズ中）[LoseState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _LOSESTATE_H_
#define _LOSESTATE_H_

#include "PlayerState.h"
#include "Player.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class LoseState :
	public PlayerState
{
private:
	Player * owner_;

public:
	LoseState(Player* owner);
	~LoseState();

	virtual void Update(int AnimCurtID)override;

};

#endif
