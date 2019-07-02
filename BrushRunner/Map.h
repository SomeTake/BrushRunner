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
#define MAP_SIZE_X		(500)								// マップの横の枚数
#define MAP_SIZE_Y		(50)								// マップの縦の枚数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Map
{
private:
	std::vector<std::vector<int>>	maptbl;
	std::vector<Chip*>				MapChipVector;
	//int maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// マップ用の配列
	//int	*pMaptbl[MAP_SIZE_Y];				// 配列のポインタ
	//Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];	// チップのポインタ
	//std::vector<Chip*>				NoEmptyMapChip;

	std::vector<std::vector<int>>	objtbl;
	std::vector<ObjectChip*>		ObjectChipVector;
	//int objtbl[MAP_SIZE_Y][MAP_SIZE_X];		// フィールドオブジェクト用の配列
	//int *pObjtbl[MAP_SIZE_Y];
	//ObjectChip *pObjChip[MAP_SIZE_Y][MAP_SIZE_X];
	//std::vector<ObjectChip *> NoEmptyObjectChip;

public:
	Map();
	~Map();

	void Update();
	void Draw();

	int GetMapTbl(int MapX, int MapY);
	int GetObjTbl(int ObjX, int ObjY);
	static void GetMapChipXY(D3DXVECTOR3 Pos, int *MapX, int *MapY);
	static D3DXVECTOR3 GetMapChipPos(int MapX, int MapY);
};

//D3DXVECTOR3 GetMapCenterPos();					// 表示されているマップの中心座標

#endif
