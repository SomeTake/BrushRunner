//=============================================================================
//
// �^�C�g����ʏ��� [SceneTitle.h]
// Author : HAL���� GP12B332-11 81156 �������g
//
//=============================================================================
#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "Scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum TitleUINum
{
	TitleLogo,
	TitleRunner,
	TitleMenu,
	TitleCursor,
	UIMax,										// UI�\���̍ő吔
};
class _2dobj;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneTitle :
	public Scene
{
private:
	_2dobj *p2dObj[UIMax];		// 2D�I�u�W�F�N�g�p�̃|�C���^
	bool IsOption;				// �I�����t���O

public:
	SceneTitle();
	~SceneTitle();

	void Update(int SceneID);
	void Draw();
};

#endif
