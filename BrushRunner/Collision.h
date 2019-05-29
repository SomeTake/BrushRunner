//=============================================================================
//
// コリジョン[Collision.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Player.h"
#include "Map.h"

bool HitCheckBB(D3DXVECTOR3 posA, D3DXVECTOR3 posB, D3DXVECTOR2 sizeA, D3DXVECTOR2 sizeB);	// 矩形の当たり判定
bool HitCheckPToM(PLAYER *pP, MAP *pM);	// プレイヤーとマップの当たり判定

#endif

