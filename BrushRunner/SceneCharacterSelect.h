//=============================================================================
//
// �L�����N�^�[�Z���N�g��ʏ��� [SceneCharacterSelect.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
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
// �N���X��`
//*****************************************************************************
class SceneCharacterSelect : public Scene, public _2dobj
{
private:
	std::vector<Cursor*> cursor;
	std::vector<CharSelectFrame*>	SelectFrame;
	std::vector<CharSelectUI*>		charSelectUI;
	SelectLogo* selectLogo;
	bool SelectOver[PLAYER_MAX];			// �L�����N�^�[��I���I������t���O
	static bool AIUse[PLAYER_MAX];					// AI�̎g�p�t���O
	static int SelectedCharacter[PLAYER_MAX];		// �I�������L�����N�^�[���f���̔ԍ�

	void MakeVertex(void);

public:
	SceneCharacterSelect();
	~SceneCharacterSelect();

	void Update(int SceneID);
	void Draw();
	bool CheckSelect(int PlayerNo);

	static int GetSelectCharacter(int PlayerNo);		// �I�������L�����N�^�[�̔ԍ�
	static bool GetAIUse(int PlayerNo);
};

#endif
