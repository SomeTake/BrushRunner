//=============================================================================
//
// コリジョン[Collision.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Collision.h"
#include "Debugproc.h"
#include "Gravity.h"
#include "Input.h"

//=============================================================================
// 矩形の当たり判定
//=============================================================================
bool HitCheckBB(D3DXVECTOR3 posA, D3DXVECTOR3 posB, D3DXVECTOR2 sizeA, D3DXVECTOR2 sizeB)
{
	sizeA.x /= 2.0f;
	sizeA.y /= 2.0f;
	sizeB.x /= 2.0f;
	sizeB.y /= 2.0f;

	if ((posB.x + sizeB.x > posA.x - sizeA.x) && (posA.x + sizeA.x > posB.x - sizeB.x) &&
		(posB.y + sizeB.y > posA.y - sizeA.y) && (posA.y + sizeA.y > posB.y - sizeB.y))
	{
		return true;
	}

	return false;
}

//=============================================================================
// 球の当たり判定
//=============================================================================
bool HitSphere(D3DXVECTOR3 Pos1, D3DXVECTOR3 Pos2, float Radius1, float Radius2)
{
	// 当たり判定の中心の距離を測る
	float dist = D3DXVec3LengthSq(&D3DXVECTOR3(Pos1 - Pos2));

	// 当たり判定の範囲を足した距離を出す（球なのでXYZどれとっても同じ）
	float hitrange = powf((Radius1 + Radius2), 2);

	// 当たり判定の中心の距離よりも範囲を足した距離の方が長ければ当たる
	return dist <= hitrange ? true : false;
}

