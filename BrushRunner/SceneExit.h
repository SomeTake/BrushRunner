//=============================================================================
//
// Q[IΉ [SceneExit.h]
// Author : HAL GP12B332-19 80277 υJu
//
//=============================================================================
#ifndef _SCENEEXIT_H_
#define _SCENEEXIT_H_

#include "Scene.h"
//*****************************************************************************
// NXθ`
//*****************************************************************************
class SceneExit :
	public Scene
{
public:
	SceneExit();
	~SceneExit();

	void Update(int SceneID)override;
	void Draw()override;
};

#endif
