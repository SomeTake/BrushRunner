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
#define TEXTURE_FACE1		_T("data/texture/charasl_obj.png")			// フレーム用画像
#define TEXTURE_FACE2		_T("data/texture/charasl_obj2.png")			// フレーム用画像
#define TEXTURE_FACE3		_T("data/texture/charasl_obj3.png")			// フレーム用画像
#define TEXTURE_FACE4		_T("data/texture/charasl_obj4.png")			// フレーム用画像

#define FACEFRAME_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// テクスチャサイズ

#define FACEFRAME_POS01     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACEFRAME_POS02		D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACEFRAME_POS03		D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACEFRAME_POS04		D3DXVECTOR3(954.0f, 0.0f, 0.0f)

#define FACE1_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACE2_POS			D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE3_POS			D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE4_POS			D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Faceframe :
	public _2dobj {
public:
	Faceframe(D3DXVECTOR3 _pos, const char *texno);
	~Faceframe();

	int fc;

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif