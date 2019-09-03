//=============================================================================
//
// パーティクルマネージャ [ParticleManager.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "Particle.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ParticleManager
{
private:
	std::vector<Particle*> particle;

	void Check();
	void Debug();

public:
	ParticleManager();
	~ParticleManager();

	void Update();
	void Draw();
};

#endif
