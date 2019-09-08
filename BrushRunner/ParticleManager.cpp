//=============================================================================
//
// パーティクルマネージャ [ParticleManager.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ParticleManager.h"
#include "DebugWindow.h"

std::vector<UIParticle*> ParticleManager::uiparticleVector;

//=============================================================================
// コンストラクタ
//=============================================================================
ParticleManager::ParticleManager()
{
	// メモリ確保
	confettiVector.reserve(500);
	uiparticleVector.reserve(500);
}

//=============================================================================
// デストラクタ
//=============================================================================
ParticleManager::~ParticleManager()
{
	// ベクターの削除
	for (auto &Particle : confettiVector)
	{
		SAFE_DELETE(Particle);
	}
	confettiVector.clear();
	ReleaseVector(confettiVector);

	for (auto &Particle : uiparticleVector)
	{
		SAFE_DELETE(Particle);
	}
	uiparticleVector.clear();
	ReleaseVector(uiparticleVector);
}

//=============================================================================
// 更新
//=============================================================================
void ParticleManager::Update()
{
	// 使用確認
	Check();

	for (auto &Confetti : confettiVector)
	{
		Confetti->Update();
	}

	for (auto &Particle : uiparticleVector)
	{
		Particle->Update();
	}

#if _DEBUG_
	//Debug();
#endif
}

//=============================================================================
// 描画
//=============================================================================
void ParticleManager::Draw()
{
	for (auto &Confetti : confettiVector)
	{
		Confetti->Draw();
	}

	for (auto &Particle : uiparticleVector)
	{
		Particle->Draw();
	}
}

//=============================================================================
// 使用確認
//=============================================================================
void ParticleManager::Check()
{
	for (auto Confetti = confettiVector.begin(); Confetti != confettiVector.end();)
	{
		if ((*Confetti)->GetUse() == false)
		{
			SAFE_DELETE((*Confetti));
			Confetti = confettiVector.erase(Confetti);
		}
		else
		{
			Confetti++;
		}
	}

	for (auto Particle = uiparticleVector.begin(); Particle != uiparticleVector.end();)
	{
		if ((*Particle)->GetUse() == false)
		{
			SAFE_DELETE((*Particle));
			Particle = uiparticleVector.erase(Particle);
		}
		else
		{
			Particle++;
		}
	}

}

//=============================================================================
// デバッグ
//=============================================================================
void ParticleManager::Debug()
{
	int count = 0;
	for (auto &p : confettiVector)
	{
		count++;
	}

	BeginDebugWindow("Particle");

	DebugText("Count:%d", count);

	EndDebugWindow("Particle");
}

//=============================================================================
// 紙吹雪のセット
//=============================================================================
void ParticleManager::SetConfetti()
{
	confettiVector.push_back(new Confetti());
}

//=============================================================================
// UI用パーティクルベクターのゲット
//=============================================================================
std::vector<UIParticle*> *ParticleManager::GetUIParticle()
{
	return &uiparticleVector;
}