//=============================================================================
// プレイヤーと足元のマップの当たり判定
//=============================================================================
bool HitCheckPToM(Player *pP, Map *pM)
{
	// キャラクターの座標からマップ配列の場所を調べる
	int x = (int)((pP->GetPos().x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pP->GetPos().y - CHIP_SIZE / 2) / CHIP_SIZE);

	// 当たり判定を確認するマップチップの場所
	D3DXVECTOR3 mappos;
	mappos.x = MAP_POS.x + CHIP_SIZE * x;
	mappos.y = MAP_POS.y + CHIP_SIZE * y;
	mappos.z = 0.0f;

	// プレイヤーの足元のマップチップから右上のマップチップの番号
	int frontx = x + 1;
	int fronty = y + 1;

	// 前方のオブジェクトに引っかかるかチェック(ジャンプ中はチェックしない)
	if (!pP->GetJumpFlag())
	{
		if (pM->GetMapTbl(frontx, fronty) >= 0)
		{
			pP->SetMoveFlag(false);
		}
		else
		{
			pP->SetMoveFlag(true);
		}
	}

	// マップ外判定
	if (!HitCheckBB(pP->GetPos(), GetMapCenterPos(), PLAYER_COLLISION_SIZE, D3DXVECTOR2(MAP_SIZE_X * CHIP_SIZE, MAP_SIZE_Y * CHIP_SIZE)))
	{
		pP->SetMoveFlag(true);

		return false;
	}

#ifndef _DEBUG_
	//PrintDebugProc("現在プレイヤーがいるMapTbl[%d][%d]\n", -y, x);
	//PrintDebugProc("プレイヤーの前のMapTbl[%d][%d]\n", -fronty, frontx);
	//PrintDebugProc("MapTblの中身:%d\n", pM->GetMapTbl(-y, x));
#endif

	// 現在座標があるところになにかオブジェクトがあればヒットしている
	if (pM->GetMapTbl(x, y) >= 0)
	{
		// めり込みを修正
		PosModification(pP, mappos);
		pP->SetJumpFlag(false);

		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// プレイヤーとペイントシステムの当たり判定
//=============================================================================
bool HitCheckPToS(Player *pP, PaintManager *pS)
{
	for (auto &Paint : pS->GetColorPaint())
	{
		if (!Paint->GetUse())
		{
			continue;
		}

		// ひとつひとつのペイントとプレイヤーの当たり判定を行う
		if (HitSphere(pP->GetPos(), Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
		{
			// 当たった場合、プレイヤーの座標を修正
			D3DXVECTOR3 setpos = pP->GetPos();
			setpos.y = Paint->GetPos().y + PAINT_WIDTH * 0.1f;

			pP->SetPos(setpos);

			return true;
		}
	}

	return false;

	//for (int i = 0; i < INK_MAX; i++)
	//{
	//	// 使用している場合当たり判定を行う
	//	if (pS->GetColorPaint(i)->GetUse())
	//	{
	//		// ひとつひとつのペイントとプレイヤーの当たり判定を行う
	//		if (HitSphere(pP->GetPos(), pS->GetColorPaint(i)->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
	//		{
	//			// 当たった場合、プレイヤーの座標を修正
	//			D3DXVECTOR3 setpos = pP->GetPos();
	//			setpos.y = pS->GetColorPaint(i)->GetPos().y + PAINT_WIDTH * 0.1f;

	//			pP->SetPos(setpos);

	//			returnflag = true;
	//		}
	//	}
	//}
}

//=============================================================================
// ペイントシステム同士の当たり判定
// pSysBlack : 黒インク用ペイントシステムのポインタ
//=============================================================================
void HitCheckSToS(QUADTREE *Quadtree, int NodeID)
{
	std::vector<Paint*> CollisionList = Quadtree->GetObjectsAt(NodeID);

	// 現在のノードはオブジェクトがない
	if (CollisionList.empty())
	{
		return;
	}

	// プレイヤー
	for (int PlayerNo = 0; PlayerNo < PLAYER_MAX; PlayerNo++)
	{
		std::vector<Paint*> BlackList;
		std::vector<Paint*> ColorList;

		for (auto &BlackPaint : CollisionList)
		{
			// 使用している、カラーが黒、所有者が現在のプレイヤーを探す
			if (!BlackPaint->GetUse() || BlackPaint->GetPaintColor() != BlackInkColor ||
				BlackPaint->GetOwner() != PlayerNo)
			{
				continue;
			}

			for (auto &ColorPaint : CollisionList)
			{
				if (!ColorPaint->GetUse() || ColorPaint->GetPaintColor() == BlackInkColor ||
					ColorPaint->GetOwner() == PlayerNo)
				{
					continue;
				}

				// 二つのペイントを判定する
				if (HitSphere(BlackPaint->GetPos(), ColorPaint->GetPos(), Paint::GetPaintRadius(), Paint::GetPaintRadius()))
				{
					// ヒットした場合そのペイントを消す
					BlackPaint->SetUse(false);
					ColorPaint->SetUse(false);
					break;
				}
			}
		}
	}
}

//=============================================================================
// 内積
//=============================================================================
float dotProduct(D3DXVECTOR3 *vl, D3DXVECTOR3 *vr)
{
#if 1
	float ans = vl->x * vr->x + vl->y * vr->y + vl->z * vr->z;
#else
	float ans = D3DXVec3Dot(vl, vr);
#endif	
	return ans;
}


//=============================================================================
// 外積
//=============================================================================
void crossProduct(D3DXVECTOR3 *ret, D3DXVECTOR3 *vl, D3DXVECTOR3 *vr)
{
#if 1
	ret->x = (vl->y * vr->z) - (vl->z * vr->y);
	ret->y = (vl->z * vr->x) - (vl->x * vr->z);
	ret->z = (vl->x * vr->y) - (vl->y * vr->x);
#else
	D3DXVec3Cross(ret, vl, vr);
#endif
}

//=============================================================================
// ポリゴンと線分との当たり判定
// OutPos :出力
// tri    :三角形ポリゴン
// pos0   :始点（移動前）
// pos1   :終点（移動後）
//=============================================================================
int hitCheck(D3DXVECTOR3 *OutPos, TriangleStr tri, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	D3DXVECTOR3		nor;		// ポリゴンの法線

	// ポリゴンの外積をとって法線を求める。そして正規化しておく。
	D3DXVECTOR3		vec01 = tri.pos1 - tri.pos0;
	D3DXVECTOR3		vec02 = tri.pos2 - tri.pos0;
	crossProduct(&nor, &vec01, &vec02);

	{
		// 平面と線分の内積とって衝突している可能性を調べる
		// 求めた法線とベクトル２つ（線分の両端とポリゴン上の任意の点）の内積とって衝突している可能性を調べる
		D3DXVECTOR3		vec1 = pos0 - tri.pos0;
		D3DXVECTOR3		vec2 = pos1 - tri.pos0;
		float a = dotProduct(&vec1, &nor);
		float b = dotProduct(&vec2, &nor);

		if ((a * b) > 0)
		{
			// 当たっている可能性は無い
			return(0);
		}
	}


	{
		// ポリゴンと線分の交点を求める
		D3DXVECTOR3		vec1 = pos0 - tri.pos0;
		D3DXVECTOR3		vec2 = pos1 - tri.pos0;
		float			d1 = (float)fabs(dotProduct(&nor, &vec1));			// 内分比を求める為の点とポリゴンとの距離
		float			d2 = (float)fabs(dotProduct(&nor, &vec2));			// 内分比を求める為の点とポリゴンとの距離
		float			a = d1 / (d1 + d2);									// 内分比
		D3DXVECTOR3		vec3 = (1 - a) * vec1 + a * vec2;
		D3DXVECTOR3		p3 = tri.pos0 + vec3;										// 交点

		{	// 求めた交点がポリゴンの中にあるか調べる

			// ポリゴンの各辺のベクトル
			D3DXVECTOR3		v1 = tri.pos1 - tri.pos0;
			D3DXVECTOR3		v2 = tri.pos2 - tri.pos1;
			D3DXVECTOR3		v3 = p3 - tri.pos2;

			// 各頂点と交点とのベクトル
			D3DXVECTOR3		v4 = p3 - tri.pos1;
			D3DXVECTOR3		v5 = p3 - tri.pos2;
			D3DXVECTOR3		v6 = p3 - tri.pos0;

			// 各辺との外積で法線を求める
			D3DXVECTOR3		n1, n2, n3;
			crossProduct(&n1, &v1, &v4);
			crossProduct(&n2, &v2, &v5);
			crossProduct(&n3, &v3, &v6);

			// それぞれのベクトルの向きを内積でチェック
			if (dotProduct(&n1, &nor) < 0) return(0);
			if (dotProduct(&n2, &nor) < 0) return(0);
			if (dotProduct(&n3, &nor) < 0) return(0);
		}

		// 出力用の座標をセット
		*OutPos = p3;
	}

	return(1);
}