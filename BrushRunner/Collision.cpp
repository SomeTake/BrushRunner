//=============================================================================
//
// �R���W����[Collision.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Collision.h"
#include "Gravity.h"
#include "Input.h"

//=============================================================================
// ��`�̓����蔻��
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
// ���̓����蔻��
//=============================================================================
bool HitSphere(D3DXVECTOR3 Pos1, D3DXVECTOR3 Pos2, float Radius1, float Radius2)
{
	// �����蔻��̒��S�̋����𑪂�
	float dist = D3DXVec3LengthSq(&D3DXVECTOR3(Pos1 - Pos2));

	// �����蔻��͈̔͂𑫂����������o���i���Ȃ̂�XYZ�ǂ�Ƃ��Ă������j
	float hitrange = powf((Radius1 + Radius2), 2);

	// �����蔻��̒��S�̋��������͈͂𑫂��������̕���������Γ�����
	return dist <= hitrange ? true : false;
}

//=============================================================================
// �v���C���[�Ƒ����̃}�b�v�̓����蔻��
//=============================================================================
bool HitCheckPToM(Player *pP, Map *pM)
{
	// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
	int x = 0, y = 0;
	Map::GetMapChipXY(pP->GetPos(), &x, &y);

	// �����蔻����m�F����}�b�v�`�b�v�̏ꏊ
	D3DXVECTOR3 mappos = Map::GetMapChipPos(x, y, eCenterUp);
	//mappos.x = MAP_POS.x + CHIP_SIZE * x;
	//mappos.y = -(MAP_POS.y + CHIP_SIZE * y);
	//mappos.z = 0.0f;

	// �v���C���[�̑����̃}�b�v�`�b�v����E��̃}�b�v�`�b�v�̔ԍ�
	int frontx = x + 1;
	int fronty = y - 1;

	// �O���̃I�u�W�F�N�g�Ɉ��������邩�`�F�b�N(�W�����v���̓`�F�b�N���Ȃ�)
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

	// �}�b�v�O����
	//if (!HitCheckBB(pP->GetPos(), GetMapCenterPos(), PLAYER_COLLISION_SIZE, D3DXVECTOR2(MAP_SIZE_X * CHIP_SIZE, MAP_SIZE_Y * CHIP_SIZE)))
	//{
	//	pP->SetMoveFlag(true);

	//	return false;
	//}

#ifndef _DEBUG_
	//PrintDebugProc("���݃v���C���[������MapTbl[%d][%d]\n", -y, x);
	//PrintDebugProc("�v���C���[�̑O��MapTbl[%d][%d]\n", -fronty, frontx);
	//PrintDebugProc("MapTbl�̒��g:%d\n", pM->GetMapTbl(-y, x));
#endif

	// ���ݍ��W������Ƃ���ɂȂɂ��I�u�W�F�N�g������΃q�b�g���Ă���
	if (pM->GetMapTbl(x, y) >= 0)
	{
		// �߂荞�݂��C��
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
// �v���C���[�ƃy�C���g�V�X�e���̓����蔻��
//=============================================================================
bool HitCheckPToS(Player *pP)
{
	for (auto &Paint : pP->GetPaintManager()->GetColorPaint())
	{
		if (!Paint->GetUse())
		{
			continue;
		}

		// �ЂƂЂƂ̃y�C���g�ƃv���C���[�̓����蔻����s��
		if (HitSphere(pP->GetPos(), Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
		{
			// ���������ꍇ�A�v���C���[�̍��W���C��
			D3DXVECTOR3 setpos = pP->GetPos();
			setpos.y = Paint->GetPos().y + PAINT_WIDTH * 0.1f;

			pP->SetPos(setpos);

			return true;
		}
	}

	return false;

	//for (int i = 0; i < INK_MAX; i++)
	//{
	//	// �g�p���Ă���ꍇ�����蔻����s��
	//	if (pS->GetColorPaint(i)->GetUse())
	//	{
	//		// �ЂƂЂƂ̃y�C���g�ƃv���C���[�̓����蔻����s��
	//		if (HitSphere(pP->GetPos(), pS->GetColorPaint(i)->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
	//		{
	//			// ���������ꍇ�A�v���C���[�̍��W���C��
	//			D3DXVECTOR3 setpos = pP->GetPos();
	//			setpos.y = pS->GetColorPaint(i)->GetPos().y + PAINT_WIDTH * 0.1f;

	//			pP->SetPos(setpos);

	//			returnflag = true;
	//		}
	//	}
	//}
}

//=============================================================================
// �y�C���g�V�X�e�����m�̓����蔻��
// pSysBlack : ���C���N�p�y�C���g�V�X�e���̃|�C���^
//=============================================================================
void HitCheckSToS(QUADTREE *Quadtree, int NodeID)
{
	std::vector<Paint*> CollisionList = Quadtree->GetObjectsAt(NodeID);

	// ���݂̃m�[�h�̓I�u�W�F�N�g���Ȃ�
	if (CollisionList.empty())
	{
		return;
	}

	// �v���C���[
	for (int PlayerNo = 0; PlayerNo < PLAYER_MAX; PlayerNo++)
	{
		std::vector<Paint*> BlackList;
		std::vector<Paint*> ColorList;

		for (auto &BlackPaint : CollisionList)
		{
			// �g�p���Ă���A�J���[�����A���L�҂����݂̃v���C���[��T��
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

				// ��̃y�C���g�𔻒肷��
				if (HitSphere(BlackPaint->GetPos(), ColorPaint->GetPos(), Paint::GetPaintRadius(), Paint::GetPaintRadius()))
				{
					// �q�b�g�����ꍇ���̃y�C���g������
					BlackPaint->SetUse(false);
					ColorPaint->SetUse(false);
					break;
				}
			}
		}
	}
}

//=============================================================================
// ����
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
// �O��
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
// �|���S���Ɛ����Ƃ̓����蔻��
// OutPos :�o��
// tri    :�O�p�`�|���S��
// pos0   :�n�_�i�ړ��O�j
// pos1   :�I�_�i�ړ���j
//=============================================================================
int hitCheck(D3DXVECTOR3 *OutPos, TriangleStr tri, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	D3DXVECTOR3		nor;		// �|���S���̖@��

	// �|���S���̊O�ς��Ƃ��Ė@�������߂�B�����Đ��K�����Ă����B
	D3DXVECTOR3		vec01 = tri.pos1 - tri.pos0;
	D3DXVECTOR3		vec02 = tri.pos2 - tri.pos0;
	crossProduct(&nor, &vec01, &vec02);

	{
		// ���ʂƐ����̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
		// ���߂��@���ƃx�N�g���Q�i�����̗��[�ƃ|���S����̔C�ӂ̓_�j�̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
		D3DXVECTOR3		vec1 = pos0 - tri.pos0;
		D3DXVECTOR3		vec2 = pos1 - tri.pos0;
		float a = dotProduct(&vec1, &nor);
		float b = dotProduct(&vec2, &nor);

		if ((a * b) > 0)
		{
			// �������Ă���\���͖���
			return(0);
		}
	}


	{
		// �|���S���Ɛ����̌�_�����߂�
		D3DXVECTOR3		vec1 = pos0 - tri.pos0;
		D3DXVECTOR3		vec2 = pos1 - tri.pos0;
		float			d1 = (float)fabs(dotProduct(&nor, &vec1));			// ����������߂�ׂ̓_�ƃ|���S���Ƃ̋���
		float			d2 = (float)fabs(dotProduct(&nor, &vec2));			// ����������߂�ׂ̓_�ƃ|���S���Ƃ̋���
		float			a = d1 / (d1 + d2);									// ������
		D3DXVECTOR3		vec3 = (1 - a) * vec1 + a * vec2;
		D3DXVECTOR3		p3 = tri.pos0 + vec3;										// ��_

		{	// ���߂���_���|���S���̒��ɂ��邩���ׂ�

			// �|���S���̊e�ӂ̃x�N�g��
			D3DXVECTOR3		v1 = tri.pos1 - tri.pos0;
			D3DXVECTOR3		v2 = tri.pos2 - tri.pos1;
			D3DXVECTOR3		v3 = p3 - tri.pos2;

			// �e���_�ƌ�_�Ƃ̃x�N�g��
			D3DXVECTOR3		v4 = p3 - tri.pos1;
			D3DXVECTOR3		v5 = p3 - tri.pos2;
			D3DXVECTOR3		v6 = p3 - tri.pos0;

			// �e�ӂƂ̊O�ςŖ@�������߂�
			D3DXVECTOR3		n1, n2, n3;
			crossProduct(&n1, &v1, &v4);
			crossProduct(&n2, &v2, &v5);
			crossProduct(&n3, &v3, &v6);

			// ���ꂼ��̃x�N�g���̌�������ςŃ`�F�b�N
			if (dotProduct(&n1, &nor) < 0) return(0);
			if (dotProduct(&n2, &nor) < 0) return(0);
			if (dotProduct(&n3, &nor) < 0) return(0);
		}

		// �o�͗p�̍��W���Z�b�g
		*OutPos = p3;
	}

	return(1);
}