//=============================================================================
//
// �v���C���[�̏�ԊǗ��i���蒆�j[ClappingState.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _CLAPPINGSTATE_H_
#define _CLAPPINGSTATE_H_

#include "PlayerState.h"
#include "Player.h"
//*****************************************************************************
// �N���X��`
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