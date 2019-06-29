#ifndef _IDLESTATE_H_
#define _IDLESTATE_H_

#include "PlayerState.h"
#include "Player.h"

class IdleState :
	public PlayerState
{
private:
	Player * owner_;	// 状態の所有者

public:
	IdleState(Player* owner);
	~IdleState();

	virtual void Update(int AnimCurtID)override;
};

#endif
