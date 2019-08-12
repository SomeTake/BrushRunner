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

// 現在AIペイントの状態
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
	int			Owner = 0;
	int			Action = eNoAction;
	int			CursorState = eNoAction;
	int			PaintState = eNoAction;
	int			InkType = ColorInk;
	int			ItemType = 0;
	bool		ChangeInk = false;
	bool		HaveItem = false;
	bool		UseItem = false;
	bool		FindEdgeOver = false;
	bool		RandomOver = false;
	bool		FindEnemyPaint = false;
	bool		ShotBullet = false;
	static PaintGroup *paintGroup;

	// 向こうのプラットフォームを探す
	void FindPlatform(D3DXVECTOR3 Pos);
	void MapChipAction(D3DXVECTOR3 Pos, int MapChipNo);
	void PaintAction(void);
	void ItemAction(void);

public:
	CharacterAI(int Owner);
	~CharacterAI();
	void Update(D3DXVECTOR3 Pos);

	void SetAIAction(int eAction) { this->Action = eAction; };
	void SetCursorState(int eState) { this->CursorState = eState; };
	void SetPaintState(int State) { this->PaintState = State; };
	void SetInkType(int InkType) { this->InkType = InkType; };
	void SetItemType(int ItemType) { this->ItemType = ItemType; };
	void SetAIChangeInk(bool Flag) { this->ChangeInk = Flag; };
	void SetHaveItem(bool Flag) { this->HaveItem = Flag; };
	void SetUseItem(bool Flag) { this->UseItem = Flag; };
	void SetFindEnemyPaint(bool Flag) { this->FindEnemyPaint = Flag; };
	void SetShotBullet(bool Flag) { this->ShotBullet = Flag; };
	static void SetPaintGroupPtr(PaintGroup *Ptr) { if (!CharacterAI::paintGroup) { CharacterAI::paintGroup = Ptr; } };

	int GetAIAction(void) { return this->Action; };
	int GetCursorState(void) { return this->CursorState; };
	int GetPaintState(void) { return this->PaintState; };
	bool GetAIChangeInk(void) { return this->ChangeInk; };
	bool GetHaveItem(void) { return this->HaveItem; };
	bool GetUseItem(void) { return this->UseItem; };
	D3DXVECTOR3 GetPaintStartPos(void) { return this->PaintStartPos; };
	D3DXVECTOR3 GetPaintEndPos(void) { return this->PaintEndPos; };
	GroupStruct* GetEnemyPaint(void) { return this->EnemyPaint; };

# if _DEBUG
	void Draw(void);
#endif
};

#endif
