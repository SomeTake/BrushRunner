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
#include "Timer.h"
#include "Model3D.h"
#include "Object3D.h"
#include "ParticleManager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneResult :
	public Scene
{
private:
	std::vector<_2dobj*>		Obj2d;		// 2Dオブジェクト用のポインタ
	std::vector<Model3D*>		anim;		// 3Dモデル用のポインタ（Xファイル）
	std::vector < Object3D*>	Obj3d;		// 3Dポリゴン用のポインタ
	ParticleManager*			particleManager;	// パーティクルマネージャ

	void Debug();

public:
	SceneResult();
	~SceneResult();

	void Update(int SceneID);
	void Draw();
};

#endif
