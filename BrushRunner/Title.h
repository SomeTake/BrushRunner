//=============================================================================
//
// タイトル表示処理 [Title.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TITLE01 _T("data/texture/Runner.png")										// タイトルのテクスチャ
#define TITLE_SIZE01			D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f)				// テクスチャサイズ
#define TITLE_POS01				D3DXVECTOR3(SCREEN_CENTER_X,SCREEN_CENTER_Y,0.0f)			// テクスチャ座標

#define TEXTURE_TITLE02 _T("data/texture/Logo.png")											// タイトルのテクスチャ
#define TITLE_SIZE02			D3DXVECTOR3(SCREEN_CENTER_X*1.5,SCREEN_CENTER_Y*1.5,0.0f)	// テクスチャサイズ
#define TITLE_POS02				D3DXVECTOR3(SCREEN_CENTER_X,SCREEN_CENTER_Y*0.75,0.0f)		// テクスチャ座標

#define TEXTURE_TITLE03 _T("data/texture/TitleLogo.png")									// タイトルのテクスチャ
#define TITLE_SIZE03			D3DXVECTOR3(SCREEN_CENTER_X/2,SCREEN_CENTER_Y/2,0.0f)		// テクスチャサイズ
#define TITLE_POS03				D3DXVECTOR3(SCREEN_CENTER_X,SCREEN_CENTER_Y*1.6,0.0f)		// テクスチャ座標

//*****************************************************************************
// クラス定義
//*****************************************************************************
class TITLE :
	public _2dobj
{
public:
	TITLE(D3DXVECTOR3 _pos,D3DXVECTOR3 _size,const char *texno);
	~TITLE();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex(void);
	void SetVertexMove(D3DXVECTOR3 pos);
};

#endif
