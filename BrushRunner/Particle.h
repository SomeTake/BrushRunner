//=============================================================================
//
// パーティクル [Particle.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Billboard.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Particle :
	public Billboard
{
private:
	bool						use;			// 使用しているかどうか
	int							texNo;			// 使用するテクスチャ番号
	int							moveCnt;		// 動きをつけるタイミング
	HRESULT MakeVertex();

public:
	Particle();
	~Particle();

	void Update();
	void Draw();

	bool GetUse() { return use; };

};

#endif
