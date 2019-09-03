//=============================================================================
//
// チュートリアルシーン [SceneTutorial.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENETUTORIAL_H_
#define _SCENETUTORIAL_H_

#include "Scene.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneTutorial :
	public Scene
{
public:
	SceneTutorial();
	~SceneTutorial();

	void Update(int SceneID);
	void Draw();
};

#endif
