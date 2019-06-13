//=============================================================================
//
// ポップアップ表示処理 [Pop.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _POP_H_
#define _POP_H_

#include "Billboard.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_POP		"data/TEXTURE/pointer.png"	// 読み込むテクスチャファイル名
#define	POP_WIDTH		(64.0f)							// 半径高さ
#define	POP_HEIGHT		(32.0f)							// 半径幅
#define POP_POS			D3DXVECTOR3(0.0f, 90.0f, 0.0f)	// 表示場所
#define POP_DIVIDE_X	(4)
#define POP_DIVIDE_Y	(1)
#define POP_ANIM_DIVIDE	(POP_DIVIDE_X * POP_DIVIDE_Y)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class POP :
	public BILLBOARD
{
private:
	PLAYER * pPlayer;
	int patternAnim;

	static LPDIRECT3DTEXTURE9 D3DTexture;		// テクスチャへのポインタ

public:
	POP(PLAYER *pP);
	~POP();

	void Update();
	void Draw();
	HRESULT MakeVertex();

};

#endif
