//=============================================================================
//
// �S�[���n�_�\�� [GoalFlag.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _GOALFLAG_H_
#define _GOALFLAG_H_

#include "Object3D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class GoalFlag :
	public Object3D
{
public:
	GoalFlag();
	~GoalFlag();

	void Update()override;
	void Draw()override;

	HRESULT MakeVertex();
};

#endif
