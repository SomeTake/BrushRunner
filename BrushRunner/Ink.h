#pragma once
#include "_2dobj.h"
#include "Player.h"

class INK :
	public _2dobj
{
private:
	PLAYER * pPlayer;	// 参照するキャラクタクラスのポインタ
public:
	INK(PLAYER *pP, D3DXVECTOR3 _pos, const char *texno);
	~INK();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

