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
#include "SelectLogo.h"
#include "Player.h"
#include "Cursor.h"
#include "CharSelectFrame.h"
#include "CharSelectUI.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SceneCharacterSelect : public Scene, public _2dobj
{
private:
	std::vector<Cursor*> cursor;
	std::vector<CharSelectFrame*>	SelectFrame;
	std::vector<CharSelectUI*>		charSelectUI;
	SelectLogo* selectLogo;
	bool SelectOver[PLAYER_MAX];			// キャラクターを選択終わったフラグ
	static bool AIUse[PLAYER_MAX];					// AIの使用フラグ
	static int SelectedCharacter[PLAYER_MAX];		// 選択したキャラクターモデルの番号

	void MakeVertex(void);

public:
	SceneCharacterSelect();
	~SceneCharacterSelect();

	void Update(int SceneID);
	void Draw();
	bool CheckSelect(int PlayerNo);

	static int GetSelectCharacter(int PlayerNo);		// 選択したキャラクターの番号
	static bool GetAIUse(int PlayerNo);
};

#endif
