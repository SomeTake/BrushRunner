//=============================================================================
//
// アイテムの状態管理（ジェットパック）[JetState.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "JetState.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ACTIVE_TIME	(600)	// 有効時間

//=============================================================================
// コンストラクタ
//=============================================================================
JetState::JetState(Item *owner) : owner_(owner)
{
	cnt = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
JetState::~JetState()
{
	delete owner_;
}

//=============================================================================
// 更新
//=============================================================================
void JetState::Update()
{
	cnt++;

	if (cnt == ACTIVE_TIME)
	{
		owner_->GetPlayer()->SetJet(false);
		// アイテムの効果終了
		owner_->Reset();
	}
}

//=============================================================================
// 有効にするときだけ使う
//=============================================================================
void JetState::Start()
{
	cnt = 0;
	owner_->GetPlayer()->SetJet(true);
}