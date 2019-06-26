//=============================================================================
//
// マップ処理 [Map.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Map.h"
#include "Input.h"
#include "Debugproc.h"

using namespace std;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3 MapCenterPos;	// 表示されているマップの中心座標

//=============================================================================
// コンストラクタ
//=============================================================================
Map::Map()
{
	// csvデータ読み込み
	ReadCsv(MAP_FILE);

	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			pChip[cntY][cntX] = new Chip(cntX, cntY, maptbl[cntY][cntX]);
		}
	}

	MapCenterPos = pChip[0][0]->GetPos();
	MapCenterPos.x += CHIP_SIZE * MAP_SIZE_X * 0.5f;
	MapCenterPos.y -= CHIP_SIZE * MAP_SIZE_Y * 0.5f;

}

//=============================================================================
// デストラクタ
//=============================================================================
Map::~Map()
{
	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			delete pChip[cntY][cntX];
		}
	}
}

//=============================================================================
// 更新
//=============================================================================
void Map::Update()
{
	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			pChip[cntY][cntX]->Update();
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void Map::Draw()
{
	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			if (maptbl[cntY][cntX] >= 0)
			{
				pChip[cntY][cntX]->Draw();
			}
		}
	}
}

//=============================================================================
// CSVファイルの読み込み
//=============================================================================
void Map::ReadCsv(const char *data)
{
	ifstream stream(data);		// マップの読み込み先

	int row = 0;
	int col;
	while (getline(stream, line))
	{
		col = 0;
		// delimを区切り文字として切り分け、intに変換してmaptbl[][]に格納する
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;)
		{
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			maptbl[row][col++] = stoi(token);
		}
		++row;
	}
}

//=============================================================================
// 表示されているマップの中心座標
//=============================================================================
D3DXVECTOR3 GetMapCenterPos()
{
	return MapCenterPos;
}