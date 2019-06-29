#ifndef _VICTORYSTATE_H_
#define _VICTORYSTATE_H_

#include "PlayerState.h"
#include "Player.h"

class VictoryState :
	public PlayerState
{
private:
	Player * owner_;

public:
	VictoryState(Player * owner);
	~VictoryState();

	virtual void Update(int AnimCurtID)override;
};

#endif
