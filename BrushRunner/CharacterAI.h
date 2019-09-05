//=============================================================================
//
// CharacterAI�N���X[CharacterAI.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _CharacterAI_H_
#define _CharacterAI_H_

#include "PaintManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum e_AIActionNo
{
	ActJump,
	ActPaintInk,
	ActFallen,
	NoAction = -1,
};


//*****************************************************************************
// �N���X��`
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
