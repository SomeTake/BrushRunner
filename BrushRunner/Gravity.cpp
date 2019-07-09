//=============================================================================
//
// 重力処理 [Gravity.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Gravity.h"
#include "Map.h"

//=============================================================================
// 重力計算　引数：落下させるキャラクタのポインタ
//=============================================================================
void GravityFall(Player *pP)
{
	// 空中はジャンプ入力できない
	pP->SetJumpFlag(true);

	// 落下最大速度よりも遅い場合、落下速度が重力加速度に合わせて加速する
	if (pP->GetJumpSpeed() > -FALL_VELOCITY_MAX)
	{
		float speed = pP->GetJumpSpeed() - STANDARD_GRAVITY;
		pP->SetJumpSpeed(speed);
	}


}

//=============================================================================
// めり込みを修正　引数：キャラクタのポインタ、足元のマップの座標
//=============================================================================
void PosModification(Player *pP, D3DXVECTOR3 mappos)
{
	D3DXVECTOR3 newpos = pP->GetPos();

	// マップチップの座標のちょっと下
	newpos.y = mappos.y - 0.01f;

	pP->SetPos(newpos);
}