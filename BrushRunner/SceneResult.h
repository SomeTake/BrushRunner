//=============================================================================
//
// リザルト画面処理 [SceneGame.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENERESULT_H_
#define _SCENERESULT_H_

#include "Scene.h"
#include "_2dobj.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneResult :
	public Scene
{
private:
	std::vector<_2dobj*>	p2dObj;	// 2Dオブジェクト用のポインタ
	ResultData*				data;	// ゲームシーンの結果を取得するポインタ

	void Debug();

public:
	SceneResult();
	~SceneResult();

	void Update(int SceneID);
	void Draw();
};

#endif
