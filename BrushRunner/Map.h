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

class QUADTREE;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_FILE		("data/MAP/map_ground.csv")				// �ǂݍ��ރ}�b�v�f�[�^
#define OBJECT_FILE		("data/MAP/map_object.csv")
#define MAP_SIZE_X		(500)								// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(50)								// �}�b�v�̏c�̖���
#define START_POS		D3DXVECTOR3(50.0f, 0.0f, 0.0f)		// �X�^�[�g�n�_
#define GOAL_POS		D3DXVECTOR3(9500.0f, 0.0f, 0.0f)	// �S�[���n�_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Map
{
private:
	int maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// �}�b�v�p�̔z��
	int	*pMaptbl[MAP_SIZE_Y];				// �z��̃|�C���^
	Chip *pChip[MAP_SIZE_Y][MAP_SIZE_X];	// �`�b�v�̃|�C���^

	int objtbl[MAP_SIZE_Y][MAP_SIZE_X];		// �t�B�[���h�I�u�W�F�N�g�p�̔z��
	int *pObjtbl[MAP_SIZE_Y];
	ObjectChip *pObjChip[MAP_SIZE_Y][MAP_SIZE_X];

public:
	Map();
	~Map();

	void Update();
	void Draw();

	void PaintCollider(QUADTREE *Quadtree, int NodeID);

	int GetMapTbl(int _MapX, int _MapY) { return maptbl[-_MapY][_MapX]; };
	int GetObjTbl(int _ObjX, int _ObjY) { return objtbl[_ObjY][_ObjX]; };
};

D3DXVECTOR3 GetMapCenterPos();					// �\������Ă���}�b�v�̒��S���W

#endif
