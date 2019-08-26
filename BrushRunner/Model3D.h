//=============================================================================
//
// 3Dモデル読み込み用抽象クラス [Model3D.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MODEL3D_H_
#define _MODEL3D_H_

#include "D3DXAnimation.h"
//*****************************************************************************
// クラス定義
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
