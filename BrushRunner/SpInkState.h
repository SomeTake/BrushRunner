//=============================================================================
//
// �A�C�e���̏�ԊǗ��iSP�C���N�j[SpInkState.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SPINKSTATE_H_
#define _SPINKSTATE_H_

#include "ItemState.h"
#include "Item.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SpInkState :
	public ItemState
{
private:
	Item * owner_;	// ��Ԃ̏��L��
	int cnt;

public:
	SpInkState(Item *owner);
	~SpInkState();

	virtual void Update()override;
	virtual void Start()override;
};

#endif
