//=============================================================================
//
// カーソル表示 [Cursor.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CURSOR_TEXTURE	_T("data/TEXTURE/brush.png")				// テクスチャ
#define CURSOR_SIZE D3DXVECTOR3(75.0f, 75.0f, 0.0f)					// サイズ
#define CURSOR_DIVIDE_X	(4)										// 横分割
#define CURSOR_DIVIDE_Y	(2)										// 縦分割
#define CURSOR_PATTERN	(CURSOR_DIVIDE_X * CURSOR_DIVIDE_Y)		// 分割数
#define CURSOR_FIRST_POS	D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
#define CURSOR_SPEED	(30.0f)									// 動くスピード

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Cursor : public _2dobj
{
private:
	int		ctrlNum;	// 操作するコントローラ番号
	float	vec;		// ジョイスティックのベクトルを1/1000にして保存(1.0f-0.0f)
	float	moveX;		// ジョイスティックのX値を1/1000にして保存(1.0f-0.0f)
	float	moveY;		// ジョイスティックのY値を1/1000にして保存(1.0f-0.0f)
	D3DXVECTOR3 oldPos;	// 画面外判定を行うための1f前の座標
	static LPDIRECT3DTEXTURE9	D3DTexture;					// テクスチャのポインタ

	// AI用変数
	bool	AIFlag;
	D3DXVECTOR3 DestPos;

	HRESULT MakeVertex();				// 頂点の作成
	void SetTexture();					// テクスチャ座標の設定
	void SetVertex();					// 頂点座標の設定
	void KeyMove();						// キーボード操作
	void PadMove();						// コントローラ操作
	void Move();						// 操作
	void Change();						// 切り替え
	void AIMove();						// AIがカーソルを移動する

public:
	Cursor(int PlayerNo, bool AIFlag);
	~Cursor();

	// オーバーライド関数
	void Update();						// 更新
	void Draw();						// 描画
	void SetDestPos(D3DXVECTOR3 DestPos) { this->DestPos = DestPos; };

	// カーソルの筆先の座標を取得
	D3DXVECTOR3 GetPenPoint();
};

#endif
