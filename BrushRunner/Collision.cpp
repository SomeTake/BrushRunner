//=============================================================================
//
// �R���W����[Collision.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Collision.h"
#include "Debugproc.h"
#include "Gravity.h"

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
// �v���C���[�Ƒ����̃}�b�v�̓����蔻��
//=============================================================================
bool HitCheckPToM(PLAYER *pP, MAP *pM)
{
	// �L�����N�^�[�̍��W����}�b�v�z��̏ꏊ�𒲂ׂ�
	int x = (int)((pP->GetPos().x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pP->GetPos().y - CHIP_SIZE / 2) / CHIP_SIZE);

	// �����蔻����m�F����}�b�v�`�b�v�̏ꏊ
	D3DXVECTOR3 mappos;
	mappos.x = MAP_POS.x + CHIP_SIZE * x;
	mappos.y = MAP_POS.y + CHIP_SIZE * y;
	mappos.z = 0.0f;

	// �v���C���[�̑����̃}�b�v�`�b�v����E��̃}�b�v�`�b�v�̔ԍ�
	int frontx = x + 1;
	int fronty = y + 1;

	// �Ȃɂ��I�u�W�F�N�g�Ɉ��������邩�`�F�b�N
	if (pM->GetMapTbl(-fronty, frontx) >= 0)
	{
		pP->SetMoveFlag(false);
	}
	else
	{
		pP->SetMoveFlag(true);
	}

	// �}�b�v�O����
	if (!HitCheckBB(pP->GetPos(), GetMapCenterPos(), PLAYER_COLLISION_SIZE, D3DXVECTOR2(MAP_SIZE_X * CHIP_SIZE, MAP_SIZE_Y * CHIP_SIZE)))
	{
		pP->SetMoveFlag(true);

		return false;
	}
	
#ifndef _DEBUG_
	PrintDebugProc("���݃v���C���[������MapTbl[%d][%d]\n", -y, x);
	PrintDebugProc("�v���C���[�̑O��MapTbl[%d][%d]\n", -fronty, frontx);
	PrintDebugProc("MapTbl�̒��g:%d\n", pM->GetMapTbl(-y, x));
#endif

	// ���ݍ��W������Ƃ���ɂȂɂ��I�u�W�F�N�g������΃q�b�g���Ă���
	if (pM->GetMapTbl(-y, x) >= 0)
	{
		// �߂荞�݂��C��
		PosModification(pP, mappos);

		return true;
	}
	else
	{
		return false;
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
int hitCheck(D3DXVECTOR3 *OutPos, TRIANGLE_WK tri, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	D3DXVECTOR3		nor;		// �|���S���̖@��

	{	// �|���S���̊O�ς��Ƃ��Ė@�������߂�B�����Đ��K�����Ă����B
		D3DXVECTOR3		vec01 = tri.pos1 - tri.pos0;
		D3DXVECTOR3		vec02 = tri.pos2 - tri.pos0;
		crossProduct(&nor, &vec01, &vec02);
	}

	{	// ���ʂƐ����̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
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


	{	// �|���S���Ɛ����̌�_�����߂�
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