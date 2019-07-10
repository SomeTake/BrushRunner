//=============================================================================
//
// �}�b�v���� [Map.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "Chip.h"

class QUADTREE;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define MAP_SIZE_X		(500)								// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(50)								// �}�b�v�̏c�̖���
#define START_POS		D3DXVECTOR3(50.0f, 0.0f, 0.0f)		// �X�^�[�g�n�_
#define GOAL_POS		D3DXVECTOR3(9500.0f, 0.0f, 0.0f)	// �S�[���n�_

// �}�b�v�`�b�v���W���擾�̎��
enum e_ChipPosType
{
	eLeftUp,	// �}�b�v�`�b�v�̍���̍��W 
	eRightUp,	// �}�b�v�`�b�v�̉E��̍��W 
	eCenter,	// �}�b�v�`�b�v�̒��S�̍��W 
	eCenterUp,	// �}�b�v�`�b�v�̒����̏�̍��W
};

// �t�B�[���h�I�u�W�F�N�g�̎��
enum e_ChipType
{
	eObjSpdup,		// �X�s�[�h�A�b�v
	eObjSpddown,	// �X�s�[�h�_�E��
	eObjNuma,		// ���i�X�s�[�h�_�E�����W�����v�̓_�E���j
	eObjJump,		// �����W�����v
	eObjDrain,		// �C���N�Q�[�W����
	eObjHeal,		// �C���N�Q�[�W����
	eObjItem,		// �A�C�e���擾
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

	void PaintCollider(QUADTREE *Quadtree, int NodeID);

	static void SetObjTbl(int ObjX, int ObjY, int texnum);

};

//D3DXVECTOR3 GetMapCenterPos();					// �\������Ă���}�b�v�̒��S���W

#endif
