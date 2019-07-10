//=============================================================================
//
// アイテムの状態管理（スパイクブーツ）[SpikeState.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "SpikeState.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ACTIVE_TIME	(600)	// 有効時間

//=============================================================================
// コンストラクタ
//=============================================================================
SpikeState::SpikeState(Item *owner) : owner_(owner)
{
	cnt = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
SpikeState::~SpikeState()
{
	delete owner_;
}

//=============================================================================
// 更新
//=============================================================================
void SpikeState::Update()
{
	cnt++;

	// 有効時間が終了
	if (cnt == ACTIVE_TIME)
	{
		owner_->SetActive(false);
		owner_->GetPlayer()->SetSpike(false);
		owner_->GetPlayer()->SetHitItem(false);
	}
}

//=============================================================================
// 有効にするときだけ使う
//=============================================================================
void SpikeState::Start()
{
	cnt = 0;
	owner_->GetPlayer()->SetSpike(true);
}