//=============================================================================
//
// アイテムの状態管理（バナナの皮）[BanananoKawaState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _BANANANOKAWASTATE_H_
#define _BANANANOKAWASTATE_H_

#include "ItemState.h"
#include "Item.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BanananoKawaState :
	public ItemState
{
private:
	Item * owner_;	// 状態の所有者

public:
	BanananoKawaState(Item *owner);
	~BanananoKawaState();

	virtual void Update()override;
	virtual void Start()override;
};

#endif
