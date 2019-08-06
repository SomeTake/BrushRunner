//=============================================================================
//
// 表彰台[Podium.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PODIUM_H_
#define _PODIUM_H_

#include "D3DXAnimation.h"
class Podium :
	public D3DXANIMATION
{
private:
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)

	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet();

public:
	Podium();
	~Podium();

	void Update();
	void Draw();
};

#endif
