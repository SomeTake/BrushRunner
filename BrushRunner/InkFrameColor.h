//=============================================================================
//
// カラーインク用フレーム処理 [InkFrameColor.h]
// Author : HAL東京 土居郁也
//
//=============================================================================
#ifndef _INKFRAMECOLOR_H_
#define _INKFRAMECOLOR_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_COLORINKFRAME   _T("data/texture/colorinkframe.png")
#define COLORINKLINE_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// テクスチャサイズ

#define COLORINKFRAME_POS01 D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS02 D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS03 D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS04 D3DXVECTOR3(964.0f, 10.0f, 0.0f)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class INKFRAMECOLOR :
	public _2dobj {
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;					// テクスチャのポインタ

public:
	INKFRAMECOLOR(D3DXVECTOR3 _pos);
	~INKFRAMECOLOR();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif