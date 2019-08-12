//=============================================================================
//
// �p�[�e�B�N���}�l�[�W�� [ParticleManager.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ParticleManager.h"
#include "DebugWindow.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ParticleManager::ParticleManager()
{
	// �������m��
	particle.reserve(500);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ParticleManager::~ParticleManager()
{
	// �x�N�^�[�̍폜
	for (auto &Particle : particle)
	{
		SAFE_DELETE(Particle);
	}
	particle.clear();
	ReleaseVector(particle);
}

//=============================================================================
// �X�V
//=============================================================================
void ParticleManager::Update()
{
	// ��莞�Ԃ��ƂɃp�[�e�B�N���𔭐�������
	particle.push_back(new Particle());

	// �g�p�m�F
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
// �`��
//=============================================================================
void ParticleManager::Draw()
{
	for (auto &Particle : particle)
	{
		Particle->Draw();
	}
}

//=============================================================================
// �g�p�m�F
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
// �f�o�b�O
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