//=============================================================================
//
// �y�C���g�O���[�v�N���X[PaintGroup.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PAINTGROUP_H_
#define _PAINTGROUP_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
typedef struct
{
	std::vector<D3DXVECTOR3> PaintPath;
	int Onwer;
	int Count;
	bool Use;
	bool PaintOver;
}GroupStruct;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PaintGroup
{
private:
	std::vector<GroupStruct> GroupVector;

public:
	// �R���X�g���N�^
	PaintGroup();
	// �f�X�g���N�^
	~PaintGroup();

	void Update();
	void Start(int Owner);
	void Insert(D3DXVECTOR3 Pos, int Owner);
	void End(int Owner);

	bool GetEnemyPaint(GroupStruct** GroupPtr, int PlayerNo);
};

#endif
