//=============================================================================
//
// マップ処理 [Map.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "Chip.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_FILE		("data/MAP/data.csv")				// 読み込むマップデータ
#define MAP_SIZE_X		(100)								// マップの横の枚数
#define MAP_SIZE_Y		(10)								// マップの縦の枚数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Map
{
private:
	string					line;								// 文字列を一時的に保存
	int						maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// マップ用の配列
	const string			delim = ",";						// データ区切り用の文字

	Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];						// チップのポインタ

public:
	Map();
	~Map();

	void Update();
	void Draw();

	void ReadCsv(const char *data);		// CSVファイルの読み込み

	int GetMapTbl(int _MapX, int _MapY) { return maptbl[_MapX][_MapY]; };
};

D3DXVECTOR3 GetMapCenterPos();			// 表示されているマップの中心座標

#endif
