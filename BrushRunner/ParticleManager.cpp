//=============================================================================
//
// パーティクルマネージャ [ParticleManager.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ParticleManager.h"
#include "DebugWindow.h"

//=============================================================================
// コンストラクタ
//=============================================================================
ParticleManager::ParticleManager()
{
	// メモリ確保
	particle.reserve(500);
}

//=============================================================================
// デストラクタ
//=============================================================================
ParticleManager::~ParticleManager()
{
	// ベクターの削除
	for (auto &Particle : particle)
	{
		SAFE_DELETE(Particle);
	}
	particle.clear();
	ReleaseVector(particle);
}

//=============================================================================
// 更新
//=============================================================================
void ParticleManager::Update()
{
	// 一定時間ごとにパーティクルを発生させる
	particle.push_back(new Particle());

	// 使用確認
	Check();

	for (auto &Particle : particle)
	{
		Particle->Update();
	}

#ifndef _DEBUG_
	Debug();
#endif
}

//=============================================================================
// 描画
//=============================================================================
void ParticleManager::Draw()
{
	for (auto &Particle : particle)
	{
		Particle->Draw();
	}
}

//=============================================================================
// 使用確認
//=============================================================================
void ParticleManager::Check()
{
	for (auto Particle = particle.begin(); Particle != particle.end();)
	{
		if ((*Particle)->GetUse() == false)
		{
			SAFE_DELETE((*Particle));
			Particle = particle.erase(Particle);
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
	for (auto &p : particle)
	{
		count++;
	}

	BeginDebugWindow("Particle");

	DebugText("Count:%d", count);

	EndDebugWindow("Particle");
}