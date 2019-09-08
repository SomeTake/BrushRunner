//=============================================================================
//
// �p�[�e�B�N���}�l�[�W�� [ParticleManager.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ParticleManager.h"
#include "DebugWindow.h"

std::vector<Confetti*> ParticleManager::confettiVector;	// ������

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ParticleManager::ParticleManager()
{
	// �������m��
	confettiVector.reserve(500);
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
// �Q�b�^�[
//=============================================================================
std::vector<Confetti*>*ParticleManager::GetConfettiVector()
{
	return &confettiVector;
}