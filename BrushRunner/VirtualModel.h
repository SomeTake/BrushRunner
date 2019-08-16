//=============================================================================
//
// ���p���z���f���N���X[VirtualModel.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _VIRTUALMODEL_H_
#define _VIRTUALMODEL_H_

#include "Model3D.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class VirtualModel
{
protected:
	Model3D *model;

public:
	VirtualModel();
	virtual ~VirtualModel();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	Model3D *GetModel() { return model; };

};

#endif
