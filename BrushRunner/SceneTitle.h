//=============================================================================
//
// タイトル画面処理 [SceneTitle.h]
// Author : HAL東京 GP12B332-11 81156 小松将吉
//
//=============================================================================
#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "Scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneTitle :
	public Scene
{
public:
	SceneTitle();
	~SceneTitle();

	void Update(int SceneID);
	void Draw();
};

#endif
