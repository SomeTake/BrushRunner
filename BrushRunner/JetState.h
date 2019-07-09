//=============================================================================
//
// �A�C�e���̏�ԊǗ��i�W�F�b�g�p�b�N�j[JetState.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _JETSTATE_H_
#define _JETSTATE_H_

#include "ItemState.h"
#include "Item.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class JetState :
	public ItemState
{
private:
	Item * owner_;
	int cnt;

public:
	JetState(Item *owner);
	~JetState();

	virtual void Update()override;
	virtual void Start()override;
};

#endif
