//=============================================================================
//
// 3D���f���ǂݍ��ݗp���ۃN���X [Model3D.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MODEL3D_H_
#define _MODEL3D_H_

#include "D3DXAnimation.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Model3D :
	public D3DXAnimation
{
protected:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scl;
	D3DXVECTOR3 rot;
	float		animSpd;

	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)override;

public:
	Model3D(const char* tag);
	virtual ~Model3D();

	virtual void Update();
	virtual void Draw();

	D3DXVECTOR3 GetPos() { return pos; };
	void SetAnimSpd(float animSpd) { this->animSpd = animSpd; };
};

#endif
