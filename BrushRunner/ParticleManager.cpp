//=============================================================================
//
// パーティクルマネージャ [ParticleManager.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ParticleManager.h"
#include "DebugWindow.h"

std::vector<Confetti*> ParticleManager::confettiVector;	// 紙吹雪

//=============================================================================
// コンストラクタ
//=============================================================================
ParticleManager::ParticleManager()
{
	// メモリ確保
	confettiVector.reserve(500);
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
// ゲッター
//=============================================================================
std::vector<Confetti*>*ParticleManager::GetConfettiVector()
{
	return &confettiVector;
}