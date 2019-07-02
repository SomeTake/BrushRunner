//=============================================================================
//
// マップ処理 [Map.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "Chip.h"
#include "ObjectChip.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_FILE		("data/MAP/map.csv")				// 読み込むマップデータ
#define OBJECT_FILE		("data/MAP/obj.csv")
#define MAP_SIZE_X		(500)								// マップの横の枚数
#define MAP_SIZE_Y		(50)								// マップの縦の枚数
#define START_POS		D3DXVECTOR3(50.0f, 0.0f, 0.0f)		// スタート地点
#define GOAL_POS		D3DXVECTOR3(1000.0f, 0.0f, 0.0f)	// ゴール地点

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Map
{
private:
	int maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// マップ用の配列
	int	*pMaptbl[MAP_SIZE_Y];				// 配列のポインタ
	Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];	// チップのポインタ

	int objtbl[MAP_SIZE_Y][MAP_SIZE_X];		// フィールドオブジェクト用の配列
	int *pObjtbl[MAP_SIZE_Y];
	ObjectChip *pObjChip[MAP_SIZE_Y][MAP_SIZE_X];

public:
	Map();
	~Map();

	void Update();
	void Draw();

	int GetMapTbl(int _MapX, int _MapY) { return maptbl[-_MapY][_MapX]; };
	int GetObjTbl(int _ObjX, int _ObjY) { return objtbl[_ObjY][_ObjX]; };
};

D3DXVECTOR3 GetMapCenterPos();					// 表示されているマップの中心座標

#endif
