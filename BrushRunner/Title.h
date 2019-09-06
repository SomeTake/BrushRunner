//=============================================================================
//
// タイトル画面処理 [Title.h]
// Author : HAL東京 GP12B312 11 小松将吉
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "_2dobj.h"

enum TitleUI {
	TitleLogo,
	TitleRunner,
	TitleMenu,
};

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
