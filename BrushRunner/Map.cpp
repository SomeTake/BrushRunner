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
// �\������Ă���}�b�v�̒��S���W
//=============================================================================
D3DXVECTOR3 GetMapCenterPos()
{
	return MapCenterPos;
}