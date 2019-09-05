//=============================================================================
//
// ペイントグループクラス[PaintGroup.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PAINTGROUP_H_
#define _PAINTGROUP_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
typedef struct
{
	std::vector<D3DXVECTOR3> PaintPath;
	int Onwer;
	int Count;
	bool Use;
	bool PaintOver;
}GroupStruct;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class PaintGroup
{
private:
	std::vector<GroupStruct> GroupVector;

public:
	// コンストラクタ
	PaintGroup();
	// デストラクタ
	~PaintGroup();

	void Update();
	void Start(int Owner);
	void Insert(D3DXVECTOR3 Pos, int Owner);
	void End(int Owner);

	bool GetEnemyPaint(GroupStruct** GroupPtr, int PlayerNo);
};

#endif
