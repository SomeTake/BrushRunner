//=============================================================================
//
// ペイント管理クラス [PaintSystem.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PAINTSYSTEM_H_
#define _PAINTSYSTEM_H_

#include "Paint.h"
#include "Cursor.h"
#include "Quadtree.h"

class Player;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class PaintManager
{
private:
	std::vector<Paint*> BlackPaint;
	std::vector<Paint*> ColorPaint;
	Cursor				*pCursor;				// 参照するカーソルクラスのポインタ
	Player				*pPlayer;				// 参照するプレイヤークラスのポインタ
	D3DXVECTOR3			pos;
	int					Owner;
	static QUADTREE		*Quadtree;

	void CheckPaintUse(void);

public:
	PaintManager(Cursor *pC, Player *pP, QUADTREE *Quadtree);
	~PaintManager();

	void Update(bool PressMode);
	void Draw();
	void SetPaint(int InkType);

	// ゲッター
	int GetOwner(void) { return this->Owner; };
	std::vector<Paint*> GetBlackPaint(void) { return this->BlackPaint; };
	std::vector<Paint*> GetColorPaint(void) { return this->ColorPaint; };
	// 四分木から衝突可能なオブジェクトを探す
	std::vector<Paint*> GetCollisionList(int NodeID);
};

#endif
