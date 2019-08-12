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
// クラス定義
//*****************************************************************************
class FaceFrame : public _2dobj 
{
private:
	HRESULT MakeVertex(void);
	void SetVertex(void);

public:
	FaceFrame(int PlayerNo);
	~FaceFrame();

	// オーバーライド関数
	void Update();
	void Draw();
	void SetPlayerDeadTexture(void);
};

#endif