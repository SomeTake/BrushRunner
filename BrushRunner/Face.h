//=============================================================================
//
// バトル画面フレーム表示処理 [Face.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _FACE_H_
#define _FACE_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FACE_SIZE		D3DXVECTOR3(50.0f, 50.0f, 0.0f)		// テクスチャサイズ

#define FACE_POS01     D3DXVECTOR3(22.0f, 22.0f, 0.0f)
#define FACE_POS02		D3DXVECTOR3(340.0f, 22.0f, 0.0f)
#define FACE_POS03		D3DXVECTOR3(657.0f, 22.0f, 0.0f)
#define FACE_POS04		D3DXVECTOR3(975.0f, 22.0f, 0.0f)

#define FACE1_POS			D3DXVECTOR3(50.0f, 50.0f, 0.0f)
#define FACE2_POS			D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE3_POS			D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE4_POS			D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Face :
	public _2dobj {
public:
	Face(D3DXVECTOR3 _pos, const char *texno);
	~Face();

	int fc;

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif