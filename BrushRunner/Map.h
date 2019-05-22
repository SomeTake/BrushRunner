//=============================================================================
//
// マップ処理 [Map.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include <string>
#include <fstream>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_TEXTURE0	("data/MAP/map0.jpg")
#define MAP_TEXTURE1	("data/MAP/map1.jpg")
#define MAP_TEXTURE2	("data/MAP/map2.jpg")
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// 表示場所
#define MAP_ROT			D3DXVECTOR3(D3DXToRadian(-90), 0.0f, 0.0f)	// 回転
#define MAP_FILE		("data/MAP/data.csv")				// 読み込むマップデータ
#define MAP_SIZE_X		(100)									// マップの横の枚数
#define MAP_SIZE_Y		(10)									// マップの縦の枚数
#define CHIP_SIZE		(20.0f)								// マップチップ一枚のサイズ

// マップチップの種類
enum MapStateNum{
	MapField,
	MapTrap,
	MapItem,

	// マップチップの種類数
	MapChipMax
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MAP
{
private:
	string					line;								// 文字列を一時的に保存
	int						maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// マップ用の配列
	const string			delim = ",";						// データ区切り用の文字
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	LPDIRECT3DTEXTURE9		D3DTexture[MapChipMax] = { NULL };	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;					// 頂点バッファへのポインタ


public:
	MAP();
	~MAP();

	void Update();
	void Draw();

	void ReadCsv(const char *data);		// CSVファイルの読み込み
	HRESULT MakeVertex();				// 頂点情報の作成

	int GetMapTbl(int _MapX, int _MapY) { return maptbl[_MapX][_MapY]; };
};

#endif
