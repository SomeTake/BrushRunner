//=============================================================================
//
// アイテムの状態管理（トリモチガン）[GunState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _GUNSTATE_H_
#define _GUNSTATE_H_

#include "ItemState.h"
#include "Item.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GunState :
	public ItemState
{
private:
	Item * owner_;	// 状態の所有者

public:
	GunState(Item *owner);
	~GunState();

	virtual void Update()override;
	virtual void Start()override;
};

#endif
