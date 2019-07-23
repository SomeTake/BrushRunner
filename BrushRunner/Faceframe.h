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

#define FACEFRAME_POS01     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACEFRAME_POS02		D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACEFRAME_POS03		D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACEFRAME_POS04		D3DXVECTOR3(954.0f, 0.0f, 0.0f)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FaceFrame : public _2dobj 
{
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;					// テクスチャのポインタ

	HRESULT MakeVertex(void);
	void SetVertex(void);

public:
	FaceFrame(int PlayerNo);
	~FaceFrame();
	static void ReleaseTexture(void);

	int fc;

	// オーバーライド関数
	void Update();
	void Draw();
	void SetPlayerDeadTexture(void);
};

#endif