//=============================================================================
//
// �� [Digit.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _DIGIT_H_
#define _DIGIT_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DIGIT_MAX		(6)		// �\������
#define TEXTURE_DIGIT	("data/TEXTURE/Digit.png")
#define DIGIT_DIVIDE_X	(10)
#define DIGIT_DIVIDE_Y	(1)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Digit :
	public _2dobj
{
protected:
	static LPDIRECT3DTEXTURE9 D3DTexture;	// �e�N�X�`���̃|�C���^
	DWORD time;								// ���̌��ɕ\�����鐔���i0-9 or 0-5�j

	HRESULT MakeVertex();
	void SetTexture();

public:
	Digit(int digit);
	~Digit();

	void Update()override;
	void Update(DWORD time);
	void Draw()override;
};

#endif
