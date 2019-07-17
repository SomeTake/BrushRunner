//=============================================================================
//
// プレイヤーUI処理 [PlayerUI.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PLAYERUI_H_
#define _PLAYERUI_H_

#include "Pop.h"
#include "MiniPlayer.h"
#include "Faceframe.h"

//*****************************************************************************
// クラス定義
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
	void Draw(bool OnCamera, bool blind);
	void SetPlayerDeadTexture(void) { this->faceFrame->SetPlayerDeadTexture(); };
};

#endif

