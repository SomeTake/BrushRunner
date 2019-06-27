//=============================================================================
//
// フィールドオブジェクトチップ処理 [ObjectChip.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _OBJECTCHIP_H_
#define _OBJECTCHIP_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBJECTCHIP_TEXTURE	("data/MAP/tilea5.png")
#define OBJECTCHIP_DIVIDE_X	(8)
#define OBJECTCHIP_DIVIDE_Y	(16)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ObjectChip
{
private:
	D3DXVECTOR3	pos;
	D3DXVECTOR3	rot;
	D3DXVECTOR3	scl;
	static LPDIRECT3DTEXTURE9 D3DTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;	// 頂点バッファへのポインタ
	bool use;

	HRESULT MakeVertex(int texnum);
	void CheckOnCamera();

public:
	ObjectChip(int x, int y, int texnum);
	~ObjectChip();

	void Update();
	void Draw();

	D3DXVECTOR3 GetPos() { return pos; };

};

#endif
