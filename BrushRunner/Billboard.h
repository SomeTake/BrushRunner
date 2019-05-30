//=============================================================================
//
// ビルボード用クラス [Billboard.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BILLBOARD
{
protected:
	LPDIRECT3DTEXTURE9		D3DTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// 頂点バッファインターフェースへのポインタ
	D3DXVECTOR3				pos;			// 位置
	D3DXVECTOR3				rot;			// 回転
	D3DXVECTOR3				scl;			// スケール
	D3DXCOLOR				col;			// 色
	D3DXVECTOR3				move;			// 移動量
	float					width;			// 幅
	float					height;			// 高さ

public:
	BILLBOARD();
	~BILLBOARD();

	// 仮想関数
	virtual void Update() {};
	virtual void Draw() {};
	virtual int Set() { return 0; };
};

#endif
