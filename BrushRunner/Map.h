//=============================================================================
//
// �}�b�v���� [Map.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "Chip.h"
#include "ObjectChip.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_SIZE_X		(500)								// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(50)								// �}�b�v�̏c�̖���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Map
{
private:
	std::vector<std::vector<int>>	maptbl;
	std::vector<Chip*>				MapChipVector;
	//int maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// �}�b�v�p�̔z��
	//int	*pMaptbl[MAP_SIZE_Y];				// �z��̃|�C���^
	//Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];	// �`�b�v�̃|�C���^
	//std::vector<Chip*>				NoEmptyMapChip;

	std::vector<std::vector<int>>	objtbl;
	std::vector<ObjectChip*>		ObjectChipVector;
	//int objtbl[MAP_SIZE_Y][MAP_SIZE_X];		// �t�B�[���h�I�u�W�F�N�g�p�̔z��
	//int *pObjtbl[MAP_SIZE_Y];
	//ObjectChip *pObjChip[MAP_SIZE_Y][MAP_SIZE_X];
	//std::vector<ObjectChip *> NoEmptyObjectChip;

public:
	Map();
	~Map();

	void Update();
	void Draw();

	int GetMapTbl(int MapX, int MapY);
	int GetObjTbl(int ObjX, int ObjY);
	static void GetMapChipXY(D3DXVECTOR3 Pos, int *MapX, int *MapY);
	static D3DXVECTOR3 GetMapChipPos(int MapX, int MapY);
};

//D3DXVECTOR3 GetMapCenterPos();					// �\������Ă���}�b�v�̒��S���W

#endif
