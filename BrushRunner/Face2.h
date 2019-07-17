//=============================================================================
//
// バトル画面フレーム表示処理 [Face2.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _FACE2_H_
#define _FACE2_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FACE2_SIZE		D3DXVECTOR3(50.0f, 50.0f, 0.0f)		// テクスチャサイズ

#define FACE2_POS01     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACE2_POS02		D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE2_POS03		D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE2_POS04		D3DXVECTOR3(954.0f, 0.0f, 0.0f)

#define FACE21_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACE22_POS			D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE23_POS			D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE24_POS			D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Face2 :
	public _2dobj {
public:
	Face2(D3DXVECTOR3 _pos, const char *texno);
	~Face2();

	int fc;

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif