//=============================================================================
//
// CharacterAIクラス[CharacterAI.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _CharacterAI_H_
#define _CharacterAI_H_

#include "PaintManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
enum e_AIActionNo
{
	ActJump,
	ActPaintInk,
	ActFallen,
	NoAction = -1,
};


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CharacterAI
{
private:
# if _DEBUG
	D3DXVECTOR3 PaintStartPos;
	D3DXVECTOR3 PlatformEdgePos;
	bool		DrawLineFlag = false;
	void DrawLine3D(D3DXVECTOR3 P1, D3DXVECTOR3 P2);
#endif

	int Action = NoAction;
	bool AIFlag = false;

	void FindPlatform(D3DXVECTOR3 Pos);

public:
	CharacterAI(bool AIFlag);
	~CharacterAI();
	void Update(D3DXVECTOR3 Pos, PaintManager *ManagerPtr);
	int GetAIAction(void) { return this->Action; };

# if _DEBUG
	void Draw(void);
#endif
};

#endif
