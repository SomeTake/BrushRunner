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
	if (pM->GetMapTbl(-y, x) >= 0 && pM->GetMapTbl(-y, x) < MapChipMax)
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
