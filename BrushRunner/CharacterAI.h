//=============================================================================
//
// CharacterAIクラス[CharacterAI.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _CharacterAI_H_
#define _CharacterAI_H_

#include "PaintGroup.h"
#include "InkGauge.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 現在AIプレイヤーの状態
enum eAIAction
{
	eActJump,
	eActFallen,
	eNoAction = -1,
};

// 現在AIカーソルの状態
enum eAIState
{
	ePaintPath,
	eUseBlackPaint
};

// 現在AIカーソルの状態
enum eAIPaintState
{
	ePaintStart,
	ePainting,
	ePaintEnd,
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
	GroupStruct *EnemyPaint;
	int			Action = eNoAction;
	int			State = eNoAction;
	int			PaintState = eNoAction;
	int			Owner = 0;
	int			InkType = ColorInk;
	bool		ChangeInk = false;
	bool		FindEdgeOver = false;
	bool		RandomOver = false;
	bool		FindEnemyPaint = false;
	static PaintGroup *paintGroup;

	// 向こうのプラットフォームを探す
	void FindPlatform(D3DXVECTOR3 Pos);
	void MapChipAction(D3DXVECTOR3 Pos,int MapChipNo);
	void PaintAction(void);

public:
	CharacterAI(int Owner);
	~CharacterAI();
	void Update(D3DXVECTOR3 Pos);

	void SetAIAction(int eAction) { this->Action = eAction; };
	void SetAIState(int eState) { this->State = eState; };
	void SetAIPaintState(int State) { this->PaintState = State; };
	void SetAIChangeInk(bool Flag) { this->ChangeInk = Flag; };
	void SetInkType(int InkType) { this->InkType = InkType; };
	void SetFindEnemyPaint(bool Flag) { this->FindEnemyPaint = Flag; };
	static void SetPaintGroupPtr(PaintGroup *Ptr) { if (!CharacterAI::paintGroup) { CharacterAI::paintGroup = Ptr; } };

	int GetAIAction(void) { return this->Action; };
	int GetAIState(void) { return this->State; };
	int GetAIPaintState(void) { return this->PaintState; };
	bool GetAIChangeInk(void) { return this->ChangeInk; };
	D3DXVECTOR3 GetPaintStartPos(void) { return this->PaintStartPos; };
	D3DXVECTOR3 GetPaintEndPos(void) { return this->PaintEndPos; };
	GroupStruct* GetEnemyPaint(void) { return this->EnemyPaint; };

# if _DEBUG
	void Draw(void);
#endif
};

#endif
