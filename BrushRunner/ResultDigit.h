//=============================================================================
//
// ���U���g��ʂł̌� [ResultDigit.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _RESULTDIGIT_H_
#define _RESULTDIGIT_H_

#include "Digit.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultDigit :
	public Digit
{
private:
	static LPDIRECT3DTEXTURE9 D3DTexture; // �e�N�X�`���̃|�C���^

	int rank;

public:
	ResultDigit(DWORD _time, int _digit, int _rank); // time = ���̌��̐����Adigit = �����ڂ��Arank = ����
	~ResultDigit();

	void Update()override;
	void Draw()override;
};

#endif
