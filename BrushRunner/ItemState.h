//=============================================================================
//
// アイテムの状態抽象インターフェース[ItemState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _ITEMSTATE_H_
#define _ITEMSTATE_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ItemState
{
public:
	ItemState();
	virtual ~ItemState();

	// アイテムの種類に合わせて効果を変更
	virtual void Update() = 0;
	virtual void Start() = 0;

};

#endif
