//=============================================================================
//
// vC[UI [PlayerUI.h]
// Author : HAL GP12B332-19 80277 υJu
//
//=============================================================================
#ifndef _PLAYERUI_H_
#define _PLAYERUI_H_

#include "Pop.h"
#include "MiniPlayer.h"
#include "Faceframe.h"

//*****************************************************************************
// NXθ`
//*****************************************************************************
class PlayerUI
{
private:
	Pop			*PopUp;
	MiniPlayer	*miniPlayer;
	FaceFrame	*faceFrame;

public:
	PlayerUI(int PlayerNo);
	~PlayerUI();

	void Update(D3DXVECTOR3 PlayerPos);
	void Draw(bool OnCamera);
	void SetPlayerDeadTexture(void) { this->faceFrame->SetPlayerDeadTexture(); };
};

#endif

