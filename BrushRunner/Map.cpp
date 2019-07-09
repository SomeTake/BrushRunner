//=============================================================================
//
// �}�b�v���� [Map.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Map.h"
#include "Input.h"
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
std::vector<std::vector<int>> Map::maptbl;
std::vector<std::vector<int>> Map::objtbl;

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

	// csv�f�[�^�ǂݍ���
	ReadCsv(MAP_FILE, &this->maptbl);
	ReadCsv(OBJECT_FILE, &this->objtbl);

	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			if (maptbl.at(cntY).at(cntX) >= 0)
			{
				MapChipVector.push_back(new Chip(cntX, cntY, maptbl.at(cntY).at(cntX), eMapChip));
			}

			if (objtbl.at(cntY).at(cntX) >= 0)
			{
				ObjectChipVector.push_back(new Chip(cntX, cntY, objtbl.at(cntY).at(cntX), eObjectChip));
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
	// �}�b�v�e�[�u���N���A
	maptbl.clear();
	ReleaseVector(maptbl);

	// �I�u�W�F�N�g�e�[�u���N���A
	objtbl.clear();
	ReleaseVector(objtbl);

	// �`�b�v�e�N�X�`�������[�X
	Chip::ReleaseTexture();

	// �}�b�v�`�b�v�x�N�g���N���A
	for (auto &MapChip : this->MapChipVector)
	{
		SAFE_DELETE(MapChip);
	}
	MapChipVector.clear();
	ReleaseVector(MapChipVector);

	// �I�u�W�F�N�g�`�b�v�x�N�g���N���A
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

//=============================================================================
// ���݂̍��W���瑫���}�b�v�`�b�v��XY���擾����
//=============================================================================
void Map::GetMapChipXY(D3DXVECTOR3 Pos, int *MapX, int *MapY)
{
	*MapX = (int)((Pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	*MapY = abs((int)((Pos.y - CHIP_SIZE / 2) / CHIP_SIZE));
}

//=============================================================================
// �}�b�v�`�b�v�̍��W���擾����
//=============================================================================
D3DXVECTOR3 Map::GetMapChipPos(int x, int y, int PosType)
{
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 2D��Y���W��3D��Y���W�̕����͋t
	switch (PosType)
	{
	case eLeftUp:
		Pos = D3DXVECTOR3(x * CHIP_SIZE - CHIP_SIZE / 2, -(y * CHIP_SIZE - CHIP_SIZE / 2), 0.0f);
		break;
	case eRightUp:
		Pos = D3DXVECTOR3(x * CHIP_SIZE + CHIP_SIZE / 2, -(y * CHIP_SIZE - CHIP_SIZE / 2), 0.0f);
		break;
	case eCenter:
		Pos = D3DXVECTOR3(x * CHIP_SIZE, -(y * CHIP_SIZE), 0.0f);
		break;
	case eCenterUp:
		Pos = D3DXVECTOR3(x * CHIP_SIZE, -(y * CHIP_SIZE - CHIP_SIZE / 2), 0.0f);
		break;
	default:
		break;
	}

	return Pos;
}

//=============================================================================
// �}�b�v�`�b�vXY����}�b�v�e�[�u���̐��l���擾����
//=============================================================================
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

//=============================================================================
// ���W����}�b�v�e�[�u���̐��l���擾����
//=============================================================================
// ������
// ������	���FCenterChip
// ������
int Map::GetMapTbl(D3DXVECTOR3 Pos, int ChipDirection)
{
	int x = 0;
	int y = 0;

	GetMapChipXY(Pos, &x, &y);

	switch (ChipDirection)
	{
	case eCenterUp:
		// �����̏�̃`�b�v
		y--;
		break;
	default:
		break;
	}

	return GetMapTbl(x, y);
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
