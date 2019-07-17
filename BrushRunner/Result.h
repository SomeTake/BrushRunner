//=============================================================================
//
// タイトル表示処理 [Result.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_RESULT01 _T("data/texture/result.png")											// タイトルのテクスチャ
#define RESULT_SIZE01			D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f)					// テクスチャサイズ
#define RESULT_POS01				D3DXVECTOR3(0.0f,0.0f,0.0f)									// テクスチャ座標



//*****************************************************************************
// クラス定義
//*****************************************************************************
class RESULT :
	public _2dobj
{
public:
	RESULT(D3DXVECTOR3 _pos, D3DXVECTOR3 _size, const char *texno);
	~RESULT();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex(void);
};

#endif
