//=============================================================================
//
// キャラクターセレクトカーソル [CursorObj.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _CURSOROBJ_H_
#define _CURSOROBJ_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_CURSOROBJ	("data/TEXTURE/CharSelectCursor.png")		// フレーム用画像
#define CURSOROBJ_DIVIDE_X	(4)											// 分割数
#define CURSOROBJ_MAX		(4)											// 1プレイヤーあたりのカーソル数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CursorObj :
	public _2dobj
{
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;	// テクスチャのポインタ

	HRESULT MakeVertex();
	void SetTexture();
	void SetVertex();

	void Move();	// カーソルの移動

public:
	int playerNo;	// 参照するプレイヤー番号
	int cursorNo;	// 座標を参照する番号
	int selectNo;	// 選択したキャラクターの番号

	CursorObj(int playerNo, int cursorNo);
	~CursorObj();

	// オーバーライド関数
	void Update();
	void Draw();

	int GetCursorNo() { return cursorNo; };
	int GetSelectNo() { return selectNo; };

};

#endif