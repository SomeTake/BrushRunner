//=============================================================================
//
// バトル画面フレーム表示処理 [Carsl_obj4.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _CARSL_OBJ4_H_
#define _CARSL_OBJ4_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_CARSL_OBJ4	_T("data/texture/charasl_obj4.png")			// フレーム用画像
#define CARSL_OBJ4_SIZE		D3DXVECTOR3(114.0f, 114.0f, 0.0f)		// テクスチャサイズ

#define CARSL_OBJ4_POS01		D3DXVECTOR3(400.0f, 540.0f, 0.0f)
#define CARSL_OBJ4_POS02		D3DXVECTOR3(550.0f, 540.0f, 0.0f)
#define CARSL_OBJ4_POS03		D3DXVECTOR3(700.0f, 540.0f, 0.0f)
#define CARSL_OBJ4_POS04		D3DXVECTOR3(850.0f, 540.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Carsl_obj4 :
	public _2dobj {
public:
	bool  player = false;
	Carsl_obj4(D3DXVECTOR3 _pos, const char *texno);
	~Carsl_obj4();
	int char4;

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();
};
int Getchar4num();
#endif