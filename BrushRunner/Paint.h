//=============================================================================
//
// ペイント [Paint.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PAINT_H_
#define _PAINT_H_

#include "Billboard.h"
#include "Player.h"
#include "Cursor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PAINT		"data/TEXTURE/paint.png"	// 読み込むテクスチャファイル名
#define	PAINT_WIDTH			(30.0f)						// 幅
#define	PAINT_HEIGHT		(30.0f)						// 高さ
#define PAINT_DIVIDE_X		(5)
#define PAINT_DIVIDE_Y		(1)
#define PAINT_DIVIDE		(PAINT_DIVIDE_X * PAINT_DIVIDE_Y)
#define PAINT_MAX			(INK_MAX * 2)				// カラーインク＆黒インク
#define DRAW_FRAME_COLOR	(300)						// 表示しておくフレーム数
#define DRAW_FRAME_BLACK	(60)						// 表示しておくフレーム数

enum InkColor
{
	RedInkColor,
	BlueInkColor,
	YellowInkColor,
	GreenInkColor,
	BlackInkColor
};

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
	static LPDIRECT3DTEXTURE9		D3DTexture;		// テクスチャへのポインタ

public:
	PAINT();
	~PAINT();

	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetVertex();
	void SetColor();
	void SetTexture();

	// ゲッター
	bool GetUse() { return use; };
	int GetTime() { return time; };
	D3DXVECTOR3 GetPos() { return pos; };
	int GetPatternAnim() { return patternAnim; };

	// セッター
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetRot(D3DXVECTOR3 _rot) { rot = _rot; };
	void SetScl(D3DXVECTOR3 _scl) { scl = _scl; };
	void SetCol(D3DXCOLOR _col) { col = _col; };
	void SetMove(D3DXVECTOR3 _move) { move = _move; };
	void SetWidth(float _width) { width = _width; };
	void SetHeight(float _height) { height = _height; };
	void SetUse(bool _use) { use = _use; };
	void SetDecAlpha(float _DecAlpha) { DecAlpha = _DecAlpha; };
	void SetTime(int _time) { time = _time; };
	void SetPatternAnim(int num) { patternAnim = num; };
};

#endif
