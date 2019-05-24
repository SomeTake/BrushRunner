//=============================================================================
//
// カーソル表示 [Cursor.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "_2dobj.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CURSOR_TEXTURE	_T("data/TEXTURE/pen.png")				// テクスチャ
#define CURSOR_SIZE D3DXVECTOR2(50.0f, 100.0f)					// サイズ
#define CURSOR_DIVIDE_X	(4)										// 横分割
#define CURSOR_DIVIDE_Y	(2)										// 縦分割
#define CURSOR_PATTERN	(CURSOR_DIVIDE_X * CURSOR_DIVIDE_Y)		// 分割数
#define CURSOR_FIRST_POS	D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
#define CURSOR_SPEED	(10.0f)									// 動くスピード

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CURSOR :
	public _2dobj
{
private:
	int ctrlNum;		// 操作するコントローラ番号
	PLAYER *pPlayer;	// 参照するキャラクタのポインタ

public:
	CURSOR(int _ctrlNum, PLAYER *pP);
	~CURSOR();

	// オーバーライド関数
	void Update();						// 更新
	void Draw();						// 描画
	HRESULT MakeVertex();				// 頂点の作成
	void SetTexture(int cntPattern);	// テクスチャ座標の設定
	void SetVertex();					// 頂点座標の設定

	void Move();						// 操作
	void Change();						// 切り替え

	void KeyMove();						// キーボード操作
	void PadMove();						// コントローラ操作

};

#endif
