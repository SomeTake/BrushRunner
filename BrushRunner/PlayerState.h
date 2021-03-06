//=============================================================================
//
// プレイヤーの状態抽象インターフェース[PlayerState.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PLAYERSTATE_H_
#define _PLAYERSTATE_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class PlayerState
{
public:
	PlayerState();
	virtual ~PlayerState();

	// 現在のアニメーションによって状態を更新
	virtual void Update(int AnimCurtID) = 0;
};

#endif