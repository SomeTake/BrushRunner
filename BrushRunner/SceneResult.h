//=============================================================================
//
// ���U���g��ʏ��� [SceneGame.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SCENERESULT_H_
#define _SCENERESULT_H_

#include "Scene.h"
#include "_2dobj.h"
#include "Timer.h"
#include "D3DXAnimation.h"
#include "Object3D.h"
#include "ParticleManager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneResult :
	public Scene
{
private:
	std::vector<_2dobj*>		Obj2d;		// 2D�I�u�W�F�N�g�p�̃|�C���^
	std::vector<D3DXANIMATION*> anim;		// 3D���f���p�̃|�C���^�iX�t�@�C���j
	std::vector < Object3D*>	Obj3d;		// 3D�|���S���p�̃|�C���^
	ParticleManager*			particleManager;	// �p�[�e�B�N���}�l�[�W��

	void Debug();

public:
	SceneResult();
	~SceneResult();

	void Update(int SceneID);
	void Draw();
};

#endif
