//=============================================================================
//
// キャラクターセレクトロゴ [SelectLogo.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _SELECTLOGO_H_
#define _SELECTLOGO_H_

#include "_2dobj.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SelectLogo :
	public _2dobj {
private:
	int cntFlash;
	bool flash;

public:
	SelectLogo();
	~SelectLogo();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();
};


#endif