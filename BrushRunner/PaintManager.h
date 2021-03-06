//=============================================================================
//
// ペイント管理クラス [PaintManager.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PAINTSYSTEM_H_
#define _PAINTSYSTEM_H_

#include "Paint.h"
#include "PaintGroup.h"
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
	std::vector<Paint*>		BlackPaint;				// 黒ペイントベクトル
	std::vector<Paint*>		ColorPaint;				// カラーペイントベクトル
	std::vector<InkGauge*>	inkGauge;				// インク残量ゲージ
	Cursor					*pCursor;				// 参照するカーソルクラスのポインタ
	int						Owner;					// 所有者
	int						InkValue[InkNum];		// インクの残量
	int						InkType;				// 使用するインクの種類(enum ColorInk=カラー, BlackInk=黒)
	bool					SpInk;					// trueのときインクが減らない
	int						HealCnt;				// 自動回復カウント

	// AI用
	bool					AIUse = false;			// AI使用フラグ
	CharacterAI				*AIptr = nullptr;		// AIクラスのポインタ

	static QUADTREE			*Quadtree;
	static PaintGroup		*paintGroup;

	void SetPaint(int InkType);
	void CheckPaintUse(void);
	void AutoHeal();

public:
	PaintManager(int PlayerNo, bool AIUse, CharacterAI *AIptr);
	~PaintManager();

	void Update();
	void Draw();

	// ゲッター
	bool GetSpInk() { return SpInk; };
	int GetInkValue(int type) { return InkValue[type]; };
	int GetOwner(void) { return this->Owner; };
	std::vector<Paint*> GetBlackPaint(void) { return this->BlackPaint; };
	std::vector<Paint*> GetColorPaint(void) { return this->ColorPaint; };
	// 四分木から衝突可能なオブジェクトを探す
	std::vector<Paint*> GetCollisionList(int NodeID);

	// セッター
	void SetSpInk(bool _SpInk) { SpInk = _SpInk; };
	void SetInkValue(int value, int type) { InkValue[type] = value; };
	static void SetQuadtreePtr(QUADTREE *Quadtree) { PaintManager::Quadtree = Quadtree; };
	static void SetPaintGroupPtr(PaintGroup *Ptr) { PaintManager::paintGroup = Ptr; };
};

#endif
