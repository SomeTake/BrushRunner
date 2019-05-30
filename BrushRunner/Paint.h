//=============================================================================
//
// ペイント [Paint.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _PAINT_H_
#define _PAINT_H_

#include "Billboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PAINT		"data/TEXTURE/paint"		// 読み込むテクスチャファイル名
#define	PAINT_WIDTH			(10.0f)						// 幅
#define	PAINT_HEIGHT		(10.0f)						// 高さ
#define MAX_PAINT			(100)						// 同時に表示できる最大数
#define PAINT_DIVIDE_X		(5)
#define PAINT_DIVIDE_Y		(1)
#define PAINT_DIVIDE		(PAINT_DIVIDE_X * PAINT_DIVIDE_Y)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class PAINT :
	public BILLBOARD
{
private:
	bool					use;			// 使用しているかどうか
	float					DecAlpha;		// 減衰値
	int						time;			// 表示する時間
	int						patternAnim;	// テクスチャパターン
	int						ctrlNum;		// コントローラ番号

public:
	PAINT(int _ctrlNum);
	~PAINT();

	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetVertex(int nIdxParticle, float _Width, float _Height);
	void SetColor(int nIdxParticle, D3DXCOLOR _col);
	void SetTexture();
};

#endif
