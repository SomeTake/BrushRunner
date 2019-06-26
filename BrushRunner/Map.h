//=============================================================================
//
// �}�b�v���� [Map.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "Chip.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_FILE		("data/MAP/data.csv")				// �ǂݍ��ރ}�b�v�f�[�^
#define MAP_SIZE_X		(100)								// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(10)								// �}�b�v�̏c�̖���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Map
{
private:
	string					line;								// ��������ꎞ�I�ɕۑ�
	int						maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// �}�b�v�p�̔z��
	const string			delim = ",";						// �f�[�^��؂�p�̕���

	Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];						// �`�b�v�̃|�C���^

public:
	Map();
	~Map();

	void Update();
	void Draw();

	void ReadCsv(const char *data);		// CSV�t�@�C���̓ǂݍ���

	int GetMapTbl(int _MapX, int _MapY) { return maptbl[_MapX][_MapY]; };
};

D3DXVECTOR3 GetMapCenterPos();			// �\������Ă���}�b�v�̒��S���W

#endif
