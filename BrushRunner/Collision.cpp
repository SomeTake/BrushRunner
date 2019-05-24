//=============================================================================
//
// �R���W����[Collision.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Collision.h"
#include "Debugproc.h"

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
// �v���C���[�ƃ}�b�v�̓����蔻��
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

	// �}�b�v�O����
	if (!(pP->GetPos().x > 0 && pP->GetPos().x < (MAP_POS.x + CHIP_SIZE * MAP_SIZE_X)))
	{
		if (!(pP->GetPos().y < 0 && pP->GetPos().y > -(MAP_POS.y + CHIP_SIZE * MAP_SIZE_X)))
		{
			return false;
		}
	}

#ifndef _DEBUG_
	PrintDebugProc("MapTbl[%d][%d]\n", -y, x);
	PrintDebugProc("MapTbl�̒��g:%d\n", pM->GetMapTbl(-y, x));
#endif

	// ���ݍ��W������Ƃ���ɂȂɂ��I�u�W�F�N�g������΃q�b�g���Ă���
	if (HitCheckBB(pP->GetPos(), mappos, PLAYER_COLLISION_SIZE, D3DXVECTOR2(CHIP_SIZE, CHIP_SIZE)))
	{
		if (pM->GetMapTbl(-y, x) >= 0 && pM->GetMapTbl(-y, x) < MapChipMax)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
