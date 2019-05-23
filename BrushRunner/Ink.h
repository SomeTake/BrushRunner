//=============================================================================
//
// インクゲージ表示処理 [Ink.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _INK_H_
#define _INK_H_

#include "_2dobj.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INK_SIZE	D3DXVECTOR2(300.0f, 100.0f)	// 表示サイズ

#define INKLINEBLUE_POS     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define INKLINERED_POS      D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define INKLINEYELLOW_POS   D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define INKLINEGREEN_POS    D3DXVECTOR3(954.0f, 0.0f, 0.0f)

#define INKLINEBLACK_POS01  D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define INKLINEBLACK_POS02  D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define INKLINEBLACK_POS03  D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define INKLINEBLACK_POS04  D3DXVECTOR3(954.0f, 0.0f, 0.0f)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class INK :
	public _2dobj
{
private:
	PLAYER * pPlayer;	// 参照するキャラクタクラスのポインタ
	int inktype;		// 使用するインクの種類(0=color,1=black)
public:
	INK(PLAYER *pP, D3DXVECTOR3 _pos, const char *texno, int _inktype);
	~INK();

	// オーバーライド関数
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif
