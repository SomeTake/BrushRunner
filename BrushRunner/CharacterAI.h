//=============================================================================
//
// CharacterAIクラス[CharacterAI.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _CharacterAI_H_
#define _CharacterAI_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
enum eAIAction
{
	eActJump,
	eActFallen,
	eNoAction = -1,
};

enum eAIState
{
	eCursorMove,
	eNoEvent = -1,
};


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CharacterAI
{
private:
# if _DEBUG
	bool		DrawLineFlag = false;
	void DrawLine3D(D3DXVECTOR3 P1, D3DXVECTOR3 P2);
#endif

	D3DXVECTOR3	PaintStartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	PaintEndPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int Action = eNoAction;
	int State = eNoEvent;
	bool AIPaint = false;

	void FindPlatform(D3DXVECTOR3 Pos);

public:
	CharacterAI();
	~CharacterAI();
	void Update(D3DXVECTOR3 Pos);

	void SetAIAction(int eAction) { this->Action = eAction; };
	void SetAIState(int eState) { this->State = eState; };
	void SetAIPaint(bool Flag) { this->AIPaint = Flag; };

	int GetAIAction(void) { return this->Action; };
	int GetAIState(void) { return this->State; };
	bool GetAIPaint(void) { return this->AIPaint; };
	D3DXVECTOR3 GetPaintStartPos(void) { return this->PaintStartPos; };
	D3DXVECTOR3 GetPaintEndPos(void) { return this->PaintEndPos; };

# if _DEBUG
	void Draw(void);
#endif

};

#endif
