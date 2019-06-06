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
#define TEXTURE_INKGAUGEBLACK	_T("data/texture/inkline.black.png")			// フレーム用画像
#define TEXTURE_INKGAUGEBLUE		_T("data/texture/inkline.blue.png")			// フレーム用画像
#define TEXTURE_INKGAUGERED		_T("data/texture/inkline.red.png")			// フレーム用画像
#define TEXTURE_INKGAUGEYELLOW	_T("data/texture/inkline.yellow.png")			// フレーム用画像
#define TEXTURE_INKGAUGEGREEN	_T("data/texture/inkline.green.png")			// フレーム用画像

#define INK_SIZE	D3DXVECTOR2(135.0f, 30.0f)	// 表示サイズ

#define INKLINEBLUE_POS     D3DXVECTOR3(70.0f, 35.0f, 0.0f)
#define INKLINERED_POS      D3DXVECTOR3(388.0f, 35.0f, 0.0f)
#define INKLINEYELLOW_POS   D3DXVECTOR3(706.0f, 35.0f, 0.0f)
#define INKLINEGREEN_POS    D3DXVECTOR3(1024.0f, 35.0f, 0.0f)

#define INKLINEBLACK_POS01  D3DXVECTOR3(70.0f, 45.0f, 0.0f)
#define INKLINEBLACK_POS02  D3DXVECTOR3(388.0f, 45.0f, 0.0f)
#define INKLINEBLACK_POS03  D3DXVECTOR3(706.0f, 45.0f, 0.0f)
#define INKLINEBLACK_POS04  D3DXVECTOR3(1024.0f, 45.0f, 0.0f)

#define DISPLACE	(20.0f)		// 斜めにずらす角度

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
