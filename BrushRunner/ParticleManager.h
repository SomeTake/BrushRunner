//=============================================================================
//
// �p�[�e�B�N���}�l�[�W�� [ParticleManager.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "Confetti.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ParticleManager
{
private:
	static std::vector<Confetti*> confettiVector;	// ������

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
