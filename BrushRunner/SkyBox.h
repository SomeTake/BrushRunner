// Author : HAL“Œ‹ GP11B341-17 80277 õ’J•u
//
//=============================================================================
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "Object3D.h"

//*****************************************************************************
// ƒNƒ‰ƒX’è‹`
//*****************************************************************************

class SkyBox :
	public Object3D
{
public:
	SkyBox();
	~SkyBox();

	void Update();
	void Draw();
	HRESULT MakeVertex();

};

#endif
