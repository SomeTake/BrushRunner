//=============================================================================
//
// マップ処理 [Map.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "Chip.h"

class QUADTREE;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define MAP_SIZE_X		(500)								// マップの横の枚数
#define MAP_SIZE_Y		(50)								// マップの縦の枚数
#define START_POS		D3DXVECTOR3(50.0f, 0.0f, 0.0f)		// スタート地点
#define GOAL_POS		D3DXVECTOR3(9500.0f, 0.0f, 0.0f)	// ゴール地点

// マップチップ座標を取得の種類
enum e_ChipPosType
{
	eLeftUp,	// マップチップの左上の座標 
	eRightUp,	// マップチップの右上の座標 
	eCenter,	// マップチップの中心の座標 
	eCenterUp,	// マップチップの中央の上の座標
};

#define OBJ_NUM_SPDUP	(0)
#define OBJ_NUM_SPDDOWN	(1)
#define OBJ_NUM_NUMA	(2)
#define OBJ_NUM_JUMP	(3)
#define OBJ_NUM_DRAIN	(4)
#define OBJ_NUM_HEAL	(5)
#define OBJ_NUM_ITEM	(6)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Map
{
private:
	static std::vector<std::vector<int>>	maptbl;
	std::vector<Chip*>						MapChipVector;
	//int maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// マップ用の配列
	//int	*pMaptbl[MAP_SIZE_Y];				// 配列のポインタ
	//Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];	// チップのポインタ
	//std::vector<Chip*>				NoEmptyMapChip;

	static std::vector<std::vector<int>>	objtbl;
	std::vector<Chip*>						ObjectChipVector;
	//int objtbl[MAP_SIZE_Y][MAP_SIZE_X];		// フィールドオブジェクト用の配列
	//int *pObjtbl[MAP_SIZE_Y];
	//ObjectChip *pObjChip[MAP_SIZE_Y][MAP_SIZE_X];
	//std::vector<ObjectChip *> NoEmptyObjectChip;

public:
	Map();
	~Map();

	void Update();
	void Draw();

	static int GetMapTbl(int MapX, int MapY);
	static int GetMapTbl(D3DXVECTOR3 Pos, int ChipDirection);
	static int GetObjTbl(int ObjX, int ObjY);
	static void GetMapChipXY(D3DXVECTOR3 Pos, int *MapX, int *MapY);
	static D3DXVECTOR3 GetMapChipPos(int x, int y, int PosType);

	void PaintCollider(QUADTREE *Quadtree, int NodeID);

};

//D3DXVECTOR3 GetMapCenterPos();					// 表示されているマップの中心座標

#endif
