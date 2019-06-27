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
#include "MyLibrary.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3 MapCenterPos;	// 表示されているマップの中心座標

//=============================================================================
// コンストラクタ
//=============================================================================
Map::Map()
{
	// ポインタのセット
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		pMaptbl[i] = maptbl[i];
		pObjtbl[i] = objtbl[i];
	}

	// csvデータ読み込み
	ReadCsv(MAP_FILE, pMaptbl);
	ReadCsv(OBJECT_FILE, pObjtbl);

	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			pChip[cntY][cntX] = new Chip(cntX, cntY, maptbl[cntY][cntX]);
			pObjChip[cntY][cntX] = new ObjectChip(cntX, cntY, objtbl[cntY][cntX]);
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
			delete pObjChip[cntY][cntX];
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
			pObjChip[cntY][cntX]->Update();
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
			// 描画判定
			if (maptbl[cntY][cntX] >= 0)
			{
				pChip[cntY][cntX]->Draw();
			}
			if (objtbl[cntY][cntX] >= 0)
			{
				pObjChip[cntY][cntX]->Draw();
			}
		}
	}
}

//=============================================================================
// 表示されているマップの中心座標
//=============================================================================
D3DXVECTOR3 GetMapCenterPos()
{
	return MapCenterPos;
}