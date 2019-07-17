//=============================================================================
//
// アイテムの状態管理（SPインク）[SpInkState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SPINKSTATE_H_
#define _SPINKSTATE_H_

#include "ItemState.h"
#include "Item.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SpInkState :
	public ItemState
{
private:
	Item * owner_;	// 状態の所有者
	int cnt;

public:
	SpInkState(Item *owner);
	~SpInkState();

	virtual void Update()override;
	virtual void Start()override;
};

#endif
