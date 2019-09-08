//=============================================================================
//
// パーティクルマネージャ [ParticleManager.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "Confetti.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ParticleManager
{
private:
	static std::vector<Confetti*> confettiVector;	// 紙吹雪

	void Check();
	void Debug();

public:
	ParticleManager();
	~ParticleManager();

	void Update();
	void Draw();

	static std::vector<Confetti*> *GetConfettiVector();
};

#endif
