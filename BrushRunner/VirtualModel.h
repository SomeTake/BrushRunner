//=============================================================================
//
// 基底用仮想モデルクラス[VirtualModel.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _VIRTUALMODEL_H_
#define _VIRTUALMODEL_H_

#include "Model3D.h"
//*****************************************************************************
// クラス定義
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
