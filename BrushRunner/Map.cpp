//=============================================================================
//
// �}�b�v���� [Map.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Map.h"
#include "Input.h"
#include "Debugproc.h"
#include "MyLibrary.h"
#include "Collision.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3 MapCenterPos;	// �\������Ă���}�b�v�̒��S���W

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Map::Map()
{
	// �|�C���^�̃Z�b�g
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		pMaptbl[i] = maptbl[i];
		pObjtbl[i] = objtbl[i];
	}

	// csv�f�[�^�ǂݍ���
	ReadCsv(MAP_FILE, pMaptbl);
	ReadCsv(OBJECT_FILE, pObjtbl);

	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			pChip[cntY][cntX] = new Chip(cntX, cntY, maptbl[cntY][cntX]);
			pObjChip[cntY][cntX] = new ObjectChip(cntX, cntY, objtbl[cntY][cntX]);
		}
	}

	MapCenterPos = pChip[0][0]->GetPos();
	MapCenterPos.x += CHIP_SIZE * MAP_SIZE_X * 0.5f;
	MapCenterPos.y -= CHIP_SIZE * MAP_SIZE_Y * 0.5f;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Map::~Map()
{
	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			delete pChip[cntY][cntX];
			delete pObjChip[cntY][cntX];
		}
	}
}

//=============================================================================
// �X�V
//=============================================================================
void Map::Update()
{
	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			pChip[cntY][cntX]->Update();
			pObjChip[cntY][cntX]->Update();
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void Map::Draw()
{
	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			// �`�攻��
			if (maptbl[cntY][cntX] >= 0)
			{
				pChip[cntY][cntX]->Draw();
			}
			if (objtbl[cntY][cntX] >= 0)
			{
				pObjChip[cntY][cntX]->Draw();
			}
		}
	}
}

//=============================================================================
// �y�C���g�}�l�[�W���Ƃ̓����蔻��
//=============================================================================
void Map::PaintCollider(QUADTREE *Quadtree, int NodeID)
{
	std::vector<Paint*> CollisionList = Quadtree->GetObjectsAt(NodeID);

	// ���݂̃m�[�h�̓I�u�W�F�N�g���Ȃ�
	if (CollisionList.empty())
	{
		return;
	}

	for (auto &BlackPaint : CollisionList)
	{
		// �g�p���Ă���A�J���[�����̂��̂�T��
		if (!BlackPaint->GetUse() || BlackPaint->GetPaintColor() != BlackInkColor)
			continue;

		for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
		{
			for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
			{
				// ���݂��Ă���A�����]���Ă��Ȃ����̂�T��
				if (objtbl[cntY][cntX] = -1 || pObjChip[cntY][cntX]->GetReverse() ||
					!pObjChip[cntY][cntX]->GetUse())
					continue;

				// ���g�̊m�F
				if (!(objtbl[cntY][cntX] == OBJ_NUM_SPDUP || objtbl[cntY][cntX] == OBJ_NUM_SPDDOWN ||
					objtbl[cntY][cntX] == OBJ_NUM_DRAIN || objtbl[cntY][cntX] == OBJ_NUM_HEAL))
					continue;

				// �y�C���g�ƃt�B�[���h�I�u�W�F�N�g�𔻒肷��
				if (HitSphere(BlackPaint->GetPos(), pObjChip[cntY][cntX]->GetPos(), Paint::GetPaintRadius(), CHIP_SIZE))
				{
					// �q�b�g�����ꍇ���̃y�C���g������
					BlackPaint->SetUse(false);
					// �t�B�[���h�I�u�W�F�N�g�𔽓]������
					pObjChip[cntY][cntX]->SetReverse(true);
					pObjChip[cntY][cntX]->ReverseTexture();
					break;
				}
			}
		}
	}
}

//=============================================================================
// �\������Ă���}�b�v�̒��S���W
//=============================================================================
D3DXVECTOR3 GetMapCenterPos()
{
	return MapCenterPos;
}