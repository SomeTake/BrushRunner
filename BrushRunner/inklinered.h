//=============================================================================
//
// バトル画面フレーム表示処理 [Inklinered.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _INKLINERED_H_
#define _INKLINERED_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_INKLINERED	_T("data/texture/inkline.red.png")			// フレーム用画像
#define INKLINERED_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// テクスチャサイズ

#define INKLINERED_POS1      D3DXVECTOR3(0.0f, 0.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Inklinered :
	public _2dobj {
public:
	Inklinered(D3DXVECTOR3 _pos);
	~Inklinered();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif