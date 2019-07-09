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
#define MAP_SIZE_X		(500)								// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(50)								// �}�b�v�̏c�̖���

// �}�b�v�`�b�v���W���擾�̎��
enum e_ChipPosType
{
	eLeftUp,	// �}�b�v�`�b�v�̍���̍��W 
	eRightUp,	// �}�b�v�`�b�v�̉E��̍��W 
	eCenter,	// �}�b�v�`�b�v�̒��S�̍��W 
	eCenterUp,	// �}�b�v�`�b�v�̒����̏�̍��W
};


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Map
{
private:
	static std::vector<std::vector<int>>	maptbl;
	std::vector<Chip*>						MapChipVector;
	//int maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// �}�b�v�p�̔z��
	//int	*pMaptbl[MAP_SIZE_Y];				// �z��̃|�C���^
	//Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];	// �`�b�v�̃|�C���^
	//std::vector<Chip*>				NoEmptyMapChip;

	static std::vector<std::vector<int>>	objtbl;
	std::vector<Chip*>						ObjectChipVector;
	//int objtbl[MAP_SIZE_Y][MAP_SIZE_X];		// �t�B�[���h�I�u�W�F�N�g�p�̔z��
	//int *pObjtbl[MAP_SIZE_Y];
	//ObjectChip *pObjChip[MAP_SIZE_Y][MAP_SIZE_X];
	//std::vector<ObjectChip *> NoEmptyObjectChip;

public:
	Map();
	~Map();

	void Update();
	void Draw();

	static int GetMapTbl(int MapX, int MapY);
	static int GetMapTbl(D3DXVECTOR3 Pos, int ChipDirection);
	static int GetObjTbl(int ObjX, int ObjY);
	static void GetMapChipXY(D3DXVECTOR3 Pos, int *MapX, int *MapY);
	static D3DXVECTOR3 GetMapChipPos(int x, int y, int PosType);
};

//D3DXVECTOR3 GetMapCenterPos();					// �\������Ă���}�b�v�̒��S���W

#endif
