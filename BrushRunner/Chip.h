//=============================================================================
//
// チップ処理 [Chip.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _CHIP_H_
#define _CHIP_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHIP_TEXTURE	("data/MAP/tilea5.png")
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// 表示場所
#define MAP_ROT			D3DXVECTOR3(D3DXToRadian(-90), 0.0f, 0.0f)	// 回転
#define CHIP_SIZE		(20.0f)								// マップチップ一枚のサイズ
#define CHIP_DIVIDE_X	(8)
#define CHIP_DIVIDE_Y	(16)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Chip
{
private:
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	static LPDIRECT3DTEXTURE9 D3DTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;	// 頂点バッファへのポインタ
	bool use;

	HRESULT MakeVertex(int texnum);
	void CheckOnCamera();

public:
	Chip(int x, int y, int texnum);
	~Chip();

	void Update();
	void Draw();

	D3DXVECTOR3 GetPos() { return pos; };
	bool GetUse() { return use; };

};

#endif
