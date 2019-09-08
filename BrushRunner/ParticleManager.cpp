//=============================================================================
//
// �p�[�e�B�N���}�l�[�W�� [ParticleManager.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ParticleManager.h"
#include "DebugWindow.h"

std::vector<UIParticle*> ParticleManager::uiparticleVector;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ParticleManager::ParticleManager()
{
	// �������m��
	confettiVector.reserve(500);
	uiparticleVector.reserve(500);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ParticleManager::~ParticleManager()
{
	// �x�N�^�[�̍폜
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
// �X�V
//=============================================================================
void ParticleManager::Update()
{
	// �g�p�m�F
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
// �`��
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
// �g�p�m�F
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
// �f�o�b�O
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
// ������̃Z�b�g
//=============================================================================
void ParticleManager::SetConfetti()
{
	confettiVector.push_back(new Confetti());
}

//=============================================================================
// UI�p�p�[�e�B�N���x�N�^�[�̃Q�b�g
//=============================================================================
std::vector<UIParticle*> *ParticleManager::GetUIParticle()
{
	return &uiparticleVector;
}