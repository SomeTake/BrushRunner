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
	public D3DXANIMATION
{
private:
	float animSpd;		// アニメーションの再生スピード

	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)override;
	void CreateAnimSet()override;

public:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scl;
	D3DXVECTOR3 rot;

	Model3D(const char* tag, const char* path);
	~Model3D();

	void Update();
	void Draw();

	float GetAnimSpd() { return this->animSpd; };
	void SetAnimSpd(float animSpd) { this->animSpd = animSpd; };
};

#endif
