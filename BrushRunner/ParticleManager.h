//=============================================================================
//
// パーティクルマネージャ [ParticleManager.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "Confetti.h"
#include "UIParticle.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class ParticleManager
{
private:
	std::vector<Confetti*> confettiVector;		// 紙吹雪
	static std::vector<UIParticle*> uiparticleVector;	// UI用パーティクル
	void Check();
	void Debug();

public:
	ParticleManager();
	~ParticleManager();

	void Update();
	void Draw();

	void SetConfetti();
	static std::vector<UIParticle*> *GetUIParticle();
};

#endif
