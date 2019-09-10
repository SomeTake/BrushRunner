//=============================================================================
//
// �p�[�e�B�N���}�l�[�W�� [ParticleManager.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "Confetti.h"
#include "UIParticle.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ParticleManager
{
private:
	std::vector<Confetti*> confettiVector;		// ������
	static std::vector<UIParticle*> uiparticleVector;	// UI�p�p�[�e�B�N��
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
