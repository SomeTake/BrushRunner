//=============================================================================
//
// エフェクト管理マネージャ [EffectManager.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_

#include "Effect.h"
#include "Effect3D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EffectManager
{
private:
	void Check();

public:
	EffectManager();
	~EffectManager();

	void Update();
	void Draw();

};

std::vector<Effect*> *GetEffectVector();
std::vector<Effect3D*> *GetEffect3DVector();

#endif
