//=============================================================================
//
// バトル画面フレーム表示処理 [Blackinkline.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _BLACKINKLINE_H_
#define _BLACKINKLINE_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_INKLINEBLACK	_T("data/texture/inkline.black.png")			// フレーム用画像
#define TEXTURE_BLACKINKFRAME   _T("data/texture/blackinkframe.png")
#define BLACKINKLINE_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// テクスチャサイズ

#define BLACKINKFRAME_POS01 D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS02 D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS03 D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS04 D3DXVECTOR3(964.0f, 10.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Blackinkline :
	public _2dobj {
public:
	Blackinkline(D3DXVECTOR3 _pos, const char *texno); //constにより定数化を成しdefineの使用可　ポインタにしないとtextureファイルをうけとれない
	~Blackinkline();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif