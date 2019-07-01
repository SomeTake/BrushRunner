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
// �}�N����`
//*****************************************************************************
#define MAP_FILE		("data/MAP/map.csv")				// �ǂݍ��ރ}�b�v�f�[�^
#define OBJECT_FILE		("data/MAP/obj.csv")

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//D3DXVECTOR3 MapCenterPos;	// �\������Ă���}�b�v�̒��S���W

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Map::Map()
{
	this->maptbl.reserve(MAP_SIZE_Y);
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		vector<int> Vector_X;
		maptbl.push_back(Vector_X);
		maptbl.at(i).reserve(MAP_SIZE_X);
	}

	this->objtbl.reserve(MAP_SIZE_Y);
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		vector<int> Vector_X;
		objtbl.push_back(Vector_X);
		objtbl.at(i).reserve(MAP_SIZE_X);
	}

	//this->MapChipVector.reserve(1000);
	//this->ObjectChipVector.reserve(1000);

	// �|�C���^�̃Z�b�g
	//for (int i = 0; i < MAP_SIZE_Y; i++)
	//{
	//	pMaptbl[i] = maptbl[i];
	//	pObjtbl[i] = objtbl[i];
	//}

	// csv�f�[�^�ǂݍ���
	ReadCsv(MAP_FILE, &this->maptbl);
	ReadCsv(OBJECT_FILE, &this->objtbl);

	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			if (maptbl.at(cntY).at(cntX) >= 0)
			{
				MapChipVector.push_back(new Chip(cntX, cntY, maptbl.at(cntY).at(cntX)));
			}

			if (objtbl.at(cntY).at(cntX) >= 0)
			{
				ObjectChipVector.push_back(new Chip(cntX, cntY, maptbl.at(cntY).at(cntX)));
			}
		}
	}
#if 0
	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			pChip[cntY][cntX] = new Chip(cntX, cntY, maptbl.at(cntY).at(cntX));
			if (maptbl.at(cntY).at(cntX) >= 0)
			{
				this->MapChipVector.push_back(pChip[cntY][cntX]);
			}

			pObjChip[cntY][cntX] = new ObjectChip(cntX, cntY, objtbl[cntY][cntX]);
			if (objtbl[cntY][cntX] >= 0)
			{
				this->ObjectChipVector.push_back(pObjChip[cntY][cntX]);
			}
		}
	}
#endif

	//MapCenterPos = pChip[0][0]->GetPos();
	//MapCenterPos.x += CHIP_SIZE * MAP_SIZE_X * 0.5f;
	//MapCenterPos.y -= CHIP_SIZE * MAP_SIZE_Y * 0.5f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Map::~Map()
{
	maptbl.clear();
	ReleaseVector(maptbl);
	objtbl.clear();
	ReleaseVector(objtbl);

	Chip::ReleaseTexture();
	for (auto &MapChip : this->MapChipVector)
	{
		SAFE_DELETE(MapChip);
	}
	MapChipVector.clear();
	ReleaseVector(MapChipVector);

	ObjectChip::ReleaseTexture();
	for (auto &ObjectChip : this->ObjectChipVector)
	{
		SAFE_DELETE(ObjectChip);
	}
	ObjectChipVector.clear();
	ReleaseVector(ObjectChipVector);
}

//=============================================================================
// �X�V
//=============================================================================
void Map::Update()
{
	for (auto &MapChip : this->MapChipVector)
	{
		MapChip->Update();
	}
	for (auto &ObjectChip : this->ObjectChipVector)
	{
		ObjectChip->Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void Map::Draw()
{
	for (auto &MapChip : this->MapChipVector)
	{
		MapChip->Draw();
	}
	for (auto &ObjectChip : this->ObjectChipVector)
	{
		ObjectChip->Draw();
	}
}

//=============================================================================
// �\������Ă���}�b�v�̒��S���W
//=============================================================================
//D3DXVECTOR3 GetMapCenterPos()
//{
//	return MapCenterPos;
//}

void Map::GetMapChipXY(D3DXVECTOR3 Pos, int *MapX, int *MapY)
{
	*MapX = (int)((Pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	*MapY = abs((int)((Pos.y - CHIP_SIZE / 2) / CHIP_SIZE));
}

D3DXVECTOR3 Map::GetMapChipPos(int MapX, int MapY)
{
	return D3DXVECTOR3(CHIP_SIZE * MapX, -(CHIP_SIZE * MapY), 0.0f);
}

int Map::GetMapTbl(int MapX, int MapY)
{
	if (MapX < 0 ||
		MapX >= MAP_SIZE_X ||
		MapY < 0 ||
		MapY >= MAP_SIZE_Y)
	{
		return -1;
	}
	else
	{
		return maptbl.at(MapY).at(MapX);
	}
}

int Map::GetObjTbl(int ObjX, int ObjY)
{
	if (ObjX < 0 ||
		ObjX >= MAP_SIZE_X ||
		ObjY < 0 ||
		ObjY >= MAP_SIZE_Y)
	{
		return -1;
	}
	else
	{
		return objtbl.at(ObjY).at(ObjX);
	}
}