//=============================================================================
//
// 桁 [Digit.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _DIGIT_H_
#define _DIGIT_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DIGIT_MAX		(6)		// 表示桁数
#define TEXTURE_DIGIT	("data/TEXTURE/Digit.png")
#define DIGIT_DIVIDE_X	(10)
#define DIGIT_DIVIDE_Y	(1)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Digit :
	public _2dobj
{
protected:
	static LPDIRECT3DTEXTURE9 D3DTexture;	// テクスチャのポインタ
	DWORD time;								// その桁に表示する数字（0-9 or 0-5）

	HRESULT MakeVertex();
	void SetTexture();

public:
	Digit(int digit);
	~Digit();

	void Update()override;
	void Update(DWORD time);
	void Draw()override;
};

#endif
