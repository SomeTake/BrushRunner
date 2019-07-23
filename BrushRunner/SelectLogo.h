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
// マクロ定義
//*****************************************************************************
#define TEXTURE_SELECTLOGO	_T("data/TEXTURE/CharSelectLogo.png")			// フレーム用画像
#define SELECTLOGO_SIZE		D3DXVECTOR3(1280.0f, 114.0f, 0.0f)		// テクスチャサイズ

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SelectLogo :
	public _2dobj {
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