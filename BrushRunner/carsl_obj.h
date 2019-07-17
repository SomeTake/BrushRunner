//=============================================================================
//
// バトル画面フレーム表示処理 [Carsl_obj.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _CARSL_OBJ_H_
#define _CARSL_OBJ_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_CARSL_OBJ	_T("data/texture/charasl_obj.png")			// フレーム用画像
#define CARSL_OBJ_SIZE		D3DXVECTOR3(114.0f, 114.0f, 0.0f)		// テクスチャサイズ

#define CARSL_OBJ_POS01		D3DXVECTOR3(400.0f, 150.0f, 0.0f)
#define CARSL_OBJ_POS02		D3DXVECTOR3(550.0f, 150.0f, 0.0f)
#define CARSL_OBJ_POS03		D3DXVECTOR3(700.0f, 150.0f, 0.0f)
#define CARSL_OBJ_POS04		D3DXVECTOR3(850.0f, 150.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Carsl_obj :
	public _2dobj {
public:
	Carsl_obj(D3DXVECTOR3 _pos, const char *texno);
	~Carsl_obj();

	int char1;

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();
};
int Getchar1num(void);

#endif