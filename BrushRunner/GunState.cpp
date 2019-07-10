//=============================================================================
//
// �A�C�e���̏�ԊǗ��i�g�����`�K���j[GunState.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
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
// �R���X�g���N�^
//=============================================================================
GunState::GunState(Item *owner) : owner_(owner)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
GunState::~GunState()
{
	delete owner_;
}

//=============================================================================
// �X�V
//=============================================================================
void GunState::Update()
{
	if (IsButtonTriggered(owner_->GetPlayer()->GetCtrlNum(), BUTTON_D) || GetKeyboardTrigger(DIK_I))
	{
		D3DXVECTOR3 setpos = owner_->GetPlayer()->GetPos();
		setpos.y += FIRE_POS_PLUS;
		owner_->GetPlayer()->GetFieldItemManager()->Set(NumKawa, setpos, D3DXVECTOR3(MOVE_SPEED, 0.0f, 0.0f));
		// �A�C�e�����g�p
		owner_->SetActive(false);
	}
}

//=============================================================================
// �L���ɂ���Ƃ������g��
//=============================================================================
void GunState::Start()
{

}