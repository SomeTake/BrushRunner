//=============================================================================
//
// リザルト画面 [Result.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "_2dobj.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RESULT :
	public _2dobj
{
public:
	RESULT();
	~RESULT();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex(void);
};

#endif
