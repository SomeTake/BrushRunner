//=============================================================================
//
// �G�t�F�N�g�Ǘ��}�l�[�W�� [EffectManager.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_

#include "Effect.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EffectManager
{
private:
	void Check();

public:
	EffectManager();
	~EffectManager();

	void Update();
	void Draw();

};

std::vector<Effect*> *GetEffectVector();

#endif
