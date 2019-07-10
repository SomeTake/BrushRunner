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
#define CHIP_SIZE		(20.0f)								// マップチップ一枚のサイズ


enum eChipType
{
	eMapChip,
	eObjectChip,
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Chip
{
private:
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;	// 頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9 D3DTexture;		// テクスチャへのポインタ
	bool use;
	int ChipType;

	HRESULT MakeVertex(int texnum);
	void CheckOnCamera();

public:
	Chip(int x, int y, int texnum, int ChipType);
	~Chip();

	void Update();
	void Draw();
	static void ReleaseTexture(void) { SAFE_RELEASE(Chip::D3DTexture); };

	D3DXVECTOR3 GetPos() { return pos; };
	bool GetUse() { return use; };
};

#endif
