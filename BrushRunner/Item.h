//=============================================================================
//
// アイテム処理 [Item.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "_2dobj.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_ITEM			("data/TEXTURE/Item.png")
#define ITEM_SIZE				D3DXVECTOR2(50.0f, 50.0f)
#define ROULETTE_COUNTER		(10)						// 何フレームごとにルーレットを動かすか
#define USE_COUNTER				(3)						// 何回ルーレットを動かしたらアイテムを確定させるか
#define DIVIDE_ITEM_X			(7)
#define DIVIDE_ITEM_Y			(1)
#define TEXTURE_DIVIDE_ITEM		(DIVIDE_ITEM_X * DIVIDE_ITEM_Y)

static D3DXVECTOR3 ItemPos[PLAYER_MAX] = {
	D3DXVECTOR3(245.0f, 30.0f, 0.0f),
	D3DXVECTOR3(565.0f, 30.0f, 0.0f),
	D3DXVECTOR3(885.0f, 30.0f, 0.0f),
	D3DXVECTOR3(1200.0f, 30.0f, 0.0f),
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Item :
	public _2dobj
{
private:
	Player * pPlayer;
	int rouletteCnt;
	int useCnt;

	HRESULT MakeVertex();
	void SetTexture();
	void SetVertex();

	void Start();
	void UseInfluence();

public:
	Item(D3DXVECTOR3 _pos, Player* ptr);
	~Item();

	void Update();
	void Draw();

	bool GetUse() { return use; };
	void SetUse(bool _use) { use = _use; };
};

#endif
