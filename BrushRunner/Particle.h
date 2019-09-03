//=============================================================================
//
// �p�[�e�B�N�� [Particle.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Billboard.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Particle :
	public Billboard
{
private:
	bool						use;			// �g�p���Ă��邩�ǂ���
	int							texNo;			// �g�p����e�N�X�`���ԍ�
	int							moveCnt;		// ����������^�C�~���O
	HRESULT MakeVertex();

public:
	Particle();
	~Particle();

	void Update();
	void Draw();

	bool GetUse() { return use; };

};

#endif
