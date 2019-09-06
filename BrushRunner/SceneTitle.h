//=============================================================================
//
// �^�C�g����ʏ��� [SceneTitle.h]
// Author : HAL���� GP12B332-11 81156 �������g
//
//=============================================================================
#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "Scene.h"
class _2dobj;
class Map;
class Object3D;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneTitle :
	public Scene
{
private:
	std::vector<_2dobj*> p2dObj;	// 2D�I�u�W�F�N�g�p�̃|�C���^
	std::vector <Object3D*>		object3d;	// 3D�I�u�W�F�N�g
	Map* map;						// �}�b�v
	bool IsOption;					// �I�����t���O

public:
	SceneTitle();
	~SceneTitle();

	void Update(int SceneID);
	void Draw();
};

#endif
