//=============================================================================
//
// アイテムの状態管理（トリモチガン）[GunState.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "GunState.h"
#include "BanananoKawaState.h"
#include "PowerUpBananaState.h"
#include "JetState.h"
#include "SpikeState.h"
#include "SpikeState.h"
#include "Input.h"

#define MOVE_SPEED		(30.0f)
#define FIRE_POS_PLUS	(10.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
GunState::GunState(Item *owner) : owner_(owner)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
GunState::~GunState()
{
	delete owner_;
}

//=============================================================================
// 更新
//=============================================================================
void GunState::Update()
{
	if (IsButtonTriggered(owner_->GetPlayer()->GetCtrlNum(), BUTTON_D) || GetKeyboardTrigger(DIK_I))
	{
		D3DXVECTOR3 setpos = owner_->GetPlayer()->GetPos();
		setpos.y += FIRE_POS_PLUS;
		owner_->GetPlayer()->GetFieldItemManager()->Set(NumKawa, setpos, D3DXVECTOR3(MOVE_SPEED, 0.0f, 0.0f));
		// アイテムを使用
		owner_->SetActive(false);
	}
}

//=============================================================================
// 有効にするときだけ使う
//=============================================================================
void GunState::Start()
{

}