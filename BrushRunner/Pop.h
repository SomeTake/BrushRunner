//=============================================================================
//
// ポップアップ表示処理 [Pop.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _POP_H_
#define _POP_H_

#include "Billboard.h"
//#include "Player.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Pop : public Billboard
{
private:
	//Player * pPlayer;
	int PlayerNo;

	static LPDIRECT3DTEXTURE9 D3DTexture;		// テクスチャへのポインタ

	HRESULT MakeVertex();

public:
	//Pop(Player *pP);
	Pop(int PlayerNo);
	~Pop();

	void Update() {};
	void Update(D3DXVECTOR3 PlayerPos);
	void Draw();
};

#endif
