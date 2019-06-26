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

using namespace std;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3 MapCenterPos;	// �\������Ă���}�b�v�̒��S���W

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Map::Map()
{
	// csv�f�[�^�ǂݍ���
	ReadCsv(MAP_FILE);

	for (int cntY = 0; cntY < MAP_SIZE_Y; cntY++)
	{
		for (int cntX = 0; cntX < MAP_SIZE_X; cntX++)
		{
			pChip[cntY][cntX] = new Chip(cntX, cntY, maptbl[cntY][cntX]);
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
			if (maptbl[cntY][cntX] >= 0)
			{
				pChip[cntY][cntX]->Draw();
			}
		}
	}
}

//=============================================================================
// CSV�t�@�C���̓ǂݍ���
//=============================================================================
void Map::ReadCsv(const char *data)
{
	ifstream stream(data);		// �}�b�v�̓ǂݍ��ݐ�

	int row = 0;
	int col;
	while (getline(stream, line))
	{
		col = 0;
		// delim����؂蕶���Ƃ��Đ؂蕪���Aint�ɕϊ�����maptbl[][]�Ɋi�[����
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;)
		{
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			maptbl[row][col++] = stoi(token);
		}
		++row;
	}
}

//=============================================================================
// �\������Ă���}�b�v�̒��S���W
//=============================================================================
D3DXVECTOR3 GetMapCenterPos()
{
	return MapCenterPos;
}