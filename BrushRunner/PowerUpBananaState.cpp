//=============================================================================
//
// アイテムの状態管理（パワーアップバナナ）[PowerUpBananaState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "PowerUpBananaState.h"
#include "ParticleManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ACTIVE_TIME	(600)	// 有効時間

//=============================================================================
// コンストラクタ
//=============================================================================
PowerUpBananaState::PowerUpBananaState(Item *owner) : owner_(owner)
{
	cnt = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
PowerUpBananaState::~PowerUpBananaState()
{
	owner_ = nullptr;
}

//=============================================================================
// 更新
//=============================================================================
void PowerUpBananaState::Update()
{
	cnt++;

	// 有効時間が終了
	if (cnt == ACTIVE_TIME)
	{
		owner_->GetPlayer()->SetPowerBanana(false);

		// アイテムを使用
		owner_->SetPatternAnim(NumKawa);
		owner_->ChangeState(NumKawa);
	}

	// プレイヤーにエフェクト発生
	if (owner_->GetPlayer()->GetAnimCurtID() == Running || owner_->GetPlayer()->GetAnimCurtID() == Idle || owner_->GetPlayer()->GetAnimCurtID() == Jump)
	{
		owner_->GetPlayer()->PowwrUpEffect();
	}
}

//=============================================================================
// 有効にするときだけ使う
//=============================================================================
void PowerUpBananaState::Start()
{
	cnt = 0;

	owner_->GetPlayer()->SetPowerBanana(true);
}