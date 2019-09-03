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
// クラス定義
//*****************************************************************************
class TITLE :
	public _2dobj
{
public:
	TITLE(int num);
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
