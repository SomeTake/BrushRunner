//=============================================================================
//
// プレイヤー順位 [ResultRank.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _RESULTRANK_H_
#define _RESULTRANK_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULTRANK_DIVIDE_X	(1)
#define RESULTRANK_DIVIDE_Y	(4)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultRank :
	public _2dobj
{
private:
	int rank;	// 順位
	int owner;	// プレイヤー番号
	HRESULT MakeVertex();

public:
	ResultRank(int rank, int owner);
	~ResultRank();

	void Update();
	void Draw();

};

#endif
