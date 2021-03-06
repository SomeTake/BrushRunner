//=============================================================================
//
// アイテムの状態管理（ジェットパック）[JetState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _JETSTATE_H_
#define _JETSTATE_H_

#include "ItemState.h"
#include "Item.h"

//*****************************************************************************
// クラス定義
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
