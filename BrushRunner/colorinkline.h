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
#define COLORINKLINE_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// テクスチャサイズ

#define COLORINKFRAME_POS01 D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS02 D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS03 D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS04 D3DXVECTOR3(964.0f, 10.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class INKFRAME :
	public _2dobj {

public:
	INKFRAME(D3DXVECTOR3 _pos, const char *texno); //constにより定数化を成しdefineの使用可　ポインタにしないとtextureファイルをうけとれない
	~INKFRAME();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif