#ifndef _RESULTDIGIT_H_
#define _RESULTDIGIT_H_

#include "Digit.h"
class ResultDigit :
	public Digit
{
private:
	static LPDIRECT3DTEXTURE9 D3DTexture; // �e�N�X�`���̃|�C���^

	int rank;

public:
	ResultDigit(DWORD _time, int _digit, int _rank);
	~ResultDigit();

	void Update()override;
};

#endif
