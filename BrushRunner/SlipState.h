//=============================================================================
//
// �v���C���[�̏�ԊǗ��i�X���b�v�j[SlipState.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SLIPSTATE_H_
#define _SLIPSTATE_H_

#include "PlayerState.h"
#include "Player.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************

class SlipState :
	public PlayerState
{
private:
	Player * owner_;	// ��Ԃ̏��L��

public:
	SlipState(Player* owner);
	~SlipState();

	virtual void Update(int AnimCurtID)override;
};

#endif
