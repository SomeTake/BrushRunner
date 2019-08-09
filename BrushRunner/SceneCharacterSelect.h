//=============================================================================
//
// キャラクターセレクト画面処理 [SceneCharacterSelect.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _SCENECHARACTERSELECT_H_
#define _SCENECHARACTERSELECT_H_

#include "Scene.h"
#include "_2dobj.h"
#include "CursorObj.h"
#include "Player.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneCharacterSelect :
	public Scene
{
private:
	std::vector<_2dobj*> p2dobj;

	CursorObj *pCursor[PLAYER_MAX][CURSOROBJ_MAX];

public:
	SceneCharacterSelect();
	~SceneCharacterSelect();

	void Update(int SceneID);
	void Draw();
};

int *GetSelectCharacter(int no);		// 選択したキャラクターの番号

#endif
