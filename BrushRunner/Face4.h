//=============================================================================
//
// バトル画面フレーム表示処理 [Face4.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _FACE4_H_
#define _FACE4_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FACE4_SIZE		D3DXVECTOR3(50.0f, 50.0f, 0.0f)		// テクスチャサイズ

#define FACE4_POS01     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACE4_POS02		D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE4_POS03		D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE4_POS04		D3DXVECTOR3(954.0f, 0.0f, 0.0f)

#define FACE41_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACE42_POS			D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE43_POS			D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE44_POS			D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Face4 :
	public _2dobj {
public:
	Face4(D3DXVECTOR3 _pos, const char *texno);
	~Face4();

	int fc;

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif