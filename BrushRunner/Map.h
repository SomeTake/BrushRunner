//=============================================================================
//
// �}�b�v���� [Map.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "Chip.h"
#include "Quadtree.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define MAP_SIZE_X		(500)								// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(50)								// �}�b�v�̏c�̖���
#define START_POS		D3DXVECTOR3(50.0f, 0.0f, 0.0f)		// �X�^�[�g�n�_
#define GOAL_POS		D3DXVECTOR3(9800.0f, 0.0f, 0.0f)	// �S�[���n�_

// �}�b�v�`�b�v���W���擾�̎��
enum e_ChipPosType
{
	eLeftUp,	// �}�b�v�`�b�v�̍���̍��W 
	eLeftCenter,// �}�b�v�`�b�v�̍������̍��W 
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
	static std::vector<std::vector<int>>	maptbl;				// csv�f�[�^��ۑ�����2�����x�N�g��
	std::vector<Chip*>						MapChipVector;		// �}�b�v�`�b�v�̃x�N�g��

	static std::vector<std::vector<int>>	objtbl;				// csv�f�[�^��ۑ�����2�����x�N�g��
	std::vector<Chip*>						ObjectChipVector;	// �I�u�W�F�N�g�`�b�v�̃x�N�g��

public:
	Map();
	~Map();

	void Update();
	void Draw();

	void PaintCollider(QUADTREE *Quadtree, int NodeID);

	static int GetMapTbl(int MapX, int MapY);
	static int GetMapTbl(D3DXVECTOR3 Pos, int ChipDirection);
	static void GetMapChipXY(D3DXVECTOR3 Pos, int *MapX, int *MapY);
	static D3DXVECTOR3 GetMapChipPos(int x, int y, int PosType);
	static int GetObjTbl(int ObjX, int ObjY);
	static int GetObjTbl(D3DXVECTOR3 Pos, int ChipDirection);
	std::vector<Chip*> GetObjectChip() { return ObjectChipVector; };

	static void SetObjTbl(int ObjX, int ObjY, int texnum);
};

#endif
