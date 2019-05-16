//=============================================================================
//
// �o�g����ʃt���[���\������ [Inklinered.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _INKLINERED_H_
#define _INKLINERED_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_INKLINERED	_T("data/texture/inkline.red.png")			// �t���[���p�摜
#define INKLINERED_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define INKLINERED_POS1      D3DXVECTOR3(0.0f, 0.0f, 0.0f)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Inklinered :
	public _2dobj {
public:
	Inklinered(D3DXVECTOR3 _pos);
	~Inklinered();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif