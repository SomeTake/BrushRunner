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
class PAINTSYSTEM
{
private:
	PAINT * pPaint[MAX_PAINT];		// 発生させるペイントのポインタ
	CURSOR *pCursor;				// 参照するカーソルクラスのポインタ
	PLAYER *pPlayer;				// 参照するプレイヤークラスのポインタ
	D3DXVECTOR3 pos;

public:
	PAINTSYSTEM(CURSOR *pC, PLAYER *pP);
	~PAINTSYSTEM();

	void Update();
	void Draw();
	void Set(int InkType);
};

#endif
