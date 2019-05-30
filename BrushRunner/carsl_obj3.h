//=============================================================================
//
// バトル画面フレーム表示処理 [Carsl_obj3.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _CARSL_OBJ3_H_
#define _CARSL_OBJ3_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_CARSL_OBJ3	_T("data/texture/charasl_obj3.png")			// フレーム用画像
#define CARSL_OBJ3_SIZE		D3DXVECTOR3(114.0f, 114.0f, 0.0f)		// テクスチャサイズ

#define CARSL_OBJ3_POS01		D3DXVECTOR3(400.0f, 350.0f, 0.0f)
#define CARSL_OBJ3_POS02		D3DXVECTOR3(550.0f, 350.0f, 0.0f)
#define CARSL_OBJ3_POS03		D3DXVECTOR3(700.0f, 350.0f, 0.0f)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Carsl_obj3 :
	public _2dobj {
public:
	Carsl_obj3(D3DXVECTOR3 _pos, const char *texno);
	~Carsl_obj3();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();
	float getobjpos();
};
#endif