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
enum TitleUINum
{
	TitleLogo,
	TitleRunner,
	TitleMenu,
	UIMax,										// UI表示の最大数
};
class _2dobj;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneTitle :
	public Scene
{
private:
	_2dobj *p2dObj[UIMax];		// 2Dオブジェクト用のポインタ
	bool IsOption;				// 選択肢フラグ

public:
	SceneTitle();
	~SceneTitle();

	void Update(int SceneID);
	void Draw();
};

#endif
