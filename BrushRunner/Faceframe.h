//=============================================================================
//
// バトル画面フレーム表示処理 [Faceframe.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _FACEFRAME_H_
#define _FACEFRAME_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_FACEFRAME	_T("data/texture/faceframe.png")			// フレーム用画像
#define FACEFRAME_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// テクスチャサイズ

#define FACEFRAME_POS01     D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define FACEFRAME_POS02		D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define FACEFRAME_POS03		D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define FACEFRAME_POS04		D3DXVECTOR3(964.0f, 10.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class FACEFRAME :
	public _2dobj {
public:
	FACEFRAME(D3DXVECTOR3 _pos);
	~FACEFRAME();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif