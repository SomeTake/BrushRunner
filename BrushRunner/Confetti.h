//=============================================================================
//
// ������ [Confetti.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _CONFETTI_H_
#define _CONFETTI_H_

#include "Billboard.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Confetti :
	public Billboard
{
private:
	bool						use;			// �g�p���Ă��邩�ǂ���
	int							texNo;			// �g�p����e�N�X�`���ԍ�
	int							moveCnt;		// ����������^�C�~���O
	HRESULT MakeVertex();

public:
	Confetti();
	~Confetti();

	void Update();
	void Draw();

	bool GetUse() { return use; };

};

#endif
