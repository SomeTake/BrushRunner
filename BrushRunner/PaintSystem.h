//=============================================================================
//
// ペイント管理クラス [PaintSystem.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PAINTSYSTEM_H_
#define _PAINTSYSTEM_H_

#include "Paint.h"
#include "Player.h"
#include "Cursor.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class PaintManager
{
private:
	Paint * pBlackPaint[INK_MAX];	// 黒用のポインタ
	Paint * pColorPaint[INK_MAX];	// カラー用のポインタ
	Cursor *pCursor;				// 参照するカーソルクラスのポインタ
	Player *pPlayer;				// 参照するプレイヤークラスのポインタ
	D3DXVECTOR3 pos;

public:
	PaintManager(Cursor *pC, Player *pP);
	~PaintManager();

	void Update();
	void Draw();
	void Set(int InkType);

	// ゲッター
	Paint *GetBlackPaint(int _num) { return pBlackPaint[_num]; };
	Paint *GetColorPaint(int _num) { return pColorPaint[_num]; };
};

#endif
