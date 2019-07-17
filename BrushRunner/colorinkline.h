//=============================================================================
//
// バトル画面フレーム表示処理 [Colorinkline.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _COLORINKLINE_H_
#define _COLORINKLINE_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_INKLINEBLUE		_T("data/texture/inkline.blue.png")			// フレーム用画像
#define TEXTURE_INKLINERED		_T("data/texture/inkline.red.png")			// フレーム用画像
#define TEXTURE_INKLINEYELLOW	_T("data/texture/inkline.yellow.png")			// フレーム用画像
#define TEXTURE_INKLINEGREEN	_T("data/texture/inkline.green.png")			// フレーム用画像
#define TEXTURE_COLORINKFRAME   _T("data/texture/colorinkframe.png")
#define COLORINKLINE_SIZE		D3DXVECTOR3(100.0f, 30.0f, 0.0f)		// テクスチャサイズ

#define INKLINEBLUE_POS     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define INKLINERED_POS      D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define INKLINEYELLOW_POS   D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define INKLINEGREEN_POS    D3DXVECTOR3(954.0f, 0.0f, 0.0f)

#define COLORINKFRAME_POS01 D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define COLORINKFRAME_POS02 D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define COLORINKFRAME_POS03 D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define COLORINKFRAME_POS04 D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Colorinkline :
	public _2dobj {
public:
	Colorinkline(D3DXVECTOR3 _pos, const char *texno); //constにより定数化を成しdefineの使用可　ポインタにしないとtextureファイルをうけとれない
	~Colorinkline();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif