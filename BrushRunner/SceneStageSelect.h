//=============================================================================
//
// �X�e�[�W�Z���N�g [SceneStageSelect.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SCENESTAGESELECT_H_
#define _SCENESTAGESELECT_H_

#include "Scene.h"

#include "_2dobj.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneStageSelect :
	public Scene
{
private:
	std::vector<_2dobj*> obj;

public:
	SceneStageSelect();
	~SceneStageSelect();

	void Update(int SceneID)override;
	void Draw()override;
};

#endif
