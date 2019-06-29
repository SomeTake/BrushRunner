#ifndef _IDLESTATE_H_
#define _IDLESTATE_H_

#include "PlayerState.h"
#include "Player.h"

class IdleState :
	public PlayerState
{
private:
	Player * owner_;	// ó‘Ô‚ÌŠ—LÒ

public:
	IdleState(Player* owner);
	~IdleState();

	virtual void Update(int AnimCurtID)override;
};

#endif
