//=============================================================================
//
// タイトル画面処理 [SceneTitle.h]
// Author : HAL東京 GP12B332-11 81156 小松将吉
//
//=============================================================================
#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "Scene.h"
class _2dobj;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneTitle :
	public Scene
{
private:
	std::vector<_2dobj*> p2dObj;	// 2Dオブジェクト用のポインタ
	bool IsOption;					// 選択肢フラグ

public:
	SceneTitle();
	~SceneTitle();

	void Update(int SceneID);
	void Draw();
};

#endif
