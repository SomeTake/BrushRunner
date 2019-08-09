//=============================================================================
//
// ペイント管理クラス [PaintManager.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PAINTSYSTEM_H_
#define _PAINTSYSTEM_H_

#include "Paint.h"
#include "Cursor.h"
#include "Quadtree.h"
#include "InkGauge.h"
#include "CharacterAI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INK_MAX	(50)	// インクの最大量

//*****************************************************************************
// クラス定義
//*****************************************************************************
class PaintManager
{
private:
	std::vector<Paint*>		BlackPaint;
	std::vector<Paint*>		ColorPaint;
	std::vector<InkGauge*>	inkGauge;
	Cursor					*pCursor;				// 参照するカーソルクラスのポインタ
	int						Owner;
	int						InkValue[InkNum];		// インクの残量
	int						InkType;				// 使用するインクの種類(enum ColorInk=カラー, BlackInk=黒)
	bool					AIUse;
	CharacterAI				*AIptr;

	static QUADTREE			*Quadtree;
#if _DEBUG
	static bool				PressMode;
#endif

	void SetPaint(int InkType);
	void CheckPaintUse(void);

public:
	PaintManager(int PlayerNo, bool AIUse, CharacterAI *AIptr);
	~PaintManager();

	void Update();
	void Draw();
	static void SetQuadtreePtr(QUADTREE *Quadtree) { if (!PaintManager::Quadtree) { PaintManager::Quadtree = Quadtree; } };

	// ゲッター
	int GetOwner(void) { return this->Owner; };
	std::vector<Paint*> GetBlackPaint(void) { return this->BlackPaint; };
	std::vector<Paint*> GetColorPaint(void) { return this->ColorPaint; };
	// 四分木から衝突可能なオブジェクトを探す
	std::vector<Paint*> GetCollisionList(int NodeID);
};

#endif
